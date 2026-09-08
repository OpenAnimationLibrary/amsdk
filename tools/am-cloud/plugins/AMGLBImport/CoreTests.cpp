// Portable test driver; stdout is machine-readable summary, no A:M dependency.
#include "ImportCore.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <iomanip>
#include <set>
#include <algorithm>
int main(int argc,char** argv){
    try{
        if(argc!=2)throw amglb::Error("Expected one GLB path.");
        std::ifstream input(argv[1],std::ios::binary);
        if(!input)throw amglb::Error("Cannot read fixture.");
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(input)),{});
        auto plan=amglb::ReadGLB(bytes);amglb::ConvertToQuads(plan);
        size_t boundary=0,threeWay=0,highValence=0,splineCount=0,closed=0;double area=0;
        std::map<uint32_t,size_t> materials;
        for(const auto& part:plan.parts){
            std::map<std::pair<uint32_t,uint32_t>,int> edges;
            std::vector<std::set<uint32_t>> neighbors(part.vertices.size());
            for(const auto& f:part.faces){
                ++materials[f.material];
                if(f.count!=4)throw amglb::Error("Test found a non-quad.");
                for(size_t i=0;i<4;++i){auto a=f.vertex[i],b=f.vertex[(i+1)%4];if(a>b)std::swap(a,b);++edges[{a,b}];neighbors[a].insert(b);neighbors[b].insert(a);}
                const auto a=part.vertices[f.vertex[0]],b=part.vertices[f.vertex[1]],c=part.vertices[f.vertex[2]],d=part.vertices[f.vertex[3]];
                area+=(amglb::Length(amglb::Cross(b-a,c-a))+amglb::Length(amglb::Cross(c-a,d-a)))*.5;
            }
            for(const auto& e:edges)if(e.second==1)++boundary;
            const auto routing=amglb::RouteSplines(part);splineCount+=routing.paths.size();
            std::map<std::pair<uint32_t,uint32_t>,size_t> routed;
            std::vector<size_t> occurrences(part.vertices.size());
            for(const auto& path:routing.paths){
                if(path.closed)++closed;
                for(auto v:path.vertex)++occurrences.at(v);
                for(size_t k=0;k+1<path.vertex.size();++k)++routed[std::minmax(path.vertex[k],path.vertex[k+1])];
                if(path.closed)++routed[std::minmax(path.vertex.back(),path.vertex.front())];
            }
            if(routed.size()!=edges.size())throw amglb::Error("Routing added or omitted an edge.");
            for(const auto& e:edges)if(routed.at(e.first)!=1)throw amglb::Error("Routing duplicated an edge.");
            for(size_t v=0;v<neighbors.size();++v){
                const auto degree=neighbors[v].size();
                if(degree==3){++threeWay;if(occurrences[v]!=2)throw amglb::Error("Three-way center has more than two spline CPs.");}
                if(degree==4&&occurrences[v]!=2)throw amglb::Error("Four-way crossing has more than two spline CPs.");
                if(degree>4)++highValence;
            }
        }
        std::cout<<std::setprecision(12)<<"{\"triangles\":"<<plan.inputTriangles<<",\"quads\":"<<plan.outputQuads
            <<",\"paired\":"<<plan.pairedQuads<<",\"subdivided\":"<<plan.subdividedComponents
            <<",\"parts\":"<<plan.parts.size()<<",\"vertices\":"<<plan.vertices<<",\"boundary\":"<<boundary
            <<",\"three_way\":"<<threeWay<<",\"high_valence\":"<<highValence<<",\"splines\":"<<splineCount<<",\"closed_splines\":"<<closed
            <<",\"area\":"<<area<<",\"min\":["<<plan.minimum.x<<","<<plan.minimum.y<<","<<plan.minimum.z
            <<"],\"max\":["<<plan.maximum.x<<","<<plan.maximum.y<<","<<plan.maximum.z<<"],\"materials\":[";
        bool first=true;
        for(const auto& item:materials){if(!first)std::cout<<',';first=false;const auto& m=plan.materials[item.first];
            std::cout<<"{\"faces\":"<<item.second<<",\"rgba\":["<<m.color[0]<<','<<m.color[1]<<','<<m.color[2]<<','<<m.color[3]<<"]}";
        }
        std::cout<<"]}\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
