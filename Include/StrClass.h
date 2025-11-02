//WEP  3/31/2005  \will120\Include\StrClass.h
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyCppcoreguidelinesPreferMemberInitializer
// ReSharper disable CppTooWideScopeInitStatement
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
// ReSharper disable CppClangTidyBugproneExceptionEscape
#pragma once

#include "StdAfx.h"

#include "Allocate.h"
#include "Macros.h"
#include "RGBFloat.h"
#include "Rotate.h"
#include "Vector2.h"
#include "Vector4.h"

#include <array>
#include <charconv>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

#define STRINGALLOC(baz) (char *)AllocString(baz)
#define STRINGFREE(baz)  { if (baz) { FreeString(baz); (baz) = nullptr; } }

constexpr int STRINGSIZE = 255;
static constexpr char NATIVESEPARATOR = '\\';
static constexpr char SEPARATOR = '/';

static constexpr char quotech = '\"';
static constexpr char quotech1[] = "\"";

//this now seperates linked file matchnames v10.03
//#define quotech    '\"'

static constexpr char periodch_r = (unsigned char)255;
static constexpr char pathch_r = (unsigned char)254;
//static constexpr char linefeed = '\n';
//static constexpr char carriagereturn = '\r';

class Time;
class CWnd;

template <typename T>
using EnableIfIntegral = std::enable_if_t<std::is_integral_v<T>>;

template <typename T, typename = EnableIfIntegral<T>>
std::string ToChars(T &value, int base = 10) noexcept {
    std::array<char, std::numeric_limits<T>::digits + 1 + std::is_signed_v<T>> buffer{};
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, base);
    if (result.ec == std::errc{}) {
        const std::string::size_type len = static_cast<std::string::size_type>(result.ptr - buffer.data());
        std::string r_val(buffer.data(), len);
        return r_val;
    }
    ODSF("Error: ToChars %d\n", static_cast<int>(result.ec));
    return std::string();
}

inline std::string ToCharsFloat(const float &value) noexcept {
    std::array<char, 2 + std::numeric_limits<float>::max_exponent10 + std::numeric_limits<float>::max_digits10> buffer{};
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, std::chars_format::general, std::numeric_limits<float>::max_digits10);
    if (result.ec == std::errc{}) {
        const std::string::size_type len = static_cast<std::string::size_type>(result.ptr - buffer.data());
        std::string r_val(buffer.data(), len);
        const auto scientific_minus = r_val.find("e-");
        const auto scientific_plus = r_val.find("e+");
        if (scientific_minus == std::string::npos && scientific_plus == std::string::npos) {
            if (r_val.find('.') != std::string::npos) {
                auto lastdigit = r_val.find_last_not_of('0');
                if (lastdigit != std::string::npos && ++lastdigit < len) {
                    r_val = r_val.substr(0, lastdigit);
                }
                if (r_val.back() == '.')
                    r_val.pop_back();
            }
        }
        return r_val;
    }
    ODSF("Error: ToCharsFloat %d\n", static_cast<int>(result.ec));
    return std::string();
}

inline std::string ToCharsDouble(const double &value) noexcept {
    std::array<char, 2 + std::numeric_limits<double>::max_exponent10 + std::numeric_limits<double>::max_digits10> buffer{};
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, std::chars_format::general, std::numeric_limits<double>::max_digits10);
    if (result.ec == std::errc{}) {
        const std::string::size_type len = static_cast<std::string::size_type>(result.ptr - buffer.data());
        std::string r_val(buffer.data(), len);
        const auto scientific_minus = r_val.find("e-");
        const auto scientific_plus = r_val.find("e+");
        if (scientific_minus == std::string::npos && scientific_plus == std::string::npos) {
            if (r_val.find('.') != std::string::npos) {
                auto lastdigit = r_val.find_last_not_of('0');
                if (lastdigit != std::string::npos && ++lastdigit < len) {
                    r_val = r_val.substr(0, lastdigit);
                }
                if (r_val.back() == '.')
                    r_val.pop_back();
            }
        }
        return r_val;
    }
    ODSF("Error: ToCharsFloat %d\n", static_cast<int>(result.ec));
    return std::string();
}

