// Terrain Wizard interaction reference: Plugin/HXT/Terrain/WizardDialog.cpp at
// 2aef54165a47a05f25f83e4a9e4a10a1e1716878. New bounded canvas implementation;
// no legacy raster/noise/height routines or SDK model-editing code are copied.
#include <afxwin.h>
#include "CanvasDialog.h"
#include "SavePlan.h"
#include <commdlg.h>
#include <exception>
#include <vector>

BEGIN_MESSAGE_MAP(PatchCanvas,CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_CAPTURECHANGED()
    ON_WM_CANCELMODE()
    ON_WM_KILLFOCUS()
    ON_WM_SIZE()
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()
void PatchCanvas::geometry() {
    CRect r; GetClientRect(&r);
    const int pad=8, side=std::max(1,std::min(r.Width(),r.Height())-2*pad);
    area_=CRect((r.Width()-side)/2,(r.Height()-side)/2,(r.Width()+side)/2,(r.Height()+side)/2);
    scale_=static_cast<double>(area_.Width())/document_.grid().side;
}
patchdraw::XY PatchCanvas::position(CPoint p) const {
    // Screen Y down -> model Y up; the document never stores screen pixels.
    return {(p.x-area_.left)/scale_, (area_.bottom-p.y)/scale_};
}
void PatchCanvas::changed() {
    Invalidate(FALSE);
    if(GetParent()) GetParent()->PostMessage(WM_PATCH_DRAW_CHANGED);
}
void PatchCanvas::failed(const char* reason) {
    cancelStroke();
    ::MessageBoxA(GetSafeHwnd(),reason,"Patch Draw canvas error",MB_OK|MB_ICONERROR);
}
void PatchCanvas::brush(bool paint,double diameter) {
    cancelStroke(); paint_=paint; diameter_=diameter; changed();
}
void PatchCanvas::cancelStroke(bool notify) {
    document_.cancel(); // Reset first: our own ReleaseCapture generates capture loss.
    if(::GetCapture()==GetSafeHwnd()) ::ReleaseCapture();
    if(notify) changed(); else Invalidate(FALSE);
}
BOOL PatchCanvas::OnEraseBkgnd(CDC*) { return TRUE; }
void PatchCanvas::OnPaint() {
    CPaintDC screen(this);
    try {
        geometry(); CRect client; GetClientRect(&client);
        if(client.Width()<1 || client.Height()<1) return;
        const auto& grid=document_.grid();
        const auto topology=patchdraw::Compile(grid);
        CBitmap bitmap; CDC buffer;
        if(!buffer.CreateCompatibleDC(&screen) || !bitmap.CreateCompatibleBitmap(&screen,client.Width(),client.Height()))
            throw std::runtime_error("Cannot allocate canvas backing bitmap.");
        CBitmap* old=buffer.SelectObject(&bitmap);
        // Every drawing resource below is stack-owned and restored before exit.
        buffer.FillSolidRect(client,GetSysColor(COLOR_3DFACE));
        buffer.FillSolidRect(area_,RGB(250,250,250));
        const COLORREF colors[]={RGB(83,148,196),RGB(93,169,137),RGB(194,139,82),RGB(164,123,190)};
        for(std::size_t i=0;i<topology.faces.size();++i) {
            const auto [x,y]=topology.faceCells[i];
            const int l=area_.left+static_cast<int>(std::lround(x*scale_/2));
            const int r=area_.left+static_cast<int>(std::lround((x+1)*scale_/2));
            const int t=area_.bottom-static_cast<int>(std::lround((y+1)*scale_/2));
            const int b=area_.bottom-static_cast<int>(std::lround(y*scale_/2));
            const auto component=static_cast<unsigned>(topology.components[topology.faces[i][0]]);
            buffer.FillSolidRect(l,t,r-l,b-t,colors[component%4]);
        }
        HGDIOBJ priorPen=::SelectObject(buffer.GetSafeHdc(),::GetStockObject(DC_PEN));
        ::SetDCPenColor(buffer.GetSafeHdc(),RGB(184,204,218));
        for(auto e:topology.edges) {
            const auto a=topology.vertices[e[0]], b=topology.vertices[e[1]];
            buffer.MoveTo(area_.left+static_cast<int>(std::lround(a.first*scale_/2)),area_.bottom-static_cast<int>(std::lround(a.second*scale_/2)));
            buffer.LineTo(area_.left+static_cast<int>(std::lround(b.first*scale_/2)),area_.bottom-static_cast<int>(std::lround(b.second*scale_/2)));
        }
        ::SelectObject(buffer.GetSafeHdc(),priorPen);
        priorPen=::SelectObject(buffer.GetSafeHdc(),::GetStockObject(DC_PEN));
        ::SetDCPenColor(buffer.GetSafeHdc(),RGB(100,108,118));
        for(int i=0;i<=grid.side;++i) {
            const int x=area_.left+static_cast<int>(std::lround(i*scale_));
            const int y=area_.bottom-static_cast<int>(std::lround(i*scale_));
            buffer.MoveTo(x,area_.top); buffer.LineTo(x,area_.bottom);
            buffer.MoveTo(area_.left,y); buffer.LineTo(area_.right,y);
        }
        ::SelectObject(buffer.GetSafeHdc(),priorPen);
        if(hover_) {
            const int state=buffer.SaveDC(); buffer.IntersectClipRect(area_);
            HGDIOBJ p=::SelectObject(buffer.GetSafeHdc(),::GetStockObject(DC_PEN));
            HGDIOBJ b=::SelectObject(buffer.GetSafeHdc(),::GetStockObject(NULL_BRUSH));
            ::SetDCPenColor(buffer.GetSafeHdc(),paint_?RGB(20,60,95):RGB(180,45,30));
            const int x=area_.left+static_cast<int>(std::lround(hover_->x*scale_));
            const int y=area_.bottom-static_cast<int>(std::lround(hover_->y*scale_));
            const int radius=std::max(1,static_cast<int>(std::lround(diameter_*scale_/2)));
            buffer.Ellipse(x-radius,y-radius,x+radius+1,y+radius+1);
            ::SelectObject(buffer.GetSafeHdc(),p); ::SelectObject(buffer.GetSafeHdc(),b); buffer.RestoreDC(state);
        }
        screen.BitBlt(0,0,client.Width(),client.Height(),&buffer,0,0,SRCCOPY);
        buffer.SelectObject(old);
    } catch(CException* error) {
        error->Delete(); screen.TextOut(10,10,"Canvas resources unavailable.");
    } catch(const std::exception&) { screen.TextOut(10,10,"Canvas preview unavailable."); }
}
void PatchCanvas::OnLButtonDown(UINT,CPoint p) {
    try {
        geometry(); if(!area_.PtInRect(p)) return;
        auto point=position(p);
        // The top border maps to side exactly; clamp only that included pixel.
        point.y=std::min(point.y,document_.grid().side-1.0/1024.0);
        SetFocus(); SetCapture();
        if(::GetCapture()!=GetSafeHwnd()) throw std::runtime_error("Mouse capture unavailable.");
        document_.begin(point,diameter_/2,paint_); hover_=point; changed();
    } catch(const std::exception& e) { failed(e.what()); }
}
void PatchCanvas::OnMouseMove(UINT flags,CPoint p) {
    try {
        geometry(); hover_=position(p);
        if(!tracking_) { TRACKMOUSEEVENT t{sizeof(t),TME_LEAVE,GetSafeHwnd(),0}; tracking_=TrackMouseEvent(&t)!=FALSE; }
        if(document_.active()) {
            if(!(flags&MK_LBUTTON)) cancelStroke();
            else document_.move(*hover_);
        }
        changed();
    } catch(const std::exception& e) { failed(e.what()); }
}
void PatchCanvas::OnLButtonUp(UINT,CPoint p) {
    try {
        if(document_.active()) document_.end(position(p));
        if(::GetCapture()==GetSafeHwnd()) ::ReleaseCapture();
        changed();
    } catch(const std::exception& e) { failed(e.what()); }
}
void PatchCanvas::OnCaptureChanged(CWnd* other) { document_.cancel(); changed(); CWnd::OnCaptureChanged(other); }
void PatchCanvas::OnCancelMode() { cancelStroke(); CWnd::OnCancelMode(); }
void PatchCanvas::OnKillFocus(CWnd* other) { cancelStroke(); CWnd::OnKillFocus(other); }
void PatchCanvas::OnSize(UINT type,int x,int y) { CWnd::OnSize(type,x,y); cancelStroke(); geometry(); }
LRESULT PatchCanvas::OnMouseLeave(WPARAM,LPARAM) { tracking_=false; hover_.reset(); Invalidate(FALSE); return 0; }

BEGIN_MESSAGE_MAP(PatchDrawDialog,CDialog)
    ON_BN_CLICKED(IDC_DRAW,OnBrush)
    ON_BN_CLICKED(IDC_ERASE,OnBrush)
    ON_CBN_SELCHANGE(IDC_BRUSH,OnBrush)
    ON_BN_CLICKED(IDC_NEW_DRAWING,OnNewDrawing)
    ON_BN_CLICKED(IDC_UNDO_DRAWING,OnUndo)
    ON_BN_CLICKED(IDC_REDO_DRAWING,OnRedo)
    ON_BN_CLICKED(IDC_CLEAR_DRAWING,OnClear)
    ON_BN_CLICKED(IDC_EXPORT_PLAN,OnExport)
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
    ON_WM_ACTIVATE()
    ON_MESSAGE(WM_PATCH_DRAW_CHANGED,OnCanvasChanged)
    ON_MESSAGE(WM_DPICHANGED,OnDpiChanged)
END_MESSAGE_MAP()
PatchDrawDialog::PatchDrawDialog(CWnd* owner,std::string version)
    : CDialog(IDD_PATCH_DRAW,owner),canvas_(document_),hostVersion_(std::move(version)) {}
BOOL PatchDrawDialog::OnInitDialog() {
    CDialog::OnInitDialog();
    if(!canvas_.SubclassDlgItem(IDC_CANVAS,this)) { EndDialog(IDABORT); return TRUE; }
    auto* brush=static_cast<CComboBox*>(GetDlgItem(IDC_BRUSH));
    for(const auto* name : {"0.5","1","2","4"}) brush->AddString(name);
    brush->SetCurSel(0);
    auto* grid=static_cast<CComboBox*>(GetDlgItem(IDC_GRID));
    for(const auto* name : {"3","4","8","12","16"}) grid->AddString(name);
    grid->SetCurSel(2); SetDlgItemInt(IDC_CELL_SIZE,10);
    CheckRadioButton(IDC_DRAW,IDC_ERASE,IDC_DRAW);
    dpi_=GetDpiForWindow(GetSafeHwnd()); if(!dpi_) dpi_=96;
    ready_=true;
    CRect current; GetWindowRect(&current);
    SetWindowPos(nullptr,0,0,std::max(current.Width(),MulDiv(750,static_cast<int>(dpi_),96)),
        std::max(current.Height(),MulDiv(690,static_cast<int>(dpi_),96)),SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
    layout(); refresh(); return TRUE;
}
void PatchDrawDialog::layout() {
    if(!ready_) return;
    CRect c; GetClientRect(&c);
    const int p=MulDiv(10,static_cast<int>(dpi_),96), row=MulDiv(24,static_cast<int>(dpi_),96);
    const int right=MulDiv(225,static_cast<int>(dpi_),96), x=std::max(6*p,c.Width()-right-p);
    auto place=[&](int id,int l,int t,int w,int h) { if(auto* a=GetDlgItem(id)) a->MoveWindow(l,t,std::max(1,w),std::max(1,h)); };
    place(IDC_CAPTION,p,p,c.Width()-2*p,row);
    place(IDC_CANVAS,p,3*p+row,x-2*p,c.Height()-10*p-3*row);
    place(IDC_DRAW,x,3*p+row,right/2,row); place(IDC_ERASE,x+right/2,3*p+row,right/2,row);
    int y=4*p+2*row;
    place(IDC_BRUSH_LABEL,x,y,right,row); place(IDC_BRUSH,x,y+row,right,5*row);
    place(IDC_BRUSH_SIZE,x,y+2*row+p,right,2*row);
    y+=4*row+2*p;
    place(IDC_GRID_LABEL,x,y,right,row); place(IDC_GRID,x,y+row,right/3,6*row);
    place(IDC_NEW_DRAWING,x+right/3+p,y+row,right*2/3-p,row);
    place(IDC_CELL_LABEL,x,y+2*row+p,right,row); place(IDC_CELL_SIZE,x,y+3*row+p,right/3,row);
    y+=4*row+2*p;
    place(IDC_UNDO_DRAWING,x,y,right/3-p,row); place(IDC_REDO_DRAWING,x+right/3,y,right/3-p,row); place(IDC_CLEAR_DRAWING,x+right*2/3,y,right/3,row);
    place(IDC_SUMMARY,x,y+row+p,right,c.Height()-(y+row+p)-(3*row+4*p));
    place(IDC_GUIDE,p,c.Height()-3*row-3*p,c.Width()-2*p,2*row);
    place(IDC_SESSION,p,c.Height()-row-p,c.Width()-right-3*p,row);
    place(IDC_EXPORT_PLAN,c.Width()-right-p,c.Height()-row-p,right*2/3-p,row);
    place(IDCANCEL,c.Width()-right/3-p,c.Height()-row-p,right/3,row);
}
void PatchDrawDialog::refresh() {
    if(!ready_) return;
    const auto& g=document_.grid(); const auto t=patchdraw::Compile(g);
    std::ostringstream s;
    s<<"Active grid: "<<g.side<<" x "<<g.side<<"; XY plane\nPainted cells: "<<g.count()<<"\nProposed quads: "<<t.faces.size()
     <<"\nComponents: "<<t.componentCount<<"; holes: "<<t.holeCount
     <<"\nLogical points: "<<t.vertices.size()<<"\nSplines: "<<t.splines.size()<<"; CP records: "<<t.occurrences
     <<"\n\n"<<(document_.active()?"Stroke in progress (Escape to cancel).":patchdraw::ExportProblem(t).empty()?"Ready to export a plan.":patchdraw::ExportProblem(t));
    ::SetDlgItemTextA(GetSafeHwnd(),IDC_SUMMARY,s.str().c_str());
    std::ostringstream b; b<<"Brush: "<<canvas_.diameter()*g.cellSize<<" model units\nCell: "<<g.cellSize<<" units; 4 quads/cell";
    ::SetDlgItemTextA(GetSafeHwnd(),IDC_BRUSH_SIZE,b.str().c_str());
    const bool active=document_.active();
    for(int id:{IDC_DRAW,IDC_ERASE,IDC_BRUSH,IDC_GRID,IDC_CELL_SIZE,IDC_NEW_DRAWING}) GetDlgItem(id)->EnableWindow(!active);
    GetDlgItem(IDC_UNDO_DRAWING)->EnableWindow(document_.canUndo()); GetDlgItem(IDC_REDO_DRAWING)->EnableWindow(document_.canRedo());
    GetDlgItem(IDC_CLEAR_DRAWING)->EnableWindow(!active && g.count()!=0);
    GetDlgItem(IDC_EXPORT_PLAN)->EnableWindow(!active && patchdraw::ExportProblem(t).empty());
    std::string line="A:M "+hostVersion_+" | Canvas only; no model editing";
    if(document_.dropped()) line="Undo history capped: oldest "+std::to_string(document_.dropped())+" steps dropped";
    ::SetDlgItemTextA(GetSafeHwnd(),IDC_SESSION,line.c_str());
}
void PatchDrawDialog::report(const char* reason) { canvas_.cancelStroke(false); ::MessageBoxA(GetSafeHwnd(),reason,"Patch Draw",MB_OK|MB_ICONERROR); }
bool PatchDrawDialog::discardPrompt() {
    if(document_.grid().count()==0 || (exported_ && *exported_==document_.grid())) return true;
    return MessageBox("Discard this unexported drawing? A:M geometry is unchanged.","Patch Draw",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES;
}
BOOL PatchDrawDialog::PreTranslateMessage(MSG* msg) {
    if(msg->message==WM_KEYDOWN) {
        if(msg->wParam==VK_ESCAPE && document_.active()) { canvas_.cancelStroke(); return TRUE; }
        if(GetKeyState(VK_CONTROL)<0 && ::GetFocus()==canvas_.GetSafeHwnd()) {
            if(msg->wParam=='Z') { OnUndo(); return TRUE; }
            if(msg->wParam=='Y') { OnRedo(); return TRUE; }
        }
    }
    return CDialog::PreTranslateMessage(msg);
}
void PatchDrawDialog::OnCancel() {
    if(document_.active()) { canvas_.cancelStroke(); return; }
    if(discardPrompt()) { canvas_.cancelStroke(); CDialog::OnCancel(); }
}
void PatchDrawDialog::OnBrush() {
    const auto selected=static_cast<CComboBox*>(GetDlgItem(IDC_BRUSH))->GetCurSel();
    constexpr double diameters[]={.5,1,2,4};
    canvas_.brush(IsDlgButtonChecked(IDC_ERASE)!=BST_CHECKED,diameters[selected>=0 && selected<4?selected:0]);
}
void PatchDrawDialog::OnNewDrawing() {
    try {
        canvas_.cancelStroke();
        constexpr int sizes[]={3,4,8,12,16};
        const int selection=static_cast<CComboBox*>(GetDlgItem(IDC_GRID))->GetCurSel();
        BOOL valid=FALSE; const UINT size=GetDlgItemInt(IDC_CELL_SIZE,&valid,FALSE);
        if(!valid || size<1 || size>1000 || selection<0 || selection>=5) throw std::runtime_error("Choose grid and integer cell size 1-1000.");
        if(!discardPrompt()) return;
        document_.reset(patchdraw::Grid(sizes[selection],static_cast<int>(size))); exported_.reset(); canvas_.Invalidate(FALSE); refresh();
    } catch(const std::exception& e) { report(e.what()); }
}
void PatchDrawDialog::OnUndo() { try { if(!document_.active()) document_.undo(); canvas_.Invalidate(FALSE); refresh(); } catch(const std::exception& e) { report(e.what()); } }
void PatchDrawDialog::OnRedo() { try { if(!document_.active()) document_.redo(); canvas_.Invalidate(FALSE); refresh(); } catch(const std::exception& e) { report(e.what()); } }
void PatchDrawDialog::OnClear() { try { if(!document_.active()) document_.clear(); canvas_.Invalidate(FALSE); refresh(); } catch(const std::exception& e) { report(e.what()); } }
void PatchDrawDialog::OnExport() {
    if(document_.active()) return;
    try {
        const auto grid=document_.grid(); const auto topology=patchdraw::Compile(grid);
        const auto json=patchdraw::ToPlan(grid,topology);
        std::vector<wchar_t> name(32768,L'\0'); const std::wstring initial=L"PatchDraw.json"; std::copy(initial.begin(),initial.end(),name.begin());
        OPENFILENAMEW choose{}; choose.lStructSize=sizeof(choose); choose.hwndOwner=GetSafeHwnd();
        choose.lpstrTitle=L"Export NEW Script Builder JSON (existing files are not overwritten)";
        choose.lpstrFilter=L"Script Builder plan (*.json)\0*.json\0\0"; choose.lpstrDefExt=L"json";
        choose.lpstrFile=name.data(); choose.nMaxFile=static_cast<DWORD>(name.size()); choose.Flags=OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_EXPLORER;
        if(!GetSaveFileNameW(&choose)) { if(CommDlgExtendedError()) throw std::runtime_error("Export file chooser failed."); return; }
        patchdraw::SaveNewPlan(std::filesystem::path(name.data()),json); exported_=grid;
        MessageBox("Plan exported. Close this canvas, then choose that JSON in A:M Script Builder.\n\nThe export did not create or edit any A:M model. The JSON is model data, not a reloadable drawing recipe.","Patch Draw",MB_OK|MB_ICONINFORMATION);
        refresh();
    } catch(const std::exception& e) { report(e.what()); }
}
void PatchDrawDialog::OnSize(UINT type,int x,int y) { CDialog::OnSize(type,x,y); if(ready_) { canvas_.cancelStroke(); layout(); } }
void PatchDrawDialog::OnGetMinMaxInfo(MINMAXINFO* value) {
    CDialog::OnGetMinMaxInfo(value); const auto dpi=GetSafeHwnd()?GetDpiForWindow(GetSafeHwnd()):96;
    value->ptMinTrackSize.x=MulDiv(750,static_cast<int>(dpi?dpi:96),96);
    value->ptMinTrackSize.y=MulDiv(690,static_cast<int>(dpi?dpi:96),96);
}
void PatchDrawDialog::OnActivate(UINT state,CWnd* other,BOOL minimized) { CDialog::OnActivate(state,other,minimized); if(ready_ && state==WA_INACTIVE) canvas_.cancelStroke(); }
LRESULT PatchDrawDialog::OnCanvasChanged(WPARAM,LPARAM) { try { refresh(); } catch(const std::exception&) {
    canvas_.cancelStroke(false); GetDlgItem(IDC_EXPORT_PLAN)->EnableWindow(FALSE);
    SetDlgItemText(IDC_SUMMARY,"Preview unavailable. Export disabled; close and reopen the canvas.");
} return 0; }
LRESULT PatchDrawDialog::OnDpiChanged(WPARAM w,LPARAM l) {
    if(ready_) canvas_.cancelStroke();
    dpi_=HIWORD(w); if(!dpi_) dpi_=96;
    const auto* r=reinterpret_cast<const RECT*>(l);
    if(r) SetWindowPos(nullptr,r->left,r->top,r->right-r->left,r->bottom-r->top,SWP_NOZORDER|SWP_NOACTIVATE);
    layout(); return 0;
}
