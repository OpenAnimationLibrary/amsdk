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
            Check(amastra::Base64Decode("").empty(), "Empty Base64 decode changed");
            Check(amastra::Base64Decode("TQ==") == std::vector<unsigned char>{'M'},
                  "One-byte Base64 decoding failed");
            Check(amastra::Base64Decode("TWE=") ==
                      (std::vector<unsigned char>{'M', 'a'}),
                  "Two-byte Base64 decoding failed");
            Check(amastra::Base64Decode("TWFu") ==
                      (std::vector<unsigned char>{'M', 'a', 'n'}),
                  "Three-byte Base64 decoding failed");
            Reject([] { amastra::Base64Decode("TQ="); },
                   "Base64 with a non-multiple-of-four length was accepted");
            Reject([] { amastra::Base64Decode("TW\n="); },
                   "Base64 whitespace was accepted");
            Reject([] { amastra::Base64Decode("TW$="); },
                   "Invalid Base64 alphabet character was accepted");
            Reject([] { amastra::Base64Decode("TQ==AAAA"); },
                   "Base64 padding before the final quartet was accepted");
            Reject([] { amastra::Base64Decode("TR=="); },
                   "Non-canonical two-character Base64 was accepted");
            Reject([] { amastra::Base64Decode("TWF="); },
                   "Non-canonical three-character Base64 was accepted");
            Reject([] { amastra::Base64Decode("TWFu", 2); },
                   "Base64 decoded-size limit was not enforced");

            Check(amastra::Sha256Hex({}) ==
                      "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
                  "Empty SHA-256 test vector failed");
            Check(amastra::Sha256Hex({'a', 'b', 'c'}) ==
                      "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
                  "SHA-256 abc test vector failed");
            Check(amastra::ReferenceImageSourceName(amastra::ReferenceImageSource::File) ==
                      "file" &&
                      amastra::ReferenceImageSourceName(
                          amastra::ReferenceImageSource::Clipboard) == "clipboard" &&
                      amastra::ReferenceImageSourceName(
                          amastra::ReferenceImageSource::ApiGenerated) == "api_generated" &&
                      amastra::ReferenceImageSourceName(
                          amastra::ReferenceImageSource::ApiRefined) == "api_refined",
                  "Reference-image source names changed");

            const auto png = amastra::PrepareReferenceImage("subject.jpg", PngFixture());
            Check(png.metadata.mimeType == "image/png", "PNG magic was not authoritative");
            Check(png.metadata.fileName == "subject.jpg", "Reference-image basename changed");
            Check(png.metadata.width == 3 && png.metadata.height == 2, "PNG dimensions were not read");
            Check(png.metadata.byteSize == PngFixture().size(), "PNG byte size was not retained");
            Check(png.metadata.source == amastra::ReferenceImageSource::File,
                  "Default reference-image source changed");
            Check(png.metadata.sha256 == amastra::Sha256Hex(PngFixture()) &&
                      png.metadata.sha256.size() == 64,
                  "Reference-image SHA-256 was not retained");
            Check(!png.base64.empty() && png.base64.find('\n') == std::string::npos,
                  "PNG Base64 is empty or wrapped");

            const auto jpeg = amastra::PrepareReferenceImage(
                "subject.jpeg", JpegFixture(), amastra::ReferenceImageSource::Clipboard);
            Check(jpeg.metadata.mimeType == "image/jpeg", "JPEG MIME detection failed");
            Check(jpeg.metadata.width == 3 && jpeg.metadata.height == 2,
                  "JPEG dimensions were not read");
            Check(jpeg.metadata.source == amastra::ReferenceImageSource::Clipboard,
                  "Explicit reference-image source was not retained");

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
                amastra::PrepareReferenceImage(
                    "subject.png", PngFixture(),
                    static_cast<amastra::ReferenceImageSource>(999));
            }, "Unknown reference-image source was accepted");
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
            const auto generatedJson =
                amastra::BuildImageGenerationRequestJson("Create a clean toy robot reference.");
            Check(generatedJson.size() <= amastra::MaxRequestBytes,
                  "Image-generation request exceeds request limit");
            const auto generated = amjson::parse(generatedJson);
            Check(generated.as_object().size() == 9,
                  "Image-generation request contains unexpected fields");
            Check(generated.at("model").as_string() == amastra::ImageGenerationModel &&
                      generated.at("prompt").as_string() ==
                          "Create a clean toy robot reference.",
                  "Image-generation model or prompt changed");
            Check(generated.at("n").as_number() == 1 &&
                      generated.at("size").as_string() == "1024x1024" &&
                      generated.at("quality").as_string() == "medium" &&
                      generated.at("background").as_string() == "opaque" &&
                      generated.at("output_format").as_string() == "jpeg" &&
                      generated.at("output_compression").as_number() == 85 &&
                      generated.at("moderation").as_string() == "auto",
                  "Image-generation request settings changed");
            Check(generated.find("images") == nullptr &&
                      generatedJson.find("data:image/") == std::string::npos,
                  "Image-generation request unexpectedly contains an input image");

            const auto reference = amastra::PrepareReferenceImage(
                "private-subject-name.jpeg", JpegFixture(),
                amastra::ReferenceImageSource::Clipboard);
            const auto editJson =
                amastra::BuildImageEditRequestJson("Simplify this subject.", reference);
            Check(editJson.size() <= amastra::MaxRequestBytes,
                  "Image-edit request exceeds request limit");
            const auto edit = amjson::parse(editJson);
            Check(edit.as_object().size() == 11,
                  "Image-edit request contains unexpected fields");
            Check(edit.at("model").as_string() == amastra::ImageEditModel &&
                      edit.at("prompt").as_string() == "Simplify this subject." &&
                      edit.at("input_fidelity").as_string() == "high",
                  "Image-edit model, prompt, or fidelity changed");
            Check(edit.at("n").as_number() == 1 &&
                      edit.at("size").as_string() == "1024x1024" &&
                      edit.at("quality").as_string() == "medium" &&
                      edit.at("background").as_string() == "opaque" &&
                      edit.at("output_format").as_string() == "jpeg" &&
                      edit.at("output_compression").as_number() == 85 &&
                      edit.at("moderation").as_string() == "auto",
                  "Image-edit request settings changed");
            const auto& images = edit.at("images").as_array();
            Check(images.size() == 1 && images[0].as_object().size() == 1,
                  "Image-edit request did not contain exactly one image reference");
            Check(images[0].at("image_url").as_string() ==
                      "data:image/jpeg;base64," + reference.base64,
                  "Image-edit data URL changed");
            Check(editJson.find("private-subject-name.jpeg") == std::string::npos,
                  "Reference-image basename leaked into image-edit request");

            Reject([] { amastra::BuildImageGenerationRequestJson(""); },
                   "Empty image-generation prompt was accepted");
            Check(!amastra::BuildImageGenerationRequestJson(
                       std::string(amastra::MaxImagePromptBytes, 'x')).empty(),
                  "Maximum-length image-generation prompt was rejected");
            Reject([] {
                amastra::BuildImageGenerationRequestJson(
                    std::string(amastra::MaxImagePromptBytes + 1, 'x'));
            }, "Oversized image-generation prompt was accepted");
            Reject([&] { amastra::BuildImageEditRequestJson("", reference); },
                   "Empty image-edit prompt was accepted");
            auto alteredHash = reference;
            alteredHash.metadata.sha256[0] = alteredHash.metadata.sha256[0] == '0' ? '1' : '0';
            Reject([&] {
                amastra::BuildImageEditRequestJson("Simplify this subject.", alteredHash);
            }, "Image edit accepted a mismatched SHA-256");
        }
        {
            const std::string encoded(256, 'A');
            const auto sanitized = amastra::SanitizeDiagnostic(
                "bad \"data:image/png;base64," + encoded + "\" and token " + encoded);
            Check(sanitized.find("data:image/") == std::string::npos,
                  "Diagnostic retained an image data URL");
            Check(sanitized.find(encoded) == std::string::npos,
                  "Diagnostic retained a long encoded value");
            Check(sanitized.find("[image data omitted]") != std::string::npos &&
                  sanitized.find("[long encoded value omitted]") != std::string::npos,
                  "Diagnostic redaction markers are missing");
            const std::string wrappedFirst(80, 'B');
            const std::string wrappedSecond(80, 'C');
            const auto wrapped = amastra::SanitizeDiagnostic(
                "prefix \"DATA:IMAGE/jpeg;base64," + wrappedFirst + "\r\n\t" +
                wrappedSecond + "\" suffix");
            Check(wrapped.find("DATA:IMAGE/") == std::string::npos &&
                      wrapped.find(wrappedFirst) == std::string::npos &&
                      wrapped.find(wrappedSecond) == std::string::npos &&
                      wrapped.find("[image data omitted]") != std::string::npos &&
                      wrapped.find("prefix") != std::string::npos &&
                      wrapped.find("suffix") != std::string::npos,
                  "Wrapped image data URL was not fully redacted");

            const auto bearer = amastra::SanitizeDiagnostic(
                "auth bEaReR sk-proj-secret.value, retry normally");
            Check(bearer == "auth Bearer [token omitted], retry normally",
                  "Case-insensitive Bearer token was not safely redacted");
            const auto apiKey = amastra::SanitizeDiagnostic(
                "key=sk-proj-abc_DEF-123; status denied");
            Check(apiKey == "key=[API key omitted]; status denied",
                  "OpenAI API key was not safely redacted");
            Check(amastra::SanitizeDiagnostic("key=SK-not-lowercase; status denied") ==
                      "key=SK-not-lowercase; status denied",
                  "API-key prefix redaction unexpectedly became case-insensitive");
            Check(amastra::SanitizeDiagnostic("Connection timed out; retry later.") ==
                      "Connection timed out; retry later.",
                  "Normal diagnostic text changed during sanitization");
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
            const auto encoded = amastra::Base64Encode(JpegFixture());
            const auto envelope = amjson::Value::object({
                {"created", 123},
                {"background", "opaque"},
                {"data", amjson::Value::array({amjson::Value::object({
                    {"b64_json", encoded},
                    {"revised_prompt", "A simplified robot on a plain background."}
                })})},
                {"output_format", "jpeg"},
                {"output_compression", 77},
                {"quality", "high"},
                {"size", "3x2"},
                {"usage", amjson::Value::object({
                    {"input_tokens", 11},
                    {"output_tokens", 22},
                    {"total_tokens", 33},
                    {"input_tokens_details", amjson::Value::object({
                        {"text_tokens", 4}, {"image_tokens", 7}
                    })},
                    {"output_tokens_details", amjson::Value::object({
                        {"text_tokens", 2}, {"image_tokens", 20}
                    })}
                })}
            });
            const auto result = amastra::ExtractImageApiResult(
                amjson::dump(envelope), "req_image_test");
            Check(result.requestId == "req_image_test" &&
                      result.model == amastra::ImageGenerationModel,
                  "Image API request ID or model was lost");
            Check(result.image.metadata.source ==
                          amastra::ReferenceImageSource::ApiGenerated &&
                      result.image.metadata.fileName == "openai-generated.jpg" &&
                      result.image.metadata.mimeType == "image/jpeg" &&
                      result.image.metadata.sha256 == amastra::Sha256Hex(JpegFixture()),
                  "Generated API image metadata was not prepared correctly");
            Check(result.revisedPrompt ==
                          "A simplified robot on a plain background." &&
                      result.outputFormat == "jpeg" && result.outputCompression == 77 &&
                      result.hasOutputCompression && result.size == "3x2" &&
                      result.quality == "high" && result.background == "opaque",
                  "Image API output settings were not parsed");
            Check(result.usagePresent && result.inputTokens == 11 && result.outputTokens == 22 &&
                      result.totalTokens == 33 && result.inputTextTokens == 4 &&
                      result.inputImageTokens == 7 && result.outputTextTokens == 2 &&
                      result.outputImageTokens == 20,
                  "Image API usage was not parsed");

            const auto minimal = amjson::Value::object({
                {"data", amjson::Value::array({
                    amjson::Value::object({{"b64_json", encoded}})
                })}
            });
            const auto refined = amastra::ExtractImageApiResult(
                amjson::dump(minimal), "req_refine", amastra::ReferenceImageSource::ApiRefined);
            Check(refined.model == amastra::ImageEditModel &&
                      refined.image.metadata.source ==
                          amastra::ReferenceImageSource::ApiRefined &&
                      refined.image.metadata.fileName == "openai-refined.jpg",
                  "Refined API image source or model was not retained");
            Check(refined.outputFormat == "jpeg" && refined.size == "3x2" &&
                      refined.quality.empty() && refined.background.empty() &&
                      refined.outputCompression == 0 && !refined.hasOutputCompression &&
                      !refined.usagePresent,
                  "Omitted image API result settings were populated with request defaults");

            const auto zeroUsage = amjson::Value::object({
                {"data", amjson::Value::array({
                    amjson::Value::object({{"b64_json", encoded}})
                })},
                {"usage", amjson::Value::object({})}
            });
            const auto zeroUsageResult =
                amastra::ExtractImageApiResult(amjson::dump(zeroUsage));
            Check(zeroUsageResult.usagePresent && zeroUsageResult.inputTokens == 0 &&
                      zeroUsageResult.outputTokens == 0 && zeroUsageResult.totalTokens == 0,
                  "Present all-zero image usage was treated as omitted");

            const auto pngMinimal = amjson::Value::object({
                {"data", amjson::Value::array({amjson::Value::object({
                    {"b64_json", amastra::Base64Encode(PngFixture())}
                })})}
            });
            const auto unlabelledPng =
                amastra::ExtractImageApiResult(amjson::dump(pngMinimal));
            Check(unlabelledPng.outputFormat == "png" &&
                      unlabelledPng.size == "3x2" &&
                      unlabelledPng.image.metadata.mimeType == "image/png" &&
                      unlabelledPng.image.metadata.fileName == "openai-generated.png",
                  "Unlabelled PNG output settings were not inferred from validated bytes");

            Reject([&] {
                auto multiple = envelope;
                multiple.as_object().at("data").as_array().push_back(
                    amjson::Value::object({{"b64_json", encoded}}));
                amastra::ExtractImageApiResult(amjson::dump(multiple));
            }, "Image API response with multiple images was accepted");
            Reject([] {
                amastra::ExtractImageApiResult(R"({"data":[]})");
            }, "Image API response with no images was accepted");
            Reject([] {
                amastra::ExtractImageApiResult(
                    R"({"data":[{"url":"https://example.invalid/image.jpg"}]})");
            }, "Image API URL response without b64_json was accepted");
            Reject([] {
                amastra::ExtractImageApiResult(R"({"data":[{"b64_json":42}]})");
            }, "Non-string image API Base64 was accepted");
            Reject([] {
                amastra::ExtractImageApiResult(R"({"data":[{"b64_json":"TR=="}]})");
            }, "Non-canonical image API Base64 was accepted");
            Reject([&] {
                auto mismatched = envelope;
                mismatched.as_object().at("output_format") = "png";
                amastra::ExtractImageApiResult(amjson::dump(mismatched));
            }, "Image API output-format mismatch was accepted");
            Reject([&] {
                auto mismatched = envelope;
                mismatched.as_object().at("size") = "1024x1024";
                amastra::ExtractImageApiResult(amjson::dump(mismatched));
            }, "Image API output-size mismatch was accepted");
            Reject([&] {
                amastra::ExtractImageApiResult(
                    amjson::dump(minimal), "bad\nrequest");
            }, "Image API request ID with a control character was accepted");
            Reject([&] {
                amastra::ExtractImageApiResult(
                    amjson::dump(minimal), {}, amastra::ReferenceImageSource::File);
            }, "Non-API source was accepted for an image API response");
            Reject([] {
                amastra::ExtractImageApiResult(
                    std::string(amastra::MaxResponseBytes + 1, 'x'));
            }, "Oversized image API response was accepted");

            const std::string secret(256, 'A');
            try {
                amastra::ExtractImageApiResult(amjson::dump(amjson::Value::object({
                    {"error", amjson::Value::object({
                        {"message", "invalid data:image/jpeg;base64," + secret}
                    })}
                })));
                throw std::runtime_error("Image API error response was accepted");
            } catch (const amastra::Error& error) {
                const std::string message = error.what();
                Check(message.find("data:image/") == std::string::npos &&
                          message.find(secret) == std::string::npos &&
                          message.find("[image data omitted]") != std::string::npos,
                      "Image API error exposed encoded image data");
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