inline std::string ToCharsFloat(const float value, const int int_precision) noexcept {
    std::array<char, 2 + std::numeric_limits<float>::max_exponent10 + std::numeric_limits<float>::max_digits10> buffer{};
    const int precision = (std::min)(int_precision, std::numeric_limits<float>::max_digits10);
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, std::chars_format::fixed, precision);
    if (result.ec == std::errc{}) {
        const std::string::size_type len = static_cast<std::string::size_type>(result.ptr - buffer.data());
        std::string r_val(buffer.data(), len);
        const auto scientific_minus = r_val.find("e-");
        const auto scientific_plus = r_val.find("e+");
        if (scientific_minus == std::string::npos && scientific_plus == std::string::npos) {
            if (r_val.find('.') != std::string::npos) {
                auto lastdigit = r_val.find_last_not_of('0');
                if (lastdigit != std::string::npos && ++lastdigit < len) {
                    r_val = r_val.substr(0, lastdigit);
                }
                if (r_val.back() == '.')
                    r_val.pop_back();
            }
        }
        return r_val;
    }
    ODSF("Error: ToCharsFloatPrec %d\n", static_cast<int>(result.ec));
    return std::string();
}

inline std::string ToCharsDouble(const double value, const int int_precision) noexcept {
    std::array<char, 2 + std::numeric_limits<double>::max_exponent10 + std::numeric_limits<double>::max_digits10> buffer{};
    const int precision = (std::min)(int_precision, std::numeric_limits<double>::max_digits10);
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, std::chars_format::fixed, precision);
    if (result.ec == std::errc{}) {
        const std::string::size_type len = static_cast<std::string::size_type>(result.ptr - buffer.data());
        std::string r_val(buffer.data(), len);
        const auto scientific_minus = r_val.find("e-");
        const auto scientific_plus = r_val.find("e+");
        if (scientific_minus == std::string::npos && scientific_plus == std::string::npos) {
            if (r_val.find('.') != std::string::npos) {
                auto lastdigit = r_val.find_last_not_of('0');
                if (lastdigit != std::string::npos && ++lastdigit < len) {
                    r_val = r_val.substr(0, lastdigit);
                }
                if (r_val.back() == '.')
                    r_val.pop_back();
            }
        }
        return r_val;
    }
    ODSF("Error: ToCharsDoublePrec %d\n", static_cast<int>(result.ec));
    return std::string();
}

//Replacement for strtok
//usage
// std::vector<std::string> tokens = split_string(temp.Get(), " ");
// for (int i = 0; i < tokens.size(); ++i) {
//       String t = tokens[i].Get();
//       ODSF("%s\n",t);
//       std::cout << tokens[i] << "\n";
// }

inline std::vector<std::string> split_string(const std::string &input, const std::string &delims) noexcept {
    std::vector<std::string> ret;
    // ReSharper disable once CppInitializedValueIsAlwaysRewritten
    for (std::string::size_type start = 0, pos = 0; ; start = pos + 1) {
        pos = input.find_first_of(delims, start);
        std::string token = input.substr(start, pos - start);
        if (token.length() > 0) // ignore empty tokens
            ret.push_back(token);
        if (pos == std::string::npos)
            break;
    }
    return ret;
}

//Replacement for strtok with only one delimiter
//usage
// std::vector<std::string> tokens = str_tokenize(temp.Get(), " ");
// for (int i = 0; i < tokens.size(); ++i) {
//       String t = tokens[i].Get();
//       ODSF("%s\n",t);
//       std::cout << tokens[i] << "\n";
// }

inline std::vector<std::string> &str_tokenize(const std::string &s, const char delim, std::vector<std::string> &elems, const bool include_empty) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty() || include_empty)
            elems.push_back(item);
    }
    return elems;
}

inline std::vector<std::string> str_tokenize(const std::string &s, const char delim, const bool include_empty = false) {
    std::vector<std::string> elems;
    str_tokenize(s, delim, elems, include_empty);
    return elems;
}

