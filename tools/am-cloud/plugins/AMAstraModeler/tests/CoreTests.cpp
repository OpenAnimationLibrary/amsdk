#include "../source/ModelPlan.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
int checks = 0;
void Check(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
template<class Function> void Reject(Function function, const char* message) {
    ++checks;
    try { function(); } catch (const std::exception&) { return; }
    throw std::runtime_error(message);
}

std::string ValidPlan() {
    return R"JSON({
      "name":"Astra Test Model",
      "description":"All procedural component kinds.",
      "materials":[
        {"name":"Red","color":[0.8,0.1,0.1],"finish":"matte","opacity":1},
        {"name":"Glass","color":[0.2,0.6,0.9],"finish":"glass","opacity":0.35}
      ],
      "components":[
        {"kind":"box","name":"Body","material":0,"center":[0,0,0],"rotation":[0,0,0],"size":[10,20,30]},
        {"kind":"ellipsoid","name":"Head","material":0,"center":[0,20,0],"rotation":[0,0,0],"radii":[5,6,5],"detail":1},
        {"kind":"torus","name":"Ring","material":1,"center":[0,0,0],"rotation":[90,0,0],"major_radius":8,"minor_radius":2,"major_segments":8,"minor_segments":4},
        {"kind":"tube","name":"Arm","material":0,"start":[-5,5,0],"end":[-15,10,0],"radius_start":2,"radius_end":1.5,"sides":6},
        {"kind":"lathe","name":"Vase","material":1,"center":[20,0,0],"rotation":[0,0,0],"segments":8,"profile":[[3,0],[5,5],[2,10]]},
        {"kind":"patch_grid","name":"Cape","material":0,"rows":2,"columns":3,"smooth":true,"points":[[-4,8,1],[0,8,2],[4,8,1],[-6,0,3],[0,0,5],[6,0,3]]}
      ]
    })JSON";
}
}

int main() {
    try {
        {
            const auto value = amjson::parse(R"({"text":"line\n\u263a","array":[true,false,null,-1.25e2]})");
            Check(value.at("text").as_string().find("line\n") == 0, "JSON escape decode failed");
            const auto roundTrip = amjson::parse(amjson::dump(value));
            Check(roundTrip.at("array").as_array()[3].as_number() == -125, "JSON round trip failed");
            Reject([] { amjson::parse(R"({"a":1,"a":2})"); }, "Duplicate JSON key accepted");
            Reject([] { amjson::parse(R"("\ud800")"); }, "Unpaired surrogate accepted");
        }
        {
            const auto request = amjson::parse(amastra::BuildRequestJson("Build a red robot.", 12, 1500));
            Check(request.at("model").as_string() == "gpt-6-astra", "Wrong API model");
            Check(request.at("store").as_bool() == false, "API storage was not disabled");
            Check(request.at("parallel_tool_calls").as_bool() == false, "Parallel tool calls were not disabled");
            Check(request.at("reasoning").at("effort").as_string() == "high", "Wrong reasoning effort");
            Check(request.at("tool_choice").at("name").as_string() == "build_animation_master_model", "Tool not forced");
            const auto& tool = request.at("tools").as_array().at(0);
            Check(tool.at("strict").as_bool(), "Strict function schema disabled");
            Check(tool.at("parameters").at("additionalProperties").as_bool() == false, "Plan schema accepts extra fields");
            Check(request.find("temperature") == nullptr && request.find("top_p") == nullptr,
                  "Unsupported sampling fields were sent");
            Reject([] { amastra::BuildRequestJson("", 12, 1500); }, "Empty prompt accepted");
        }
        {
            const std::string arguments = ValidPlan();
            const auto envelope = amjson::Value::object({
                {"id","resp_test"},{"status","completed"},
                {"output",amjson::Value::array({amjson::Value::object({
                    {"type","reasoning"},{"content",amjson::Value::Array{}}}),
                    amjson::Value::object({{"type","function_call"},{"name","build_animation_master_model"},{"arguments",arguments},{"call_id","call_test"}})})},
                {"usage",amjson::Value::object({{"input_tokens",100},{"output_tokens",200}})}
            });
            const auto extracted = amastra::ExtractApiResult(amjson::dump(envelope), "req_test");
            Check(extracted.responseId == "resp_test" && extracted.requestId == "req_test", "API identifiers lost");
            Check(extracted.arguments == arguments, "Function arguments changed");
            Check(extracted.inputTokens == 100 && extracted.outputTokens == 200, "Usage not parsed");
            Reject([] { amastra::ExtractApiResult(R"({"id":"x","status":"incomplete","output":[]})"); }, "Incomplete response accepted");
            Reject([] { amastra::ExtractApiResult(R"({"error":{"message":"bad request"}})"); }, "API error accepted");
        }
        {
            auto plan = amastra::ParseModelPlan(amjson::parse(ValidPlan()));
            Check(plan.components.size() == 6 && plan.materials.size() == 2, "Plan count mismatch");
            const auto prepared = amastra::PreparePlan(std::move(plan), 1000);
            Check(prepared.patches == 86, "Unexpected generated patch count");
            Check(prepared.parts.size() == 6, "Part count mismatch");
            Check(prepared.splinePaths > 0 && prepared.controlPointRecords > prepared.vertices, "Spline routing summary invalid");
            const auto matte = amastra::SurfaceForMaterial(prepared.source.materials[0]);
            const auto glass = amastra::SurfaceForMaterial(prepared.source.materials[1]);
            Check(matte.transparency == 0 && matte.reflectivity == 0, "Matte surface mapping changed");
            Check(std::abs(glass.transparency - .65) < 1e-12 && glass.refraction == 1.5,
                  "Glass surface mapping changed");
            for (const auto& part : prepared.parts) {
                Check(!part.splines.paths.empty(), "Part has no spline paths");
                for (auto count : part.splines.occurrences) Check(count >= 1 && count <= 2, "A point exceeds two spline records");
            }
            Reject([] { amastra::PreparePlan(amastra::ParseModelPlan(amjson::parse(ValidPlan())), 85); }, "Patch budget not enforced");
        }
        {
            auto malformed = amjson::parse(ValidPlan());
            malformed.as_object().at("components").as_array()[0].as_object().at("material") = 15;
            Reject([&] { amastra::ParseModelPlan(malformed); }, "Invalid material index accepted");
            auto collapsed = amjson::parse(ValidPlan());
            auto& points = collapsed.as_object().at("components").as_array().back().as_object().at("points").as_array();
            points[1] = points[0];
            Reject([&] { amastra::PreparePlan(amastra::ParseModelPlan(collapsed), 1000); }, "Collapsed grid accepted");
            auto unknown = amjson::parse(ValidPlan());
            unknown.as_object().at("components").as_array()[0].as_object().emplace("surprise", true);
            Reject([&] { amastra::ParseModelPlan(unknown); }, "Unknown component field accepted");
        }
        std::cout << "AMAstraModeler core tests passed: " << checks << " checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAILED after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}
