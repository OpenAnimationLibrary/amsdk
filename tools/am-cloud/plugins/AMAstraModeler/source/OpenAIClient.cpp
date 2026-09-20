#include "OpenAIClient.h"

#include "ModelPlan.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winhttp.h>
#include <wincodec.h>
#include <objidl.h>
#include <ocidl.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

namespace amastra {
namespace {

std::string WindowsError(const char* operation);
[[noreturn]] void ImageDecodeError(const char* operation, HRESULT result);

class InternetHandle {
public:
    InternetHandle() = default;
    explicit InternetHandle(HINTERNET value) : value_(value) {}
    ~InternetHandle() { if (value_) WinHttpCloseHandle(value_); }
    InternetHandle(const InternetHandle&) = delete;
    InternetHandle& operator=(const InternetHandle&) = delete;
    InternetHandle(InternetHandle&& other) noexcept : value_(other.value_) { other.value_ = nullptr; }
    InternetHandle& operator=(InternetHandle&& other) noexcept {
        if (this != &other) {
            if (value_) WinHttpCloseHandle(value_);
            value_ = other.value_;
            other.value_ = nullptr;
        }
        return *this;
    }
    HINTERNET get() const { return value_; }
    explicit operator bool() const { return value_ != nullptr; }
private:
    HINTERNET value_ = nullptr;
};

template<class Interface>
class ComHandle {
public:
    ComHandle() = default;
    explicit ComHandle(Interface* value) : value_(value) {}
    ~ComHandle() { if (value_) value_->Release(); }
    ComHandle(const ComHandle&) = delete;
    ComHandle& operator=(const ComHandle&) = delete;
    ComHandle(ComHandle&& other) noexcept : value_(other.value_) { other.value_ = nullptr; }
    ComHandle& operator=(ComHandle&& other) noexcept {
        if (this != &other) {
            if (value_) value_->Release();
            value_ = other.value_;
            other.value_ = nullptr;
        }
        return *this;
    }
    Interface* get() const { return value_; }
    Interface** put() { return &value_; }
private:
    Interface* value_ = nullptr;
};

class ComApartment {
public:
    ComApartment() {
        result_ = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        if (FAILED(result_) && result_ != RPC_E_CHANGED_MODE)
            ImageDecodeError("Initialize Windows imaging", result_);
    }
    ~ComApartment() {
        if (result_ == S_OK || result_ == S_FALSE) CoUninitialize();
    }
    ComApartment(const ComApartment&) = delete;
    ComApartment& operator=(const ComApartment&) = delete;
private:
    HRESULT result_ = E_FAIL;
};

class ClipboardGuard {
public:
    ClipboardGuard() {
        if (!OpenClipboard(nullptr))
            throw Error(WindowsError("Open Windows clipboard"));
        open_ = true;
    }
    ~ClipboardGuard() { if (open_) CloseClipboard(); }
    ClipboardGuard(const ClipboardGuard&) = delete;
    ClipboardGuard& operator=(const ClipboardGuard&) = delete;
private:
    bool open_ = false;
};

class GlobalLockGuard {
public:
    explicit GlobalLockGuard(HGLOBAL global) : global_(global), data_(GlobalLock(global)) {}
    ~GlobalLockGuard() { if (data_) GlobalUnlock(global_); }
    GlobalLockGuard(const GlobalLockGuard&) = delete;
    GlobalLockGuard& operator=(const GlobalLockGuard&) = delete;
    void* get() const { return data_; }
private:
    HGLOBAL global_ = nullptr;
    void* data_ = nullptr;
};

class EraseStreamGlobal {
public:
    explicit EraseStreamGlobal(IStream* stream) : stream_(stream) {}
    ~EraseStreamGlobal() {
        HGLOBAL global = nullptr;
        if (!stream_ || FAILED(GetHGlobalFromStream(stream_, &global)) || !global) return;
        const SIZE_T size = GlobalSize(global);
        if (!size) return;
        void* data = GlobalLock(global);
        if (!data) return;
        SecureZeroMemory(data, size);
        GlobalUnlock(global);
    }
    EraseStreamGlobal(const EraseStreamGlobal&) = delete;
    EraseStreamGlobal& operator=(const EraseStreamGlobal&) = delete;
private:
    IStream* stream_ = nullptr;
};

struct DeleteBitmap {
    void operator()(HBITMAP bitmap) const noexcept {
        if (bitmap) DeleteObject(bitmap);
    }
};
using UniqueBitmap = std::unique_ptr<std::remove_pointer_t<HBITMAP>, DeleteBitmap>;

struct EraseBytes {
    std::vector<unsigned char>& value;
    ~EraseBytes() { if (!value.empty()) SecureZeroMemory(value.data(), value.size()); }
};

std::string WindowsError(const char* operation) {
    const DWORD code = GetLastError();
    LPWSTR buffer = nullptr;
    const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS;
    const DWORD count = FormatMessageW(flags, nullptr, code, 0,
                                       reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);
    std::wstring message = count && buffer ? std::wstring(buffer, count) : L"unknown Windows error";
    if (buffer) LocalFree(buffer);
    while (!message.empty() && (message.back() == L'\r' || message.back() == L'\n' || message.back() == L' '))
        message.pop_back();
    return std::string(operation) + " failed (Windows error " + std::to_string(code) + "): " +
           Utf8FromWide(message);
}

std::vector<unsigned char> ReadSmallFile(const std::wstring& path) {
    HANDLE raw = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (raw == INVALID_HANDLE_VALUE)
        throw Error("Cannot open api_key.txt beside master.exe. " + WindowsError("Open api_key.txt"));
    struct CloseFile { HANDLE value; ~CloseFile() { CloseHandle(value); } } file{raw};
    LARGE_INTEGER size{};
    if (!GetFileSizeEx(raw, &size)) throw Error(WindowsError("Read api_key.txt size"));
    if (size.QuadPart <= 0 || size.QuadPart > 8192)
        throw Error("api_key.txt must contain one API key and be no larger than 8 KiB");
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size.QuadPart));
    DWORD read = 0;
    if (!ReadFile(raw, bytes.data(), static_cast<DWORD>(bytes.size()), &read, nullptr) ||
        read != static_cast<DWORD>(bytes.size()))
        throw Error(WindowsError("Read api_key.txt"));
    return bytes;
}