//trim empty spaces
inline std::string trim(std::string str) noexcept {
    const std::string::size_type first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    const std::string::size_type last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

inline std::size_t replace_all(std::string &inout, const std::string_view what, const std::string_view with) noexcept {
    std::size_t count{};
    for (std::string::size_type pos{}; std::string::npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length(), ++count)
        inout.replace(pos, what.length(), with.data(), with.length());
    return count;
}

inline std::size_t remove_all(std::string &inout, const std::string_view what) noexcept {
    return replace_all(inout, what, "");
}

inline std::string replace_caseinsensitive(std::string s, std::string &a, const std::string &b) noexcept {
    std::string lower_s(s);
    // ReSharper disable once CppParameterMayBeConst
    std::ranges::transform(lower_s, lower_s.begin(), [](unsigned char c) { return std::tolower(c); });
    // ReSharper disable once CppParameterMayBeConst
    std::ranges::transform(a, a.begin(), [](unsigned char c) { return std::tolower(c); });
    auto position = lower_s.find(a);
    while (position != std::string::npos) {
        s.replace(position, a.size(), b);
        position = lower_s.find(a, position + 1);
    }
    return s;
}

class FILEIOEXPORT String final {
public:
    char *buf{nullptr}; //SHOULD CHANGE THIS TO PROTECTED OR PRIVATE

    enum {
        NOCHANGE,
        KEEPASKING,
        ASKCANCLED
    };
#ifdef _MEMDEBUG
    void *operator new(size_t size, char *file, const int line) noexcept {
        return ALLOCSTRING(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocString(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeString(ptr);
    }

    String() noexcept = default;

    String(const int size, BOOL) noexcept {
        //avoid using String(int) etc.
        buf = STRINGALLOC(size);
    }

    String(const String &) noexcept;
    String(const char *) noexcept; //CONVERT CHAR * TO STRING
    // ! use it with care, no checks !
    String(const char *init, const int count) noexcept {
        buf = STRINGALLOC(count);
        memcpy(buf, init, count);
    }

    String(char, int count) noexcept;
    String(const std::string &initstr) noexcept; //CONVERT CHAR * TO STRING
    String(const CString &initcstr) noexcept;
    String(char) noexcept;
    String(unsigned char) noexcept;
    String(SSHORT) noexcept;
    String(USHORT) noexcept;
    String(int) noexcept;
    String(UINT) noexcept;
    String(ULONG) noexcept;
    String(LONG) noexcept;
    String(int64_t) noexcept; //same as LONG_PTR
    String(uint64_t) noexcept; // same as ULONG_PTR
    String(float) noexcept;
    String(double) noexcept;
    String(float, int precision) noexcept;
    String(double, int precision) noexcept;

    explicit String(const Vector &) noexcept;
    explicit String(const Vector2 &) noexcept;
    explicit String(const Vector4 &) noexcept;
    explicit String(const Quaternion &) noexcept;
    explicit String(const RotateEuler &) noexcept;
    explicit String(const RGBFloat &) noexcept;
    explicit String(const RGBAFloat &) noexcept;

    String(String &&) noexcept;
    void Set(const char *other, int len) noexcept;

    ~String() noexcept {
        if (buf)
            FreeString(buf);
        buf = nullptr;
    }

    [[nodiscard]] char *Get() const noexcept {
        return buf;
    }

    [[nodiscard]] const char *Get_const_char() const noexcept {
        return buf;
    }

    char operator [](const int index) const noexcept {
        if (buf) {
            return buf[index];
        }
        return 0;
    }

    //operator char * () const;         // CONVERT STRING TO CHAR *, THE CAN'T USE COMPILER OFTEN GETS CONFUSED ON WHICH OVERLOADED FUNCTION TO CALL

    [[nodiscard]] bool IsEmpty() const noexcept {
        return !buf || *buf == '\0';
    }

    [[nodiscard]] bool IsNotEmpty() const noexcept {
        return buf && *buf != '\0';
    }

    void Empty() noexcept {
        if (buf)
            FreeString(buf);
        buf = nullptr;
    }

    bool operator==(const String &other) const noexcept {
        if (!buf)
            return !other.buf;
        if (!other.buf)
            return false;
        return _stricmp(buf, other.buf) == 0;
    }

    bool operator!=(const String &other) const noexcept {
        return !(*this == other);
    }

    bool operator <(const String &) const;
    bool operator >(const String &) const;
    bool operator <=(const String &) const;
    bool operator >=(const String &) const;

    String &operator=(String &&) noexcept;
    String &operator=(const String &) noexcept;
    String &operator=(const char *) noexcept;
    String &operator=(const unsigned char *) noexcept;
    String &operator=(CString);

    void operator+=(const String &) noexcept;
    void operator+=(char);

    friend String operator +(const String &, const String &) noexcept;

    [[nodiscard]] HASH_INLINE size_t GetLength() const noexcept;
    [[nodiscard]] HASH_INLINE int GetLength_Int() const noexcept;

    [[nodiscard]] String Left(int count) const;
    [[nodiscard]] String Right(int count) const;
    [[nodiscard]] String Mid(int start, int count) const noexcept;
    [[nodiscard]] String ToUpper() const;
    [[nodiscard]] String ToLower() const;
    void TrimRight(); //new functions like MFC CString
    void TrimLeft();
    void TrimRightSlash();
    void FindAndRemoveDoubleSeparators(); // '//' replaced with '/' and '\\' replaced with '\'

    int RemoveAll(const String &find) {
        //replace all occurences for find and return number of occurences
        std::string to_change(buf);
        const std::string::size_type occurences = remove_all(to_change, std::string(find.buf));
        if (occurences > 0) {
            STRINGFREE(buf)
            const size_t len = to_change.length();
            buf = STRINGALLOC(len);
            memcpy(buf, to_change.data(), len);
        }
        return (int)occurences;
    }

    void Replace(const String &find, const String &replace);
    void ReplaceS(const String &find, const String &replace); //case sensitive version

    // all Find functions returning -1 , if nothing found
    [[nodiscard]] int Find(char ch) const noexcept; //like "C" strchr
    [[nodiscard]] int Find(int startindex, char ch) const noexcept;
    [[nodiscard]] int Find(const String &sub) const; //like "C" strstr
    [[nodiscard]] int FindS(const String &sub) const noexcept; //like "C" strstr case sensitive
    [[nodiscard]] int Find(int startindex, const String &sub) const; //like "C" strstr
    [[nodiscard]] int FindS(int startindex, const String &sub) const noexcept; //like "C" strstr case sensitive
    [[nodiscard]] int ReverseFind(char ch) const; //like "C" strrchr
    [[nodiscard]] int ReverseFindS(char ch) const noexcept; //like "C" strrchr case sensitive
    [[nodiscard]] int FindOccurrence(const String &find, int minoccurences = -1) const; //return numbers of occurence from char in string,fast return if occurences > minoccurences
    [[nodiscard]] int FindOccurrence(char ch, int minoccurences = -1) const; //return numbers of occurence from substring in string,fast return if occurences > minoccurences
    [[nodiscard]] int FindOneOf(const String &charset) const;

    String StrTok(const String &separators);
    String StrTok2(const String &separator);

    void ExpandXMLEscapes();
    void ContractXMLEscapes();

    [[nodiscard]] String Quote() const;

    [[nodiscard]] String GetPathOnly() const;
    [[nodiscard]] String GetNameOnly() const;
    [[nodiscard]] String GetSuffixOnly() const;
    [[nodiscard]] String GetWithoutSuffix() const;
    [[nodiscard]] String GetNameOnlyWithoutSuffix() const;
    [[nodiscard]] String GetWithoutDigits() const;
    [[nodiscard]] String GetFileDigits() const;
    [[nodiscard]] int GetEndingNumber() const;
    [[nodiscard]] String GetWithoutCRLFs() const;
    [[nodiscard]] String GetWithoutLineFeed() const;
    [[nodiscard]] String GetAbbreviated(int maxLength, bool bAtLeastName = true) const;
    String GetAbbreviated(CWnd *window) const;
    [[nodiscard]] String GetToolTip() const;
    [[nodiscard]] String GetStatusMessageText() const;
    [[nodiscard]] String GetRelativePath() const; //Always UNC
    [[nodiscard]] String GetNonRelativePath() const;
    [[nodiscard]] String GetAbsolutePath() const;
    [[nodiscard]] String GetAbsolutePath(bool forceunc) const;
    [[nodiscard]] String GetUNCFileName() const;
    [[nodiscard]] String GetServerFileName() const;
    [[nodiscard]] String NumberFrame(int frame) const;
    [[nodiscard]] String StripLeadingSlash() const;
    [[nodiscard]] String StripLeadingSpace() const;
    [[nodiscard]] String StripPunctuation() const;
    [[nodiscard]] String NetSharePlaceHolder() const;
    [[nodiscard]] String GetFileNamesMatchName() const noexcept; //assumes string is an UNC filename on pc for speed
    [[nodiscard]] String GetMatchNameRelativeForFile() const;
    [[nodiscard]] String GetMatchNameAbsoluteFromFile() const;
    [[nodiscard]] String ToRelativePathDescription() const; //converts descriptions to linked files
    String ToAbsolutePathDescription(float productversion, bool askforfile, int &result) const;
    String FitWidth(CDC *dc, int maxwidth, const String &padwith) const;
    [[nodiscard]] String GetEncrypted(const String &password) const;
    void Decrypt(const String &password) const;
    [[nodiscard]] String SpanExcluding(const String &charset) const;
    [[nodiscard]] String GetFileTitle() const;
    [[nodiscard]] Time ToTime(int fps, TimeUnit timeunits, bool treatasdelta = false) const;
    [[nodiscard]] bool Compare(const String &other, bool casesensitive = true) const noexcept;

    //void Format(const String &format, ...); //not implemented yet
    //String SpanIncluding(const String &charset); //not implemented yet

    [[nodiscard]] int Str_atoi() const noexcept {
#ifdef _DEBUG_FULLDIAG
        char *end;
        errno = 0;
        const long sl = strtol(buf, &end, 10);
        if (end == buf) {
            ODSF("atoi_replace %s: not a decimal number\n", buf);
        } else if ('\0' != *end) {
            ODSF("atoi_replace %s: extra characters at end of input: %s\n", buf, end);
        } else if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno) {
            ODSF("atoi_replace %s out of range of type long\n", buf);
        } else if (sl > INT_MAX) {
            ODSF("atoi_replace %ld greater than INT_MAX\n", sl);
        } else if (sl < INT_MIN) {
            ODSF("atoi_replace %ld less than INT_MIN\n", sl);
        } else {
            return (int)sl;
        }
        return 0;
#else
        return static_cast<int>(strtol(buf, nullptr, 10));
#endif
    }

    [[nodiscard]] long Str_atol() const noexcept {
        return strtol(buf, nullptr, 10);
    }

    [[nodiscard]] float Str_atof() const noexcept {
        return strtof(buf, nullptr);
    }

    [[nodiscard]] double Str_atod() const noexcept {
        return strtod(buf, nullptr);
    }

    [[nodiscard]] ULONG Str_atoul() const noexcept {
        return strtoul(buf, nullptr, 10);
    }

    [[nodiscard]] ULONGLONG Str_atoull() const noexcept {
        return strtoull(buf, nullptr, 10);
    }

    [[nodiscard]] int64_t Str_atoll() const noexcept {
        //the same as "long long"
        return strtoll(buf, nullptr, 10);
    }

    static String GetAppPath();
    static String GetDLLsPath();
    static String GetOsPath();
    static String GetTempPathHash();
    static String GetTempFilename(const String &prefix);
    static String GetAppDataPath();
    static String GetMyDocumentsPath();
    static String GetAppName();
    static String GetRegisteredOwner();
    static String GetLastSystemError();
    static String GetLogFileName();

    static String Seperator() noexcept; // " / "
    static String Seperator2() noexcept; // "|"
    static String Percent() noexcept; // "%"
    static String Comma_Space() noexcept; // ", "
    static String Space() noexcept; // " "
    static String Grad() noexcept; // "\xB0"
    static String Point() noexcept; // "."
#if defined (__INTEL_LLVM_COMPILER)
    PLUGINEXPORT float GetCM() const;
#else
    PLUGINEXPORT [[nodiscard]] float GetCM() const;
#endif
    friend std::ostream &operator<<(std::ostream &os, const String &val) {
        os << val.Get_const_char();
        return os;
    }
};

HASH_INLINE String::String(String &&init) noexcept {
    if (const size_t s_size = init.GetLength(); s_size > 0) {
        buf = STRINGALLOC(s_size);
        memcpy(buf, init.buf, s_size);
    }
}

HASH_INLINE String::String(const String &init) noexcept {
    if (const size_t s_size = init.GetLength(); s_size > 0) {
        buf = STRINGALLOC(s_size);
        memcpy(buf, init.buf, s_size);
    }
}

HASH_INLINE String::String(const char *init) noexcept {
    if (init) {
        if (const size_t s_size = strlen(init); s_size > 0) {
            buf = STRINGALLOC(s_size);
            memcpy(buf, init, s_size);
        }
    }
}

/*
HASH_INLINE String::String(const char *init, int count) {
    buf = STRINGALLOC(count);
    memcpy(buf, init, count);
}
*/
HASH_INLINE String::String(const char init) noexcept {
    buf = STRINGALLOC(1);
    buf[0] = init;
}

HASH_INLINE String::String(const unsigned char init) noexcept {
    buf = STRINGALLOC(1);
    buf[0] = static_cast<char>(init);
}

HASH_INLINE String::String(const std::string &initstr) noexcept {
    if (const size_t s_size = initstr.length(); s_size > 0) {
        buf = STRINGALLOC(s_size);
        memcpy(buf, initstr.data(), s_size);
    }
}

HASH_INLINE String::String(const CString &initcstr) noexcept {
    if (const size_t s_size = initcstr.GetLength(); s_size > 0) {
        buf = STRINGALLOC(s_size);
        memcpy(buf, initcstr.GetString(), s_size);
    }
}

HASH_INLINE String::String(const char init, const int count) noexcept {
    ASSERT(count > 0);
    buf = STRINGALLOC(count);
    memset(buf, init, count);
    buf[count] = '\0';
}

HASH_INLINE String::String(const SSHORT number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const USHORT number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const int number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const UINT number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const int64_t number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const uint64_t number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const float number) noexcept {
    const std::string temp = ToCharsFloat(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const double number) noexcept {
    const std::string temp = ToCharsDouble(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const float number, const int precision) noexcept {
    const std::string temp = ToCharsFloat(number, precision);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const double number, const int precision) noexcept {
    const std::string temp = ToCharsDouble(number, precision);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const LONG number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const ULONG number) noexcept {
    const std::string temp = ToChars(number);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const Vector &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.x) + " " + ToCharsFloat(initval.y) + " " + ToCharsFloat(initval.z);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const Vector2 &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.x) + " " + ToCharsFloat(initval.y);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const Vector4 &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.x) + " " + ToCharsFloat(initval.y) + " " + ToCharsFloat(initval.z) + " " + ToCharsFloat(initval.w);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const Quaternion &initval) noexcept {
    const std::string temp = ToCharsFloat(initval[0]) + " " + ToCharsFloat(initval[1]) + " " + ToCharsFloat(initval[2]) + " " + ToCharsFloat(initval[3]);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const RotateEuler &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.x) + " " + ToCharsFloat(initval.y) + " " + ToCharsFloat(initval.z);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const RGBFloat &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.m_blue) + " " + ToCharsFloat(initval.m_green) + " " + ToCharsFloat(initval.m_red);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE String::String(const RGBAFloat &initval) noexcept {
    const std::string temp = ToCharsFloat(initval.m_color.m_blue) + " " + ToCharsFloat(initval.m_color.m_green) + " " + ToCharsFloat(initval.m_color.m_red) + " " + ToCharsFloat(initval.m_alpha);
    const size_t len = temp.length();
    buf = STRINGALLOC(len);
    memcpy(buf, temp.data(), len);
}

