#include "ImportCore.h"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <tuple>

namespace amglb {
namespace {
SplinePlan RouteConnected(const Part& part) {
    using Edge = std::pair<uint32_t,uint32_t>;
    const auto edge = [](uint32_t a,uint32_t b)->Edge { return std::minmax(a,b); };
    constexpr uint32_t end = UINT32_MAX;
    std::set<Edge> edges;
    std::vector<std::set<uint32_t>> neighbors(part.vertices.size());
    std::vector<std::set<Edge>> adjacent(part.vertices.size());
    for(const auto& f:part.faces) {
        if(f.count!=4)throw Error("Spline routing requires quads.");
        for(uint32_t k=0;k<4;++k) {
            const auto a=f.vertex[k],b=f.vertex[(k+1)%4],c=f.vertex[(k+3)%4];
            if(a>=neighbors.size()||b>=neighbors.size()||c>=neighbors.size()||a==b)throw Error("Invalid routing vertex.");
            edges.insert(edge(a,b));neighbors[a].insert(b);neighbors[b].insert(a);
            adjacent[a].insert(edge(b,c));
        }
    }
    std::vector<std::map<uint32_t,uint32_t>> through(neighbors.size());
    for(uint32_t v=0;v<neighbors.size();++v) {
        const auto& ns=neighbors[v];
        if(ns.empty())throw Error("Spline plan contains an unused vertex.");
        if(ns.size()>4)throw Error("Part '"+part.name+"' exceeds the two-spline limit at vertex "+std::to_string(v+1)+". Retopologize it before import.");
        for(auto n:ns)through[v][n]=end;
        // Two boundary edges terminate at their corner. At three-way junctions
        // continue the straightest pair; on a regular four-way junction the
        // non-adjacent face edges must continue through each other.
        if(ns.size()<3)continue;
        struct Pair { bool adjacent;double bend;uint32_t a,b; };
        std::vector<Pair> pairs;
        for(auto a:ns)for(auto b:ns)if(a<b)
            pairs.push_back({adjacent[v].count(edge(a,b))!=0,
                Dot(Unit(part.vertices[a]-part.vertices[v]),Unit(part.vertices[b]-part.vertices[v])),a,b});
        std::sort(pairs.begin(),pairs.end(),[](const Pair& a,const Pair& b){
            return std::tie(a.adjacent,a.bend,a.a,a.b)<std::tie(b.adjacent,b.bend,b.a,b.b);
        });
        std::set<uint32_t> paired;
        for(const auto& p:pairs)if(!paired.count(p.a)&&!paired.count(p.b)) {
            through[v][p.a]=p.b;through[v][p.b]=p.a;paired.insert(p.a);paired.insert(p.b);
        }
    }
    const auto emit = [&]() {
        SplinePlan result;result.edges=edges.size();result.occurrences.resize(neighbors.size());
        std::set<Edge> remaining=edges;
        const auto walk = [&](uint32_t start,uint32_t next) {
            SplinePath path;path.vertex.push_back(start);
            uint32_t previous=start,current=next;
            while(true) {
                if(!remaining.erase(edge(previous,current)))throw Error("Spline routing reused an edge.");
                const auto following=through[current].at(previous);
                if(current==start&&following==next) {path.closed=true;break;}
                path.vertex.push_back(current);
                if(following==end)break;
                previous=current;current=following;
            }
            // Two unpaired boundary half-edges can terminate the same walk at its
            // starting corner. Close that path explicitly instead of asking AttachCPs
            // to delete a duplicated endpoint later.
            if(!path.closed&&path.vertex.front()==path.vertex.back()) {
                path.closed=true;path.vertex.pop_back();
            }
            if(path.vertex.size()<2||(path.closed&&path.vertex.size()<3))throw Error("Invalid spline path.");
            for(auto v:path.vertex)++result.occurrences[v];
            result.paths.push_back(std::move(path));
        };
        // Start with unpaired half-edges, then consume the remaining closed paths.
        for(uint32_t v=0;v<through.size();++v)for(const auto& p:through[v])
            if(p.second==end&&remaining.count(edge(v,p.first)))walk(v,p.first);
        while(!remaining.empty()){const auto e=*remaining.begin();walk(e.first,e.second);}
        for(size_t v=0;v<neighbors.size();++v) {
            const auto degree=neighbors[v].size();
            const auto expected=degree<3?degree:(degree+1)/2;
            if(result.occurrences[v]>2||(result.occurrences[v]!=expected&&!(degree==2&&result.occurrences[v]==1)))throw Error("Spline junction does not match the routing plan.");
        }
        return result;
    };
    const auto singleSplineFaces = [&](const SplinePlan& routing) {
        std::map<Edge,size_t> owner;
        for(size_t i=0;i<routing.paths.size();++i){const auto& path=routing.paths[i];
            for(size_t k=1;k<path.vertex.size();++k)owner.emplace(edge(path.vertex[k-1],path.vertex[k]),i);
            if(path.closed)owner.emplace(edge(path.vertex.back(),path.vertex.front()),i);
        }
        std::vector<size_t> bad;
        for(size_t i=0;i<part.faces.size();++i){const auto& f=part.faces[i];
            const auto first=owner.at(edge(f.vertex[0],f.vertex[1]));bool single=true;
            for(size_t k=1;k<4;++k)if(owner.at(edge(f.vertex[k],f.vertex[(k+1)%4]))!=first)single=false;
            if(single)bad.push_back(i);
        }
        return bad;
    };
    auto result=emit();auto bad=singleSplineFaces(result);
    // A:M did not discover the two hinge backs in the owner's saved model:
    // each was a four-CP loop on one spline. A valid edge graph alone was
    // insufficient. Change through-pairs at existing three-edge junctions;
    // do not add points, seams or a third CP record to an attachment.
    size_t work=0;
    while(!bad.empty()){
        bool repaired=false;const auto& face=part.faces[bad.front()];
        for(size_t a=0;a<4&&!repaired;++a)for(size_t b=a+1;b<4&&!repaired;++b){
            const auto u=face.vertex[a],v=face.vertex[b];
            if(neighbors[u].size()!=3||neighbors[v].size()!=3)continue;
            const auto beforeU=through[u],beforeV=through[v];
            for(auto endU:neighbors[u])for(auto endV:neighbors[v]){
                if(repaired||beforeU.at(endU)==end||beforeV.at(endV)==end)continue;
                if(work+edges.size()>20000000)throw Error("Spline routing repair exceeded its work limit in part '"+part.name+"'.");
                work+=edges.size();
                const auto pairOthers=[&](uint32_t at,uint32_t endpoint){
                    std::vector<uint32_t> pair;
                    for(auto n:neighbors[at]){through[at][n]=end;if(n!=endpoint)pair.push_back(n);}
                    through[at][pair[0]]=pair[1];through[at][pair[1]]=pair[0];
                };
                pairOthers(u,endU);pairOthers(v,endV);
                auto candidate=emit();auto next=singleSplineFaces(candidate);
                if(next.size()<bad.size()){
                    result=std::move(candidate);bad=std::move(next);repaired=true;
                }else{through[u]=beforeU;through[v]=beforeV;}
            }
        }
        if(!repaired)throw Error("Cannot route every quad across at least two splines in part '"+part.name+"'.");
    }
    return result;
}
}

SplinePlan RouteSplines(const Part& part) {
    // Repair disconnected solids separately. Thousands of small boxes in one
    // named part must not require rescanning every other box for each repair.
    std::vector<uint32_t> parent(part.vertices.size());
    for(uint32_t i=0;i<parent.size();++i)parent[i]=i;
    const auto root=[&](uint32_t v){while(parent[v]!=v){parent[v]=parent[parent[v]];v=parent[v];}return v;};
    for(const auto& f:part.faces){
        if(f.count!=4)throw Error("Spline routing requires quads.");
        for(auto v:f.vertex)if(v>=parent.size())throw Error("Invalid routing vertex.");
        for(auto v:f.vertex)parent[root(v)]=root(f.vertex[0]);
    }
    std::set<uint32_t> roots;for(uint32_t i=0;i<parent.size();++i)roots.insert(root(i));
    if(roots.size()<=1)return RouteConnected(part);
    struct Component { Part part;std::vector<uint32_t> global; };
    std::map<uint32_t,Component> components;std::vector<uint32_t> local(parent.size());
    for(uint32_t i=0;i<parent.size();++i){auto& c=components[root(i)];
        local[i]=static_cast<uint32_t>(c.global.size());c.global.push_back(i);c.part.vertices.push_back(part.vertices[i]);
    }
    for(auto f:part.faces){const auto component=root(f.vertex[0]);for(auto& v:f.vertex)v=local[v];components.at(component).part.faces.push_back(f);}
    SplinePlan result;result.occurrences.resize(part.vertices.size());
    for(auto& entry:components){auto& c=entry.second;c.part.name=part.name;auto routed=RouteConnected(c.part);
        result.edges+=routed.edges;
        for(size_t i=0;i<c.global.size();++i)result.occurrences[c.global[i]]=routed.occurrences[i];
        for(auto& path:routed.paths){for(auto& v:path.vertex)v=c.global[v];result.paths.push_back(std::move(path));}
    }
    return result;
}
}
