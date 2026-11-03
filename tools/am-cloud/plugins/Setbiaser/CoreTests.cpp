#include "BiasCore.h"
#include <iostream>
#include <functional>
#include <cstring>
#include <random>
static int checks = 0;
static void require(bool condition) { ++checks; if (!condition) throw std::runtime_error("Regression check failed: " + std::to_string(checks)); }
static void close(double a, double b) { require(std::abs(a-b) < 0.00003); }
static void rejects(const std::function<void()> &f) { bool caught = false; try { f(); } catch (const std::exception &) { caught = true; } require(caught); }
int main() {
    try {
        const sb::Units u;
        sb::Values a{0.75F, 1.25F, -0.0872664626F, 0.174532925F, 0.25F, -0.5F};
        const auto saved = a;
        for (std::size_t field = 0; field < 6; ++field) {
            for (bool linked : {false, true}) {
                for (auto op : {sb::Operation::Set, sb::Operation::Offset, sb::Operation::Scale}) {
                    if (op == sb::Operation::Scale && field >= 2) { rejects([&] { sb::calculate(a,u,{field,op,1.1,linked}); }); continue; }
                    const double input = op == sb::Operation::Set ? 12.5 : op == sb::Operation::Offset ? 3.0 : 1.1;
                    const auto out = sb::calculate(a,u,{field,op,input,linked});
                    for (std::size_t f = 0; f < 6; ++f) {
                        if (f == field || (linked && f == (field ^ std::size_t{1}))) {
                            const double expected = op == sb::Operation::Set ? input/u.factor[f/2] :
                                op == sb::Operation::Offset ? double(a[f])+input/u.factor[f/2] : double(a[f])*input;
                            close(out[f],expected);
                        } else require(std::memcmp(&out[f],&a[f],sizeof(float)) == 0);
                    }
                    require(a == saved);
                }
            }
        }
        auto out = sb::calculate(a,u,{0,sb::Operation::Scale,1.1,true});
        close(u.display(out[0],0),82.5); close(u.display(out[1],1),137.5);
        out = sb::calculate(a,u,{2,sb::Operation::Offset,3,true});
        close(u.display(out[2],2),-2); close(u.display(out[3],3),13);
        out = sb::calculate(a,u,{0,sb::Operation::Scale,1.2,true});
        close(u.display(out[0],0),90); close(u.display(out[1],1),150);
        for (std::size_t f=0; f<6; ++f) {
            require(sb::calculate(a,u,{f,sb::Operation::Offset,0,true}) == a);
            close(sb::calculate(a,u,{f,sb::Operation::Set,u.display(a[f],f),false})[f],a[f]);
        }
        require(sb::calculate(a,u,{0,sb::Operation::Scale,1,true}) == a);
        out=sb::calculate(a,u,{0,sb::Operation::Set,0,false,true});
        for (std::size_t f=0; f<6; ++f) close(u.display(out[f],f),f<2?100:0);
        require(!sb::common({},0)); require(sb::common({a,a},2).value()==a[2]);
        auto b=a; b[2]=0; require(!sb::common({a,b},2)); require(sb::common({a,b},0).value()==a[0]);
        rejects([&] { sb::calculate(a,u,{0,sb::Operation::Set,-1}); });
        rejects([&] { sb::calculate(a,u,{0,sb::Operation::Scale,-1}); });
        rejects([&] { sb::calculate(a,u,{6,sb::Operation::Set,1}); });
        rejects([&] { sb::calculate(a,u,{0,sb::Operation::Scale,1e300}); });
        rejects([&] { sb::calculate(a,u,{0,sb::Operation::Set,std::numeric_limits<double>::infinity()}); });
        auto bad=u; bad.factor[0]=0; rejects([&] { sb::calculate(a,bad,{}); });
        bad=u; bad.maximum[1]=-100; rejects([&] { sb::calculate(a,bad,{2,sb::Operation::Set,0}); });
        for (const char *invalid : {"", "Mixed", "nan", "inf", "1x", "1,2", "--3", "0x10", "1e999", "+"}) rejects([&] { sb::parse(invalid); });
        close(sb::parse(" -1.25 "),-1.25); close(sb::parse("+2.5e1"),25); close(sb::parse(".5"),.5);
        std::mt19937 random(20261103);
        std::uniform_real_distribution<float> magnitude(0.001F,10.F);
        for (int sample=0; sample<1000; ++sample) {
            sb::Values baseline{magnitude(random),magnitude(random),.1F,-.2F,.3F,-.4F};
            const auto scaled=sb::calculate(baseline,u,{0,sb::Operation::Scale,1.17,true});
            close(scaled[0],double(baseline[0])*1.17); close(scaled[1],double(baseline[1])*1.17);
            for (std::size_t f=2;f<6;++f) require(scaled[f]==baseline[f]);
        }
        std::cout << "PASS: " << checks << " Setbiaser core checks. Host behavior is not tested.\n";
        return 0;
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