HASH_INLINE size_t String::GetLength() const noexcept {
    if (buf)
        return strlen(buf);
    return 0;
}

HASH_INLINE int String::GetLength_Int() const noexcept {
    return (int)GetLength();
}

HASH_INLINE String operator+(const String &left, const String &right) noexcept {
    String result(left);
    if (right.IsEmpty())
        return result;
    result += right;
    return result;
}

HASH_INLINE String &String::operator=(const char *other) noexcept {
    STRINGFREE(buf)
    if (other) {
        const size_t s_size = strlen(other);
        buf = STRINGALLOC(s_size);
        memcpy(buf, other, s_size);
    }
    return *this;
}

HASH_INLINE String &String::operator=(const unsigned char *other) noexcept {
    STRINGFREE(buf)
    if (other) {
        const size_t s_size = strlen((const char *)other);
        buf = STRINGALLOC(s_size);
        memcpy(buf, other, s_size);
    }
    return *this;
}

HASH_INLINE String &String::operator=(CString init) {
    STRINGFREE(buf)
    if (const size_t s_size = init.GetLength(); s_size > 0) {
        buf = STRINGALLOC(s_size);
        memcpy(buf, init.GetBuffer(), s_size);
    }
    return *this;
}

HASH_INLINE void String::Set(const char *other, const int len) noexcept {
    STRINGFREE(buf)
    if (other && len) {
        buf = STRINGALLOC(len);
        memcpy(buf, other, len);
        buf[len] = '\0';
    }
}