std::string QueryHeader(HINTERNET request, const wchar_t* name) {
    DWORD bytes = 0;
    WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM, name, nullptr, &bytes, WINHTTP_NO_HEADER_INDEX);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || bytes < sizeof(wchar_t)) return {};
    if (bytes > 4096) throw Error("OpenAI returned an oversized response header");
    std::vector<wchar_t> value(bytes / sizeof(wchar_t));
    if (!WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM, name, value.data(), &bytes,
                             WINHTTP_NO_HEADER_INDEX)) return {};
    const std::wstring_view text(value.data(), wcsnlen_s(value.data(), value.size()));
    return Utf8FromWide(text);
}

void CheckCancel(const std::atomic_bool& cancelRequested) {
    if (cancelRequested.load(std::memory_order_relaxed)) throw Error("Generation cancelled");
}

[[noreturn]] void ImageDecodeError(const char* operation, HRESULT result) {
    std::ostringstream message;
    message << operation << " failed while decoding the selected reference image (HRESULT 0x"
            << std::hex << static_cast<unsigned long>(result) << ')';
    throw Error(message.str());
}

ComHandle<IWICImagingFactory> CreateWicFactory() {
    ComHandle<IWICImagingFactory> factory;
    const HRESULT result = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                            CLSCTX_INPROC_SERVER,
                                            IID_PPV_ARGS(factory.put()));
    if (FAILED(result)) ImageDecodeError("Create Windows image decoder", result);
    return factory;
}

void ValidateImageDimensions(UINT width, UINT height) {
    if (!width || !height || width > MaxReferenceImageDimension ||
        height > MaxReferenceImageDimension ||
        static_cast<std::size_t>(width) > MaxReferenceImagePixels / height)
        throw Error("Reference image dimensions exceed the 65,535-pixel or 64-megapixel safety limit");
}

struct DecodedWicImage {
    ComHandle<IWICStream> stream;
    ComHandle<IWICBitmapDecoder> decoder;
    ComHandle<IWICBitmapFrameDecode> frame;
    UINT width = 0;
    UINT height = 0;
};

DecodedWicImage DecodeImageBytes(IWICImagingFactory* factory,
                                 const std::vector<unsigned char>& bytes) {
    if (bytes.empty() || bytes.size() > std::numeric_limits<DWORD>::max())
        throw Error("Reference image data has an invalid size");
    DecodedWicImage decoded;
    HRESULT result = factory->CreateStream(decoded.stream.put());
    if (FAILED(result)) ImageDecodeError("Create image memory stream", result);
    result = decoded.stream.get()->InitializeFromMemory(
        const_cast<BYTE*>(reinterpret_cast<const BYTE*>(bytes.data())),
        static_cast<DWORD>(bytes.size()));
    if (FAILED(result)) ImageDecodeError("Open image memory stream", result);
    result = factory->CreateDecoderFromStream(decoded.stream.get(), nullptr,
                                              WICDecodeMetadataCacheOnLoad,
                                              decoded.decoder.put());
    if (FAILED(result)) ImageDecodeError("Decode image container", result);
    UINT frames = 0;
    result = decoded.decoder.get()->GetFrameCount(&frames);
    if (FAILED(result)) ImageDecodeError("Read image frame count", result);
    if (frames != 1) throw Error("Reference image must contain exactly one decodable frame");
    result = decoded.decoder.get()->GetFrame(0, decoded.frame.put());
    if (FAILED(result)) ImageDecodeError("Read image frame", result);
    result = decoded.frame.get()->GetSize(&decoded.width, &decoded.height);
    if (FAILED(result)) ImageDecodeError("Read decoded image dimensions", result);
    ValidateImageDimensions(decoded.width, decoded.height);
    return decoded;
}

