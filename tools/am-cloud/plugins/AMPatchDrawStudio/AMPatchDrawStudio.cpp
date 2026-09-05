#include "StdAfx.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HProject.h"
#include "SDK/HDecal.h"
#include "StudioPlan.h"
#include "resource.h"
#include <commdlg.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <cctype>
#include <set>
#include <sstream>

CPluginApp theApp;
namespace {
namespace fs=std::filesystem;
struct Receiver {
    fs::path folder;
    std::string session,target,project;
    HANDLE lock=INVALID_HANDLE_VALUE;
    bool windowOwns=false;
    ~Receiver() { if(lock!=INVALID_HANDLE_VALUE) CloseHandle(lock); }
    bool busy=false;
    bool blocked=false;
};
HWND receiverWindow=nullptr;
int moduleAnchor=0;

std::string Read(const fs::path& p,std::size_t limit=patchstudio::MaxBytes) {
    std::ifstream f(p,std::ios::binary);
    if(!f) throw std::runtime_error("Cannot read transfer file");
    std::string value(limit+1,'\0'); f.read(value.data(),static_cast<std::streamsize>(value.size()));
    value.resize(static_cast<std::size_t>(f.gcount()));
    if(f.bad() || value.size()>limit) throw std::runtime_error("Transfer file exceeds its byte limit");
    return value;
}
void Write(const fs::path& p,const std::string& bytes,bool replace=true) {
    const fs::path temporary=p.wstring()+L".tmp-"+std::to_wstring(GetCurrentProcessId());
    HANDLE file=CreateFileW(temporary.c_str(),GENERIC_WRITE,0,nullptr,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file==INVALID_HANDLE_VALUE) throw std::runtime_error("Cannot create transfer acknowledgement; no automatic retry");
    DWORD written=0;
    const bool ok=WriteFile(file,bytes.data(),static_cast<DWORD>(bytes.size()),&written,nullptr) && written==bytes.size() && FlushFileBuffers(file);
    CloseHandle(file);
    if(!ok || !MoveFileExW(temporary.c_str(),p.c_str(),(replace?MOVEFILE_REPLACE_EXISTING:0)|MOVEFILE_WRITE_THROUGH)) {
        DeleteFileW(temporary.c_str()); throw std::runtime_error("Cannot complete transfer acknowledgement; inspect A:M before retrying");
    }
}
std::string Escape(const std::string& text) {
    std::string out="\"";
    for(unsigned char c:text) {
        if(c=='\\' || c=='\"') { out+='\\'; out+=static_cast<char>(c); }
        else if(c=='\n') out+="\\n";
        else if(c=='\r') out+="\\r";
        else if(c=='\t') out+="\\t";
        else if(c>=32) out+=static_cast<char>(c);
    }
    return out+'\"';
}
std::wstring Wide(const std::string& text,UINT codepage=CP_ACP) {
    if(text.empty()) return {};
    int n=MultiByteToWideChar(codepage,0,text.data(),static_cast<int>(text.size()),nullptr,0);
    if(n<=0) throw std::runtime_error("Text conversion failed");
    std::wstring out(static_cast<std::size_t>(n),L'\0');
    MultiByteToWideChar(codepage,0,text.data(),static_cast<int>(text.size()),out.data(),n); return out;
}
std::string Utf8(const std::string& text) {
    const auto wide=Wide(text);
    if(wide.empty()) return {};
    int n=WideCharToMultiByte(CP_UTF8,0,wide.data(),static_cast<int>(wide.size()),nullptr,0,nullptr,nullptr);
    std::string out(static_cast<std::size_t>(n),'\0');
    WideCharToMultiByte(CP_UTF8,0,wide.data(),static_cast<int>(wide.size()),out.data(),n,nullptr,nullptr); return out;
}
std::string SDKPath(const fs::path& path) {
    const auto& wide=path.native(); BOOL substituted=FALSE;
    // Windows can use UTF-8 as its active ANSI code page. That mode forbids
    // the best-fit flags/default-character output used by legacy code pages.
    const UINT codepage=GetACP();
    const DWORD flags=codepage==CP_UTF8?0:WC_NO_BEST_FIT_CHARS;
    BOOL* usedDefault=codepage==CP_UTF8?nullptr:&substituted;
    int n=WideCharToMultiByte(codepage,flags,wide.c_str(),-1,nullptr,0,nullptr,usedDefault);
    if(n<=0 || substituted) throw std::runtime_error("This paint-folder path cannot be represented by the legacy SDK. Choose a path in the Windows code page or send without paint.");
    std::string value(static_cast<std::size_t>(n),'\0');
    const int converted=WideCharToMultiByte(codepage,flags,wide.c_str(),-1,value.data(),n,nullptr,usedDefault);
    if(converted!=n || substituted) throw std::runtime_error("Lossy SDK paint path rejected");
    value.resize(value.size()-1); return value;
}
void Heartbeat(const Receiver& r,const char* status) {
    const auto now=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    Write(r.folder/L"receiver.json","{\"session\":"+Escape(r.session)+",\"target\":"+Escape(Utf8(r.target))+
        ",\"status\":"+Escape(status)+",\"updated\":"+std::to_string(now)+"}");
}
void Result(const Receiver& r,std::size_t serial,const char* status,const std::string& message) {
    Write(r.folder/L"result.json","{\"session\":"+Escape(r.session)+",\"serial\":"+std::to_string(serial)+
        ",\"status\":"+Escape(status)+",\"message\":"+Escape(Utf8(message))+"}");
}
HModelCache* Context(HTreeObject* object) {
    if(!object) return nullptr;
    if(object->GetObjectType()==HOT_GROUP) object=static_cast<HGroup*>(object)->GetParentOfType(HOT_MODEL);
    if(!object || object->GetObjectType()!=HOT_MODEL || !static_cast<HAnimObject*>(object)->IsCache()) return nullptr;
    return static_cast<HModelCache*>(object);
}
std::string ProjectName(HProject* project) {
    const String name=project->GetFileName();
    const char* value=name.Get();
    return value?value:""; // An unsaved SDK String can contain a null buffer.
}
HModelCache* Resolve(const Receiver& r) {
    // No SDK handles/pointers are retained between messages. Resolve the explicitly
    // named destination from the live project's model cache list on every send.
    HProject* project=GetHProject();
    if(!project || project->IsLoadingProject() || ProjectName(project)!=r.project)
        throw std::runtime_error("The project changed or is loading. Disconnect, then reconnect from the intended model.");
    auto* container=project->GetChildObjectCacheContainer(); HModelCache* found=nullptr;
    std::set<HHashObject*> seen;
    for(HHashObject* item=container?container->GetChildModelCache():nullptr;item;item=item->GetSiblingSame()) {
        if(seen.size()>=4096 || !seen.insert(item).second) throw std::runtime_error("Unexpected model list; nothing sent");
        if(item->GetObjectType()==HOT_MODEL && static_cast<HAnimObject*>(item)->IsCache() && item->GetName() && std::string(item->GetName())==r.target) {
            if(found) throw std::runtime_error("More than one model has the destination name. Rename them before connecting.");
            found=static_cast<HModelCache*>(item);
        }
    }
    if(!found) throw std::runtime_error("Destination model is no longer open. Reconnect from the intended model.");
    return found;
}
std::string GroupName(HModelCache* model,const std::string& base) {
    auto folded=[](std::string value) { for(char& c:value) if(c>='A' && c<='Z') c=static_cast<char>(c+32); return value; };
    std::set<std::string> names; std::set<HHashObject*> visited;
    auto* container=model->GetChildGroupContainer();
    for(HHashObject* group=container?container->GetChildGroup():nullptr;group;group=group->GetSiblingSame()) {
        if(visited.size()>=100000 || !visited.insert(group).second) throw std::runtime_error("Unexpected group list");
        const char* name=group->GetName(); if(name) names.insert(folded(name));
    }
    for(unsigned n=1;n<1000000;++n) {
        const auto suffix=std::to_string(n);
        const std::string name="PD_"+base+"_"+std::string(suffix.size()<3?3-suffix.size():0,'0')+suffix;
        if(!names.count(folded(name))) return name;
    }
    throw std::runtime_error("No free shape-group name");
}
std::string CheckTexture(const Receiver& r,const patchstudio::Plan& plan) {
    if(plan.texture.empty()) return {};
    const auto path=r.folder/plan.texture;
    if(!fs::is_regular_file(path) || fs::file_size(path)>16*1024*1024 || fs::file_size(path)<33)
        throw std::runtime_error("Missing or oversized snapshot PNG");
    const auto raw=Read(path,16*1024*1024);
    const unsigned char signature[]={137,80,78,71,13,10,26,10};
    for(unsigned i=0;i<8;++i) if(static_cast<unsigned char>(raw[i])!=signature[i]) throw std::runtime_error("Not a PNG snapshot");
    if(raw.substr(12,4)!="IHDR") throw std::runtime_error("PNG header missing");
    auto number=[&](unsigned at) { unsigned value=0; for(unsigned i=0;i<4;++i) value=(value<<8)|static_cast<unsigned char>(raw[at+i]); return value; };
    const auto width=number(16),height=number(20);
    if(width!=height || (width!=256 && width!=512 && width!=1024 && width!=2048))
        throw std::runtime_error("PNG must be a 256, 512, 1024 or 2048 pixel square");
    return SDKPath(path);
}
using Face=std::array<std::size_t,4>;
std::vector<std::pair<HPatch*,Face>> MatchFaces(HModelCache* model,const patchstudio::Plan& plan,const std::vector<HCP*>& heads) {
    std::map<uint32_t,std::size_t> ids;
    for(std::size_t i=0;i<heads.size();++i) {
        auto* head=heads[i]->GetHead(); if(!head || !ids.emplace(head->GetID(),i).second) throw std::runtime_error("Native CP identity collision");
    }
    std::set<Face> expected; std::map<Face,Face> winding;
    for(auto face:plan.faces) { auto key=face; std::sort(key.begin(),key.end()); expected.insert(key); winding.emplace(key,face); }
    std::set<Face> found; std::vector<std::pair<HPatch*,Face>> result; result.reserve(plan.faces.size());
    const int count=model->GetPatchCount(); if(count<0 || count>1000000) throw std::runtime_error("Native patch count outside readback budget");
    for(int i=0;i<count;++i) {
        auto* p=model->GetPatch(i); if(!p) throw std::runtime_error("Missing native patch during readback");
        HCP* corners[]={p->GetCP1(),p->GetCP2(),p->GetCP3(),p->GetCP4()}; Face order{}; unsigned ours=0;
        for(unsigned j=0;j<4;++j) {
            auto* cp=corners[j]?corners[j]->GetHead():nullptr;
            auto it=cp?ids.find(cp->GetID()):ids.end();
            if(it!=ids.end()) { order[j]=it->second; ++ours; }
        }
        if(!ours) continue;
        if(ours!=4 || p->GetNumPoints()!=4) throw std::runtime_error("Unexpected native face involving the new geometry");
        auto key=order; std::sort(key.begin(),key.end());
        if(!expected.count(key) || !found.insert(key).second) throw std::runtime_error("Native faces differ from the intended painted surface; inspect partial group");
        const auto intended=winding.at(key);
        auto position=[&](std::size_t id) { const auto point=plan.points[id]; return Vector(point[0],point[1],point[2]); };
        const Vector desired=(position(intended[1])-position(intended[0]))^(position(intended[3])-position(intended[0]));
        Vector normal; p->GetPointNormalOnPatch(.5F,.5F,normal);
        const double direction=double(normal.x)*desired.x+double(normal.y)*desired.y+double(normal.z)*desired.z;
        if(!std::isfinite(direction) || direction==0) throw std::runtime_error("Cannot establish a finite native patch normal");
        if(direction<0) {
            p->ReverseNormal();
            HCP* reordered[]={p->GetCP1(),p->GetCP2(),p->GetCP3(),p->GetCP4()};
            for(unsigned j=0;j<4;++j) {
                if(!reordered[j] || !reordered[j]->GetHead()) throw std::runtime_error("Missing corner after normal adjustment");
                order[j]=ids.at(reordered[j]->GetHead()->GetID());
            }
        }
        result.emplace_back(p,order);
    }
    if(found!=expected) throw std::runtime_error("Missing native patches; inspect partial group before retrying");
    return result;
}
void Append(HModelCache* model,const patchstudio::Plan& plan,const std::string& groupName,const std::string& texturePath) {
    // Bookkeeping allocation and plan validation precede the first mutation.
    std::vector<HCP*> heads(plan.points.size(),nullptr);
    std::vector<std::pair<std::size_t,HCP*>> occurrences; occurrences.reserve(plan.occurrences);
    model->SaveAllToUndo(); // SDK-supported snapshot, NOT a claimed atomic transaction.
    auto* group=model->CreateGroup(String(groupName.c_str()));
    if(!group) throw std::runtime_error("Cannot create the shape group");
    auto position=[&](std::size_t id) { const auto p=plan.points[id]; return Vector(p[0],p[1],p[2]); };
    auto setMode=[&](HCP* cp) { if(plan.smooth) cp->SetSmooth(); else cp->SetPeaked(); };
    for(const auto& run:plan.splines) {
        Vector a=position(run[0]),b=position(run[1]); auto* spline=model->StartSpline(&a,&b);
        if(!spline) throw std::runtime_error("Cannot create a spline");
        auto* first=spline->GetHeadCP(); auto* second=first?first->GetNext():nullptr;
        if(!first || !second) throw std::runtime_error("SDK returned an incomplete spline");
        setMode(first); setMode(second); occurrences.emplace_back(run[0],first); occurrences.emplace_back(run[1],second);
        // Group every created CP immediately, so partial output remains selectable.
        group->AddCP(first); group->AddCP(second);
        for(std::size_t i=2;i<run.size();++i) {
            auto* cp=spline->CreateCPAtTail(position(run[i])); if(!cp) throw std::runtime_error("Cannot create a control point");
            setMode(cp); group->AddCP(cp); occurrences.emplace_back(run[i],cp);
        }
    }
    for(const auto& [index,cp]:occurrences) {
        auto*& head=heads[index];
        if(!head) head=cp;
        else {
            // TRUE means the second CP was deleted during attachment; FALSE is
            // a normal success result, as in the SDK's TexturedGrid example.
            const BOOL deleted=model->AttachCPs(head,cp);
            group->AddCP(head); if(!deleted) group->AddCP(cp);
        }
    }
    model->Update(); model->FindPatches();
    const auto patches=MatchFaces(model,plan,heads);
    // Verify both occurrences remain in the named group without dereferencing
    // potentially deleted attachment records.
    for(auto* head:heads) {
        auto* first=head->GetHead(); std::set<HCP*> stack;
        for(auto* cp=first;cp;cp=cp->GetNextAttached()) {
            if(!stack.insert(cp).second) { if(cp==first) break; throw std::runtime_error("Invalid attachment stack"); }
            if(stack.size()>2 || !group->IsCPInGroup(cp)) throw std::runtime_error("Named-group membership readback failed");
        }
    }
    if(!texturePath.empty()) {
        auto* project=GetHProject(); if(!project) throw std::runtime_error("Project unavailable while applying paint");
        auto* clip=project->AddClip(String(texturePath.c_str()),FALSE); if(!clip) throw std::runtime_error("Cannot load the immutable paint PNG");
        auto* decal=model->AddDecal(clip); if(!decal) throw std::runtime_error("Cannot add the paint decal");
        decal->SetName((groupName+"_Paint").c_str());
        auto* stamp=decal->AddDecalStamp(); if(!stamp) throw std::runtime_error("Cannot add UV stamp");
        for(const auto& [patch,order]:patches) {
            Vector uv[12];
            for(unsigned edge=0;edge<4;++edge) {
                const auto a=plan.uvs[order[edge]],b=plan.uvs[order[(edge+1)%4]];
                for(unsigned k=0;k<3;++k) {
                    const float t=static_cast<float>(k)/3.F;
                    // Pillow top-left V becomes A:M bottom-left V. Corner order
                    // comes from native readback, never patch enumeration order.
                    uv[3*edge+k]=Vector(a[0]+t*(b[0]-a[0]),1.F-(a[1]+t*(b[1]-a[1])),0.F);
                }
            }
            if(!stamp->AddPatchUV(patch,uv)) throw std::runtime_error("Native UV assignment failed");
        }
    }
    model->SetChanged(); model->MarkViewsNeedDrawn(); RefreshAllTrees(); GetHProject()->UpdateAllViews(TRUE);
    group->HilightInProjectBar();
}
void Receive(HWND window,Receiver& r) {
    // A disabled host owner generally indicates an existing modal operation.
    // Leave the snapshot queued rather than nesting model mutation into it.
    if(!IsWindowEnabled(GetMainApplicationWnd())) return;
    const auto request=r.folder/L"request.json",processing=r.folder/L"processing.json";
    if(r.blocked) { Heartbeat(r,"blocked"); return; }
    if(fs::exists(processing)) { r.blocked=true; SetDlgItemTextA(window,IDC_STATUS,"Unacknowledged prior send. Inspect A:M; reconnect using a new session."); Heartbeat(r,"blocked"); return; }
    Heartbeat(r,"connected");
    if(!fs::exists(request)) return;
    r.busy=true; KillTimer(window,1);
    struct Reset { HWND w; Receiver& r; ~Reset(){ r.busy=false; if(IsWindow(w)) SetTimer(w,1,500,nullptr); } } reset{window,r};
    if(!MoveFileExW(request.c_str(),processing.c_str(),MOVEFILE_WRITE_THROUGH)) throw std::runtime_error("Cannot claim request; nothing sent");
    std::size_t serial=0; bool mutationStarted=false; std::string groupName; std::string message; const char* status="failed";
    try {
        const auto plan=patchstudio::Parse(Read(processing)); serial=plan.serial;
        if(plan.session!=r.session) throw std::runtime_error("Request belongs to another session");
        const auto flag=r.folder/("claimed-"+std::to_string(serial)+".txt");
        Write(flag,"Claimed before any native mutation. Never replay automatically.\n",false);
        const auto texture=CheckTexture(r,plan);
        auto* model=Resolve(r); groupName=GroupName(model,plan.name);
        const auto text="Append "+std::to_string(plan.faces.size())+" native patches to model:\n"+r.target+
            "\nProject: "+(r.project.empty()?"<unsaved project>":r.project)+"\n\nNew group: "+groupName+"\nSplines: "+(plan.smooth?"Smooth":"Peaked")+
            (texture.empty()?"\nNo paint texture.":"\nPaint snapshot will be linked from the persistent Studio folder.")+
            "\n\nExisting shapes are not replaced. Test undo and save/reopen on a disposable model. Continue?";
        if(MessageBoxW(window,Wide(text).c_str(),L"Confirm current destination model",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)!=IDYES)
            throw std::runtime_error("Send cancelled. Draft is unchanged; no A:M geometry was added.");
        // Reacquire after the modal confirmation. No stale pointer from before
        // its message loop is dereferenced; the name is confirmed for this send.
        model=Resolve(r); groupName=GroupName(model,plan.name);
        const int existing=model->GetPatchCount();
        if(existing<0 || static_cast<std::size_t>(existing)+plan.faces.size()>1000000)
            throw std::runtime_error("The target exceeds Studio's patch readback budget; nothing added.");
        SetDlgItemTextA(window,IDC_STATUS,"Adding native geometry; please wait...");
        CWaitCursor cursor; mutationStarted=true; Append(model,plan,groupName,texture);
        status="ok"; message="Added "+groupName+" to "+r.target+" ("+std::to_string(plan.faces.size())+" patches). The draft remains open.";
    } catch(CException* error) { error->Delete(); message="MFC operation failed."; }
      catch(const std::exception& error) { message=error.what(); }
      catch(...) { message="Unexpected native failure."; }
    if(std::string(status)!="ok" && mutationStarted) {
        r.blocked=true;
        message+="\nA partial group/model change may remain: "+groupName+". Inspect A:M and its undo state. Automatic retries are disabled; keep this session's files.";
    }
    Result(r,serial,status,message); // If this fails, leave processing.json as an explicit ambiguity marker.
    const auto archive=r.folder/("processed-"+std::to_string(serial)+".json");
    if(!MoveFileExW(processing.c_str(),archive.c_str(),MOVEFILE_WRITE_THROUGH)) { r.blocked=true; throw std::runtime_error("Send acknowledged but journal archive failed; inspect the session folder"); }
    SetDlgItemTextA(window,IDC_STATUS,std::string(status)=="ok"?"Sent. Ready for another named shape.":"Send stopped. Read the Studio message.");
    Heartbeat(r,r.blocked?"blocked":"connected");
}
INT_PTR CALLBACK ReceiverProc(HWND window,UINT message,WPARAM w,LPARAM l) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    auto* r=reinterpret_cast<Receiver*>(GetWindowLongPtrW(window,DWLP_USER));
    if(message==WM_INITDIALOG) {
        r=reinterpret_cast<Receiver*>(l); SetWindowLongPtrW(window,DWLP_USER,l);
        try { SetDlgItemTextW(window,IDC_TARGET,Wide("Destination model: "+r->target).c_str()); }
        catch(...) { DestroyWindow(window); return TRUE; }
        SetDlgItemTextW(window,IDC_FOLDER,r->folder.c_str());
        if(!SetTimer(window,1,500,nullptr)) { DestroyWindow(window); return TRUE; }
        return TRUE;
    }
    if(!r) return FALSE;
    if(message==WM_TIMER && w==1 && !r->busy) {
        try { Receive(window,*r); }
        catch(CException* error) { error->Delete(); r->blocked=true; SetDlgItemTextA(window,IDC_STATUS,"Receiver blocked after an MFC failure; inspect A:M."); }
        catch(const std::exception& error) { r->blocked=true; SetDlgItemTextA(window,IDC_STATUS,error.what()); }
        catch(...) { r->blocked=true; SetDlgItemTextA(window,IDC_STATUS,"Receiver blocked; inspect A:M before retrying."); }
        return TRUE;
    }
    if(message==WM_CLOSE || (message==WM_COMMAND && LOWORD(w)==IDCANCEL)) {
        if(!r->busy) DestroyWindow(window);
        return TRUE;
    }
    if(message==WM_DESTROY) {
        KillTimer(window,1);
        try { Heartbeat(*r,"disconnected"); } catch(...) {}
        return TRUE;
    }
    if(message==WM_NCDESTROY) { SetWindowLongPtrW(window,DWLP_USER,0); if(r->windowOwns) delete r; receiverWindow=nullptr; return FALSE; }
    return FALSE;
}
void Connect(HTreeObject* context) {
    auto* model=Context(context); auto* project=GetHProject();
    if(!model || !project || project->IsLoadingProject()) throw std::runtime_error("Invoke Studio on an open model cache, not an Action/Choreography instance.");
    if(receiverWindow && IsWindow(receiverWindow)) {
        ShowWindow(receiverWindow,SW_SHOW); SetForegroundWindow(receiverWindow);
        MessageBoxA(receiverWindow,"A receiver is already connected. Disconnect it first to choose another model or Studio session.","Patch Draw Studio",MB_OK); return;
    }
    // Snapshot names only; command-context handles never outlive this callback.
    const char* modelName=model->GetName();
    if(!modelName || !*modelName) throw std::runtime_error("Name the destination model before connecting Studio.");
    const std::string target=modelName, projectName=ProjectName(project);
    std::vector<wchar_t> path(32768,L'\0'); OPENFILENAMEW open{}; open.lStructSize=sizeof(open);
    open.hwndOwner=GetMainApplicationWnd(); open.lpstrFile=path.data(); open.nMaxFile=static_cast<DWORD>(path.size());
    open.lpstrTitle=L"Select connection.pdstudio from the open Python Studio (copy its connection path)";
    open.lpstrFilter=L"Patch Draw Studio connection (*.pdstudio)\0*.pdstudio\0\0";
    open.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_EXPLORER;
    if(!GetOpenFileNameW(&open)) { if(CommDlgExtendedError()) throw std::runtime_error("Connection chooser failed"); return; }
    const fs::path file(path.data());
    if(file.filename()!=L"connection.pdstudio") throw std::runtime_error("Choose the Studio-generated connection.pdstudio file");
    std::istringstream input(Read(file,128)); std::string header,session,trailing;
    std::getline(input,header); std::getline(input,session);
    if(!header.empty() && header.back()=='\r') header.pop_back();
    if(!session.empty() && session.back()=='\r') session.pop_back();
    if(header!="PATCHDRAW-STUDIO/1" || session.size()!=32 || session.find_first_not_of("0123456789abcdef")!=std::string::npos || std::getline(input,trailing))
        throw std::runtime_error("Invalid Studio connection file");
    auto r=std::make_unique<Receiver>(); r->folder=file.parent_path(); r->session=session; r->target=target; r->project=projectName;
    Resolve(*r);
    r->lock=CreateFileW((r->folder/L"receiver.lock").c_str(),GENERIC_READ|GENERIC_WRITE,0,nullptr,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(r->lock==INVALID_HANDLE_VALUE) throw std::runtime_error("Another A:M receiver already owns this Studio session. Disconnect it first.");
    if(fs::exists(r->folder/L"processing.json")) throw std::runtime_error("This session has an ambiguous earlier send. Inspect A:M; do not replay. Start a fresh Studio session.");
    HMODULE module=nullptr;
    // A modeless window outlives HxtOnCommand. Pin this small receiver DLL until
    // process exit so the host cannot unload its callback code underneath it.
    if(!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_PIN,
        reinterpret_cast<LPCWSTR>(&moduleAnchor),&module)) throw std::runtime_error("Cannot retain the modeless receiver module");
    Receiver* raw=r.get();
    receiverWindow=CreateDialogParamW(module,MAKEINTRESOURCEW(IDD_RECEIVER),GetMainApplicationWnd(),ReceiverProc,reinterpret_cast<LPARAM>(raw));
    if(!receiverWindow || !IsWindow(receiverWindow)) throw std::runtime_error("Cannot create the modeless receiver");
    r->windowOwns=true; r.release();
    ShowWindow(receiverWindow,SW_SHOW);
}
} // namespace
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(uint32_t index,ObjectType& type) {
    if(index>1) return FALSE; type=index==0?HOT_MODEL:HOT_GROUP; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject* object,uint32_t index,String& name,MenuCategory& category,BOOL& disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>1) return FALSE;
    name="A:M Patch Draw Studio v0.2 - Connect"; category=MC_WIZARD;
    disabled=Context(object)==nullptr; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject* object,uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>1) return FALSE;
    try { Connect(object); }
    catch(CException* error) { error->Delete(); MessageBoxA(GetMainApplicationWnd(),"MFC connection failure; no model was requested.","Patch Draw Studio",MB_OK|MB_ICONERROR); }
    catch(const std::exception& error) { MessageBoxA(GetMainApplicationWnd(),error.what(),"Patch Draw Studio",MB_OK|MB_ICONERROR); }
    catch(...) { MessageBoxA(GetMainApplicationWnd(),"Unexpected connection failure.","Patch Draw Studio",MB_OK|MB_ICONERROR); }
    return TRUE;
}