#if defined(__INTEL_LLVM_COMPILER)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif
static bool IsRelativePath(const String &path) noexcept {
    if (path[0] == SEPARATOR && path[1] == SEPARATOR)
        return false;
    if (path[1] == ':')
        return false;
    return true;
}
#if defined(__INTEL_LLVM_COMPILER)
#pragma clang diagnostic pop
#endif

void StripOffName(String &);
FILEIOEXPORT String FormatTime(int sec, bool force = false);
FILEIOEXPORT void AddNameToPath(String &path, const String &name) noexcept;
FILEIOEXPORT String CombineNameToPath(const String &path, const String &name) noexcept;
FILEIOEXPORT String AddNameToExeDirectory(const String &name) noexcept;
FILEIOEXPORT String AddNameToDataDirectory(const String &name) noexcept;
FILEIOEXPORT void FreeAppPath() noexcept;
FILEIOEXPORT void AFXAPI DDX_Text(CDataExchange *pDX, int nIDC, String &value);
FILEIOEXPORT String NativeToUniversal(const String &nativepath) noexcept;
FILEIOEXPORT String UniversalToNative(const String &puniversalpath);
//the following functions only work on Universal Paths.  (Separator '/' on Mac and PC)
FILEIOEXPORT int GetPathDepth(const String &path);
FILEIOEXPORT int MatchPathDepth(const String &path1, const String &path2);
FILEIOEXPORT String ShortenPath(const String &path, int skip) noexcept; //shortens from the front, by the number of folders indicated in skip
enum {
    UNIT_NONE,
    UNIT_CENTIMETERS,
    UNIT_METERS,
    UNIT_FEET,
    UNIT_INCHES,
    UNIT_FEETANDINCHES,
    UNIT_PERCENTAGE,
    UNIT_ANGLE,
    UNIT_SMPTE,
    UNIT_FRAMES
};

PLUGINEXPORT int GetMeasurementUnits() noexcept;
PLUGINEXPORT void SetMeasurementUnits(int pmeasurementunits) noexcept;
PLUGINEXPORT int GetDefaultPrecision() noexcept;
PLUGINEXPORT void SetDefaultPrecision(int precision) noexcept;
PLUGINEXPORT String UnitToString(float cm, int pmeasurementunits = -1, int fps = -1, double modulo = 0.001) noexcept;
PLUGINEXPORT void AFXAPI DDX_Unit(CDataExchange *pDX, int nIDC, float &cm);
PLUGINEXPORT void AFXAPI DDV_MinMaxUnit(CDataExchange *pDX, float const &value, float minVal, float maxVal);