void DecodeReferenceImage(const std::vector<unsigned char>& bytes,
                          const ReferenceImageMetadata& metadata) {
    ComApartment apartment;
    auto factory = CreateWicFactory();
    auto decoded = DecodeImageBytes(factory.get(), bytes);
    if (decoded.width != metadata.width || decoded.height != metadata.height)
        throw Error("Decoded reference-image dimensions do not match its file header");

    constexpr UINT DecodeMaximum = 1024;
    UINT decodedWidth = decoded.width;
    UINT decodedHeight = decoded.height;
    ComHandle<IWICBitmapScaler> scaler;
    IWICBitmapSource* source = decoded.frame.get();
    HRESULT result = S_OK;
    if (decoded.width > DecodeMaximum || decoded.height > DecodeMaximum) {
        if (decoded.width >= decoded.height) {
            decodedWidth = DecodeMaximum;
            decodedHeight = std::max<UINT>(1, static_cast<UINT>(
                (static_cast<std::uint64_t>(decoded.height) * DecodeMaximum) / decoded.width));
        } else {
            decodedHeight = DecodeMaximum;
            decodedWidth = std::max<UINT>(1, static_cast<UINT>(
                (static_cast<std::uint64_t>(decoded.width) * DecodeMaximum) / decoded.height));
        }
        result = factory.get()->CreateBitmapScaler(scaler.put());
        if (FAILED(result)) ImageDecodeError("Create image decoder scaler", result);
        result = scaler.get()->Initialize(decoded.frame.get(), decodedWidth, decodedHeight,
                                           WICBitmapInterpolationModeFant);
        if (FAILED(result)) ImageDecodeError("Scale decoded image", result);
        source = scaler.get();
    }
    ComHandle<IWICFormatConverter> converter;
    result = factory.get()->CreateFormatConverter(converter.put());
    if (FAILED(result)) ImageDecodeError("Create image format converter", result);
    result = converter.get()->Initialize(source, GUID_WICPixelFormat32bppBGRA,
                                         WICBitmapDitherTypeNone, nullptr, 0,
                                         WICBitmapPaletteTypeCustom);
    if (FAILED(result)) ImageDecodeError("Convert decoded image", result);
    const UINT stride = decodedWidth * 4;
    std::vector<unsigned char> decodedPixels(
        static_cast<std::size_t>(stride) * decodedHeight);
    result = converter.get()->CopyPixels(nullptr, stride,
                                         static_cast<UINT>(decodedPixels.size()),
                                         decodedPixels.data());
    if (!decodedPixels.empty())
        SecureZeroMemory(decodedPixels.data(), decodedPixels.size());
    if (FAILED(result)) ImageDecodeError("Read decoded image pixels", result);
}

std::uint16_t ReadLittle16(const unsigned char* bytes) {
    return static_cast<std::uint16_t>(bytes[0]) |
           static_cast<std::uint16_t>(bytes[1] << 8);
}

std::uint32_t ReadLittle32(const unsigned char* bytes) {
    return static_cast<std::uint32_t>(bytes[0]) |
           (static_cast<std::uint32_t>(bytes[1]) << 8) |
           (static_cast<std::uint32_t>(bytes[2]) << 16) |
           (static_cast<std::uint32_t>(bytes[3]) << 24);
}

void WriteLittle32(unsigned char* bytes, std::uint32_t value) {
    bytes[0] = static_cast<unsigned char>(value);
    bytes[1] = static_cast<unsigned char>(value >> 8);
    bytes[2] = static_cast<unsigned char>(value >> 16);
    bytes[3] = static_cast<unsigned char>(value >> 24);
}

constexpr std::size_t MaxClipboardPayloadBytes =
    MaxReferenceImagePixels * 4 + 1024 * 1024;

std::vector<unsigned char> CopyClipboardGlobal(HGLOBAL global, const char* formatName) {
    if (!global) throw Error(std::string("Clipboard ") + formatName + " data is unavailable");
    const SIZE_T size = GlobalSize(global);
    if (!size || size > MaxClipboardPayloadBytes)
        throw Error(std::string("Clipboard ") + formatName + " data exceeds the safe pixel-buffer limit");
    GlobalLockGuard lock(global);
    if (!lock.get()) throw Error(WindowsError("Lock clipboard image data"));
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size));
    std::memcpy(bytes.data(), lock.get(), bytes.size());
    return bytes;
}

std::size_t DibPixelOffset(const std::vector<unsigned char>& dib) {
    if (dib.size() < 12) throw Error("Clipboard DIB header is truncated");
    const std::uint32_t headerSize = ReadLittle32(dib.data());
    std::size_t offset = headerSize;
    std::uint16_t bitCount = 0;
    std::uint32_t colorCount = 0;
    std::size_t paletteEntrySize = 0;
    if (headerSize == 12) {
        bitCount = ReadLittle16(dib.data() + 10);
        colorCount = bitCount <= 8 ? (1u << bitCount) : 0;
        paletteEntrySize = 3;
    } else if (headerSize >= 40 && headerSize <= dib.size()) {
        bitCount = ReadLittle16(dib.data() + 14);
        const std::uint32_t compression = ReadLittle32(dib.data() + 16);
        colorCount = ReadLittle32(dib.data() + 32);
        if (!colorCount && bitCount <= 8) colorCount = 1u << bitCount;
        paletteEntrySize = 4;
        if (headerSize == 40 && (compression == BI_BITFIELDS || compression == 6)) {
            const std::size_t masks = compression == 6 ? 16 : 12;
            if (offset > dib.size() || masks > dib.size() - offset)
                throw Error("Clipboard DIB color masks are truncated");
            offset += masks;
        }
    } else {
        throw Error("Clipboard DIB uses an unsupported or malformed header");
    }
    if (!bitCount || colorCount > 256 ||
        colorCount > (dib.size() - std::min(offset, dib.size())) / paletteEntrySize)
        throw Error("Clipboard DIB palette is malformed");
    const std::size_t paletteBytes = static_cast<std::size_t>(colorCount) * paletteEntrySize;
    if (offset > dib.size() || paletteBytes > dib.size() - offset)
        throw Error("Clipboard DIB palette is truncated");
    offset += paletteBytes;
    if (offset >= dib.size()) throw Error("Clipboard DIB contains no pixel data");
    return offset;
}

