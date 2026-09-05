#pragma once
// SDK-independent stage-B document and compiler. No Windows, host or file calls.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <locale>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

namespace patchdraw {
constexpr int MaxSide = 16;
constexpr std::size_t HistoryLimit = 128;
struct XY { double x = 0, y = 0; };
struct Grid {
    int side = 8;
    int cellSize = 10; // Raw model units per DRAWING cell; always XY, Z=0.
    std::array<bool, MaxSide * MaxSide> cells{};
    explicit Grid(int n = 8, int size = 10) : side(n), cellSize(size) {
        if (n < 1 || n > MaxSide || size < 1 || size > 1000)
            throw std::invalid_argument("Grid: 1-16 cells per side; cell size: 1-1000.");
    }
    bool get(int x, int y) const {
        return x >= 0 && y >= 0 && x < side && y < side &&
            cells[static_cast<std::size_t>(y * MaxSide + x)];
    }
    void set(int x, int y, bool value) {
        if (x < 0 || y < 0 || x >= side || y >= side)
            throw std::out_of_range("Cell outside drawing.");
        cells[static_cast<std::size_t>(y * MaxSide + x)] = value;
    }
    std::size_t count() const {
        return static_cast<std::size_t>(std::count(cells.begin(), cells.end(), true));
    }
    bool operator==(const Grid&) const = default;
};

inline XY Quantized(XY p) {
    for (double a : {p.x, p.y})
        if (!std::isfinite(a) || std::abs(a) > 1000000.0)
            throw std::invalid_argument("Nonfinite or excessive pointer coordinate.");
    return {std::round(p.x * 1024.0) / 1024.0, std::round(p.y * 1024.0) / 1024.0};
}
inline double PointSegment2(XY p, XY a, XY b) {
    const double dx = b.x-a.x, dy = b.y-a.y, den = dx*dx+dy*dy;
    const double t = den ? std::clamp(((p.x-a.x)*dx+(p.y-a.y)*dy)/den, 0.0, 1.0) : 0;
    const double x = p.x-a.x-t*dx, y = p.y-a.y-t*dy;
    return x*x+y*y;
}
inline double PointBox2(XY p, double x, double y) {
    const double dx = p.x-std::clamp(p.x,x,x+1), dy = p.y-std::clamp(p.y,y,y+1);
    return dx*dx+dy*dy;
}
inline double SegmentBox2(XY a, XY b, double x, double y) {
    double lo = 0, hi = 1;
    bool intersects = true;
    for (int axis = 0; axis != 2; ++axis) {
        const double origin = axis ? a.y : a.x, delta = axis ? b.y-a.y : b.x-a.x;
        const double minimum = axis ? y : x;
        if (delta == 0) {
            if (origin < minimum || origin > minimum+1) intersects = false;
        } else {
            double first = (minimum-origin)/delta, last = (minimum+1-origin)/delta;
            if (first > last) std::swap(first,last);
            lo = std::max(lo,first); hi = std::min(hi,last);
        }
    }
    if (intersects && lo <= hi) return 0;
    double distance = std::min(PointBox2(a,x,y),PointBox2(b,x,y));
    for (XY corner : {XY{x,y}, XY{x+1,y}, XY{x+1,y+1}, XY{x,y+1}})
        distance = std::min(distance, PointSegment2(corner,a,b));
    return distance;
}
inline void Sweep(Grid& grid, XY a, XY b, double radius, bool paint) {
    a = Quantized(a); b = Quantized(b);
    if (!std::isfinite(radius) || radius < 0.125 || radius > 8)
        throw std::invalid_argument("Brush radius outside supported range.");
    // Positive-area intersection of cell and swept disk. Tangency alone does
    // not paint. Iterate only the bounded document, never index by raw input.
    for (int y=0; y<grid.side; ++y) for (int x=0; x<grid.side; ++x)
        if (SegmentBox2(a,b,x,y) < radius*radius) grid.set(x,y,paint);
}

class Document {
    Grid grid_, before_;
    std::deque<Grid> undo_, redo_;
    bool active_ = false, paint_ = true;
    double radius_ = .25;
    XY previous_{};
    std::size_t dropped_ = 0;
    void commit(const Grid& previous) {
        if (grid_ == previous) return;
        undo_.push_back(previous); // Allocate before dropping any old history.
        if (undo_.size() > HistoryLimit) { undo_.pop_front(); ++dropped_; }
        redo_.clear();
    }
public:
    explicit Document(Grid value = Grid()) : grid_(value), before_(value) {}
    const Grid& grid() const { return grid_; }
    bool active() const { return active_; }
    bool canUndo() const { return !active_ && !undo_.empty(); }
    bool canRedo() const { return !active_ && !redo_.empty(); }
    std::size_t dropped() const { return dropped_; }
    void begin(XY p, double radius, bool paint) {
        if (active_) throw std::logic_error("Stroke already active.");
        p = Quantized(p);
        if (p.x < 0 || p.y < 0 || p.x >= grid_.side || p.y >= grid_.side)
            throw std::invalid_argument("Begin stroke inside the canvas.");
        before_ = grid_; radius_ = radius; paint_ = paint; previous_ = p;
        try { Sweep(grid_,p,p,radius_,paint_); active_ = true; }
        catch (...) { grid_ = before_; throw; }
    }
    void move(XY p) {
        if (!active_) return;
        p = Quantized(p); Sweep(grid_,previous_,p,radius_,paint_); previous_ = p;
    }
    void end(XY p) {
        if (!active_) return;
        try { move(p); commit(before_); active_ = false; }
        catch (...) { cancel(); throw; }
    }
    void cancel() noexcept { if (active_) { grid_ = before_; active_ = false; } }
    void clear() {
        if (active_) throw std::logic_error("Finish stroke before Clear.");
        const Grid old = grid_; grid_.cells.fill(false);
        try { commit(old); } catch (...) { grid_ = old; throw; }
    }
    void undo() {
        if (!canUndo()) return;
        redo_.push_back(grid_); grid_ = undo_.back(); undo_.pop_back();
    }
    void redo() {
        if (!canRedo()) return;
        undo_.push_back(grid_); grid_ = redo_.back(); redo_.pop_back();
    }
    void reset(Grid value) { cancel(); grid_ = value; undo_.clear(); redo_.clear(); dropped_ = 0; }
};

using Cell = std::pair<int,int>;
using Edge = std::array<std::size_t,2>;
using Face = std::array<std::size_t,4>;
inline Edge OrderedEdge(std::size_t a, std::size_t b) { return a < b ? Edge{a,b} : Edge{b,a}; }
struct Topology {
    std::vector<Cell> vertices; // Coordinates in half-cell integer lattice.
    std::vector<Face> faces;
    std::vector<Cell> faceCells; // Stable fine-cell IDs; not native patch IDs.
    std::vector<Edge> edges;
    std::vector<std::vector<std::size_t>> splines;
    std::vector<int> components; // Per vertex; suitable for a component preview.
    std::size_t occurrences = 0;
    int componentCount = 0, holeCount = 0;
};
inline Topology Compile(const Grid& grid) {
    if (grid.side<1 || grid.side>MaxSide || grid.cellSize<1 || grid.cellSize>1000)
        throw std::invalid_argument("Invalid document dimensions.");
    std::set<Cell> fine;
    for (int y=0;y<grid.side;++y) for(int x=0;x<grid.side;++x) if(grid.get(x,y))
        for(int dy=0;dy<2;++dy) for(int dx=0;dx<2;++dx) fine.emplace(2*x+dx,2*y+dy);
    std::map<Cell,std::set<Cell>> around;
    for(auto [x,y] : fine) for(Cell v : {Cell{x,y},{x+1,y},{x+1,y+1},{x,y+1}}) around[v].insert({x,y});
    using Corner = std::tuple<int,int,int,int>;
    std::map<Corner,std::size_t> identity;
    Topology out;
    // Split only local edge-connected face fans. A distant path connecting two
    // diagonal fans is NOT permission to weld their common coordinate.
    for(const auto& [v,incident] : around) {
        auto pending = incident;
        while(!pending.empty()) {
            std::vector<Cell> fan{*pending.begin()}; pending.erase(pending.begin());
            for(std::size_t i=0;i<fan.size();++i) {
                for(auto it=pending.begin();it!=pending.end();) {
                    if(std::abs(it->first-fan[i].first)+std::abs(it->second-fan[i].second)==1) {
                        fan.push_back(*it); it=pending.erase(it);
                    } else ++it;
                }
            }
            const auto id=out.vertices.size(); out.vertices.push_back(v);
            for(auto f : fan) identity.emplace(Corner{v.first,v.second,f.first,f.second},id);
        }
    }
    std::map<Edge,unsigned> uses;
    for(auto [x,y] : fine) {
        Face face{}; std::size_t i=0;
        for(Cell v : {Cell{x,y},{x+1,y},{x+1,y+1},{x,y+1}})
            face[i++]=identity.at({v.first,v.second,x,y});
        out.faces.push_back(face); out.faceCells.emplace_back(x,y);
        for(i=0;i<4;++i) ++uses[OrderedEdge(face[i],face[(i+1)%4])];
    }
    std::vector<std::vector<std::size_t>> adjacency(out.vertices.size());
    std::vector<unsigned> boundary(out.vertices.size(),0);
    for(const auto& [e,n] : uses) {
        if(n!=1 && n!=2) throw std::logic_error("Nonmanifold edge.");
        out.edges.push_back(e); adjacency[e[0]].push_back(e[1]); adjacency[e[1]].push_back(e[0]);
        if(n==1) { ++boundary[e[0]]; ++boundary[e[1]]; }
    }
    for(auto n:boundary) if(n!=0 && n!=2) throw std::logic_error("Nonmanifold boundary vertex.");
    out.components.assign(out.vertices.size(),-1);
    for(std::size_t start=0;start<out.vertices.size();++start) if(out.components[start]<0) {
        std::vector<std::size_t> todo{start}; out.components[start]=out.componentCount;
        for(std::size_t i=0;i<todo.size();++i) for(auto v:adjacency[todo[i]]) if(out.components[v]<0) {
            out.components[v]=out.componentCount; todo.push_back(v);
        }
        ++out.componentCount;
    }
    out.holeCount=out.componentCount-static_cast<int>(out.vertices.size())+
        static_cast<int>(out.edges.size())-static_cast<int>(out.faces.size());
    if(out.holeCount<0) throw std::logic_error("Invalid planar Euler characteristic.");
    const auto none=out.vertices.size();
    for(int axis=0;axis<2;++axis) {
        std::vector<std::size_t> next(none,none), previous(none,none);
        for(auto e:out.edges) {
            auto a=e[0], b=e[1]; const auto va=out.vertices[a], vb=out.vertices[b];
            if((axis==0 && va.second!=vb.second) || (axis==1 && va.first!=vb.first)) continue;
            if((axis==0 && va.first>vb.first) || (axis==1 && va.second>vb.second)) std::swap(a,b);
            if(next[a]!=none || previous[b]!=none) throw std::logic_error("Ambiguous spline run.");
            next[a]=b; previous[b]=a;
        }
        for(std::size_t a=0;a<none;++a) if(previous[a]==none && next[a]!=none) {
            std::vector<std::size_t> run;
            for(auto b=a;b!=none;b=next[b]) {
                if(run.size()>none) throw std::logic_error("Cyclic straight run.");
                run.push_back(b);
            }
            out.occurrences+=run.size(); out.splines.push_back(std::move(run));
        }
    }
    std::vector<unsigned> usage(out.vertices.size(),0);
    for(const auto& s:out.splines) for(auto v:s) ++usage[v];
    for(auto n:usage) if(n!=2) throw std::logic_error("Each vertex must occur in both spline families.");
    return out;
}
inline std::string ExportProblem(const Topology& t) {
    if(t.faces.empty()) return "Draw at least one cell before exporting.";
    if(t.vertices.size()>1024 || t.splines.size()>128 || t.occurrences>2048)
        return "Drawing exceeds Script Builder v1 limits (1024 points / 128 splines / 2048 CP records). Use a smaller drawing or fewer separated islands. Nothing was truncated.";
    for(const auto& s:t.splines) if(s.size()<2 || s.size()>256)
        return "A spline exceeds Script Builder v1 limits.";
    return {};
}
inline std::string ToPlan(const Grid& grid, const Topology& t) {
    const auto problem=ExportProblem(t);
    if(!problem.empty()) throw std::runtime_error(problem);
    std::ostringstream text; text.imbue(std::locale::classic()); text<<std::setprecision(9);
    text<<"{\n  \"am_plan\": 1,\n  \"name\": \"Patch Draw Canvas\",\n  \"points\": [\n";
    for(std::size_t i=0;i<t.vertices.size();++i) {
        const auto [x,y]=t.vertices[i];
        text<<"    ["<<(x-grid.side)*grid.cellSize/2.0<<", "<<(y-grid.side)*grid.cellSize/2.0<<", 0]";
        text<<(i+1==t.vertices.size()?"\n":",\n");
    }
    text<<"  ],\n  \"splines\": [\n";
    for(std::size_t i=0;i<t.splines.size();++i) {
        text<<"    [";
        for(std::size_t j=0;j<t.splines[i].size();++j) { if(j) text<<", "; text<<t.splines[i][j]; }
        text<<"]"<<(i+1==t.splines.size()?"\n":",\n");
    }
    text<<"  ]\n}\n"; const auto bytes=text.str();
    if(bytes.size()>262144) throw std::runtime_error("Plan exceeds Script Builder byte limit.");
    return bytes;
}
} // namespace patchdraw
