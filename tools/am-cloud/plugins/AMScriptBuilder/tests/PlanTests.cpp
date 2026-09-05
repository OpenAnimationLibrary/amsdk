#include "../Plan.h"
#include "../FivePoint.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

const std::string valid = R"({"am_plan":1,"name":"Test","points":[[0,0,0],[10,0,0],[20,10,0]],"splines":[[0,1,2]]})";
void Check(bool good) { if (!good) throw std::runtime_error("Test assertion failed"); }
void Reject(const std::string& value) {
    try { (void)amscript::Parse(value); }
    catch (const std::exception&) { return; }
    throw std::runtime_error("Accepted invalid plan: " + value.substr(0, 200));
}
std::string Replace(std::string value, const std::string& old, const std::string& changed) {
    const auto pos = value.find(old); Check(pos != value.npos); value.replace(pos, old.size(), changed); return value;
}
int main(int argc, char** argv) {
    try {
        if (argc == 2) {
            std::ifstream file(argv[1], std::ios::binary);
            if (!file) throw std::runtime_error("Cannot open plan fixture");
            const std::string data((std::istreambuf_iterator<char>(file)), {});
            const auto plan = amscript::Parse(data);
            std::cout << plan.points.size() << ' ' << plan.splines.size() << ' ' << plan.occurrences << ' ' << plan.attachments
                      << ' ' << amscript::FivePointCandidates(plan).size() << '\n';
            return 0;
        }
        const auto plan = amscript::Parse(valid);
        Check(plan.points.size() == 3 && plan.splines.size() == 1 && plan.occurrences == 3 && plan.attachments == 0);
        Check(amscript::FivePointCandidates(plan).empty());
        for (const auto& text : {"", "{}", "[]", "null", "true", "{{", "\xEF\xBB\xBF{}"}) Reject(text);
        Reject(std::string(amscript::MaxBytes + 1, ' '));
        Reject(valid + "x"); Reject(valid + valid);
        Reject(Replace(valid, "\"am_plan\":1", "\"am_plan\":1,\"am_plan\":1"));
        Reject(Replace(valid, "\"am_plan\":1", "\"other\":1"));
        for (const auto& number : {"2", "1.0", "1e0", "true", "-0", "-1", "01", "+1", "9999999999999999999999"})
            Reject(Replace(valid, "\"am_plan\":1", std::string("\"am_plan\":") + number));
        for (const auto& number : {"NaN", "Infinity", "1e999", "1e-999", "1e-99", "+1", "01", ".1", "1.", "1e", "100001", "-100001", "null", "true"})
            Reject(Replace(valid, "[0,0,0]", std::string("[") + number + ",0,0]"));
        for (const auto& indexes : {"[]", "[[]]", "[[0]]", "[[0,1,3]]", "[[0,1,0]]", "[[0,1]]", "[[0,1.0,2]]", "[[0,true,2]]", "[[0,-1,2]]", "[[0,1,2],[1,0]]", "[[0,1],[0,2],[0,1]]"})
            Reject(Replace(valid, "[[0,1,2]]", indexes));
        Reject(Replace(valid, "[10,0,0]", "[0,0,0]"));
        Reject(Replace(valid, "[20,10,0]", "[10.00000001,0,0]"));
        Reject(Replace(valid, "\"Test\"", "\"Bad\\nName\""));
        Reject(Replace(valid, "\"Test\"", "\" Bad\""));
        Reject(Replace(valid, "\"Test\"", "\"Bad/Name\""));
        Reject(Replace(valid, "\"Test\"", "\"" + std::string(65, 'x') + "\""));
        Reject(Replace(valid, "[0,0,0]", "[0,0,0,0]"));
        Reject(Replace(valid, "[0,0,0]", "[0,0]"));
        Reject(Replace(valid, "[0,0,0]", "[[0],0,0]"));
        const auto shared = amscript::Parse(Replace(valid, "[[0,1,2]]", "[[0,1],[1,2]]"));
        Check(shared.attachments == 1 && shared.occurrences == 4);
        const auto reordered = amscript::Parse(R"({"splines":[[0,1]],"points":[[0,0,0],[1e1,-2.5,0]],"name":"Order","am_plan":1})");
        Check(reordered.points[1][0] == 10);
        const auto five = amscript::Parse(R"({"am_plan":1,"name":"Five","points":[[0,1,0],[1,1,0],[2,0,0],[1,-1,0],[0,-1,0]],"splines":[[0,1],[1,2],[2,3],[3,4],[4,0]]})");
        const auto candidates = amscript::FivePointCandidates(five);
        Check(candidates.size() == 1 && candidates[0] == amscript::FiveCycle{0,1,2,3,4});
        // Broader chord rejection is covered by the standalone Python analyzer;
        // v1 native plans intentionally reject degree-3 logical points first.
        for (std::size_t i = 0; i < valid.size(); ++i) Reject(valid.substr(0, i));
        std::cout << "PASS: strict plan parser, topology limits, five-point candidates and truncated-input cases\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
