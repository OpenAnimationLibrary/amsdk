#pragma once
#include "ImportCore.h"
#include <algorithm>
#include <limits>
#include <numeric>
#include <utility>

namespace amglb {
struct QuadCandidate {
    double score;
    size_t a,b;
    std::array<uint32_t,2> diagonal;
    Face face;
    bool curved;
};

// Removing a paired diagonal reduces the edge count at both endpoints. Search
// alternating paths/cycles to improve that count before subdividing any leftovers.
// This is bounded local reconstruction, not a complete/global remeshing solver.
class QuadMatching {
    static constexpr size_t none=std::numeric_limits<size_t>::max();
    const std::vector<QuadCandidate>& candidates;
    std::vector<std::vector<size_t>> adjacent;
    std::vector<size_t> mate;
    std::vector<int> degree;
    std::vector<bool> visited;
    size_t excess=0,pairs=0;
    size_t& budget;
    using Cost=std::pair<size_t,size_t>;
    struct Change { size_t removed,added; };
    std::vector<Change> path,bestPath;
    Cost bestCost;
    Cost CostNow() const { return {excess,mate.size()-2*pairs}; }
    void ChangeDegree(uint32_t v,int delta) {
        excess-=static_cast<size_t>(std::max(0,degree[v]-4));
        degree[v]+=delta;
        excess+=static_cast<size_t>(std::max(0,degree[v]-4));
    }
    void Select(size_t i) {
        const auto& c=candidates[i];mate[c.a]=mate[c.b]=i;++pairs;
        for(auto v:c.diagonal)ChangeDegree(v,-1);
    }
    void Remove(size_t i) {
        const auto& c=candidates[i];mate[c.a]=mate[c.b]=none;--pairs;
        for(auto v:c.diagonal)ChangeDegree(v,1);
    }
    size_t Other(size_t i,size_t f) const { return candidates[i].a==f?candidates[i].b:candidates[i].a; }
    void Explore(size_t a,size_t forbidden,size_t depth,size_t& localBudget) {
        if(depth==12)return;
        for(auto i:adjacent[a]) {
            if(!budget||!localBudget)return;
            --budget;--localBudget;
            if(i==forbidden)continue;
            const auto b=Other(i,a);
            if(visited[b])continue;
            const auto old=mate[b];const auto next=old==none?none:Other(old,b);
            if(next!=none&&visited[next])continue;
            if(old!=none)Remove(old);
            Select(i);path.push_back({old,i});visited[b]=true;
            if(next==none) {
                const auto cost=CostNow();
                if(cost<bestCost){bestCost=cost;bestPath=path;}
            } else {
                visited[next]=true;Explore(next,forbidden,depth+1,localBudget);visited[next]=false;
            }
            visited[b]=false;path.pop_back();Remove(i);
            if(old!=none)Select(old);
        }
    }
    bool Improve(size_t start,size_t removed) {
        bestCost=CostNow();bestPath.clear();path.clear();
        if(removed!=none)Remove(removed);
        size_t localBudget=1024;visited[start]=true;
        Explore(start,removed,0,localBudget);visited[start]=false;
        if(bestPath.empty()){if(removed!=none)Select(removed);return false;}
        for(const auto& change:bestPath){if(change.removed!=none)Remove(change.removed);Select(change.added);}
        return true;
    }
public:
    QuadMatching(const std::vector<QuadCandidate>& c,size_t faces,const std::vector<int>& degrees,size_t& work,uint32_t seed=0):
        candidates(c),adjacent(faces),mate(faces,none),degree(degrees),visited(faces,false),budget(work) {
        for(auto d:degree)excess+=static_cast<size_t>(std::max(0,d-4));
        std::vector<size_t> order(c.size());std::iota(order.begin(),order.end(),0);
        if(seed){
            // Small deterministic changes in quality ordering escape local
            // matching traps. Every attempt shares the same file-wide budget.
            const auto rank=[&](size_t i){
                uint32_t x=static_cast<uint32_t>(i+1)*0x9e3779b9U^seed*0x85ebca6bU;
                x^=x>>16;x*=0x7feb352dU;x^=x>>15;
                return c[i].score+.25*static_cast<double>(x)/4294967295.;
            };
            std::sort(order.begin(),order.end(),[&](size_t a,size_t b){const auto x=rank(a),y=rank(b);return x==y?a<b:x<y;});
        }
        for(auto i:order){adjacent[c[i].a].push_back(i);adjacent[c[i].b].push_back(i);}
        for(auto i:order)if(mate[c[i].a]==none&&mate[c[i].b]==none)Select(i);
        // Augmenting paths recover pairs missed by the initial quality ordering.
        for(int pass=0;pass<2&&budget;++pass)
            for(size_t f=0;f<faces&&budget;++f)if(mate[f]==none)Improve(f,none);
        for(int pass=0;pass<4&&excess&&budget;++pass) {
            bool changed=false;
            for(size_t i=0;i<c.size()&&excess&&budget;++i) {
                if(degree[c[i].diagonal[0]]<=4&&degree[c[i].diagonal[1]]<=4)continue;
                for(auto f:{c[i].a,c[i].b}) {
                    const auto old=mate[f];
                    if(old!=none&&Improve(f,old))changed=true;
                }
            }
            if(!changed)break;
        }
    }
    std::pair<size_t,size_t> CostValue() const { return CostNow(); }
    std::vector<bool> Selected() const {
        std::vector<bool> selected(candidates.size(),false);
        for(auto i:mate)if(i!=none)selected[i]=true;
        return selected;
    }
};
}
