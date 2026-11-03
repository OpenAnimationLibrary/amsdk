#include "Adapter.h"
#include "resource.h"
#include <memory>
#include <commctrl.h>
#include <windowsx.h>
#include <utility>

CPluginApp theApp;
namespace {
constexpr UINT refreshMessage = WM_APP + 110;
constexpr wchar_t settingsKey[] = L"Software\\OpenAnimationLibrary\\Setbiaser";
struct State {
    HWND window{};
    HHOOK hook{};
    bool routing{}, filling{}, working{}, dirty{}, dragging{}, collapsed{};
    int field = -1, originX{}, expandedHeight{}, sensitivity = 1;
    double startValue{};
    bool entire{}, linked{};
    sb::Operation operation = sb::Operation::Set;
    std::shared_ptr<sb::Binding> binding;
    sb::Snapshot displayed, baseline;
};
std::shared_ptr<State> active;
void status(HWND h, const char *text) { SetDlgItemTextA(h,IDC_STATUS,text); }
void error(State &s, const char *text) {
    s.dirty = false; s.dragging = false; s.field = -1;
    if (GetCapture() && IsChild(s.window,GetCapture())) ReleaseCapture();
    status(s.window,text);
    MessageBeep(MB_ICONWARNING);
}
std::string fieldText(HWND window, int field) {
    char text[128]{};
    GetDlgItemTextA(window,IDC_VALUE0+field,text,static_cast<int>(sizeof text));
    return text;
}
void number(State &s, int field, double value) {
    const auto text = sb::format(value);
    s.filling = true;
    SetDlgItemTextA(s.window,IDC_VALUE0+field,text.c_str());
    s.filling = false;
}
void controls(State &s, bool enable) {
    for (int f=0;f!=6;++f) {
        const bool on = enable && (s.operation != sb::Operation::Scale || f<2);
        EnableWindow(GetDlgItem(s.window,IDC_VALUE0+f),on);
        EnableWindow(GetDlgItem(s.window,IDC_SCRUB0+f),on);
    }
}
void refresh(State &s, bool hint = true) {
    if (s.working || s.dragging || s.dirty) return;
    try {
        s.displayed = s.binding->read(s.entire);
        std::vector<sb::Values> values;
        for (const auto &sample : s.displayed.samples) values.push_back(sample.values);
        s.filling = true;
        for (int f=0;f!=6;++f) {
            std::string text;
            if (values.empty()) text = "-";
            else if (s.operation == sb::Operation::Offset) text = "0";
            else if (s.operation == sb::Operation::Scale) text = f<2 ? "1" : "-";
            else {
                const auto v = sb::common(values,static_cast<std::size_t>(f));
                text = v ? sb::format(s.binding->units.display(*v,static_cast<std::size_t>(f))) : "Mixed";
            }
            SetDlgItemTextA(s.window,IDC_VALUE0+f,text.c_str());
        }
        s.filling = false;
        controls(s,!values.empty());
        const auto count = std::to_string(s.displayed.locations) + " CPs / " +
            std::to_string(s.displayed.samples.size()) + " handles";
        SetDlgItemTextA(s.window,IDC_COUNT,count.c_str());
        SetDlgItemTextA(s.window,IDC_UNITS,s.operation == sb::Operation::Scale ?
            "Magnitude: multiplier (1 = unchanged)" : "Magnitude: % | Angles: degrees");
        if (hint) {
            const auto text = s.displayed.skipped ? std::to_string(s.displayed.skipped)+" occurrences skipped (locked/hidden/hook/end)." :
                s.entire ? "ENTIRE MODEL, including hidden editable CPs." : "Bound selection. Re-run plugin to select another area.";
            status(s.window,text.c_str());
        }
    } catch (...) {
        s.filling = false; controls(s,false);
        s.entire = false;
        SendDlgItemMessageW(s.window,IDC_SCOPE,CB_SETCURSEL,0,0);
        throw;
    }
}
void cancel(State &s) {
    s.dirty = false; s.dragging = false; s.field = -1;
    s.baseline = {};
    if (GetCapture() && IsChild(s.window,GetCapture())) ReleaseCapture();
    refresh(s);
}
void begin(State &s, int field) {
    if (field<0 || field>=6) throw std::runtime_error("Unknown bias field.");
    if (s.operation == sb::Operation::Scale && field>=2) throw std::runtime_error("Only magnitudes can be scaled.");
    s.baseline = s.binding->read(s.entire);
    if (s.baseline.samples.empty()) throw std::runtime_error("No eligible points. Bind a selection or explicitly choose Entire model.");
    // Reject edits started from a stale display, rather than assigning an old
    // displayed number after an intervening host edit.
    if (s.baseline.samples != s.displayed.samples)
        throw std::runtime_error("The displayed values are stale. Click Refresh before editing.");
    s.field = field;
}
void commit(State &s, bool reset = false) {
    if (!reset && (!s.dirty || s.field<0)) return;
    sb::Edit edit;
    if (reset) { s.baseline = s.binding->read(s.entire); edit.reset=true; }
    else {
        edit = {static_cast<std::size_t>(s.field),s.operation,sb::parse(fieldText(s.window,s.field)),s.linked,false};
    }
    struct Busy { bool &flag; explicit Busy(bool &f):flag(f){flag=true;} ~Busy(){flag=false;} } busy(s.working);
    const auto changed = s.binding->commit(s.entire,s.baseline,edit);
    s.dirty=false; s.field=-1; s.baseline={};
    const auto text=std::to_string(changed)+" spline occurrences changed. Native history needs host testing.";
    status(s.window,text.c_str());
    PostMessageW(s.window,refreshMessage,0,0);
}
double step(const State &s, int field) {
    double scale = s.operation == sb::Operation::Scale ? 0.01 : field<2 ? 1.0 : 0.5;
    scale *= s.sensitivity==0 ? 0.1 : s.sensitivity==2 ? 10.0 : 1.0;
    if (GetKeyState(VK_SHIFT)<0) scale*=0.1;
    return scale;
}
void keyStep(State &s, int field, int direction) {
    cancel(s); begin(s,field);
    const double value = sb::parse(fieldText(s.window,field));
    number(s,field,value + static_cast<double>(direction)*step(s,field));
    s.dirty=true; commit(s);
}
void loadPlacement(State &s) {
    DWORD value{}, size=sizeof value;
    if (RegGetValueW(HKEY_CURRENT_USER,settingsKey,L"Sensitivity",RRF_RT_REG_DWORD,nullptr,&value,&size)==ERROR_SUCCESS && value<=2)
        s.sensitivity=static_cast<int>(value);
    DWORD x{},y{}; size=sizeof x;
    const bool hasX=RegGetValueW(HKEY_CURRENT_USER,settingsKey,L"X",RRF_RT_REG_DWORD,nullptr,&x,&size)==ERROR_SUCCESS;
    size=sizeof y;
    const bool hasY=RegGetValueW(HKEY_CURRENT_USER,settingsKey,L"Y",RRF_RT_REG_DWORD,nullptr,&y,&size)==ERROR_SUCCESS;
    RECT r{}; GetWindowRect(s.window,&r); s.expandedHeight=r.bottom-r.top;
    POINT p{hasX?static_cast<LONG>(x):r.left,hasY?static_cast<LONG>(y):r.top};
    MONITORINFO monitor{}; monitor.cbSize=sizeof monitor;
    if (GetMonitorInfoW(MonitorFromPoint(p,MONITOR_DEFAULTTONEAREST),&monitor)) {
        const auto &w=monitor.rcWork;
        p.x=(std::max)(w.left,(std::min)(p.x,w.right-(r.right-r.left)));
        p.y=(std::max)(w.top,(std::min)(p.y,w.bottom-(r.bottom-r.top)));
    }
    SetWindowPos(s.window,nullptr,p.x,p.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
}
void savePlacement(const State &s) noexcept {
    HKEY key{};
    if (RegCreateKeyExW(HKEY_CURRENT_USER,settingsKey,0,nullptr,0,KEY_SET_VALUE,nullptr,&key,nullptr)!=ERROR_SUCCESS) return;
    RECT r{}; GetWindowRect(s.window,&r);
    const DWORD x=static_cast<DWORD>(r.left),y=static_cast<DWORD>(r.top),sensitivity=static_cast<DWORD>(s.sensitivity);
    RegSetValueExW(key,L"X",0,REG_DWORD,reinterpret_cast<const BYTE*>(&x),sizeof x);
    RegSetValueExW(key,L"Y",0,REG_DWORD,reinterpret_cast<const BYTE*>(&y),sizeof y);
    RegSetValueExW(key,L"Sensitivity",0,REG_DWORD,reinterpret_cast<const BYTE*>(&sensitivity),sizeof sensitivity);
    RegCloseKey(key);
}
void options(State &s) {
    cancel(s);
    HMENU menu=CreatePopupMenu();
    if (!menu) throw std::runtime_error("Cannot create options menu.");
    AppendMenuW(menu,MF_STRING|MF_GRAYED,1,L"Live model preview: pending host validation");
    AppendMenuW(menu,MF_SEPARATOR,0,nullptr);
    for (int i=0;i<3;++i) AppendMenuW(menu,MF_STRING|(s.sensitivity==i?MF_CHECKED:0),static_cast<UINT_PTR>(10+i),
        i==0?L"Sensitivity: Fine":i==1?L"Sensitivity: Normal":L"Sensitivity: Coarse");
    AppendMenuW(menu,MF_SEPARATOR,0,nullptr);
    AppendMenuW(menu,MF_STRING,20,L"Reset all six biases...");
    AppendMenuW(menu,MF_STRING,21,L"About / limitations...");
    RECT r{}; GetWindowRect(GetDlgItem(s.window,IDC_OPTIONS),&r);
    const auto choice=TrackPopupMenu(menu,TPM_RETURNCMD|TPM_NONOTIFY,r.left,r.bottom,0,s.window,nullptr);
    DestroyMenu(menu);
    if (choice>=10 && choice<=12) s.sensitivity=static_cast<int>(choice)-10;
    if (choice==20 && MessageBoxW(s.window,
        s.entire?L"Reset ALL eligible spline biases in this model, including hidden CPs, to 100% magnitude and zero angles?":
        L"Reset all six biases on the bound eligible selection to 100% magnitude and zero angles?",
        L"Setbiaser - reset biases",MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING)==IDYES) commit(s,true);
    if (choice==21) MessageBoxW(s.window,
        L"Setbiaser 0.1.0-preview\nInspired by Emilio Le Roux's Setbias.\nNew implementation with AI assistance.\n\n"
        L"Selection is explicitly bound when invoked. Re-run the plugin to rebind.\n"
        L"Drag <> horizontally; Shift is fine. Enter/Tab commits text; Escape cancels.\n"
        L"Model writes occur only on release/commit. Hooks and open endpoints are skipped.\n\n"
        L"Native undo, save/reopen, modeless input and DPI require testing in A:M.\n"
        L"Use disposable models. This is not a host-validated release.",L"Setbiaser",MB_OK|MB_ICONINFORMATION);
}
LRESULT CALLBACK scrub(HWND h, UINT msg, WPARAM w, LPARAM l, UINT_PTR, DWORD_PTR data) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    const auto s=active;
    if (!s || !s->window) return DefSubclassProc(h,msg,w,l);
    const int field=static_cast<int>(data);
    try {
        if (msg==WM_LBUTTONDOWN) {
            cancel(*s); begin(*s,field);
            s->startValue=sb::parse(fieldText(s->window,field));
            POINT p{}; GetCursorPos(&p); s->originX=p.x;
            s->dragging=true; s->dirty=false;
            SetFocus(h); SetCapture(h); return 0;
        }
        if (msg==WM_MOUSEMOVE && s->dragging && s->field==field) {
            POINT p{}; GetCursorPos(&p);
            const UINT dpi=GetDpiForWindow(s->window);
            const double delta=static_cast<double>(p.x-s->originX)*96.0/(dpi?dpi:96);
            number(*s,field,s->startValue+delta*step(*s,field));
            s->dirty=delta!=0;
            return 0;
        }
        if (msg==WM_LBUTTONUP && s->dragging && s->field==field) {
            s->dragging=false;
            ReleaseCapture();
            if (s->dirty) commit(*s); else cancel(*s);
            return 0;
        }
        if ((msg==WM_CAPTURECHANGED || msg==WM_CANCELMODE) && s->dragging) { cancel(*s); return 0; }
        if (msg==WM_NCDESTROY) RemoveWindowSubclass(h,scrub,1);
    } catch (CException *e) { if(e)e->Delete(); error(*s,"A:M/MFC reported an error. Refresh or rebind before retrying."); }
    catch (const std::exception &e) { error(*s,e.what()); }
    catch (...) { error(*s,"Unexpected error. Rebind before retrying."); }
    return DefSubclassProc(h,msg,w,l);
}
LRESULT CALLBACK inputHook(int code, WPARAM w, LPARAM l) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    const auto s=active;
    if (code==HC_ACTION && w==PM_REMOVE && s && !s->routing && IsWindowEnabled(s->window)) {
        auto *msg=reinterpret_cast<MSG*>(l);
        const bool keyboard=msg->message>=WM_KEYFIRST && msg->message<=WM_KEYLAST;
        const bool mouse=(msg->message>=WM_MOUSEFIRST && msg->message<=WM_MOUSELAST) ||
                         (msg->message>=WM_NCMOUSEMOVE && msg->message<=WM_NCXBUTTONDBLCLK);
        bool dropdown=false;
        for (const int id : {IDC_SCOPE,IDC_OPERATION}) {
            COMBOBOXINFO combo{}; combo.cbSize=sizeof combo;
            if (GetComboBoxInfo(GetDlgItem(s->window,id),&combo) && msg->hwnd==combo.hwndList) dropdown=true;
        }
        if ((keyboard||mouse) && (msg->hwnd==s->window || IsChild(s->window,msg->hwnd) || dropdown)) {
            MSG input=*msg; msg->hwnd=nullptr; msg->message=WM_NULL; msg->wParam=0; msg->lParam=0;
            struct Routing { bool &flag; explicit Routing(bool &f):flag(f){flag=true;} ~Routing(){flag=false;} } guard(s->routing);
            try {
                const int id=GetDlgCtrlID(input.hwnd);
                const bool edit=id>=IDC_VALUE0 && id<=IDC_VALUE5;
                const bool handle=id>=IDC_SCRUB0 && id<=IDC_SCRUB5;
                bool consumed=false;
                if (input.message==WM_KEYDOWN && !dropdown) {
                    if (input.wParam==VK_ESCAPE) { cancel(*s); consumed=true; }
                    else if (input.wParam==VK_RETURN && edit) { commit(*s); consumed=true; }
                    else if (input.wParam==VK_TAB && edit) commit(*s);
                    else if ((input.wParam==VK_UP || input.wParam==VK_DOWN) && (edit||handle)) {
                        keyStep(*s,edit?id-IDC_VALUE0:id-IDC_SCRUB0,input.wParam==VK_UP?1:-1); consumed=true;
                    }
                }
                if (!consumed && (!keyboard || dropdown || !IsDialogMessageW(s->window,&input))) {
                    TranslateMessage(&input); DispatchMessageW(&input);
                }
            } catch (CException *e) { if(e)e->Delete(); error(*s,"A:M/MFC input error. Refresh or rebind."); }
            catch (const std::exception &e) { error(*s,e.what()); }
            catch (...) { error(*s,"Unexpected input error. Rebind before retrying."); }
        }
    }
    return CallNextHookEx(nullptr,code,w,l);
}
INT_PTR CALLBACK procedure(HWND h, UINT msg, WPARAM w, LPARAM l) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    const auto s=active;
    if (!s || (msg!=WM_INITDIALOG && s->window!=h)) return FALSE;
    if (msg==WM_INITDIALOG) s->window=h;
    if (msg==WM_NCDESTROY) {
        savePlacement(*s);
        if(s->hook) {UnhookWindowsHookEx(s->hook);s->hook=nullptr;}
        s->window=nullptr; active.reset(); return FALSE;
    }
    if(s->working && (msg==WM_COMMAND || msg==WM_CLOSE)) return TRUE;
    try {
        if (msg==WM_INITDIALOG) {
            for (auto text : {L"Bound selection",L"Entire model"}) SendDlgItemMessageW(h,IDC_SCOPE,CB_ADDSTRING,0,reinterpret_cast<LPARAM>(text));
            for (auto text : {L"Set value",L"Add offset",L"Scale magnitude"}) SendDlgItemMessageW(h,IDC_OPERATION,CB_ADDSTRING,0,reinterpret_cast<LPARAM>(text));
            SendDlgItemMessageW(h,IDC_SCOPE,CB_SETCURSEL,0,0);
            SendDlgItemMessageW(h,IDC_OPERATION,CB_SETCURSEL,0,0);
            for(int f=0;f<6;++f) {
                SendDlgItemMessageW(h,IDC_VALUE0+f,EM_SETLIMITTEXT,64,0);
                if(!SetWindowSubclass(GetDlgItem(h,IDC_SCRUB0+f),scrub,1,static_cast<DWORD_PTR>(f)))
                    throw std::runtime_error("Cannot initialize numeric scrub controls.");
            }
            loadPlacement(*s); refresh(*s); return TRUE;
        }
        if (msg==WM_CLOSE) { DestroyWindow(h); return TRUE; }
        if (msg==refreshMessage) { refresh(*s,w!=0); return TRUE; }
        if (msg==WM_ACTIVATE && LOWORD(w)==WA_INACTIVE && !s->working) {
            // Losing activation cancels uncommitted input; it never writes to A:M.
            if(s->dirty||s->dragging) cancel(*s);
        }
        if (msg==WM_NCLBUTTONDBLCLK && w==HTCAPTION) {
            cancel(*s); RECT r{}; GetWindowRect(h,&r); s->collapsed=!s->collapsed;
            const UINT dpi=GetDpiForWindow(h);
            const int rolled=GetSystemMetricsForDpi(SM_CYCAPTION,dpi)+2*GetSystemMetricsForDpi(SM_CYFIXEDFRAME,dpi);
            SetWindowPos(h,nullptr,0,0,r.right-r.left,s->collapsed?rolled:s->expandedHeight,SWP_NOMOVE|SWP_NOZORDER);
            return TRUE;
        }
        if(msg==WM_DPICHANGED) {
            const auto *r=reinterpret_cast<const RECT*>(l);
            SetWindowPos(h,nullptr,r->left,r->top,r->right-r->left,r->bottom-r->top,SWP_NOZORDER|SWP_NOACTIVATE);
            if(!s->collapsed)s->expandedHeight=r->bottom-r->top;
            return TRUE;
        }
        if(msg==WM_COMMAND) {
            const int id=LOWORD(w), event=HIWORD(w);
            if(id==IDCANCEL) { cancel(*s); return TRUE; }
            if(id>=IDC_VALUE0 && id<=IDC_VALUE5 && event==EN_CHANGE && !s->filling) {
                const int field=id-IDC_VALUE0;
                if(!s->dirty || s->field!=field) begin(*s,field);
                s->dirty=true; return TRUE;
            }
            if(id>=IDC_VALUE0 && id<=IDC_VALUE5 && event==EN_KILLFOCUS && s->dirty && !s->working) {
                cancel(*s); return TRUE;
            }
            if(id==IDC_SCOPE && event==CBN_SELCHANGE) {
                cancel(*s); s->entire=SendDlgItemMessageW(h,id,CB_GETCURSEL,0,0)==1; refresh(*s); return TRUE;
            }
            if(id==IDC_OPERATION && event==CBN_SELCHANGE) {
                cancel(*s); const auto selected=SendDlgItemMessageW(h,id,CB_GETCURSEL,0,0);
                s->operation=selected==1?sb::Operation::Offset:selected==2?sb::Operation::Scale:sb::Operation::Set;
                refresh(*s); return TRUE;
            }
            if(id==IDC_LINK) {cancel(*s);s->linked=IsDlgButtonChecked(h,id)==BST_CHECKED;return TRUE;}
            if(id==IDC_REFRESH) {cancel(*s);return TRUE;}
            if(id==IDC_OPTIONS) {options(*s);return TRUE;}
        }
    } catch(CException *e) {if(e)e->Delete();error(*s,"A:M/MFC error. Rebind the palette before retrying.");}
    catch(const std::exception &e) {error(*s,e.what());}
    catch(...) {error(*s,"Unexpected error. Rebind the palette before retrying.");}
    return FALSE;
}
constexpr ObjectType contexts[]={HOT_MODEL,HOT_GROUP,HOT_CP};
} // namespace
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(std::uint32_t index,ObjectType &type) {
    if(index>=3)return FALSE; type=contexts[index]; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *object,std::uint32_t index,String &name,MenuCategory &category,BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>=3)return FALSE;
    try {
        CString label("Setbiaser..."); name=label; category=MC_WIZARD;
        disabled=IsInNetRender() || (active && active->working) || !sb::Binding::resolve(object); return TRUE;
    } catch(CException *e) {if(e)e->Delete();} catch(...) {}
    return FALSE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object,std::uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>=3 || IsInNetRender())return FALSE;
    try {
        HWND owner=GetMainApplicationWnd();
        if(!owner || GetWindowThreadProcessId(owner,nullptr)!=GetCurrentThreadId())
            throw std::runtime_error("Setbiaser must run on A:M's UI thread.");
        if(active && active->working)return FALSE;
        auto binding=std::make_shared<sb::Binding>(object);
        if(active && IsWindow(active->window)) {
            active->dirty=false; active->dragging=false; active->field=-1;
            if(GetCapture() && IsChild(active->window,GetCapture()))ReleaseCapture();
            active->binding=binding;active->entire=false;active->baseline={};
            SendDlgItemMessageW(active->window,IDC_SCOPE,CB_SETCURSEL,0,0);
            SetWindowTextA(active->window,("Setbiaser - "+binding->name()).c_str());
            refresh(*active); ShowWindow(active->window,SW_SHOWNORMAL); SetForegroundWindow(active->window); return TRUE;
        }
        // Retain callback code after the exported command returns.
        HMODULE module{};
        if(!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_PIN,
            reinterpret_cast<LPCWSTR>(&HxtOnCommand),&module))throw std::runtime_error("Cannot retain the modeless plugin module.");
        INITCOMMONCONTROLSEX common{sizeof common,ICC_STANDARD_CLASSES};InitCommonControlsEx(&common);
        active=std::make_shared<State>();active->binding=binding;
        HWND window=CreateDialogParamW(AfxGetInstanceHandle(),MAKEINTRESOURCEW(IDD_SETBIASER),owner,procedure,0);
        if(!window) {active.reset();throw std::runtime_error("Cannot create the Setbiaser palette.");}
        SetWindowTextA(window,("Setbiaser - "+binding->name()).c_str());
        active->hook=SetWindowsHookExW(WH_GETMESSAGE,inputHook,nullptr,GetCurrentThreadId());
        if(!active->hook){DestroyWindow(window);throw std::runtime_error("Cannot route modeless palette input safely.");}
        ShowWindow(window,SW_SHOW);return TRUE;
    } catch(CException *e) {if(e)e->Delete();MessageBoxW(GetMainApplicationWnd(),L"A:M/MFC could not open Setbiaser.",L"Setbiaser",MB_OK|MB_ICONERROR);}
    catch(const std::exception &e){MessageBoxA(GetMainApplicationWnd(),e.what(),"Setbiaser",MB_OK|MB_ICONERROR);}
    catch(...){MessageBoxW(GetMainApplicationWnd(),L"Cannot open Setbiaser.",L"Setbiaser",MB_OK|MB_ICONERROR);}
    return FALSE;
}
