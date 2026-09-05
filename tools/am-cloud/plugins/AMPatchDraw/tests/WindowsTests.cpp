#include <afxwin.h>
#include "../CanvasDialog.h"
#include "../SavePlan.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

CWinApp application;
void Check(bool good,const char* reason){if(!good)throw std::runtime_error(reason);}
void Pump(){MSG m{};int count=0;while(PeekMessage(&m,nullptr,0,0,PM_REMOVE)){
    if(++count>5000)throw std::runtime_error("Unbounded UI notification loop");
    TranslateMessage(&m);DispatchMessage(&m);
}}
CPoint Point(CWnd* c,double x,double y,int side=8){
    CRect r;c->GetClientRect(r);const int s=std::max(1,std::min(r.Width(),r.Height())-16);
    return { (r.Width()-s)/2+static_cast<int>(std::lround(x*s/side)),
             (r.Height()+s)/2-static_cast<int>(std::lround(y*s/side)) };
}
void Send(CWnd* c,UINT msg,CPoint p,WPARAM flags=0){ c->SendMessage(msg,flags,MAKELPARAM(p.x,p.y));Pump(); }
void Count(PatchDrawDialog& d,int expected){CString text;d.GetDlgItemText(IDC_SUMMARY,text);
    const std::string match="Painted cells: "+std::to_string(expected)+"\n";
    Check(std::string(text.GetString()).find(match)!=std::string::npos,"Unexpected UI painted count");
}
void Click(PatchDrawDialog& d,int id){d.SendMessage(WM_COMMAND,MAKEWPARAM(id,BN_CLICKED),reinterpret_cast<LPARAM>(d.GetDlgItem(id)->GetSafeHwnd()));Pump();}
void SaveBitmap(HWND wnd,const std::filesystem::path& target){
    RECT r{};GetWindowRect(wnd,&r);const int w=r.right-r.left,h=r.bottom-r.top;
    BITMAPINFO info{};info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);info.bmiHeader.biWidth=w;
    info.bmiHeader.biHeight=-h;info.bmiHeader.biPlanes=1;info.bmiHeader.biBitCount=32;info.bmiHeader.biCompression=BI_RGB;
    void* pixels=nullptr;HDC screen=GetWindowDC(wnd);HDC buffer=CreateCompatibleDC(screen);
    HBITMAP bitmap=CreateDIBSection(screen,&info,DIB_RGB_COLORS,&pixels,nullptr,0);
    if(bitmap && buffer){
        HGDIOBJ old=SelectObject(buffer,bitmap);
        if(PrintWindow(wnd,buffer,2)){
            BITMAPFILEHEADER header{};header.bfType=0x4D42;header.bfOffBits=sizeof(header)+sizeof(info.bmiHeader);
            header.bfSize=header.bfOffBits+static_cast<DWORD>(w*h*4);
            std::ofstream file(target,std::ios::binary);file.write(reinterpret_cast<const char*>(&header),sizeof(header));
            file.write(reinterpret_cast<const char*>(&info.bmiHeader),sizeof(info.bmiHeader));file.write(static_cast<const char*>(pixels),static_cast<std::streamsize>(w)*h*4);
        }
        SelectObject(buffer,old);
    }
    if(bitmap)DeleteObject(bitmap);if(buffer)DeleteDC(buffer);if(screen)ReleaseDC(wnd,screen);
}
int main(int argc,char** argv){
    try{
        Check(argc==2,"Expected new working directory");const std::filesystem::path work(argv[1]);
        Check(AfxWinInit(GetModuleHandle(nullptr),nullptr,GetCommandLine(),0)!=FALSE,"Initialize MFC");
        PatchDrawDialog dialog(nullptr,"CI harness - not A:M");
        Check(dialog.Create(IDD_PATCH_DRAW)!=FALSE,"Create actual dialog and resources");
        dialog.ShowWindow(SW_SHOW);dialog.SetForegroundWindow();Pump();
        auto* canvas=dialog.GetDlgItem(IDC_CANVAS);Count(dialog,0);
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,.5),MK_LBUTTON);Count(dialog,1);
        Check(GetCapture()==canvas->GetSafeHwnd(),"Mouse captured");
        Send(canvas,WM_MOUSEMOVE,Point(canvas,7.5,.5),MK_LBUTTON);Count(dialog,8);
        Send(canvas,WM_LBUTTONUP,Point(canvas,10,.5));Check(GetCapture()!=canvas->GetSafeHwnd(),"Release outside canvas ends capture");
        Count(dialog,8);Click(dialog,IDC_UNDO_DRAWING);Count(dialog,0);Click(dialog,IDC_REDO_DRAWING);Count(dialog,8);
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,1.5),MK_LBUTTON);Count(dialog,9);
        MSG escape{};escape.hwnd=canvas->GetSafeHwnd();escape.message=WM_KEYDOWN;escape.wParam=VK_ESCAPE;
        Check(dialog.PreTranslateMessage(&escape)!=FALSE,"Escape routed to active stroke");Pump();Count(dialog,8);
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,1.5),MK_LBUTTON);
        ::SetCapture(dialog.GetSafeHwnd());Pump();Count(dialog,8);::ReleaseCapture();
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,1.5),MK_LBUTTON);
        dialog.SetWindowPos(nullptr,0,0,850,760,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);Pump();Count(dialog,8);
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,1.5),MK_LBUTTON);Send(canvas,WM_CANCELMODE,{});Count(dialog,8);
        Send(canvas,WM_LBUTTONDOWN,Point(canvas,.5,1.5),MK_LBUTTON);Send(canvas,WM_MOUSEMOVE,Point(canvas,1.5,1.5));Count(dialog,8);
        Click(dialog,IDC_CLEAR_DRAWING);Count(dialog,0);
        static_cast<CComboBox*>(dialog.GetDlgItem(IDC_GRID))->SetCurSel(0);Click(dialog,IDC_NEW_DRAWING);
        for(int y=0;y<3;++y)for(int x=0;x<3;++x)if(x!=1||y!=1){Send(canvas,WM_LBUTTONDOWN,Point(canvas,x+.5,y+.5,3),MK_LBUTTON);Send(canvas,WM_LBUTTONUP,Point(canvas,x+.5,y+.5,3));}
        Count(dialog,8);CString text;dialog.GetDlgItemText(IDC_SUMMARY,text);
        Check(std::string(text.GetString()).find("Proposed quads: 32")!=std::string::npos,"Real canvas ring preview");
        Check(std::string(text.GetString()).find("holes: 1")!=std::string::npos,"Real canvas ring hole count");
        for(int i=0;i<5;++i)canvas->RedrawWindow(nullptr,nullptr,RDW_INVALIDATE|RDW_UPDATENOW);
        const DWORD before=GetGuiResources(GetCurrentProcess(),GR_GDIOBJECTS);
        for(int i=0;i<64;++i)canvas->RedrawWindow(nullptr,nullptr,RDW_INVALIDATE|RDW_UPDATENOW);
        const DWORD after=GetGuiResources(GetCurrentProcess(),GR_GDIOBJECTS);
        Check(before==after,"No GDI growth during repeated canvas paints");
        dialog.RedrawWindow(nullptr,nullptr,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ALLCHILDREN);
        SaveBitmap(dialog.GetSafeHwnd(),work/"canvas-preview.bmp");
        dialog.DestroyWindow();Pump();
        std::cout<<"PASS: real MFC dialog/resource creation; capture/release outside, Escape, stolen capture, resize, cancel mode, missing button-up, stroke undo/redo and ring preview\n";
        std::cout<<"GDI objects before/after 64 paints: "<<before<<" / "<<after<<'\n';
        const auto path=work/L"Unicode-\u65e5\u672c plan.json";
        const std::string value="{\"test\":1}";patchdraw::SaveNewPlan(path,value);
        bool rejected=false;try{patchdraw::SaveNewPlan(path,"replace");}catch(const std::exception&){rejected=true;}
        Check(rejected,"Export cannot overwrite");
        std::ifstream file(path);const std::string actual((std::istreambuf_iterator<char>(file)),{});Check(actual==value,"Existing output unchanged");
        rejected=false;try{patchdraw::SaveNewPlan(work/"model.mdl",value);}catch(const std::exception&){rejected=true;}Check(rejected,"Refuse model extension");
        rejected=false;try{patchdraw::SaveNewPlan(work/"missing"/"plan.json",value);}catch(const std::exception&){rejected=true;}Check(rejected,"Missing parent fails");
        std::cout<<"PASS: create-only Unicode JSON export, existing-file protection and failed destination\n";return 0;
    }catch(CException* e){e->Delete();std::cerr<<"MFC exception\n";return 1;}
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
