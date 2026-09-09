#include "ImportCore.h"
#include "QuadMatching.h"
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
Edges BuildEdges(const Part& p,bool checkFans=true) {
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
    if(!checkFans)return edges;
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
    // Allow gentle curvature (up to 30 degrees) while retaining sharp seams.
    const double alignment=Dot(an,bn);
    if(alignment<.8660254037844386)return false;
    // Shared edge a0->a1 is replaced by the other three sides of the pair.
    out=a;out.count=4;
    out.vertex={a.vertex[(ua.corner+1)%3],a.vertex[(ua.corner+2)%3],a.vertex[ua.corner],b.vertex[(ub.corner+2)%3]};
    for(uint32_t k=0;k<3;++k){const auto source=(ua.corner+1+k)%3;out.uv[k]=a.uv[source];out.normals[k]=a.normals[source];}
    out.uv[3]=b.uv[(ub.corner+2)%3];out.normals[3]=b.normals[(ub.corner+2)%3];
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
        if(std::abs(Dot(p.vertices[out.vertex[k]]-p.vertices[out.vertex[0]],normal))>std::max(1e-9,maxEdge*.15))return false;
    score+=.05*maxEdge/minEdge+2*(1-alignment);
    return true;
}
uint32_t Append(Part& p,Vec3 v) {
    if(p.vertices.size()>=MaxVertices)throw LimitError("Quad conversion exceeds the vertex limit.");
    const auto id=static_cast<uint32_t>(p.vertices.size());p.vertices.push_back(v);
    if(!p.seamSource.empty())p.seamSource.push_back(id);
    return id;
}
void InitSources(Part& p){if(p.seamSource.empty()){p.seamSource.resize(p.vertices.size());std::iota(p.seamSource.begin(),p.seamSource.end(),0U);}}
uint32_t CopyVertex(Part& p,uint32_t v){InitSources(p);const auto copy=Append(p,p.vertices[v]);p.seamSource[copy]=p.seamSource[v];return copy;}
void Compact(Part& p){
    std::vector<uint32_t> remap(p.vertices.size(),UINT32_MAX),sources;std::vector<Vec3> compact;
    std::map<uint32_t,uint32_t> first;
    for(auto& f:p.faces)for(uint32_t k=0;k<f.count;++k){auto& v=f.vertex[k];
        if(remap[v]==UINT32_MAX){
            const auto id=static_cast<uint32_t>(compact.size());remap[v]=id;compact.push_back(p.vertices[v]);
            if(!p.seamSource.empty())sources.push_back(first.emplace(p.seamSource[v],id).first->second);
        }
        v=remap[v];
    }
    p.vertices=std::move(compact);p.seamSource=std::move(sources);
}
void DetachFans(Part& p){
    const auto edges=BuildEdges(p,false);Components corners(p.faces.size()*4);
    for(const auto& e:edges)if(e.second.size()==2){const auto a=e.second[0],b=e.second[1];
        corners.Join(4*a.face+a.corner,4*b.face+(b.corner+1)%4);
        corners.Join(4*a.face+(a.corner+1)%4,4*b.face+b.corner);
    }
    std::map<std::pair<uint32_t,size_t>,uint32_t> ids;std::set<uint32_t> seen;
    for(size_t i=0;i<p.faces.size();++i)for(size_t k=0;k<4;++k){auto& v=p.faces[i].vertex[k];
        const auto key=std::make_pair(v,corners.Root(4*i+k));auto found=ids.find(key);
        if(found==ids.end()){const auto id=seen.insert(v).second?v:CopyVertex(p,v);found=ids.emplace(key,id).first;}
        v=found->second;
    }
}
void KeepHolesOpen(Part& p){
    // A:M discovers small patch loops automatically. Break accidental 3/4/5
    // corner boundary loops using separate attachments, retaining every quad.
    // Isolated quad loops are intentional and are left alone.
    std::set<size_t> isolated;
    for(size_t pass=0;pass<p.faces.size();++pass){
        const auto edges=BuildEdges(p);std::vector<std::vector<uint32_t>> boundary(p.vertices.size());
        std::map<Edge,size_t> owner;std::set<std::vector<uint32_t>> faces;
        for(size_t i=0;i<p.faces.size();++i){auto key=std::vector<uint32_t>(p.faces[i].vertex.begin(),p.faces[i].vertex.end());std::sort(key.begin(),key.end());faces.insert(key);}
        for(const auto& e:edges)if(e.second.size()==1){const auto [a,b]=e.first;boundary[a].push_back(b);boundary[b].push_back(a);owner[e.first]=e.second[0].face;}
        std::vector<bool> visited(p.vertices.size(),false);std::set<size_t> separate;
        for(uint32_t start=0;start<boundary.size();++start)if(!boundary[start].empty()&&!visited[start]){
            std::vector<uint32_t> loop;uint32_t v=start,previous=UINT32_MAX;
            do{
                if(visited[v]||boundary[v].size()!=2)throw Error("Invalid boundary after omitting triangles.");
                visited[v]=true;loop.push_back(v);
                const auto next=boundary[v][0]==previous?boundary[v][1]:boundary[v][0];previous=v;v=next;
            }while(v!=start);
            if(loop.size()>5)continue;
            auto key=loop;std::sort(key.begin(),key.end());if(faces.count(key))continue;
            for(size_t k=0;k<loop.size();++k){const auto face=owner.at(Key(loop[k],loop[(k+1)%loop.size()]));
                if(!isolated.count(face)){separate.insert(face);break;}
            }
        }
        if(separate.empty())return;
        // At most eight full scans. If a pathological hole keeps closing,
        // separate its remaining incident faces in this final bounded pass.
        if(pass==7){for(size_t i=0;i<p.faces.size();++i)if(!isolated.count(i))separate.insert(i);}
        for(auto i:separate){isolated.insert(i);for(auto& v:p.faces[i].vertex)v=CopyVertex(p,v);}
        DetachFans(p);Compact(p);
        if(pass==7)return; // Every remaining face is now an independent quad.
    }
}
struct VertexFan {
    std::vector<size_t> corners, joins;
    bool closed=false;
    bool Fits(const std::vector<bool>& cuts) const {
        if(corners.empty())return true;
        size_t start=0;
        if(closed){
            const auto cut=std::find_if(joins.begin(),joins.end(),[&](size_t e){return cuts[e];});
            if(cut==joins.end())return corners.size()<=4;
            start=(static_cast<size_t>(cut-joins.begin())+1)%corners.size();
        }
        size_t run=0;
        for(size_t i=0;i<corners.size();++i){
            const auto k=(start+i)%corners.size();
            if(++run>3)return false; // A boundary fan has one more edge than faces.
            if(k<joins.size()&&cuts[joins[k]])run=0;
        }
        return true;
    }
};
void SeparateCrowdedJunctions(Part& p,Plan& plan) {
    const auto edges=BuildEdges(p);
    std::vector<Edge> keys;std::map<Edge,size_t> index;
    std::vector<std::vector<size_t>> incident(p.vertices.size());
    std::vector<size_t> degree(p.vertices.size());
    for(const auto& e:edges){
        index.emplace(e.first,keys.size());keys.push_back(e.first);
        ++degree[e.first.first];++degree[e.first.second];
    }
    if(std::none_of(degree.begin(),degree.end(),[](size_t d){return d>4;}))return;
    for(size_t i=0;i<p.faces.size();++i)for(size_t k=0;k<4;++k)incident[p.faces[i].vertex[k]].push_back(4*i+k);
    std::vector<VertexFan> fans(p.vertices.size());
    for(size_t v=0;v<fans.size();++v){
        if(incident[v].empty())continue;
        auto start=incident[v][0];
        for(auto c:incident[v]){
            const auto& f=p.faces[c/4];
            if(edges.at(Key(f.vertex[(c%4+3)%4],static_cast<uint32_t>(v))).size()==1){start=c;break;}
        }
        auto c=start;auto& fan=fans[v];
        do{
            if(fan.corners.size()>=incident[v].size())throw Error("Cannot order a junction fan.");
            fan.corners.push_back(c);
            const auto& f=p.faces[c/4];const auto edge=Key(static_cast<uint32_t>(v),f.vertex[(c%4+1)%4]);
            const auto& uses=edges.at(edge);
            if(uses.size()==1)break;
            fan.joins.push_back(index.at(edge));
            const auto other=uses[0].face==c/4?uses[1]:uses[0];
            c=4*other.face+(other.corner+1)%4;
            if(c==start)fan.closed=true;
        }while(c!=start);
        if(fan.corners.size()!=incident[v].size())throw Error("Junction fan lost a face.");
    }
    std::vector<bool> cuts(keys.size(),false);
    const auto cutEdge=[&](uint32_t a,uint32_t b){const auto key=Key(a,b);if(edges.at(key).size()==2)cuts[index.at(key)]=true;};
    for(size_t v=0;v<fans.size();++v)if(degree[v]>4){
        const auto& fan=fans[v];
        // Subdivision separates old poles by regular midpoints/face centers.
        // A closed seam around each pole bounds propagation; radial seams
        // divide its fan into sectors of at most three faces (four edges).
        for(auto c:fan.corners){const auto& f=p.faces[c/4];const auto k=c%4;
            for(size_t j=1;j<4;++j)if(degree[f.vertex[(k+j)%4]]>4)throw Error("Crowded junctions were not separated by subdivision.");
            cutEdge(f.vertex[(k+1)%4],f.vertex[(k+2)%4]);
            cutEdge(f.vertex[(k+2)%4],f.vertex[(k+3)%4]);
        }
        for(size_t k=2;k<fan.joins.size();k+=3)cuts[fan.joins[k]]=true;
        if(fan.closed)cuts[fan.joins.back()]=true;
    }
    for(const auto& fan:fans)if(!fan.Fits(cuts))throw Error("Cannot bound a seam junction.");
    // Reconnect wherever possible. Prefer removing long seams and preserve
    // ordinary welded regions; this is bounded cleanup, not a minimum-cut claim.
    std::vector<size_t> order;
    for(size_t i=0;i<cuts.size();++i)if(cuts[i])order.push_back(i);
    std::sort(order.begin(),order.end(),[&](size_t a,size_t b){
        const auto length=[&](size_t e){return Length(p.vertices[keys[e].first]-p.vertices[keys[e].second]);};
        const auto al=length(a),bl=length(b);return al==bl?a<b:al>bl;
    });
    size_t budget=1000000;
    for(size_t pass=0;pass<4&&budget;++pass){
        std::vector<std::vector<size_t>> cutAt(fans.size());
        for(auto i:order)if(cuts[i]){cutAt[keys[i].first].push_back(i);cutAt[keys[i].second].push_back(i);}
        std::vector<bool> visited(keys.size(),false);bool changed=false;
        for(auto i:order)if(cuts[i]&&!visited[i]){
            std::vector<size_t> chain{i};visited[i]=true;
            // A single removed edge would leave an invalid seam tip at a
            // regular four-edge vertex. Reconnect whole paths through those
            // vertices together, including closed loops.
            for(auto start:{keys[i].first,keys[i].second}){
                auto v=start;auto previous=i;
                while(degree[v]==4&&fans[v].closed&&cutAt[v].size()==2){
                    const auto next=cutAt[v][0]==previous?cutAt[v][1]:cutAt[v][0];
                    if(visited[next]||!cuts[next])break;
                    chain.push_back(next);visited[next]=true;
                    v=keys[next].first==v?keys[next].second:keys[next].first;previous=next;
                }
            }
            std::set<uint32_t> touched;
            for(auto e:chain){touched.insert(keys[e].first);touched.insert(keys[e].second);}
            size_t cost=0;for(auto v:touched)cost+=fans[v].corners.size();
            if(cost>budget)continue;
            budget-=cost;for(auto e:chain)cuts[e]=false;
            if(std::all_of(touched.begin(),touched.end(),[&](uint32_t v){return fans[v].Fits(cuts);}))changed=true;
            else for(auto e:chain)cuts[e]=true;
        }
        if(!changed)break;
    }
    Components corners(p.faces.size()*4);
    for(size_t i=0;i<keys.size();++i)if(!cuts[i]){
        const auto& uses=edges.at(keys[i]);if(uses.size()!=2)continue;
        const auto a=uses[0],b=uses[1];
        corners.Join(4*a.face+a.corner,4*b.face+(b.corner+1)%4);
        corners.Join(4*a.face+(a.corner+1)%4,4*b.face+b.corner);
    }
    InitSources(p);
    for(size_t v=0;v<incident.size();++v){
        std::map<size_t,uint32_t> copies;
        for(auto c:incident[v]){
            const auto root=corners.Root(c);auto found=copies.find(root);
            if(found==copies.end()){
                auto id=static_cast<uint32_t>(v);
                if(!copies.empty()){id=CopyVertex(p,static_cast<uint32_t>(v));++plan.seamCopies;}
                found=copies.emplace(root,id).first;
            }
            p.faces[c/4].vertex[c%4]=found->second;
        }
    }
    size_t seams=0;
    for(const auto& e:edges)if(e.second.size()==2){
        const auto a=e.second[0],b=e.second[1];
        if(Key(p.faces[a.face].vertex[a.corner],p.faces[a.face].vertex[(a.corner+1)%4])!=
           Key(p.faces[b.face].vertex[b.corner],p.faces[b.face].vertex[(b.corner+1)%4]))++seams;
    }
    if(seams){++plan.seamedParts;plan.seamEdges+=seams;}
}
void ConvertPart(Part& p,Plan& plan,size_t& searchBudget,bool omitUnpaired) {
    const auto edges=BuildEdges(p);
    Components components(p.faces.size());
    std::vector<int> degree(p.vertices.size());
    for(const auto& e:edges){++degree[e.first.first];++degree[e.first.second];}
    std::vector<QuadCandidate> candidates;
    for(const auto& e:edges)if(e.second.size()==2){
        const auto a=e.second[0],b=e.second[1];components.Join(a.face,b.face);
        Face q;double score;
        if(Pair(p,a,b,q,score)){
            const auto n1=Unit(Cross(p.vertices[q.vertex[1]]-p.vertices[q.vertex[0]],p.vertices[q.vertex[2]]-p.vertices[q.vertex[0]]));
            const auto n2=Unit(Cross(p.vertices[q.vertex[2]]-p.vertices[q.vertex[0]],p.vertices[q.vertex[3]]-p.vertices[q.vertex[0]]));
            candidates.push_back({score,a.face,b.face,{e.first.first,e.first.second},q,Dot(n1,n2)<.9999985});
        }
    }
    std::sort(candidates.begin(),candidates.end(),[](const auto&a,const auto&b){return std::tie(a.score,a.a,a.b)<std::tie(b.score,b.a,b.b);});
    std::vector<bool> selected;
    auto best=std::make_pair(std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
    for(uint32_t seed=0;seed<8&&(seed==0||searchBudget);++seed){
        const QuadMatching matching(candidates,p.faces.size(),degree,searchBudget,seed);
        if(matching.CostValue()<best){best=matching.CostValue();selected=matching.Selected();}
        if(best.first==0)break;
    }
    std::vector<bool> used(p.faces.size(),false);
    std::vector<std::pair<size_t,Face>> mixed;
    for(size_t i=0;i<candidates.size();++i)if(selected[i]){
        const auto& c=candidates[i];
        if(used[c.a]||used[c.b])throw Error("Quad matching reused a triangle.");
        used[c.a]=used[c.b]=true;mixed.push_back({components.Root(c.a),c.face});++plan.pairedQuads;
        if(c.curved)++plan.curvedPairs;
        for(auto v:c.diagonal)--degree[v];
    }
    std::set<size_t> split;
    for(size_t i=0;i<p.faces.size();++i)if(!used[i]){
        if(omitUnpaired&&p.faces[i].count==3){++plan.omittedTriangles;continue;}
        mixed.push_back({components.Root(i),p.faces[i]});if(p.faces[i].count==3)split.insert(components.Root(i));
    }
    if(omitUnpaired){
        p.faces.clear();for(const auto& item:mixed)p.faces.push_back(item.second);
        DetachFans(p);Compact(p);
        const auto retained=BuildEdges(p);components=Components(p.faces.size());degree.assign(p.vertices.size(),0);
        for(const auto& e:retained){++degree[e.first.first];++degree[e.first.second];if(e.second.size()==2)components.Join(e.second[0].face,e.second[1].face);}
        mixed.clear();for(size_t i=0;i<p.faces.size();++i)mixed.push_back({components.Root(i),p.faces[i]});
    }
    // Also subdivide crowded all-quad regions so any necessary seam repair is
    // local to a pole neighborhood, separated from neighboring poles.
    for(const auto& item:mixed)for(uint32_t k=0;k<item.second.count;++k)
        if(degree[item.second.vertex[k]]>4)split.insert(item.first);
    size_t required=0;
    for(const auto& item:mixed)required+=split.count(item.first)?item.second.count:1;
    if(required>MaxOutputQuads-plan.outputQuads)throw LimitError("Quad conversion exceeds 100,000 patches. Simplify the source mesh first.");
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
    Compact(p);
    SeparateCrowdedJunctions(p,plan);
    if(omitUnpaired)KeepHolesOpen(p);
    BuildEdges(p);
    plan.outputQuads+=p.faces.size();
}
}
void ValidateSource(const Plan& p){
    if(p.parts.empty()||p.parts.size()>MaxParts||p.materials.empty())throw Error("No supported mesh parts, or too many parts.");
    for(const auto& part:p.parts){
        BuildEdges(part);
        for(const auto& v:part.vertices)if(!Finite(v))throw Error("Invalid source coordinates.");
        for(const auto& f:part.faces)if(f.count!=3||f.material>=p.materials.size())throw Error("Expected source triangles with valid materials.");
    }
}
void ValidatePlan(Plan& p) {
    if(p.parts.empty()||p.parts.size()>MaxParts||p.materials.empty())throw Error("No supported mesh parts, or too many parts.");
    p.vertices=0;p.outputQuads=0;
    p.seamEdges=0;p.seamCopies=0;p.seamedParts=0;
    p.minimum={1e300,1e300,1e300};p.maximum={-1e300,-1e300,-1e300};
    for(const auto& part:p.parts){
        if(!part.seamSource.empty()){
            if(part.seamSource.size()!=part.vertices.size())throw Error("Incomplete seam vertex provenance.");
            for(size_t i=0;i<part.vertices.size();++i){
                const auto source=part.seamSource[i];
                if(source>=part.vertices.size()||part.seamSource[source]!=source)throw Error("Invalid seam vertex provenance.");
                const auto a=part.vertices[i],b=part.vertices[source];
                if(a.x!=b.x||a.y!=b.y||a.z!=b.z)throw Error("Seam copies changed position.");
            }
        }
        const auto edges=BuildEdges(part);
        if(!part.seamSource.empty()){
            for(size_t v=0;v<part.vertices.size();++v)if(part.seamSource[v]!=v)++p.seamCopies;
            std::map<Edge,std::set<Edge>> original;
            for(const auto& e:edges)original[Key(part.seamSource[e.first.first],part.seamSource[e.first.second])].insert(e.first);
            size_t seams=0;for(const auto& e:original)if(e.second.size()>1)++seams;
            p.seamEdges+=seams;if(seams)++p.seamedParts;
        }
        std::vector<size_t> degree(part.vertices.size());
        for(const auto& e:edges){++degree[e.first.first];++degree[e.first.second];}
        for(auto d:degree)if(d>4)throw Error("Quad plan exceeds the two-spline junction limit.");
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
    if(p.vertices>MaxVertices||p.outputQuads>MaxOutputQuads)throw LimitError("Converted mesh exceeds import limits.");
}
void ConvertToQuads(Plan& p,bool omitUnpaired){
    p.pairedQuads=0;p.curvedPairs=0;p.subdividedComponents=0;p.outputQuads=0;
    p.seamedParts=0;p.seamEdges=0;p.seamCopies=0;
    p.omittedTriangles=0;p.omittedParts=0;
    size_t searchBudget=1000000;
    for(auto& part:p.parts)ConvertPart(part,p,searchBudget,omitUnpaired);
    p.omittedParts=static_cast<size_t>(std::count_if(p.parts.begin(),p.parts.end(),[](const Part& part){return part.faces.empty();}));
    p.parts.erase(std::remove_if(p.parts.begin(),p.parts.end(),[](const Part& part){return part.faces.empty();}),p.parts.end());
    if(omitUnpaired&&p.parts.empty()){p.minimum=p.maximum={};p.vertices=p.outputQuads=0;return;}
    ValidatePlan(p);
}
std::vector<std::array<float,3>> PreparePositions(const Part& part,double scale,bool mirror){
    if(!std::isfinite(scale)||scale<.001||scale>100000)throw Error("Invalid import scale.");
    if(!part.seamSource.empty()&&part.seamSource.size()!=part.vertices.size())throw Error("Incomplete seam vertex provenance.");
    std::vector<std::array<float,3>> out;out.reserve(part.vertices.size());
    std::map<std::array<float,3>,size_t> unique;
    for(size_t i=0;i<part.vertices.size();++i){auto v=part.vertices[i]*scale;if(mirror)v.z=-v.z;
        if(!Finite(v)||std::max({std::abs(v.x),std::abs(v.y),std::abs(v.z)})>1000000)throw Error("Scaled coordinates exceed 1,000,000 cm.");
        const std::array<float,3> p={static_cast<float>(v.x),static_cast<float>(v.y),static_cast<float>(v.z)};
        const auto [found,inserted]=unique.emplace(p,i);
        if(!inserted&&(part.seamSource.empty()||part.seamSource[i]!=part.seamSource[found->second]))
            throw Error("Scale and coordinate precision collapse distinct vertices. Recenter or simplify the mesh.");
        out.push_back(p);
    }
    for(const auto& f:part.faces){std::array<Vec3,4> p;
        for(size_t k=0;k<4;++k){const auto& v=out.at(f.vertex[k]);p[k]={v[0],v[1],v[2]};}
        const auto n=Cross(p[1]-p[0],p[2]-p[0]),n2=Cross(p[2]-p[0],p[3]-p[0]);
        if(Length(n)<1e-12||Length(n2)<1e-12||Dot(n,n2)<=0)throw Error("Scaled quad is degenerate at A:M precision.");
    }
    return out;
}
}
