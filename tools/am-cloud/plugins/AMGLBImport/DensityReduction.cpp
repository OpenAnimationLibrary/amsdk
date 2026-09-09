// Target-budget preparation; meshoptimizer supplies the edge-collapse solver.
#include "ImportCore.h"
#include "third_party/meshoptimizer/meshoptimizer.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <set>
#include <tuple>

namespace amglb {
namespace {
using Edge=std::pair<uint32_t,uint32_t>;
struct Corner { size_t face; uint32_t k; };
struct Sample { uint32_t source,material; };
using SampleKey=std::pair<uint32_t,uint32_t>;
void ReducePart(Part& p,double ratio){
    if(p.faces.size()<3)return;
    const auto target=std::max<size_t>(1,static_cast<size_t>(static_cast<double>(p.faces.size())*ratio));
    if(target>=p.faces.size())return;
    std::map<Edge,std::vector<Corner>> edges;std::vector<Vec3> normals;
    std::vector<bool> locked(p.vertices.size(),false);
    std::vector<bool> used(p.vertices.size(),false);
    std::vector<std::set<uint32_t>> border(p.vertices.size());
    for(size_t i=0;i<p.faces.size();++i){const auto& f=p.faces[i];
        normals.push_back(Unit(Cross(p.vertices[f.vertex[1]]-p.vertices[f.vertex[0]],p.vertices[f.vertex[2]]-p.vertices[f.vertex[0]])));
        for(uint32_t k=0;k<3;++k){used[f.vertex[k]]=true;edges[std::minmax(f.vertex[k],f.vertex[(k+1)%3])].push_back({i,k});}
    }
    for(const auto& e:edges){const auto [a,b]=e.first;
        if(e.second.size()==2&&Dot(normals[e.second[0].face],normals[e.second[1].face])<.8660254037844386)locked[a]=locked[b]=true;
        if(e.second.size()==1||p.faces[e.second[0].face].material!=p.faces[e.second[1].face].material){
            border[a].insert(b);border[b].insert(a);
        }
    }
    // Straight boundary runs can lose intermediate points without changing
    // their shape; corners/junctions stay fixed. Material IDs split index
    // seams so the solver cannot collapse across a color boundary.
    for(size_t v=0;v<border.size();++v)if(!border[v].empty()){
        if(border[v].size()!=2)locked[v]=true;
        else{auto i=border[v].begin();const auto a=*i++,b=*i;
            if(Dot(Unit(p.vertices[a]-p.vertices[v]),Unit(p.vertices[b]-p.vertices[v]))>-.999999)locked[v]=true;
        }
    }
    const auto firstUsed=p.faces[0].vertex[0];
    Vec3 minimum=p.vertices[firstUsed],maximum=minimum;std::array<uint32_t,6> extreme;extreme.fill(firstUsed);
    for(uint32_t i=0;i<p.vertices.size();++i)if(used[i]){const auto v=p.vertices[i];
        if(v.x<minimum.x){minimum.x=v.x;extreme[0]=i;}if(v.x>maximum.x){maximum.x=v.x;extreme[1]=i;}
        if(v.y<minimum.y){minimum.y=v.y;extreme[2]=i;}if(v.y>maximum.y){maximum.y=v.y;extreme[3]=i;}
        if(v.z<minimum.z){minimum.z=v.z;extreme[4]=i;}if(v.z>maximum.z){maximum.z=v.z;extreme[5]=i;}
    }
    for(auto v:extreme)locked[v]=true;
    const auto extent=maximum-minimum;const auto scale=std::max({extent.x,extent.y,extent.z});
    if(!(scale>0))return;
    std::vector<Sample> samples;std::vector<std::array<float,3>> positions;
    std::vector<unsigned char> locks;std::vector<unsigned int> indices;std::map<SampleKey,unsigned int> lookup;
    for(const auto& f:p.faces)for(uint32_t k=0;k<3;++k){
        const SampleKey key{f.vertex[k],f.material};
        auto found=lookup.find(key);
        if(found==lookup.end()){
            const auto id=static_cast<unsigned int>(samples.size());found=lookup.emplace(key,id).first;
            samples.push_back({f.vertex[k],f.material});
            const auto v=(p.vertices[f.vertex[k]]-minimum)*(1./scale);
            positions.push_back({static_cast<float>(v.x),static_cast<float>(v.y),static_cast<float>(v.z)});
            locks.push_back(static_cast<unsigned char>(locked[f.vertex[k]]?meshopt_SimplifyVertex_Lock:0));
        }
        indices.push_back(found->second);
    }
    std::vector<unsigned int> reduced(indices.size());
    const auto count=meshopt_simplifyWithAttributes(reduced.data(),indices.data(),indices.size(),positions[0].data(),positions.size(),sizeof(positions[0]),
        nullptr,0,nullptr,0,locks.data(),target*3,.05F,0,nullptr);
    if(count==0||count>=indices.size())return;
    if(count%3)throw Error("Density reduction returned incomplete triangles.");
    std::vector<Face> faces;std::set<uint32_t> before,after;
    for(const auto& f:p.faces)before.insert(f.material);
    // UV decals/custom shading normals are not imported by this plugin.
    // Opt-in density reduction discards their seams in reduced parts; the
    // full-density path retains the original pairing protections.
    for(size_t i=0;i<count;i+=3){Face f;f.material=samples.at(reduced[i]).material;
        for(size_t k=0;k<3;++k){const auto& s=samples.at(reduced[i+k]);
            if(s.material!=f.material)throw Error("Density reduction crossed a material boundary.");
            f.vertex[k]=s.source;
        }
        faces.push_back(f);after.insert(f.material);
    }
    if(before!=after)return; // Do not erase a whole color region to meet a target.
    p.faces=std::move(faces);
}
size_t Triangles(const Plan& p){size_t n=0;for(const auto& part:p.parts)n+=part.faces.size();return n;}
}
Plan BuildImportPlan(const Plan& source,const ImportOptions& options){
    if(options.targetPatches>MaxOutputQuads)throw Error("Target patches must be 0 to 100,000.");
    ValidateSource(source);
    Plan best=source;bool haveBest=false;std::string limit;
    try{ConvertToQuads(best,options.omitUnpaired);haveBest=true;}
    catch(const LimitError& e){if(!options.targetPatches)throw;limit=e.what();}
    best.targetPatches=options.targetPatches;
    if(!options.targetPatches||(haveBest&&best.outputQuads<=options.targetPatches))return best;
    const auto original=Triangles(source);
    const auto cost=[&](const Plan& p){return std::make_pair(p.outputQuads>options.targetPatches,
        p.outputQuads>options.targetPatches?p.outputQuads-options.targetPatches:options.targetPatches-p.outputQuads);};
    double low=0,high=1,ratio=std::clamp(static_cast<double>(options.targetPatches)/static_cast<double>(haveBest?best.outputQuads:original*3),.001,.9);
    size_t attempts=0,previous=original+1,rejected=0;
    for(;attempts<6;++attempts){
        Plan candidate=source;
        try{
            for(auto& part:candidate.parts){
                Part originalPart=part;ReducePart(part,ratio);
                if(part.faces.size()==originalPart.faces.size())continue;
                Plan check;check.parts.push_back(part);check.materials=source.materials;
                try{ValidateSource(check);}
                catch(const Error&){part=std::move(originalPart);++rejected;}
            }
            const auto remaining=Triangles(candidate);
            if(remaining==previous&&low==0)break; // Locked boundaries/error limit stopped reduction.
            previous=remaining;ValidateSource(candidate);
            ConvertToQuads(candidate,options.omitUnpaired);
            candidate.reducedTriangles=original-remaining;candidate.targetPatches=options.targetPatches;
            const auto count=candidate.outputQuads;
            if(count&&(!haveBest||cost(candidate)<cost(best))){best=std::move(candidate);haveBest=true;}
            if(count==options.targetPatches){++attempts;break;}
            if(count>options.targetPatches){high=ratio;ratio=std::max(.00001,ratio*std::max(.15,static_cast<double>(options.targetPatches)/static_cast<double>(count)*.85));}
            else{low=ratio;ratio=(low+high)*.5;}
        }catch(const Error&){++rejected;high=ratio;ratio=(low+ratio)*.5;}
    }
    if(!haveBest)throw LimitError(limit.empty()?"Cannot reach a valid density within the import limits.":limit);
    best.densityAttempts=attempts;
    if(best.outputQuads>options.targetPatches)best.notes.push_back("The density target could not be reached while preserving protected boundaries and shape. The preview shows the retained patch count.");
    if(rejected)best.notes.push_back("Some density candidates failed topology checks; a valid candidate was retained.");
    return best;
}
}
