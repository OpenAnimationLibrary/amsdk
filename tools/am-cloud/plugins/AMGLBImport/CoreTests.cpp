// Portable test driver; stdout is machine-readable summary, no A:M dependency.
#include "ImportCore.h"
#include "MaterialSurface.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <iomanip>
#include <set>
#include <algorithm>
int main(int argc,char** argv){
    try{
        if(argc<2||argc>4)throw amglb::Error("Expected a GLB path, optional target, and optional omit.");
        amglb::ImportOptions options;
        if(argc>=3){size_t used=0;options.targetPatches=std::stoull(argv[2],&used);if(argv[2][used])throw amglb::Error("Invalid target.");}
        if(argc==4){if(std::string(argv[3])!="omit")throw amglb::Error("Invalid omission option.");options.omitUnpaired=true;}
        std::ifstream input(argv[1],std::ios::binary);
        if(!input)throw amglb::Error("Cannot read fixture.");
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(input)),{});
        const auto source=amglb::ReadGLB(bytes);auto plan=amglb::BuildImportPlan(source,options);
        size_t boundary=0,geometricBoundary=0,threeWay=0,highValence=0,splineCount=0,closed=0,materialGroups=0,seams=0,copies=0,components=0,largest=0;double area=0;
        std::map<uint32_t,size_t> materials;
        std::map<uint32_t,double> materialAreas;
        for(const auto& part:plan.parts){
            for(bool mirror:{false,true})amglb::PreparePositions(part,100,mirror);
            std::map<std::pair<uint32_t,uint32_t>,int> edges;
            std::map<std::pair<uint32_t,uint32_t>,std::vector<size_t>> facesAt;
            std::map<std::pair<uint32_t,uint32_t>,std::set<std::pair<uint32_t,uint32_t>>> weldedEdges;
            std::vector<std::set<uint32_t>> neighbors(part.vertices.size());
            for(size_t face=0;face<part.faces.size();++face){const auto& f=part.faces[face];
                ++materials[f.material];
                if(f.count!=4)throw amglb::Error("Test found a non-quad.");
                for(size_t i=0;i<4;++i){auto a=f.vertex[i],b=f.vertex[(i+1)%4];if(a>b)std::swap(a,b);++edges[{a,b}];facesAt[{a,b}].push_back(face);neighbors[a].insert(b);neighbors[b].insert(a);}
                const auto a=part.vertices[f.vertex[0]],b=part.vertices[f.vertex[1]],c=part.vertices[f.vertex[2]],d=part.vertices[f.vertex[3]];
                const auto faceArea=(amglb::Length(amglb::Cross(b-a,c-a))+amglb::Length(amglb::Cross(c-a,d-a)))*.5;
                area+=faceArea;materialAreas[f.material]+=faceArea;
            }
            for(const auto& e:edges)if(e.second==1)++boundary;
            if(options.omitUnpaired){
                std::vector<std::vector<uint32_t>> outline(part.vertices.size());std::set<std::set<uint32_t>> intended;
                for(const auto& f:part.faces)intended.insert(std::set<uint32_t>(f.vertex.begin(),f.vertex.end()));
                for(const auto& e:edges)if(e.second==1){outline[e.first.first].push_back(e.first.second);outline[e.first.second].push_back(e.first.first);}
                std::set<uint32_t> checked;
                for(uint32_t v=0;v<outline.size();++v)if(!outline[v].empty()&&!checked.count(v)){
                    std::set<uint32_t> loop;std::vector<uint32_t> pending{v};
                    while(!pending.empty()){const auto n=pending.back();pending.pop_back();if(!loop.insert(n).second)continue;
                        if(outline[n].size()!=2)throw amglb::Error("Omission left a non-manifold boundary.");
                        for(auto next:outline[n])pending.push_back(next);
                    }
                    checked.insert(loop.begin(),loop.end());
                    if(loop.size()<=5&&!intended.count(loop))throw amglb::Error("Omission left a small loop that A:M could fill.");
                }
            }
            std::vector<std::vector<size_t>> adjacent(part.faces.size());
            for(const auto& e:facesAt)if(e.second.size()==2){adjacent[e.second[0]].push_back(e.second[1]);adjacent[e.second[1]].push_back(e.second[0]);}
            std::vector<bool> reached(part.faces.size(),false);
            for(size_t f=0;f<reached.size();++f)if(!reached[f]){
                ++components;size_t count=0;std::vector<size_t> pending{f};
                while(!pending.empty()){const auto next=pending.back();pending.pop_back();if(reached[next])continue;reached[next]=true;++count;for(auto n:adjacent[next])pending.push_back(n);}
                largest=std::max(largest,count);
            }
            for(const auto& e:edges){const auto [a,b]=e.first;
                auto original=e.first;if(!part.seamSource.empty())original=std::minmax(part.seamSource[a],part.seamSource[b]);
                weldedEdges[original].insert(e.first);
            }
            for(const auto& e:weldedEdges){
                size_t uses=0;for(const auto& edge:e.second)uses+=static_cast<size_t>(edges.at(edge));
                if(uses==1)++geometricBoundary;
                if(uses>2||e.second.size()>2)throw amglb::Error("Fallback duplicated a surface edge.");
                if(e.second.size()==2){++seams;for(const auto& edge:e.second)if(edges.at(edge)!=1)throw amglb::Error("Seam is not two matching boundaries.");}
            }
            for(size_t v=0;v<part.seamSource.size();++v)if(part.seamSource[v]!=v)++copies;
            const auto colorGroups=amglb::GroupMaterials(part);materialGroups+=colorGroups.size();
            std::vector<bool> colored(part.faces.size(),false);
            for(const auto& group:colorGroups){
                const std::set<uint32_t> selected(group.vertices.begin(),group.vertices.end());
                std::set<size_t> actualFaces;
                for(size_t i=0;i<part.faces.size();++i){const auto& face=part.faces[i];
                    if(std::all_of(face.vertex.begin(),face.vertex.end(),[&](uint32_t v){return selected.count(v)!=0;})){
                        if(face.material!=group.material)throw amglb::Error("Color group leaks onto another material.");
                        actualFaces.insert(i);colored[i]=true;
                    }
                }
                if(actualFaces.empty()||actualFaces!=std::set<size_t>(group.faces.begin(),group.faces.end()))throw amglb::Error("Color group coverage is incorrect.");
            }
            if(std::find(colored.begin(),colored.end(),false)!=colored.end())throw amglb::Error("A face is missing its color group.");
            const auto routing=amglb::RouteSplines(part);splineCount+=routing.paths.size();
            std::map<std::pair<uint32_t,uint32_t>,size_t> routed;
            std::map<std::pair<uint32_t,uint32_t>,size_t> edgeSpline;
            std::vector<size_t> occurrences(part.vertices.size());
            for(size_t pathIndex=0;pathIndex<routing.paths.size();++pathIndex){const auto& path=routing.paths[pathIndex];
                if(path.closed)++closed;
                for(auto v:path.vertex)++occurrences.at(v);
                for(size_t k=0;k+1<path.vertex.size();++k){const auto edge=std::minmax(path.vertex[k],path.vertex[k+1]);++routed[edge];edgeSpline[edge]=pathIndex;}
                if(path.closed){const auto edge=std::minmax(path.vertex.back(),path.vertex.front());++routed[edge];edgeSpline[edge]=pathIndex;}
            }
            if(routed.size()!=edges.size())throw amglb::Error("Routing added or omitted an edge.");
            for(const auto& e:edges)if(routed.at(e.first)!=1)throw amglb::Error("Routing duplicated an edge.");
            for(const auto& face:part.faces){std::set<size_t> boundarySplines;
                for(size_t k=0;k<4;++k)boundarySplines.insert(edgeSpline.at(std::minmax(face.vertex[k],face.vertex[(k+1)%4])));
                if(boundarySplines.size()<2)throw amglb::Error("A quad is bounded by only one spline: "+part.name);
            }
            for(size_t v=0;v<neighbors.size();++v){
                const auto degree=neighbors[v].size();
                if(degree==3){++threeWay;if(occurrences[v]!=2)throw amglb::Error("Three-way center has more than two spline CPs.");}
                if(degree==4&&occurrences[v]!=2)throw amglb::Error("Four-way crossing has more than two spline CPs.");
                if(degree>4||occurrences[v]>2)throw amglb::Error("Test found a junction exceeding two splines.");
            }
        }
        if(seams!=plan.seamEdges||copies!=plan.seamCopies||boundary!=geometricBoundary+2*seams)
            throw amglb::Error("Fallback seam reporting does not match actual topology.");
        std::cout<<std::setprecision(12)<<"{\"triangles\":"<<plan.inputTriangles<<",\"quads\":"<<plan.outputQuads
            <<",\"curved_pairs\":"<<plan.curvedPairs<<",\"paired\":"<<plan.pairedQuads<<",\"subdivided\":"<<plan.subdividedComponents
            <<",\"target\":"<<plan.targetPatches<<",\"reduced_triangles\":"<<plan.reducedTriangles<<",\"omitted_triangles\":"<<plan.omittedTriangles<<",\"omitted_parts\":"<<plan.omittedParts<<",\"density_attempts\":"<<plan.densityAttempts
            <<",\"density_target_met\":"<<(!plan.targetPatches||plan.outputQuads<=plan.targetPatches?"true":"false")
            <<",\"parts\":"<<plan.parts.size()<<",\"vertices\":"<<plan.vertices<<",\"boundary\":"<<boundary
            <<",\"geometric_boundary\":"<<geometricBoundary<<",\"seamed_parts\":"<<plan.seamedParts<<",\"seam_edges\":"<<seams<<",\"seam_copies\":"<<copies
            <<",\"surface_components\":"<<components<<",\"largest_component\":"<<largest
            <<",\"material_groups\":"<<materialGroups<<",\"three_way\":"<<threeWay<<",\"high_valence\":"<<highValence<<",\"splines\":"<<splineCount<<",\"closed_splines\":"<<closed
            <<",\"area\":"<<area<<",\"min\":["<<plan.minimum.x<<","<<plan.minimum.y<<","<<plan.minimum.z
            <<"],\"max\":["<<plan.maximum.x<<","<<plan.maximum.y<<","<<plan.maximum.z<<"],\"materials\":[";
        bool first=true;
        for(const auto& item:materials){if(!first)std::cout<<',';first=false;const auto& m=plan.materials[item.first];
            std::cout<<"{\"faces\":"<<item.second<<",\"rgba\":["<<m.color[0]<<','<<m.color[1]<<','<<m.color[2]<<','<<m.color[3]<<"]}";
        }
        std::cout<<"],\"material_areas\":[";first=true;
        for(const auto& item:materialAreas){if(!first)std::cout<<',';first=false;std::cout<<item.second;}
        std::cout<<"],\"surface_fractions\":[";first=true;
        for(const auto& item:materials){if(!first)std::cout<<',';first=false;
            const auto surface=amglb::SurfaceForMaterial(plan.materials[item.first]);
            std::cout<<"{\"specular_size\":"<<surface.specularSize<<",\"specular_intensity\":"<<surface.specularIntensity
                <<",\"reflectivity\":"<<surface.reflectivity<<",\"transparency\":"<<surface.transparency<<'}';
        }
        std::cout<<"]}\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
