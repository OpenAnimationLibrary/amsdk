#include "ImportCore.h"
#include <map>
#include <set>

namespace amglb {
std::vector<MaterialGroup> GroupMaterials(const Part& part) {
    std::vector<std::vector<size_t>> incident(part.vertices.size());
    for(size_t i=0;i<part.faces.size();++i) {
        const auto& f=part.faces[i];
        if(f.count!=4)throw Error("Material grouping requires quads.");
        for(auto v:f.vertex) {
            if(v>=incident.size())throw Error("Invalid material group vertex.");
            incident[v].push_back(i);
        }
    }
    struct Bucket { uint32_t material;std::set<uint32_t> vertices; };
    std::vector<Bucket> buckets;
    std::map<uint32_t,size_t> current;
    for(const auto& f:part.faces) {
        auto found=current.find(f.material);
        bool fits=found!=current.end();
        if(fits) {
            const auto& selected=buckets[found->second].vertices;
            std::set<uint32_t> added;
            for(auto v:f.vertex)if(!selected.count(v))added.insert(v);
            // Only faces touching a newly added CP can become newly enclosed.
            for(auto v:added)for(auto i:incident[v]) {
                const auto& other=part.faces[i];
                if(other.material==f.material)continue;
                bool enclosed=true;
                for(auto corner:other.vertex)if(!selected.count(corner)&&!added.count(corner)){enclosed=false;break;}
                if(enclosed)fits=false;
            }
        }
        if(!fits) {
            current[f.material]=buckets.size();
            buckets.push_back({f.material,{}});
        }
        auto& bucket=buckets[current.at(f.material)];
        bucket.vertices.insert(f.vertex.begin(),f.vertex.end());
    }
    std::vector<MaterialGroup> result;
    std::vector<bool> covered(part.faces.size(),false);
    for(const auto& bucket:buckets) {
        MaterialGroup group;group.material=bucket.material;
        group.vertices.assign(bucket.vertices.begin(),bucket.vertices.end());
        std::map<size_t,size_t> corners;
        for(auto v:group.vertices)for(auto i:incident[v])++corners[i];
        for(const auto& item:corners)if(item.second==4) {
            if(part.faces[item.first].material!=group.material)throw Error("A material group encloses a different color's face.");
            group.faces.push_back(item.first);covered[item.first]=true;
        }
        if(group.faces.empty())throw Error("Empty material group.");
        result.push_back(std::move(group));
    }
    for(bool present:covered)if(!present)throw Error("A face has no material group.");
    return result;
}
}
