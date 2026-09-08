// Portable test driver; stdout is machine-readable summary, no A:M dependency.
#include "ImportCore.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <iomanip>
int main(int argc,char** argv){
    try{
        if(argc!=2)throw amglb::Error("Expected one GLB path.");
        std::ifstream input(argv[1],std::ios::binary);
        if(!input)throw amglb::Error("Cannot read fixture.");
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(input)),{});
        auto plan=amglb::ReadGLB(bytes);amglb::ConvertToQuads(plan);
        size_t boundary=0;double area=0;
        for(const auto& part:plan.parts){
            std::map<std::pair<uint32_t,uint32_t>,int> edges;
            for(const auto& f:part.faces){
                if(f.count!=4)throw amglb::Error("Test found a non-quad.");
                for(size_t i=0;i<4;++i){auto a=f.vertex[i],b=f.vertex[(i+1)%4];if(a>b)std::swap(a,b);++edges[{a,b}];}
                const auto a=part.vertices[f.vertex[0]],b=part.vertices[f.vertex[1]],c=part.vertices[f.vertex[2]],d=part.vertices[f.vertex[3]];
                area+=(amglb::Length(amglb::Cross(b-a,c-a))+amglb::Length(amglb::Cross(c-a,d-a)))*.5;
            }
            for(const auto& e:edges)if(e.second==1)++boundary;
        }
        std::cout<<std::setprecision(12)<<"{\"triangles\":"<<plan.inputTriangles<<",\"quads\":"<<plan.outputQuads
            <<",\"paired\":"<<plan.pairedQuads<<",\"subdivided\":"<<plan.subdividedComponents
            <<",\"parts\":"<<plan.parts.size()<<",\"vertices\":"<<plan.vertices<<",\"boundary\":"<<boundary
            <<",\"area\":"<<area<<",\"min\":["<<plan.minimum.x<<","<<plan.minimum.y<<","<<plan.minimum.z
            <<"],\"max\":["<<plan.maximum.x<<","<<plan.maximum.y<<","<<plan.maximum.z<<"]}\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