std::vector<unsigned char> WrapDibAsBmp(const std::vector<unsigned char>& dib) {
    const std::size_t pixelOffset = DibPixelOffset(dib);
    constexpr std::size_t FileHeaderBytes = 14;
    if (dib.size() > std::numeric_limits<std::uint32_t>::max() - FileHeaderBytes)
        throw Error("Clipboard DIB is too large to decode");
    std::vector<unsigned char> bmp(FileHeaderBytes + dib.size());
    bmp[0] = 'B';
    bmp[1] = 'M';
    WriteLittle32(bmp.data() + 2, static_cast<std::uint32_t>(bmp.size()));
    WriteLittle32(bmp.data() + 6, 0);
    WriteLittle32(bmp.data() + 10,
                  static_cast<std::uint32_t>(FileHeaderBytes + pixelOffset));
    std::memcpy(bmp.data() + FileHeaderBytes, dib.data(), dib.size());
    return bmp;
}

struct EncodedAttempt {
    std::vector<unsigned char> bytes;
    std::uint64_t encodedSize = 0;
};

EncodedAttempt EncodeWicImage(IWICImagingFactory* factory, IWICBitmapSource* source,
                              UINT width, UINT height, REFGUID container,
                              WICPixelFormatGUID targetFormat, float quality) {
    ComHandle<IStream> output;
    IStream* rawOutput = nullptr;
    HRESULT result = CreateStreamOnHGlobal(nullptr, TRUE, &rawOutput);
    if (FAILED(result)) ImageDecodeError("Create encoded image stream", result);
    output = ComHandle<IStream>(rawOutput);
    EraseStreamGlobal eraseOutput(output.get());

    ComHandle<IWICBitmapEncoder> encoder;
    result = factory->CreateEncoder(container, nullptr, encoder.put());
    if (FAILED(result)) ImageDecodeError("Create reference image encoder", result);
    result = encoder.get()->Initialize(output.get(), WICBitmapEncoderNoCache);
    if (FAILED(result)) ImageDecodeError("Initialize reference image encoder", result);
    ComHandle<IWICBitmapFrameEncode> frame;
    ComHandle<IPropertyBag2> properties;
    result = encoder.get()->CreateNewFrame(frame.put(), properties.put());
    if (FAILED(result)) ImageDecodeError("Create encoded reference image frame", result);
    if (IsEqualGUID(container, GUID_ContainerFormatJpeg)) {
        if (!properties.get())
            throw Error("Windows JPEG encoder did not provide its required options");
        PROPBAG2 option{};
        option.pstrName = const_cast<LPOLESTR>(L"ImageQuality");
        VARIANT value{};
        value.vt = VT_R4;
        value.fltVal = quality;
        result = properties.get()->Write(1, &option, &value);
        if (FAILED(result)) ImageDecodeError("Set JPEG reference quality", result);
    }
    result = frame.get()->Initialize(properties.get());
    if (FAILED(result)) ImageDecodeError("Initialize encoded reference frame", result);
    result = frame.get()->SetSize(width, height);
    if (FAILED(result)) ImageDecodeError("Set encoded reference dimensions", result);
    result = frame.get()->SetPixelFormat(&targetFormat);
    if (FAILED(result)) ImageDecodeError("Set encoded reference pixel format", result);
    ComHandle<IWICFormatConverter> converter;
    result = factory->CreateFormatConverter(converter.put());
    if (FAILED(result)) ImageDecodeError("Create encoding format converter", result);
    result = converter.get()->Initialize(source, targetFormat, WICBitmapDitherTypeNone,
                                         nullptr, 0, WICBitmapPaletteTypeCustom);
    if (FAILED(result)) ImageDecodeError("Convert reference image for encoding", result);
    result = frame.get()->WriteSource(converter.get(), nullptr);
    if (FAILED(result)) ImageDecodeError("Encode reference image pixels", result);
    result = frame.get()->Commit();
    if (FAILED(result)) ImageDecodeError("Commit encoded reference frame", result);
    result = encoder.get()->Commit();
    if (FAILED(result)) ImageDecodeError("Commit encoded reference image", result);

    STATSTG status{};
    result = output.get()->Stat(&status, STATFLAG_NONAME);
    if (FAILED(result)) ImageDecodeError("Read encoded reference size", result);
    EncodedAttempt attempt;
    attempt.encodedSize = status.cbSize.QuadPart;
    if (!attempt.encodedSize || attempt.encodedSize > MaxReferenceImageBytes)
        return attempt;
    LARGE_INTEGER beginning{};
    result = output.get()->Seek(beginning, STREAM_SEEK_SET, nullptr);
    if (FAILED(result)) ImageDecodeError("Rewind encoded reference image", result);
    attempt.bytes.resize(static_cast<std::size_t>(attempt.encodedSize));
    ULONG read = 0;
    result = output.get()->Read(attempt.bytes.data(), static_cast<ULONG>(attempt.bytes.size()),
                                &read);
    if (FAILED(result) || read != attempt.bytes.size())
        ImageDecodeError("Read encoded reference image", FAILED(result) ? result : E_FAIL);
    return attempt;
}

