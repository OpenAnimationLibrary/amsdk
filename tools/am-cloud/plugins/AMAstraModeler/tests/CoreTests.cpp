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

std::vector<unsigned char> PngFixture(std::uint32_t width = 3, std::uint32_t height = 2) {
    return {
        0x89, 'P', 'N', 'G', 0x0d, 0x0a, 0x1a, 0x0a,
        0, 0, 0, 13, 'I', 'H', 'D', 'R',
        static_cast<unsigned char>(width >> 24), static_cast<unsigned char>(width >> 16),
        static_cast<unsigned char>(width >> 8), static_cast<unsigned char>(width),
        static_cast<unsigned char>(height >> 24), static_cast<unsigned char>(height >> 16),
        static_cast<unsigned char>(height >> 8), static_cast<unsigned char>(height),
        8, 2, 0, 0, 0, 0, 0, 0, 0
    };
}

std::vector<unsigned char> JpegFixture() {
    return {0xff, 0xd8, 0xff, 0xc0, 0x00, 0x0b, 0x08, 0x00, 0x02, 0x00,
            0x03, 0x01, 0x01, 0x11, 0x00, 0xff, 0xd9};
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
            const auto textOnlyJson = amastra::BuildRequestJson("Build a red robot.", 12, 1500);
            Check(textOnlyJson.find("data:image/") == std::string::npos &&
                  textOnlyJson.find("input_image") == std::string::npos,
                  "Text-only request contains image data");
            const auto request = amjson::parse(textOnlyJson);
            Check(request.at("model").as_string() == "gpt-6-astra", "Wrong API model");
            Check(request.at("input").as_string() == "Build a red robot.",
                  "Text-only request input changed");
            Check(request.at("instructions").as_string().find("A reference image is attached") ==
                      std::string::npos,
                  "Text-only request contains image instructions");
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
            const auto maximumRequest = amjson::parse(amastra::BuildRequestJson("Build a detailed model.", 100, 2000));
            const auto& maximumComponents = maximumRequest.at("tools").as_array().at(0).at("parameters")
                                                 .at("properties").at("components");
            Check(maximumComponents.at("maxItems").as_number() == 100,
                  "100-component request schema was not preserved");
            const auto clampedRequest = amjson::parse(amastra::BuildRequestJson("Build a detailed model.", 101, 2000));
            const auto& clampedComponents = clampedRequest.at("tools").as_array().at(0).at("parameters")
                                                 .at("properties").at("components");
            Check(clampedComponents.at("maxItems").as_number() == 100,
                  "Component request schema was not clamped to the hard maximum");
        }
        {
            Check(amastra::Base64Encode({}) == "", "Empty Base64 vector changed");
            Check(amastra::Base64Encode({'M'}) == "TQ==", "One-byte Base64 encoding failed");
            Check(amastra::Base64Encode({'M', 'a'}) == "TWE=", "Two-byte Base64 encoding failed");
            Check(amastra::Base64Encode({'M', 'a', 'n'}) == "TWFu", "Three-byte Base64 encoding failed");
            Check(amastra::Base64Encode({0, 1, 2, 0xfd, 0xfe, 0xff}) == "AAEC/f7/",
                  "Binary Base64 encoding failed");

            const auto png = amastra::PrepareReferenceImage("subject.jpg", PngFixture());
            Check(png.metadata.mimeType == "image/png", "PNG magic was not authoritative");
            Check(png.metadata.fileName == "subject.jpg", "Reference-image basename changed");
            Check(png.metadata.width == 3 && png.metadata.height == 2, "PNG dimensions were not read");
            Check(png.metadata.byteSize == PngFixture().size(), "PNG byte size was not retained");
            Check(!png.base64.empty() && png.base64.find('\n') == std::string::npos,
                  "PNG Base64 is empty or wrapped");

            const auto jpeg = amastra::PrepareReferenceImage("subject.jpeg", JpegFixture());
            Check(jpeg.metadata.mimeType == "image/jpeg", "JPEG MIME detection failed");
            Check(jpeg.metadata.width == 3 && jpeg.metadata.height == 2,
                  "JPEG dimensions were not read");

            Reject([] { amastra::PrepareReferenceImage("empty.png", {}); },
                   "Empty reference image accepted");
            Reject([] { amastra::PrepareReferenceImage("bad.png", {1, 2, 3, 4}); },
                   "Unsupported reference image accepted");
            Reject([] {
                auto shortPng = PngFixture();
                shortPng.resize(12);
                amastra::PrepareReferenceImage("short.png", shortPng);
            }, "Truncated PNG accepted");
            Reject([] {
                auto zero = PngFixture(0, 2);
                amastra::PrepareReferenceImage("zero.png", zero);
            }, "Zero-width PNG accepted");
            Reject([] {
                auto tooManyPixels = PngFixture(8193, 8193);
                amastra::PrepareReferenceImage("huge.png", tooManyPixels);
            }, "Reference image above the pixel limit accepted");
            Reject([] { amastra::PrepareReferenceImage("no-frame.jpg", {0xff, 0xd8, 0xff, 0xd9}); },
                   "JPEG without a frame header accepted");
            Reject([] { amastra::PrepareReferenceImage("unsupported.webp",
                                                        {'R', 'I', 'F', 'F', 4, 0, 0, 0,
                                                         'W', 'E', 'B', 'P'}); },
                   "Unsupported WebP accepted");
            Reject([] { amastra::PrepareReferenceImage("folder/subject.png", PngFixture()); },
                   "Reference-image path accepted as a basename");
            Reject([] {
                std::vector<unsigned char> oversized(amastra::MaxReferenceImageBytes + 1, 0);
                amastra::PrepareReferenceImage("large.png", oversized);
            }, "Oversized reference image accepted");

            const auto serialized = amastra::BuildRequestJson("Match the pictured vehicle.", 100, 2000,
                                                               &png);
            Check(serialized.size() <= amastra::MaxRequestBytes, "Image request exceeds request limit");
            const auto request = amjson::parse(serialized);
            const auto& input = request.at("input").as_array();
            Check(input.size() == 1 && input[0].at("role").as_string() == "user",
                  "Image request user message is malformed");
            const auto& content = input[0].at("content").as_array();
            Check(content.size() == 2, "Image request content count changed");
            Check(content[0].at("type").as_string() == "input_text" &&
                  content[0].at("text").as_string() == "Match the pictured vehicle.",
                  "Image request prompt changed");
            Check(content[1].at("type").as_string() == "input_image" &&
                  content[1].at("detail").as_string() == "high",
                  "Image request type or detail changed");
            Check(content[1].at("image_url").as_string() ==
                      "data:image/png;base64," + png.base64,
                  "Image data URL changed");
            Check(request.at("instructions").as_string().find("A reference image is attached") !=
                      std::string::npos,
                  "Image-specific modeling instruction is missing");
            Check(request.at("store").as_bool() == false, "Image request enabled API storage");
            Check(serialized.find("subject.jpg") == std::string::npos,
                  "Image basename leaked into API request");

            auto badMime = png;
            badMime.metadata.mimeType = "image/gif";
            Reject([&] { amastra::BuildRequestJson("Use this image.", 100, 2000, &badMime); },
                   "Unsupported image MIME accepted by request builder");
            auto shortBase64 = png;
            shortBase64.base64.pop_back();
            Reject([&] { amastra::BuildRequestJson("Use this image.", 100, 2000, &shortBase64); },
                   "Truncated image Base64 accepted by request builder");
        }
        {
            const std::string encoded(256, 'A');
            const auto sanitized = amastra::SanitizeDiagnostic(
                "bad data:image/png;base64," + encoded + " and token " + encoded);
            Check(sanitized.find("data:image/") == std::string::npos,
                  "Diagnostic retained an image data URL");
            Check(sanitized.find(encoded) == std::string::npos,
                  "Diagnostic retained a long encoded value");
            Check(sanitized.find("[image data omitted]") != std::string::npos &&
                  sanitized.find("[long encoded value omitted]") != std::string::npos,
                  "Diagnostic redaction markers are missing");
            Check(amastra::SanitizeDiagnostic(std::string(3000, '!')).size() == 2048,
                  "Diagnostic length limit was not enforced");
            try {
                amastra::ExtractApiResult(
                    amjson::dump(amjson::Value::object({
                        {"error", amjson::Value::object({
                            {"message", "invalid data:image/jpeg;base64," + encoded}
                        })}
                    })));
                throw std::runtime_error("API error response was accepted");
            } catch (const amastra::Error& error) {
                const std::string message = error.what();
                Check(message.find("data:image/") == std::string::npos &&
                      message.find(encoded) == std::string::npos,
                      "API error exposed image data");
            }
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
            Reject([] { amastra::ExtractApiResult(R"({"id":"x","output":[]})"); }, "Response without status accepted");
            Reject([] { amastra::ExtractApiResult(R"({"error":{"message":"bad request"}})"); }, "API error accepted");
            Reject([&] {
                auto unexpected = envelope;
                unexpected.as_object().at("output").as_array().push_back(amjson::Value::object({
                    {"type","function_call"},{"name","unexpected"},{"arguments","{}"}}));
                amastra::ExtractApiResult(amjson::dump(unexpected));
            }, "Unexpected function call accepted");
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
            Reject([] { amastra::PreparePlan(amastra::ParseModelPlan(amjson::parse(ValidPlan())), 1000, 5); },
                   "Component budget not enforced");
        }
        {
            auto malformed = amjson::parse(ValidPlan());
            malformed.as_object().at("components").as_array()[0].as_object().at("material") = 15;
            Reject([&] { amastra::ParseModelPlan(malformed); }, "Invalid material index accepted");
            auto collapsed = amjson::parse(ValidPlan());
            auto& points = collapsed.as_object().at("components").as_array().back().as_object().at("points").as_array();
            points[1] = points[0];
            Reject([&] { amastra::PreparePlan(amastra::ParseModelPlan(collapsed), 1000); }, "Collapsed grid accepted");
            auto floatCollapsed = amjson::parse(ValidPlan());
            auto& nativePoints = floatCollapsed.as_object().at("components").as_array().back().as_object().at("points").as_array();
            nativePoints[0] = amjson::Value::array({10000.0,0,0});
            nativePoints[1] = amjson::Value::array({10000.0001,0,0});
            Reject([&] { amastra::PreparePlan(amastra::ParseModelPlan(floatCollapsed), 1000); },
                   "A:M float-precision collapse accepted");
            auto unknown = amjson::parse(ValidPlan());
            unknown.as_object().at("components").as_array()[0].as_object().emplace("surprise", true);
            Reject([&] { amastra::ParseModelPlan(unknown); }, "Unknown component field accepted");
        }
        {
            auto hundred = amjson::parse(ValidPlan());
            auto& components = hundred.as_object().at("components").as_array();
            const auto prototype = components.front();
            components.clear();
            for (std::size_t index = 0; index < amastra::MaxComponents; ++index) {
                auto component = prototype;
                component.as_object().at("name") = "Box" + std::to_string(index);
                component.as_object().at("center") = amjson::Value::array({static_cast<double>(index) * 20, 0, 0});
                components.push_back(std::move(component));
            }
            auto plan = amastra::ParseModelPlan(hundred);
            Check(plan.components.size() == 100, "100-component plan was not accepted");
            const auto prepared = amastra::PreparePlan(std::move(plan), 2000, 100);
            Check(prepared.parts.size() == 100 && prepared.patches == 600,
                  "100-component plan produced unexpected totals");
            Reject([&] { amastra::PreparePlan(amastra::ParseModelPlan(hundred), 2000, 99); },
                   "Requested 99-component limit was not enforced");
            Reject([&] { amastra::PreparePlan(amastra::ParseModelPlan(hundred), 2000, 101); },
                   "Requested component limit above 100 was accepted");
            auto extra = prototype;
            extra.as_object().at("name") = "Box100";
            extra.as_object().at("center") = amjson::Value::array({2000, 0, 0});
            hundred.as_object().at("components").as_array().push_back(std::move(extra));
            Reject([&] { amastra::ParseModelPlan(hundred); }, "101-component plan was accepted");
        }
        std::cout << "AMAstraModeler core tests passed: " << checks << " checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAILED after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}
