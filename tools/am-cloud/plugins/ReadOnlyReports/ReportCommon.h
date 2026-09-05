#pragma once
#include "StdAfx.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HCP.h"
#include "SDK/HModel.h"
#include "SDK/HPatch.h"
#include "ReportMath.h"
#include <exception>
#include <stdexcept>
#include <unordered_set>

namespace am_reports {
struct Budget {
    ULONGLONG start = GetTickCount64();
    std::size_t steps = 0;
    void step() {
        if (++steps > 100000 || GetTickCount64() - start > 2000)
            throw std::runtime_error("Report stopped at the traversal limit. No complete totals are reported. Test a smaller model/selection.");
    }
};

struct Points {
    std::unordered_set<HCP *> records;
    std::unordered_set<HCP *> heads;
    PositionStats positions;
    std::size_t missingHead = 0;
    std::size_t missingPosition = 0;
    void add(HCP *cp) {
        if (!cp) throw std::runtime_error("The SDK returned a null control point.");
        if (!records.insert(cp).second) return;
        HCP *head = cp->GetHead();
        if (!head) { ++missingHead; return; }
        if (!heads.insert(head).second) return;
        const Vector *p = head->GetModelPosition();
        if (!p) { ++missingPosition; return; }
        positions.add(p->x, p->y, p->z);
    }
    void append(CString &text) const {
        text.AppendFormat("CP records: %llu\nDistinct attachment heads: %llu\n"
                          "Missing heads / positions: %llu / %llu\nInvalid coordinates excluded: %llu\n",
                          static_cast<unsigned long long>(records.size()),
                          static_cast<unsigned long long>(heads.size()),
                          static_cast<unsigned long long>(missingHead),
                          static_cast<unsigned long long>(missingPosition),
                          static_cast<unsigned long long>(positions.invalid));
        if (!positions.count) {
            text += "No finite positions available for bounds or mean.\n";
            return;
        }
        const auto center = positions.mean();
        text.AppendFormat("Model-space minimum: (%.6g, %.6g, %.6g)\n"
                          "Model-space maximum: (%.6g, %.6g, %.6g)\n"
                          "Mean of finite attachment-head positions: (%.6g, %.6g, %.6g)\n",
                          positions.minimum[0], positions.minimum[1], positions.minimum[2],
                          positions.maximum[0], positions.maximum[1], positions.maximum[2],
                          center[0], center[1], center[2]);
    }
};

template<class Function>
BOOL guarded(const char *title, Function function) {
    try { return function(); }
    catch (CException *error) {
        if (error) error->Delete();
        MessageBoxA(nullptr, "MFC could not complete the read-only report.", title, MB_OK | MB_ICONERROR);
    }
    catch (const std::exception &error) {
        MessageBoxA(nullptr, error.what(), title, MB_OK | MB_ICONERROR);
    }
    catch (...) {
        MessageBoxA(nullptr, "The read-only report failed. No complete results are available.", title, MB_OK | MB_ICONERROR);
    }
    return FALSE;
}

inline CString heading(const char *title, const char *context) {
    CString text;
    const String version = GetAMVersion();
    text.Format("%s v1\nA:M: %s\nContext: %s\n\n", title, version.Get(), context);
    return text;
}

inline void finish(CString &text, BOOL before, HTreeObject *object) {
    text.AppendFormat("\nSDK object modified flag before / after: %s / %s\n",
                      before ? "yes" : "no", object->IsModified() ? "yes" : "no");
    text += "Read-only SDK queries; no editing or save commands called.\n"
            "Positions are raw model space (SDK units), not animation/world space.\n"
            "Counts describe SDK records/attachment heads, not rendered vertices.";
    AfxMessageBox(text, MB_OK | MB_ICONINFORMATION);
}
}  // namespace am_reports