struct NormalizedClipboardImage {
    std::string fileName;
    std::vector<unsigned char> bytes;
};

NormalizedClipboardImage NormalizeClipboardSource(IWICImagingFactory* factory,
                                                   IWICBitmapSource* original,
                                                   UINT originalWidth,
                                                   UINT originalHeight) {
    ValidateImageDimensions(originalWidth, originalHeight);
    auto png = EncodeWicImage(factory, original, originalWidth, originalHeight,
                              GUID_ContainerFormatPng, GUID_WICPixelFormat32bppBGRA, 1.0f);
    if (!png.bytes.empty()) return {"clipboard.png", std::move(png.bytes)};

    UINT width = originalWidth;
    UINT height = originalHeight;
    std::uint64_t previousSize = 0;
    for (unsigned attemptNumber = 0; attemptNumber < 10; ++attemptNumber) {
        ComHandle<IWICBitmapScaler> scaler;
        IWICBitmapSource* source = original;
        if (width != originalWidth || height != originalHeight) {
            HRESULT result = factory->CreateBitmapScaler(scaler.put());
            if (FAILED(result)) ImageDecodeError("Create clipboard image scaler", result);
            result = scaler.get()->Initialize(original, width, height,
                                              WICBitmapInterpolationModeFant);
            if (FAILED(result)) ImageDecodeError("Scale clipboard reference image", result);
            source = scaler.get();
        }
        const float quality = attemptNumber < 6 ? 0.86f : 0.68f;
        auto jpeg = EncodeWicImage(factory, source, width, height,
                                   GUID_ContainerFormatJpeg,
                                   GUID_WICPixelFormat24bppBGR, quality);
        if (!jpeg.bytes.empty()) return {"clipboard.jpg", std::move(jpeg.bytes)};
        if (!jpeg.encodedSize)
            throw Error("Windows could not encode the clipboard image");
        if (width <= 256 && height <= 256) break;
        double factor = 0.80;
        if (jpeg.encodedSize != previousSize) {
            factor = std::sqrt(static_cast<double>(MaxReferenceImageBytes) /
                               static_cast<double>(jpeg.encodedSize)) * 0.92;
            factor = std::clamp(factor, 0.35, 0.85);
        }
        previousSize = jpeg.encodedSize;
        width = std::max<UINT>(1, static_cast<UINT>(std::floor(width * factor)));
        height = std::max<UINT>(1, static_cast<UINT>(std::floor(height * factor)));
    }
    throw Error("Clipboard image could not be normalized within the 4 MiB safety limit");
}

NormalizedClipboardImage NormalizeClipboardBytes(const std::vector<unsigned char>& bytes) {
    ComApartment apartment;
    auto factory = CreateWicFactory();
    auto decoded = DecodeImageBytes(factory.get(), bytes);
    return NormalizeClipboardSource(factory.get(), decoded.frame.get(),
                                    decoded.width, decoded.height);
}

NormalizedClipboardImage NormalizeClipboardBitmap(HBITMAP bitmap) {
    ComApartment apartment;
    auto factory = CreateWicFactory();
    ComHandle<IWICBitmap> source;
    HRESULT result = factory.get()->CreateBitmapFromHBITMAP(bitmap, nullptr,
                                                            WICBitmapIgnoreAlpha,
                                                            source.put());
    if (FAILED(result)) ImageDecodeError("Read clipboard bitmap pixels", result);
    UINT width = 0;
    UINT height = 0;
    result = source.get()->GetSize(&width, &height);
    if (FAILED(result)) ImageDecodeError("Read clipboard bitmap dimensions", result);
    return NormalizeClipboardSource(factory.get(), source.get(), width, height);
}

} // namespace

std::wstring ProgramDirectory() {
    std::vector<wchar_t> buffer(1024);
    for (;;) {
        const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (!length) throw Error(WindowsError("Locate master.exe"));
        if (length + 1 < buffer.size()) {
            std::wstring path(buffer.data(), length);
            const auto separator = path.find_last_of(L"\\/");
            if (separator == std::wstring::npos) throw Error("Cannot determine the master.exe directory");
            return path.substr(0, separator);
        }
        if (buffer.size() >= 32768) throw Error("The master.exe path is too long");
        buffer.resize(buffer.size() * 2);
    }
}

std::string Utf8FromWide(std::wstring_view text) {
    if (text.empty()) return {};
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw Error("Text is too long to convert to UTF-8");
    const int needed = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0, nullptr, nullptr);
    if (!needed) throw Error(WindowsError("Convert text to UTF-8"));
    std::string result(static_cast<std::size_t>(needed), '\0');
    if (!WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()),
                             result.data(), needed, nullptr, nullptr))
        throw Error(WindowsError("Convert text to UTF-8"));
    return result;
}

std::wstring WideFromUtf8(std::string_view text) {
    if (text.empty()) return {};
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw Error("UTF-8 text is too long to convert");
    const int needed = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0);
    if (!needed) throw Error(WindowsError("Convert UTF-8 text"));
    std::wstring result(static_cast<std::size_t>(needed), L'\0');
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()),
                             result.data(), needed))
        throw Error(WindowsError("Convert UTF-8 text"));
    return result;
}

void SecureErase(std::string& value) noexcept {
    if (!value.empty()) SecureZeroMemory(value.data(), value.size());
    value.clear();
}

