#include "ImportCore.h"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <tuple>

namespace amglb {
SplinePlan RouteSplines(const Part& part) {
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
    SplinePlan result;result.edges=edges.size();result.occurrences.resize(neighbors.size());
    std::vector<std::map<uint32_t,uint32_t>> through(neighbors.size());
    for(uint32_t v=0;v<neighbors.size();++v) {
        const auto& ns=neighbors[v];
        if(ns.empty())throw Error("Spline plan contains an unused vertex.");
        if(ns.size()>64)throw Error("A source pole has more than 64 edges. Retopologize that pole before import.");
        if(ns.size()>4)++result.highValenceVertices;
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
        if(result.occurrences[v]!=expected&&!(degree==2&&result.occurrences[v]==1))throw Error("Spline junction does not match the routing plan.");
    }
    return result;
}
}
