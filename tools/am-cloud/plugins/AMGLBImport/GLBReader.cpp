#include "ImportCore.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#ifdef _MSC_VER
#pragma warning(push, 0)
// cgltf is pinned portable C99; its bounded libc calls are reviewed in
// third_party/README.md. Keep this compatibility exception inside the vendor.
#pragma warning(disable: 4996)
#endif
#define CGLTF_IMPLEMENTATION
#define CGLTF_VALIDATE_ENABLE_ASSERTS 0
#include "third_party/cgltf.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace amglb {
namespace {
uint32_t U32(const uint8_t* p){return uint32_t(p[0])|(uint32_t(p[1])<<8)|(uint32_t(p[2])<<16)|(uint32_t(p[3])<<24);}
void CheckContainer(const std::vector<uint8_t>& b){
    if(b.size()<28||b.size()>MaxFileBytes||U32(b.data())!=0x46546c67||U32(b.data()+4)!=2||U32(b.data()+8)!=b.size())throw Error("Select a complete GLB 2.0 file, at most 32 MiB.");
    const size_t jsonSize=U32(b.data()+12);
    if(U32(b.data()+16)!=0x4e4f534a||jsonSize>b.size()-20||jsonSize%4)throw Error("Invalid GLB JSON chunk.");
    int depth=0;bool quoted=false,escape=false;
    for(size_t i=20;i<20+jsonSize;++i){const char c=static_cast<char>(b[i]);
        if(quoted){if(escape)escape=false;else if(c=='\\')escape=true;else if(c=='"')quoted=false;}
        else if(c=='"')quoted=true;
        else if(c=='{'||c=='['){if(++depth>64)throw Error("GLB JSON nesting is too deep.");}
        else if(c=='}'||c==']'){if(--depth<0)throw Error("Invalid GLB JSON nesting.");}
    }
    if(depth||quoted)throw Error("Incomplete GLB JSON.");
    size_t offset=20+jsonSize;bool bin=false;
    while(offset<b.size()){
        if(b.size()-offset<8)throw Error("Truncated GLB chunk.");
        const size_t n=U32(b.data()+offset);const uint32_t type=U32(b.data()+offset+4);
        if(n>b.size()-offset-8||n%4)throw Error("Invalid GLB chunk length.");
        if(type==0x004e4942){if(bin)throw Error("Duplicate GLB binary chunk.");bin=true;}
        else throw Error("This importer supports standard GLB JSON and BIN chunks only.");
        offset+=8+n;
    }
    if(!bin)throw Error("The GLB has no embedded geometry buffer.");
}
struct Budget{size_t used=0;};
struct alignas(std::max_align_t) Allocation{size_t size;};
void* Allocate(void* context,cgltf_size size){
    auto& b=*static_cast<Budget*>(context);constexpr size_t limit=128*1024*1024;
    if(size>limit-b.used)return nullptr;
    auto* p=static_cast<Allocation*>(std::malloc(sizeof(Allocation)+size));if(!p)return nullptr;
    p->size=size;b.used+=size;return p+1;
}
void Free(void* context,void* ptr){if(!ptr)return;auto* p=static_cast<Allocation*>(ptr)-1;static_cast<Budget*>(context)->used-=p->size;std::free(p);}
void Span(size_t offset,size_t stride,size_t count,size_t element,size_t size){
    if(!count||count>MaxVertices||!element||stride<element||offset>size||element>size-offset||count-1>(size-offset-element)/stride)throw Error("An accessor exceeds its buffer or supported size.");
}
void CheckBuffers(cgltf_data& d){
    if(d.buffers_count!=1||d.buffers[0].uri||d.buffers[0].size>d.bin_size)throw Error("Geometry must be embedded in this GLB. External buffers are unsupported.");
    for(size_t i=0;i<d.buffer_views_count;++i){const auto& v=d.buffer_views[i];
        if(!v.buffer||v.offset>v.buffer->size||v.size>v.buffer->size-v.offset)throw Error("Buffer view exceeds the embedded buffer.");
        if(v.has_meshopt_compression)throw Error("Meshopt compression is unsupported. Export uncompressed GLB.");
    }
    for(size_t i=0;i<d.accessors_count;++i){const auto& a=d.accessors[i];const size_t element=cgltf_calc_size(a.type,a.component_type),component=cgltf_component_size(a.component_type);
        if(!a.count||a.count>MaxVertices||!element||!component)throw Error("Invalid or oversized accessor.");
        if(a.buffer_view){
            Span(a.offset,a.stride,a.count,element,a.buffer_view->size);
            if((a.offset+a.buffer_view->offset)%component||a.stride%component)throw Error("Misaligned accessor data.");
        }
        if(a.is_sparse){const auto& s=a.sparse;const size_t c=cgltf_component_size(s.indices_component_type);
            if(!s.indices_buffer_view||!s.values_buffer_view||s.count>a.count||!c||
               (s.indices_component_type!=cgltf_component_type_r_8u&&s.indices_component_type!=cgltf_component_type_r_16u&&s.indices_component_type!=cgltf_component_type_r_32u))throw Error("Invalid sparse accessor.");
            Span(s.indices_byte_offset,c,s.count,c,s.indices_buffer_view->size);
            Span(s.values_byte_offset,element,s.count,element,s.values_buffer_view->size);
            if((s.indices_byte_offset+s.indices_buffer_view->offset)%c||(s.values_byte_offset+s.values_buffer_view->offset)%component)throw Error("Misaligned sparse data.");
        }
    }
}
std::vector<float> Unpack(const cgltf_accessor* a,cgltf_type type,size_t count){
    if(!a||a->type!=type||a->count!=count)throw Error("Missing or mismatched vertex attributes.");
    std::vector<float> result(count*cgltf_num_components(type));
    if(cgltf_accessor_unpack_floats(a,result.data(),result.size())!=result.size())throw Error("Cannot decode vertex attributes.");
    for(float f:result)if(!std::isfinite(f))throw Error("Non-finite vertex attributes.");
    return result;
}
const cgltf_accessor* Attribute(const cgltf_primitive& p,cgltf_attribute_type kind){
    const cgltf_accessor* result=nullptr;
    for(size_t i=0;i<p.attributes_count;++i)if(p.attributes[i].type==kind&&p.attributes[i].index==0){
        if(result)throw Error("Duplicate vertex attribute.");
        result=p.attributes[i].data;
    }
    return result;
}
Vec3 Transform(const float* m,Vec3 p){return {m[0]*p.x+m[4]*p.y+m[8]*p.z+m[12],m[1]*p.x+m[5]*p.y+m[9]*p.z+m[13],m[2]*p.x+m[6]*p.y+m[10]*p.z+m[14]};}
double Determinant(const float* m){return Dot({m[0],m[1],m[2]},Cross({m[4],m[5],m[6]},{m[8],m[9],m[10]}));}
Vec3 TransformNormal(const float* m,Vec3 p,double determinant){
    const Vec3 a{m[0],m[1],m[2]},b{m[4],m[5],m[6]},c{m[8],m[9],m[10]};
    return Unit((Cross(b,c)*p.x+Cross(c,a)*p.y+Cross(a,b)*p.z)*(1/determinant));
}
void AddNote(Plan& p,const std::string& s){if(std::find(p.notes.begin(),p.notes.end(),s)==p.notes.end())p.notes.push_back(s);}
void Mesh(Plan& plan,const cgltf_node& node,const cgltf_data& data){
    if(node.skin||node.mesh->weights_count)throw Error("Skinned and morphed models need a static export for this version.");
    if(node.has_mesh_gpu_instancing)throw Error("GPU instancing is unsupported. Export ordinary mesh nodes.");
    float m[16];cgltf_node_transform_world(&node,m);
    for(float f:m)if(!std::isfinite(f))throw Error("Invalid node transform.");
    if(std::abs(m[3])+std::abs(m[7])+std::abs(m[11])>1e-7||std::abs(m[15]-1)>1e-7)throw Error("Non-affine node transform.");
    const double determinant=Determinant(m);if(std::abs(determinant)<1e-12)throw Error("A mesh has a singular or extremely small transform.");
    Part part;part.name=SafeName(node.name,SafeName(node.mesh->name,"Part"))+"_"+std::to_string(plan.parts.size()+1);
    std::map<std::tuple<double,double,double>,uint32_t> positions;
    for(size_t pi=0;pi<node.mesh->primitives_count;++pi){const auto& p=node.mesh->primitives[pi];
        if(p.has_draco_mesh_compression)throw Error("Draco compression is unsupported. Export uncompressed GLB.");
        if(p.targets_count)throw Error("Morph targets are unsupported. Export the desired static shape.");
        if(p.type!=cgltf_primitive_type_triangles&&p.type!=cgltf_primitive_type_triangle_strip&&p.type!=cgltf_primitive_type_triangle_fan)throw Error("This version imports triangle surfaces only; remove point/line primitives.");
        const auto* position=Attribute(p,cgltf_attribute_type_position);if(!position||position->component_type!=cgltf_component_type_r_32f)throw Error("Mesh positions must use standard float vectors.");
        const size_t count=position->count;
        const auto pos=Unpack(position,cgltf_type_vec3,count);
        const auto* na=Attribute(p,cgltf_attribute_type_normal);const auto* ta=Attribute(p,cgltf_attribute_type_texcoord);
        const auto normals=na?Unpack(na,cgltf_type_vec3,count):std::vector<float>{};
        const auto uv=ta?Unpack(ta,cgltf_type_vec2,count):std::vector<float>{};
        if(Attribute(p,cgltf_attribute_type_color))AddNote(plan,"Vertex colors are omitted; material base colors are imported.");
        std::vector<uint32_t> map;map.reserve(count);
        for(size_t k=0;k<count;++k){const Vec3 v=Transform(m,{pos[k*3],pos[k*3+1],pos[k*3+2]});
            if(!Finite(v)||std::max({std::abs(v.x),std::abs(v.y),std::abs(v.z)})>10000)throw Error("Mesh coordinates are invalid or too large.");
            const auto key=std::make_tuple(v.x,v.y,v.z);auto it=positions.find(key);
            if(it==positions.end()){
                if(part.vertices.size()>=MaxVertices)throw Error("Too many vertices.");
                it=positions.emplace(key,static_cast<uint32_t>(part.vertices.size())).first;part.vertices.push_back(v);
            }map.push_back(it->second);
        }
        std::vector<uint32_t> indices;
        if(p.indices){
            if(p.indices->is_sparse)throw Error("Sparse index buffers are unsupported. Export ordinary indices.");
            indices.resize(p.indices->count);
            if(cgltf_accessor_unpack_indices(p.indices,indices.data(),sizeof(uint32_t),indices.size())!=indices.size())throw Error("Cannot read triangle indices.");
        }else {indices.reserve(count);for(size_t k=0;k<count;++k)indices.push_back(static_cast<uint32_t>(k));}
        if(indices.size()<3||(p.type==cgltf_primitive_type_triangles&&indices.size()%3))throw Error("Incomplete triangle list.");
        for(auto i:indices)if(i>=count)throw Error("Triangle index is outside the vertex array.");
        const uint32_t mat=p.material?static_cast<uint32_t>(p.material-data.materials):static_cast<uint32_t>(data.materials_count);
        const size_t triangles=p.type==cgltf_primitive_type_triangles?indices.size()/3:indices.size()-2;
        if(triangles>MaxInputTriangles-plan.inputTriangles)throw Error("This version imports at most 50,000 source triangles.");
        plan.inputTriangles+=triangles;
        for(size_t k=0;k<triangles;++k){
            std::array<uint32_t,3> ids;
            if(p.type==cgltf_primitive_type_triangles)ids={indices[3*k],indices[3*k+1],indices[3*k+2]};
            else if(p.type==cgltf_primitive_type_triangle_strip)ids=k%2?std::array<uint32_t,3>{indices[k+1],indices[k],indices[k+2]}:std::array<uint32_t,3>{indices[k],indices[k+1],indices[k+2]};
            else ids={indices[0],indices[k+1],indices[k+2]};
            if(determinant<0)std::swap(ids[1],ids[2]);
            Face f;f.material=mat;f.hasNormals=na!=nullptr;f.hasUV=ta!=nullptr;
            for(size_t j=0;j<3;++j){const size_t i=ids[j];f.vertex[j]=map[i];
                if(na)f.normals[j]=TransformNormal(m,{normals[3*i],normals[3*i+1],normals[3*i+2]},determinant);
                if(ta)f.uv[j]={uv[2*i],uv[2*i+1]};
            }
            if(Length(Cross(part.vertices[f.vertex[1]]-part.vertices[f.vertex[0]],part.vertices[f.vertex[2]]-part.vertices[f.vertex[0]]))<1e-14){
                AddNote(plan,"Degenerate triangles were skipped.");continue;
            }
            part.faces.push_back(f);
        }
    }
    if(!part.faces.empty()){if(plan.parts.size()>=MaxParts)throw Error("Too many mesh nodes (maximum 256).");plan.parts.push_back(std::move(part));}
}
}
Plan ReadGLB(const std::vector<uint8_t>& bytes){
    CheckContainer(bytes);Budget budget;cgltf_options options{};
    options.type=cgltf_file_type_glb;options.memory={Allocate,Free,&budget};
    cgltf_data* parsed=nullptr;
    const auto status=cgltf_parse(&options,bytes.data(),bytes.size(),&parsed);
    if(status!=cgltf_result_success)throw Error("GLB parsing failed (invalid data or memory limit).");
    std::unique_ptr<cgltf_data,decltype(&cgltf_free)> owner(parsed,cgltf_free);auto& d=*parsed;
    if(!d.asset.version||std::strcmp(d.asset.version,"2.0")||(d.asset.min_version&&std::strcmp(d.asset.min_version,"2.0")))throw Error("Only glTF 2.0 assets are supported.");
    if(d.extensions_required_count)throw Error("Required glTF extension is unsupported: "+SafeName(d.extensions_required[0],"unknown"));
    if(d.nodes_count>4096||d.meshes_count>256||d.materials_count>1024)throw Error("Scene exceeds this importer's object limits.");
    size_t primitives=0;
    for(size_t i=0;i<d.meshes_count;++i)primitives+=d.meshes[i].primitives_count;
    if(primitives>4096||d.accessors_count>8192||d.buffer_views_count>8192)throw Error("Scene exceeds the primitive or accessor limits.");
    CheckBuffers(d);
    if(cgltf_load_buffers(&options,&d,nullptr)!=cgltf_result_success||cgltf_validate(&d)!=cgltf_result_success)throw Error("GLB buffer, scene, or accessor validation failed.");
    // Check sparse ordering, not just the maximum index.
    for(size_t i=0;i<d.accessors_count;++i)if(d.accessors[i].is_sparse){const auto& a=d.accessors[i];const auto& s=a.sparse;
        const auto* p=static_cast<const uint8_t*>(s.indices_buffer_view->buffer->data)+s.indices_buffer_view->offset+s.indices_byte_offset;
        const size_t width=cgltf_component_size(s.indices_component_type);uint32_t previous=0;
        for(size_t k=0;k<s.count;++k){uint32_t value=0;for(size_t j=0;j<width;++j)value|=uint32_t(p[k*width+j])<<(8*j);
            if(value>=a.count||(k&&value<=previous))throw Error("Sparse accessor indices must be ordered and unique.");
            previous=value;
        }
    }
    Plan plan;
    for(size_t i=0;i<d.materials_count;++i){const auto& src=d.materials[i];Material m;m.name=SafeName(src.name,"Material_"+std::to_string(i+1));
        if(src.has_pbr_metallic_roughness){const auto& p=src.pbr_metallic_roughness;
            for(size_t k=0;k<4;++k)m.color[k]=p.base_color_factor[k];
            m.metallic=p.metallic_factor;m.roughness=p.roughness_factor;
        }
        for(double f:m.color)if(!std::isfinite(f)||f<0||f>1)throw Error("Invalid material color.");
        if(!std::isfinite(m.metallic)||!std::isfinite(m.roughness)||m.metallic<0||m.metallic>1||m.roughness<0||m.roughness>1)throw Error("Invalid material factors.");
        if(src.alpha_mode!=cgltf_alpha_mode_opaque)AddNote(plan,"Transparency is approximated using the base color alpha; alpha-cutout textures are omitted.");
        else m.color[3]=1;
        if(src.double_sided)AddNote(plan,"Two-sided material rendering requires checking in A:M.");
        if(src.extensions_count)AddNote(plan,"Optional material extensions are omitted; core base color and surface factors are used.");
        plan.materials.push_back(m);
    }
    Material fallback;fallback.name="Default";plan.materials.push_back(fallback);
    if(d.textures_count)AddNote(plan,"Textures and decals are not imported in v0.1; material base colors are used.");
    if(d.animations_count)AddNote(plan,"Animation is omitted; the default node transforms are imported.");
    if(d.cameras_count||d.lights_count)AddNote(plan,"Cameras and lights are omitted.");
    const cgltf_scene* scene=d.scene?d.scene:(d.scenes_count?&d.scenes[0]:nullptr);
    if(!d.scene&&d.scenes_count>1)AddNote(plan,"No default scene is specified; the first scene is imported.");
    std::vector<std::pair<const cgltf_node*,size_t>> pending;
    if(scene)for(size_t i=0;i<scene->nodes_count;++i)pending.push_back({scene->nodes[i],0});
    else for(size_t i=0;i<d.nodes_count;++i)if(!d.nodes[i].parent)pending.push_back({&d.nodes[i],0});
    std::set<const cgltf_node*> visited;
    while(!pending.empty()){const auto item=pending.back();pending.pop_back();const auto* node=item.first;
        if(item.second>64||!visited.insert(node).second)throw Error("Invalid or excessively deep scene graph.");
        if(node->mesh)Mesh(plan,*node,d);
        for(size_t i=node->children_count;i>0;--i)pending.push_back({node->children[i-1],item.second+1});
    }
    if(plan.parts.empty())throw Error("No triangle mesh is present in the selected scene.");
    return plan;
}
}