std::string LoadApiKey() {
    const std::wstring path = ProgramDirectory() + L"\\api_key.txt";
    auto bytes = ReadSmallFile(path);
    struct EraseKeyBytes {
        std::vector<unsigned char>& value;
        ~EraseKeyBytes() { if (!value.empty()) SecureZeroMemory(value.data(), value.size()); }
    } eraseKeyBytes{bytes};
    std::size_t begin = 0;
    if (bytes.size() >= 3 && bytes[0] == 0xef && bytes[1] == 0xbb && bytes[2] == 0xbf) begin = 3;
    std::size_t end = bytes.size();
    const auto whitespace = [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (begin < end && whitespace(bytes[begin])) ++begin;
    while (end > begin && whitespace(bytes[end - 1])) --end;
    if (begin == end) throw Error("api_key.txt is empty");
    std::string key(reinterpret_cast<const char*>(bytes.data() + begin), end - begin);
    if (key.size() < 20 || key.size() > 4096) {
        SecureErase(key);
        throw Error("api_key.txt does not contain a plausible API key");
    }
    for (unsigned char c : key) {
        if (c <= 0x20 || c == 0x7f) {
            SecureErase(key);
            throw Error("api_key.txt must contain only one API key, with no internal whitespace");
        }
    }
    return key;
}

ReferenceImage LoadReferenceImage(const std::wstring& path) {
    if (path.empty()) throw Error("Select a reference image or clear the image field");
    HANDLE raw = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (raw == INVALID_HANDLE_VALUE)
        throw Error("Cannot open the selected reference image. " +
                    WindowsError("Open reference image"));
    struct CloseFile { HANDLE value; ~CloseFile() { CloseHandle(value); } } file{raw};
    LARGE_INTEGER size{};
    if (!GetFileSizeEx(raw, &size))
        throw Error("Cannot read the selected reference image size. " +
                    WindowsError("Read reference image size"));
    if (size.QuadPart <= 0) throw Error("The selected reference image is empty");
    if (size.QuadPart > static_cast<LONGLONG>(MaxReferenceImageBytes))
        throw Error("Reference image exceeds the 4 MiB safety limit");
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size.QuadPart));
    EraseBytes eraseBytes{bytes};
    DWORD read = 0;
    if (!ReadFile(raw, bytes.data(), static_cast<DWORD>(bytes.size()), &read, nullptr) ||
        read != static_cast<DWORD>(bytes.size()))
        throw Error("Cannot read the complete selected reference image. " +
                    WindowsError("Read reference image"));
    const auto separator = path.find_last_of(L"\\/");
    const std::wstring_view baseName = separator == std::wstring::npos
        ? std::wstring_view(path) : std::wstring_view(path).substr(separator + 1);
    if (baseName.empty()) throw Error("The selected reference image has no filename");
    auto image = PrepareReferenceImage(Utf8FromWide(baseName), bytes,
                                       ReferenceImageSource::File);
    DecodeReferenceImage(bytes, image.metadata);
    return image;
}

ReferenceImage LoadReferenceImageFromClipboard() {
    enum class ClipboardSource { None, Png, Dib, Bitmap };
    ClipboardSource source = ClipboardSource::None;
    std::vector<unsigned char> payload;
    EraseBytes erasePayload{payload};
    UniqueBitmap bitmap;
    {
        ClipboardGuard clipboard;
        const UINT pngFormat = RegisterClipboardFormatW(L"PNG");
        if (pngFormat && IsClipboardFormatAvailable(pngFormat)) {
            HGLOBAL data = reinterpret_cast<HGLOBAL>(GetClipboardData(pngFormat));
            if (data) {
                payload = CopyClipboardGlobal(data, "PNG");
                source = ClipboardSource::Png;
            }
        }
        if (source == ClipboardSource::None && IsClipboardFormatAvailable(CF_DIBV5)) {
            HGLOBAL data = reinterpret_cast<HGLOBAL>(GetClipboardData(CF_DIBV5));
            if (data) {
                payload = CopyClipboardGlobal(data, "DIBV5");
                source = ClipboardSource::Dib;
            }
        }
        if (source == ClipboardSource::None && IsClipboardFormatAvailable(CF_DIB)) {
            HGLOBAL data = reinterpret_cast<HGLOBAL>(GetClipboardData(CF_DIB));
            if (data) {
                payload = CopyClipboardGlobal(data, "DIB");
                source = ClipboardSource::Dib;
            }
        }
        if (source == ClipboardSource::None && IsClipboardFormatAvailable(CF_BITMAP)) {
            HBITMAP original = reinterpret_cast<HBITMAP>(GetClipboardData(CF_BITMAP));
            if (original) {
                BITMAP details{};
                if (GetObjectW(original, static_cast<int>(sizeof(details)), &details) !=
                    static_cast<int>(sizeof(details)))
                    throw Error(WindowsError("Read clipboard bitmap dimensions"));
                if (details.bmWidth <= 0 || details.bmHeight <= 0)
                    throw Error("Clipboard bitmap dimensions are invalid");
                ValidateImageDimensions(static_cast<UINT>(details.bmWidth),
                                        static_cast<UINT>(details.bmHeight));
                bitmap.reset(reinterpret_cast<HBITMAP>(
                    CopyImage(original, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION)));
                if (!bitmap) throw Error(WindowsError("Copy clipboard bitmap"));
                source = ClipboardSource::Bitmap;
            }
        }
    }
    if (source == ClipboardSource::None)
        throw Error("The clipboard does not contain PNG, DIB, or bitmap pixels");

    NormalizedClipboardImage normalized;
    if (source == ClipboardSource::Png) {
        normalized = NormalizeClipboardBytes(payload);
    } else if (source == ClipboardSource::Dib) {
        auto bmp = WrapDibAsBmp(payload);
        EraseBytes eraseBmp{bmp};
        normalized = NormalizeClipboardBytes(bmp);
    } else {
        normalized = NormalizeClipboardBitmap(bitmap.get());
    }
    EraseBytes eraseNormalized{normalized.bytes};
    auto image = PrepareReferenceImage(std::move(normalized.fileName), normalized.bytes,
                                       ReferenceImageSource::Clipboard);
    DecodeReferenceImage(normalized.bytes, image.metadata);
    return image;
}

