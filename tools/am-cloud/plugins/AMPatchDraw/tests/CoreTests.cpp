#include "../PatchDrawCore.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

using namespace patchdraw;
void Check(bool value,const char* reason) { if(!value) throw std::runtime_error(reason); }
template<class F> void Reject(F f) { bool rejected=false; try { f(); } catch(const std::exception&) { rejected=true; } Check(rejected,"Expected rejection"); }
std::set<Face> GraphFaces(const Topology& t) {
    std::vector<std::set<std::size_t>> adjacency(t.vertices.size());
    for(auto e:t.edges) { adjacency[e[0]].insert(e[1]); adjacency[e[1]].insert(e[0]); }
    std::set<Face> actual;
    for(std::size_t a=0;a<adjacency.size();++a) {
        for(auto b:adjacency[a]) for(auto c:adjacency[a]) if(b<c) {
            for(auto d:adjacency[b]) if(d!=a && adjacency[c].count(d)) {
                Face face{a,b,c,d}; std::sort(face.begin(),face.end()); actual.insert(face);
            }
        }
    }
    return actual;
}
void Verify(const Grid& g,const Topology& t) {
    Check(t.faces.size()==g.count()*4,"Four faces per cell");
    std::set<Face> expected;
    for(auto f:t.faces) { std::sort(f.begin(),f.end()); Check(expected.insert(f).second,"Unique intended face"); }
    Check(GraphFaces(t)==expected,"Intended faces must equal graph four-cycles");
    std::set<Edge> represented;
    for(const auto& s:t.splines) {
        Check(s.size()>=2,"Spline has two CPs");
        std::set<std::size_t> distinct;
        for(auto v:s) Check(distinct.insert(v).second,"No closed run");
        for(std::size_t i=1;i<s.size();++i) Check(represented.insert(OrderedEdge(s[i-1],s[i])).second,"No duplicate segment");
    }
    Check(represented==std::set<Edge>(t.edges.begin(),t.edges.end()),"Spline edges exactly cover face edges");
    Check(t.occurrences==t.vertices.size()*2,"Two spline-specific CPs per logical point");
}
Grid Ring() { Grid g(3); g.cells.fill(false); for(int y=0;y<3;++y) for(int x=0;x<3;++x) g.set(x,y,x!=1 || y!=1); return g; }
void TopologyTests(const std::filesystem::path& fixtures) {
    if(!fixtures.empty()) Check(std::filesystem::create_directory(fixtures),"Fixture directory must be new");
    for(unsigned bits=0;bits<512;++bits) {
        Grid g(3);
        for(int y=0;y<3;++y) for(int x=0;x<3;++x) g.set(x,y,(bits&(1u<<(3*y+x)))!=0);
        auto t=Compile(g); Verify(g,t);
        Check(Compile(g).splines==t.splines,"Deterministic runs");
        if(bits && !fixtures.empty()) {
            std::ofstream f(fixtures/ ("mask-"+std::to_string(bits)+".json")); f<<ToPlan(g,t); Check(f.good(),"Write fixture");
        }
    }
    const auto r=Compile(Ring());
    Check(r.faces.size()==32 && r.vertices.size()==48 && r.splines.size()==16 && r.occurrences==96 && r.holeCount==1 && r.componentCount==1,"Ring fixture counts");
    Grid g(3); g.set(0,0,true); auto one=Compile(g);
    Check(one.faces.size()==4 && one.vertices.size()==9 && one.splines.size()==6,"Single-cell counts");
    g.set(1,0,true); auto pair=Compile(g);
    Check(pair.vertices.size()==15 && pair.splines.size()==8 && pair.componentCount==1,"Shared edge");
    g=Grid(3);g.set(0,0,true);g.set(1,1,true);auto diagonal=Compile(g);
    Check(diagonal.vertices.size()==18 && diagonal.componentCount==2,"Separate diagonal fans");
    g=Ring();g.set(2,2,false);auto pinch=Compile(g);
    Check(pinch.componentCount==1 && std::count(pinch.vertices.begin(),pinch.vertices.end(),Cell{4,4})==2,"Local split even when joined elsewhere");
    std::mt19937 random(195);
    for(int k=0;k<512;++k) { Grid q(4); for(int y=0;y<4;++y) for(int x=0;x<4;++x) q.set(x,y,(random()&1)!=0); Verify(q,Compile(q)); }
    Grid full(16); for(int y=0;y<16;++y)for(int x=0;x<16;++x)full.set(x,y,true);
    const auto max=Compile(full);Verify(full,max);
    Check(max.faces.size()==1024 && max.vertices.size()==1089 && max.splines.size()==66,"Full 16 limit counts");
    Reject([&]{ToPlan(full,max);});
    Grid checker(16);for(int y=0;y<16;++y)for(int x=0;x<16;++x)checker.set(x,y,(x+y)%2==0);
    const auto ct=Compile(checker); Verify(checker,ct); Check(ct.componentCount==128 && ct.splines.size()==768,"Fragmentation budget");
    Reject([&]{ToPlan(checker,ct);});
    Reject([]{Grid a(0);}); Reject([]{Grid a(17);}); Reject([]{Grid a(3,0);}); Reject([]{Grid a(3,1001);});
    Reject([]{Grid a;a.set(-1,0,true);}); Reject([]{Grid a;a.set(8,8,true);}); Reject([]{Grid a;ToPlan(a,Compile(a));});
    Grid scale(3,1);scale.set(0,0,true);auto json=ToPlan(scale,Compile(scale));
    Check(json.find("[-1.5, -1.5, 0]")!=json.npos,"Half units, centered XY mapping");
    std::cout<<"PASS: 512 exhaustive 3x3 masks + 512 seeded 4x4 masks; face/edge equality, ring, adjacency, diagonal fans, Euler counts and export bounds\n";
}
void BrushTests() {
    Grid one(8), many(8);
    Sweep(one,{.5,3.5},{7.5,3.5},.25,true);
    for(int i=0;i<28;++i) Sweep(many,{.5+i*.25,3.5},{.75+i*.25,3.5},.25,true);
    Check(one==many && one.count()==8,"Collinear sweep independent of event spacing");
    Grid tangent(4);Sweep(tangent,{.5,.5},{.5,.5},.5,true); Check(tangent.count()==1,"Tangency alone does not paint");
    Grid clipped(4);Sweep(clipped,{-20,.5},{20,.5},.25,true);Check(clipped.count()==4,"Outside path clips to document");
    Sweep(clipped,{-20,.5},{20,.5},.25,false);Check(clipped.count()==0,"Erase removes swept cells");
    Grid guard(16);
    for(int y=-4;y<=20;++y)for(int x=-4;x<=20;++x)Sweep(guard,{static_cast<double>(x),static_cast<double>(y)},{x+.25,y+.5},.5,true);
    Check(guard.count()==256,"Border/oversized sweep covers bounded grid");
    Reject([&]{Sweep(guard,{0,0},{1,1},0,true);});
    Reject([&]{Sweep(guard,{NAN,0},{1,1},.5,true);});
    Reject([&]{Sweep(guard,{0,0},{INFINITY,1},.5,true);});
    Reject([&]{Sweep(guard,{0,0},{1,1},INFINITY,true);});
    Reject([&]{Sweep(guard,{1e99,0},{1,1},.5,true);});
    Check(SegmentBox2({-1,.5},{2,.5},0,0)==0,"Crossing segment");
    Check(SegmentBox2({-1,2},{-1,3},0,0)==2,"Disjoint segment");
    std::cout<<"PASS: swept brush, tangency, clipping, all border neighborhoods, finite input and sampling tests\n";
}
void HistoryTests() {
    Document d(Grid(4));
    d.begin({.5,.5},.25,true);d.move({2.5,.5});d.end({3.5,.5});Check(d.grid().count()==4 && !d.active(),"Finish outside/inside stroke");
    d.undo();Check(d.grid().count()==0,"One stroke one undo");d.redo();Check(d.grid().count()==4,"Redo stroke");
    d.begin({.5,1.5},.25,true);d.move({2.5,1.5});d.cancel();Check(d.grid().count()==4,"Escape/capture loss restores pre-stroke");
    d.cancel();Check(d.grid().count()==4,"Capture release after end cannot revert committed stroke");
    d.clear();Check(d.grid().count()==0,"Clear");d.undo();Check(d.grid().count()==4,"Undo Clear");
    d.begin({.5,2.5},.25,true);d.end({.5,2.5});Check(!d.canRedo(),"New edit discards redo");
    const auto n=d.grid().count();d.begin({.5,2.5},.25,true);d.end({.5,2.5});d.undo();Check(d.grid().count()==n-1,"Noop stroke doesn't add undo");
    d.reset(Grid(3));Check(!d.canUndo()&&!d.canRedo()&&d.grid().count()==0,"New document resets history");
    Reject([&]{d.begin({-1,0},.25,true);});
    d.begin({.5,.5},.25,true);Reject([&]{d.begin({.5,.5},.25,true);});d.cancel();
    for(int i=0;i<140;++i) { d.begin({.5,.5},.25,i%2==0);d.end({.5,.5}); }
    Check(d.dropped()==12,"History is bounded");
    int undo=0;while(d.canUndo()){d.undo();++undo;}Check(undo==128,"Only last 128 changes retained");
    std::cout<<"PASS: stroke commit/cancel, no-op, Clear, undo/redo branch, reset and bounded history\n";
}
int main(int argc,char** argv) {
    try { TopologyTests(argc==2?std::filesystem::path(argv[1]):std::filesystem::path()); BrushTests(); HistoryTests();return 0; }
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
