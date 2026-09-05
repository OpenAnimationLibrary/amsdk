#pragma once
#include <afxwin.h>
#include "PatchDrawCore.h"
#include "resource.h"
#include <optional>
#include <string>

constexpr UINT WM_PATCH_DRAW_CHANGED = WM_APP + 241;
class PatchCanvas final : public CWnd {
    patchdraw::Document& document_;
    std::optional<patchdraw::XY> hover_;
    CRect area_{};
    double scale_ = 1;
    bool tracking_ = false;
    double diameter_ = .5;
    bool paint_ = true;
    void geometry();
    patchdraw::XY position(CPoint p) const;
    void changed();
    void failed(const char* reason);
public:
    explicit PatchCanvas(patchdraw::Document& document) : document_(document) {}
    double diameter() const { return diameter_; }
    void brush(bool paint, double diameter);
    void cancelStroke(bool notify = true);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC*);
    afx_msg void OnLButtonDown(UINT,CPoint);
    afx_msg void OnMouseMove(UINT,CPoint);
    afx_msg void OnLButtonUp(UINT,CPoint);
    afx_msg void OnCaptureChanged(CWnd*);
    afx_msg void OnCancelMode();
    afx_msg void OnKillFocus(CWnd*);
    afx_msg void OnSize(UINT,int,int);
    afx_msg LRESULT OnMouseLeave(WPARAM,LPARAM);
    DECLARE_MESSAGE_MAP()
};

class PatchDrawDialog final : public CDialog {
    patchdraw::Document document_;
    PatchCanvas canvas_;
    std::optional<patchdraw::Grid> exported_;
    std::string hostVersion_;
    bool ready_ = false;
    UINT dpi_ = 96;
    void layout();
    void refresh();
    void report(const char* reason);
    bool discardPrompt();
public:
    PatchDrawDialog(CWnd* owner, std::string hostVersion);
    BOOL OnInitDialog() override;
    BOOL PreTranslateMessage(MSG*) override;
    void OnOK() override {} // Enter never exports/builds/closes implicitly.
    void OnCancel() override;
    afx_msg void OnBrush();
    afx_msg void OnNewDrawing();
    afx_msg void OnUndo();
    afx_msg void OnRedo();
    afx_msg void OnClear();
    afx_msg void OnExport();
    afx_msg void OnSize(UINT,int,int);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO*);
    afx_msg void OnActivate(UINT,CWnd*,BOOL);
    afx_msg LRESULT OnCanvasChanged(WPARAM,LPARAM);
    afx_msg LRESULT OnDpiChanged(WPARAM,LPARAM);
    DECLARE_MESSAGE_MAP()
};