HBITMAP CreateReferenceImagePreviewBitmap(const ReferenceImage& image,
                                          unsigned maxWidth, unsigned maxHeight) {
    if (!maxWidth || !maxHeight) throw Error("Reference image preview size must be nonzero");
    if ((image.metadata.mimeType != "image/png" &&
         image.metadata.mimeType != "image/jpeg") ||
        !image.metadata.byteSize || image.metadata.byteSize > MaxReferenceImageBytes ||
        !image.metadata.width || !image.metadata.height || image.base64.empty())
        throw Error("Reference image data is incomplete or invalid");
    auto bytes = Base64Decode(image.base64);
    EraseBytes eraseBytes{bytes};
    if (bytes.size() != image.metadata.byteSize)
        throw Error("Reference image byte count does not match its metadata");
    if (image.metadata.sha256.size() != 64 || Sha256Hex(bytes) != image.metadata.sha256)
        throw Error("Reference image checksum does not match its metadata");

    ComApartment apartment;
    auto factory = CreateWicFactory();
    auto decoded = DecodeImageBytes(factory.get(), bytes);
    if (decoded.width != image.metadata.width || decoded.height != image.metadata.height)
        throw Error("Decoded reference-image dimensions do not match its metadata");
    GUID container{};
    HRESULT result = decoded.decoder.get()->GetContainerFormat(&container);
    if (FAILED(result)) ImageDecodeError("Read reference image format", result);
    if ((image.metadata.mimeType == "image/png" &&
         !IsEqualGUID(container, GUID_ContainerFormatPng)) ||
        (image.metadata.mimeType == "image/jpeg" &&
         !IsEqualGUID(container, GUID_ContainerFormatJpeg)))
        throw Error("Decoded reference-image format does not match its metadata");

    constexpr UINT MaximumPreviewDimension = 4096;
    const UINT boundedWidth = std::min<UINT>(maxWidth, MaximumPreviewDimension);
    const UINT boundedHeight = std::min<UINT>(maxHeight, MaximumPreviewDimension);
    UINT width = decoded.width;
    UINT height = decoded.height;
    if (width > boundedWidth || height > boundedHeight) {
        const long double scale = std::min(
            static_cast<long double>(boundedWidth) / width,
            static_cast<long double>(boundedHeight) / height);
        width = std::max<UINT>(1, static_cast<UINT>(std::floor(width * scale)));
        height = std::max<UINT>(1, static_cast<UINT>(std::floor(height * scale)));
    }

    ComHandle<IWICBitmapScaler> scaler;
    IWICBitmapSource* source = decoded.frame.get();
    if (width != decoded.width || height != decoded.height) {
        result = factory.get()->CreateBitmapScaler(scaler.put());
        if (FAILED(result)) ImageDecodeError("Create reference preview scaler", result);
        result = scaler.get()->Initialize(decoded.frame.get(), width, height,
                                           WICBitmapInterpolationModeFant);
        if (FAILED(result)) ImageDecodeError("Scale reference image preview", result);
        source = scaler.get();
    }
    ComHandle<IWICFormatConverter> converter;
    result = factory.get()->CreateFormatConverter(converter.put());
    if (FAILED(result)) ImageDecodeError("Create preview format converter", result);
    result = converter.get()->Initialize(source, GUID_WICPixelFormat32bppBGRA,
                                         WICBitmapDitherTypeNone, nullptr, 0,
                                         WICBitmapPaletteTypeCustom);
    if (FAILED(result)) ImageDecodeError("Convert reference preview pixels", result);

    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = static_cast<LONG>(width);
    info.bmiHeader.biHeight = -static_cast<LONG>(height);
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    void* pixels = nullptr;
    UniqueBitmap bitmap(CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, &pixels, nullptr, 0));
    if (!bitmap || !pixels) throw Error(WindowsError("Create reference image preview"));
    const UINT stride = width * 4;
    const std::size_t bufferSize = static_cast<std::size_t>(stride) * height;
    result = converter.get()->CopyPixels(nullptr, stride, static_cast<UINT>(bufferSize),
                                         static_cast<BYTE*>(pixels));
    if (FAILED(result)) ImageDecodeError("Read reference image preview pixels", result);
    return bitmap.release();
}

