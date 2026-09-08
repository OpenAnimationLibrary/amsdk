#include "ImportCore.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <tuple>

namespace amglb {
double Dot(Vec3 a, Vec3 b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
Vec3 Cross(Vec3 a, Vec3 b) { return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x}; }
double Length(Vec3 a) { return std::sqrt(Dot(a,a)); }
bool Finite(Vec3 a) { return std::isfinite(a.x)&&std::isfinite(a.y)&&std::isfinite(a.z); }
Vec3 Unit(Vec3 a) { const double n=Length(a); if (!(n>1e-15)||!std::isfinite(n)) throw Error("Degenerate face or normal."); return a*(1/n); }
std::string SafeName(const char* text, const std::string& fallback) {
    std::string s;
    if (text) for (const unsigned char* p=reinterpret_cast<const unsigned char*>(text);*p&&s.size()<100;++p)
        s+=(*p>=32&&*p<127&&*p!='<'&&*p!='>'&&*p!='/'&&*p!='\\')?static_cast<char>(*p):'_';
    return s.empty()?fallback:s;
}
namespace {
using Edge=std::pair<uint32_t,uint32_t>;
Edge Key(uint32_t a,uint32_t b) { return std::minmax(a,b); }
struct Use { size_t face; uint32_t corner; };
using Edges=std::map<Edge,std::vector<Use>>;
Edges BuildEdges(const Part& p) {
    Edges edges;
    std::set<std::vector<uint32_t>> unique;
    for(size_t i=0;i<p.faces.size();++i) {
        const auto& f=p.faces[i];
        if(f.count<3||f.count>4) throw Error("Invalid face size.");
        std::vector<uint32_t> key(f.vertex.begin(),f.vertex.begin()+f.count);
        for(auto v:key) if(v>=p.vertices.size()) throw Error("Invalid vertex index.");
        std::sort(key.begin(),key.end());
        if(std::adjacent_find(key.begin(),key.end())!=key.end()) throw Error("Face has coincident corners.");
        if(!unique.insert(key).second) throw Error("Duplicate overlapping faces. Clean the source mesh first.");
        for(uint32_t k=0;k<f.count;++k) edges[Key(f.vertex[k],f.vertex[(k+1)%f.count])].push_back({i,k});
    }
    for(const auto& item:edges) {
        const auto& u=item.second;
        if(u.size()>2) throw Error("Non-manifold edge shared by more than two faces. Split or repair the source mesh.");
        if(u.size()==2) {
            const Face& a=p.faces[u[0].face]; const Face& b=p.faces[u[1].face];
            if(a.vertex[u[0].corner]==b.vertex[u[1].corner]) throw Error("Inconsistent face winding. Recalculate source normals first.");
        }
    }
    // An edge-manifold mesh can still have a bow-tie vertex. Require one fan.
    std::vector<std::vector<size_t>> incident(p.vertices.size());
    for(size_t i=0;i<p.faces.size();++i)
        for(uint32_t k=0;k<p.faces[i].count;++k)incident[p.faces[i].vertex[k]].push_back(i);
    for(uint32_t v=0;v<incident.size();++v)if(!incident[v].empty()){
        std::set<size_t> reached;std::vector<size_t> pending{incident[v][0]};
        while(!pending.empty()){
            const auto i=pending.back();pending.pop_back();if(!reached.insert(i).second)continue;
            const auto& f=p.faces[i];
            for(uint32_t k=0;k<f.count;++k)if(f.vertex[k]==v){
                for(auto n:{f.vertex[(k+1)%f.count],f.vertex[(k+f.count-1)%f.count]})
                    for(const auto& use:edges.at(Key(v,n)))if(use.face!=i)pending.push_back(use.face);
            }
        }
        if(reached.size()!=incident[v].size())throw Error("Non-manifold vertex has disconnected face fans. Split or repair the source mesh.");
    }
    return edges;
}
struct Components {
    std::vector<size_t> parent;
    explicit Components(size_t n):parent(n){std::iota(parent.begin(),parent.end(),0);}
    size_t Root(size_t n){while(n!=parent[n]){parent[n]=parent[parent[n]];n=parent[n];}return n;}
    void Join(size_t a,size_t b){a=Root(a);b=Root(b);if(a!=b)parent[b]=a;}
};
bool SameCorner(const Face& a,uint32_t ai,const Face& b,uint32_t bi) {
    if(a.hasUV!=b.hasUV||a.hasNormals!=b.hasNormals)return false;
    if(a.hasUV) for(int k=0;k<2;++k)if(std::abs(a.uv[ai][k]-b.uv[bi][k])>1e-7)return false;
    if(a.hasNormals && Dot(a.normals[ai],b.normals[bi])<.99999)return false;
    return true;
}
bool Pair(const Part& p,const Use& ua,const Use& ub,Face& out,double& score) {
    const auto& a=p.faces[ua.face]; const auto& b=p.faces[ub.face];
    if(a.count!=3||b.count!=3||a.material!=b.material)return false;
    if(!SameCorner(a,ua.corner,b,(ub.corner+1)%3)||!SameCorner(a,(ua.corner+1)%3,b,ub.corner))return false;
    const Vec3 an=Unit(Cross(p.vertices[a.vertex[1]]-p.vertices[a.vertex[0]],p.vertices[a.vertex[2]]-p.vertices[a.vertex[0]]));
    const Vec3 bn=Unit(Cross(p.vertices[b.vertex[1]]-p.vertices[b.vertex[0]],p.vertices[b.vertex[2]]-p.vertices[b.vertex[0]]));
    if(Dot(an,bn)<.9999985)return false;
    // Shared edge a0->a1 is replaced by the other three sides of the pair.
    out=a;out.count=4;
    out.vertex={a.vertex[(ua.corner+1)%3],a.vertex[(ua.corner+2)%3],a.vertex[ua.corner],b.vertex[(ub.corner+2)%3]};
    const Vec3 normal=Unit(an+bn);
    double minEdge=std::numeric_limits<double>::max(),maxEdge=0;
    score=0;
    for(uint32_t k=0;k<4;++k) {
        const Vec3 v=p.vertices[out.vertex[k]],before=p.vertices[out.vertex[(k+3)%4]]-v,after=p.vertices[out.vertex[(k+1)%4]]-v;
        const double len=Length(after);
        minEdge=std::min(minEdge,len);maxEdge=std::max(maxEdge,len);
        if(Dot(Cross(after,before),normal)<=1e-14)return false;
        const double angle=std::acos(std::clamp(Dot(Unit(before),Unit(after)),-1.,1.));
        if(angle<.174533||angle>2.967059)return false;
        score+=std::abs(angle-1.5707963267948966);
    }
    if(minEdge<1e-10||maxEdge/minEdge>25)return false;
    for(uint32_t k=1;k<4;++k)
        if(std::abs(Dot(p.vertices[out.vertex[k]]-p.vertices[out.vertex[0]],normal))>std::max(1e-9,maxEdge*1e-6))return false;
    score+=.05*maxEdge/minEdge;
    return true;
}
uint32_t Append(Part& p,Vec3 v) {
    if(p.vertices.size()>=MaxVertices)throw Error("Quad conversion exceeds the vertex limit.");
    const auto id=static_cast<uint32_t>(p.vertices.size());p.vertices.push_back(v);return id;
}
void ConvertPart(Part& p,Plan& plan) {
    const auto edges=BuildEdges(p);
    Components components(p.faces.size());
    struct Candidate{double score;size_t a,b;Face face;};
    std::vector<Candidate> candidates;
    for(const auto& e:edges)if(e.second.size()==2){
        const auto a=e.second[0],b=e.second[1];components.Join(a.face,b.face);
        Face q;double score;
        if(Pair(p,a,b,q,score))candidates.push_back({score,a.face,b.face,q});
    }
    std::sort(candidates.begin(),candidates.end(),[](const auto&a,const auto&b){return std::tie(a.score,a.a,a.b)<std::tie(b.score,b.a,b.b);});
    std::vector<bool> used(p.faces.size(),false);
    std::vector<std::pair<size_t,Face>> mixed;
    for(const auto& c:candidates)if(!used[c.a]&&!used[c.b]){
        used[c.a]=used[c.b]=true;mixed.push_back({components.Root(c.a),c.face});++plan.pairedQuads;
    }
    std::set<size_t> split;
    for(size_t i=0;i<p.faces.size();++i)if(!used[i]){
        mixed.push_back({components.Root(i),p.faces[i]});if(p.faces[i].count==3)split.insert(components.Root(i));
    }
    size_t required=0;
    for(const auto& item:mixed)required+=split.count(item.first)?item.second.count:1;
    if(required>MaxOutputQuads-plan.outputQuads)throw Error("Quad conversion exceeds 100,000 patches. Simplify the source mesh first.");
    plan.subdividedComponents+=split.size();
    std::map<Edge,uint32_t> midpoints;
    std::vector<Face> result;result.reserve(required);
    // Uniform subdivision of a mixed connected component makes every face a
    // quad and shares edge midpoints. It introduces no T-junctions or smoothing.
    for(const auto& item:mixed){
        const auto& f=item.second;
        if(!split.count(item.first)){result.push_back(f);continue;}
        Vec3 center{};std::array<uint32_t,4> mid{};
        for(uint32_t k=0;k<f.count;++k){
            const auto a=f.vertex[k],b=f.vertex[(k+1)%f.count];center=center+p.vertices[a];
            const auto key=Key(a,b);auto it=midpoints.find(key);
            if(it==midpoints.end())it=midpoints.emplace(key,Append(p,(p.vertices[a]+p.vertices[b])*.5)).first;
            mid[k]=it->second;
        }
        const auto c=Append(p,center*(1./f.count));
        for(uint32_t k=0;k<f.count;++k){Face q;q.count=4;q.material=f.material;q.vertex={f.vertex[k],mid[k],c,mid[(k+f.count-1)%f.count]};result.push_back(q);}
    }
    p.faces=std::move(result);
    // Remove vertices left unused by reconstruction; A:M should receive no orphans.
    std::vector<uint32_t> remap(p.vertices.size(),UINT32_MAX);std::vector<Vec3> compact;
    for(auto& f:p.faces)for(auto& v:f.vertex){if(remap[v]==UINT32_MAX){remap[v]=static_cast<uint32_t>(compact.size());compact.push_back(p.vertices[v]);}v=remap[v];}
    p.vertices=std::move(compact);
    BuildEdges(p);
    plan.outputQuads+=p.faces.size();
}
}
void ValidatePlan(Plan& p) {
    if(p.parts.empty()||p.parts.size()>MaxParts||p.materials.empty())throw Error("No supported mesh parts, or too many parts.");
    p.vertices=0;p.outputQuads=0;
    p.minimum={1e300,1e300,1e300};p.maximum={-1e300,-1e300,-1e300};
    for(const auto& part:p.parts){
        BuildEdges(part);
        for(const auto& v:part.vertices){
            if(!Finite(v)||std::max({std::abs(v.x),std::abs(v.y),std::abs(v.z)})>10000)throw Error("Invalid or excessively large coordinates.");
            p.minimum={std::min(v.x,p.minimum.x),std::min(v.y,p.minimum.y),std::min(v.z,p.minimum.z)};
            p.maximum={std::max(v.x,p.maximum.x),std::max(v.y,p.maximum.y),std::max(v.z,p.maximum.z)};
        }
        for(const auto& f:part.faces){
            if(f.count!=4||f.material>=p.materials.size())throw Error("Conversion did not produce valid material-assigned quads.");
            const auto a=part.vertices[f.vertex[0]],b=part.vertices[f.vertex[1]],c=part.vertices[f.vertex[2]],d=part.vertices[f.vertex[3]];
            const auto n1=Cross(b-a,c-a),n2=Cross(c-a,d-a);
            if(Length(n1)<1e-14||Length(n2)<1e-14||Dot(n1,n2)<=0)throw Error("Conversion produced a folded or degenerate quad.");
        }
        p.vertices+=part.vertices.size();p.outputQuads+=part.faces.size();
    }
    if(p.vertices>MaxVertices||p.outputQuads>MaxOutputQuads)throw Error("Converted mesh exceeds import limits.");
}
void ConvertToQuads(Plan& p){p.pairedQuads=0;p.subdividedComponents=0;p.outputQuads=0;for(auto& part:p.parts)ConvertPart(part,p);ValidatePlan(p);}
}