HttpResponse PostOpenAIJson(const std::string& apiKey, std::wstring_view endpoint,
                            const std::string& requestBody,
                            const std::atomic_bool& cancelRequested) {
    if (apiKey.empty()) throw Error("The API key is empty");
    if (apiKey.size() > 4096 || std::any_of(apiKey.begin(), apiKey.end(),
            [](unsigned char character) { return character <= 0x20 || character == 0x7f; }))
        throw Error("The API key contains invalid characters");
    if (endpoint != L"/v1/responses" && endpoint != L"/v1/images/generations" &&
        endpoint != L"/v1/images/edits")
        throw Error("The OpenAI API endpoint is not permitted");
    if (requestBody.empty() || requestBody.size() > MaxRequestBytes)
        throw Error("The OpenAI request body has an invalid size");
    if (requestBody.size() > std::numeric_limits<DWORD>::max())
        throw Error("The OpenAI request body is too large for WinHTTP");
    CheckCancel(cancelRequested);

    InternetHandle session(WinHttpOpen(L"AnimationMaster-AstraModeler/0.3.0",
                                        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                                        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0));
    if (!session) throw Error(WindowsError("Initialize HTTPS"));
    if (!WinHttpSetTimeouts(session.get(), 15000, 30000, 60000, 300000))
        throw Error(WindowsError("Configure HTTPS timeouts"));
    InternetHandle connection(WinHttpConnect(session.get(), L"api.openai.com",
                                              INTERNET_DEFAULT_HTTPS_PORT, 0));
    if (!connection) throw Error(WindowsError("Connect to api.openai.com"));
    const std::wstring endpointText(endpoint);
    InternetHandle request(WinHttpOpenRequest(connection.get(), L"POST", endpointText.c_str(),
                                               nullptr, WINHTTP_NO_REFERER,
                                               WINHTTP_DEFAULT_ACCEPT_TYPES,
                                               WINHTTP_FLAG_SECURE));
    if (!request) throw Error(WindowsError("Create OpenAI request"));
    DWORD disabled = WINHTTP_DISABLE_REDIRECTS;
    if (!WinHttpSetOption(request.get(), WINHTTP_OPTION_DISABLE_FEATURE, &disabled, sizeof(disabled)))
        throw Error(WindowsError("Disable HTTPS redirects"));

    std::wstring authorization = L"Authorization: Bearer " + WideFromUtf8(apiKey) + L"\r\n";
    struct EraseAuthorization {
        std::wstring& text;
        ~EraseAuthorization() {
            if (!text.empty()) SecureZeroMemory(text.data(), text.size() * sizeof(wchar_t));
        }
    } eraseAuthorization{authorization};
    const wchar_t headers[] = L"Content-Type: application/json\r\nAccept: application/json\r\n";
    if (!WinHttpAddRequestHeaders(request.get(), headers, -1L,
                                  WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE))
        throw Error(WindowsError("Set OpenAI request headers"));
    if (!WinHttpAddRequestHeaders(request.get(), authorization.c_str(),
                                  static_cast<DWORD>(authorization.size()),
                                  WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE))
        throw Error(WindowsError("Set OpenAI authorization"));
    CheckCancel(cancelRequested);
    if (!WinHttpSendRequest(request.get(), WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                            const_cast<char*>(requestBody.data()),
                            static_cast<DWORD>(requestBody.size()),
                            static_cast<DWORD>(requestBody.size()), 0)) {
        CheckCancel(cancelRequested);
        throw Error(WindowsError("Send OpenAI request"));
    }
    CheckCancel(cancelRequested);
    if (!WinHttpReceiveResponse(request.get(), nullptr)) {
        CheckCancel(cancelRequested);
        throw Error(WindowsError("Receive OpenAI response"));
    }
    CheckCancel(cancelRequested);

    HttpResponse response;
    DWORD statusBytes = sizeof(response.status);
    if (!WinHttpQueryHeaders(request.get(), WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                             WINHTTP_HEADER_NAME_BY_INDEX, &response.status, &statusBytes,
                             WINHTTP_NO_HEADER_INDEX))
        throw Error(WindowsError("Read OpenAI status"));
    response.requestId = QueryHeader(request.get(), L"x-request-id");

    for (;;) {
        CheckCancel(cancelRequested);
        DWORD available = 0;
        if (!WinHttpQueryDataAvailable(request.get(), &available)) {
            CheckCancel(cancelRequested);
            throw Error(WindowsError("Read OpenAI response size"));
        }
        if (!available) break;
        if (response.body.size() + available > MaxResponseBytes)
            throw Error("OpenAI response exceeds the 8 MiB safety limit");
        const std::size_t offset = response.body.size();
        response.body.resize(offset + available);
        DWORD read = 0;
        if (!WinHttpReadData(request.get(), response.body.data() + offset, available, &read)) {
            CheckCancel(cancelRequested);
            throw Error(WindowsError("Read OpenAI response"));
        }
        response.body.resize(offset + read);
        if (!read) break;
    }
    return response;
}

HttpResponse PostResponses(const std::string& apiKey, const std::string& requestBody,
                           const std::atomic_bool& cancelRequested) {
    return PostOpenAIJson(apiKey, L"/v1/responses", requestBody, cancelRequested);
}

HttpResponse PostImageRequest(const std::string& apiKey, bool edit,
                              const std::string& requestBody,
                              const std::atomic_bool& cancelRequested) {
    return PostOpenAIJson(apiKey,
                          edit ? L"/v1/images/edits" : L"/v1/images/generations",
                          requestBody, cancelRequested);
}

} // namespace amastra
