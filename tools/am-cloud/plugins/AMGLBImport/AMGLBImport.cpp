// AMGLBImport 0.1.0. Developed for Rodney Baker with OpenAI Codex assistance.
#include "StdAfx.h"
#include "ImportCore.h"
#include "resource.h"
#include "SDK/Entry.h"
#include "SDK/HModel.h"
#include "IEModel.h"
#include "SDK/HPatch.h"
#include "SDK/HCP.h"
#include "SDK/Misc.h"
#include <algorithm>
#include <locale>
#include <memory>
#include <set>
#include <sstream>

CPluginApp theApp;
namespace {
constexpr ObjectType Contexts[]={HOT_OBJECTS,HOT_MODEL,HOT_GROUP};
bool ContextOK(HTreeObject* object,uint32_t index){
    if(!object||index>=_countof(Contexts)||object->GetObjectType()!=Contexts[index])return false;
    if(index==0)return true;
    auto* parent=object;
    for(size_t depth=0;parent&&depth<64;++depth,parent=parent->GetParent())
        if(parent->GetObjectType()==HOT_MODEL){auto* model=parent->GetAnimObject();return model&&model->IsCache();}
    return false;
}
class ImportDialog final:public CDialog {
    const amglb::Plan& plan;
public:
    double scale=100;
    bool mirror=false;
    explicit ImportDialog(const amglb::Plan& p):CDialog(IDD_IMPORT,CWnd::FromHandle(GetMainApplicationWnd())),plan(p){}
protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        std::ostringstream s;s.imbue(std::locale::classic());
        s<<plan.parts.size()<<" named parts; "<<plan.inputTriangles<<" source triangles\r\n"
         <<plan.pairedQuads<<" triangle pairs reconstructed; "<<plan.subdividedComponents<<" regions subdivided\r\n"
         <<plan.outputQuads<<" four-sided faces; "<<plan.vertices<<" mesh vertices\r\n\r\n"
         <<"Creates a new editable model with peaked control points and basic colors.\r\n"
         <<"Dimensions at 100 cm/unit: "<<(plan.maximum.x-plan.minimum.x)*100<<" x "
         <<(plan.maximum.y-plan.minimum.y)*100<<" x "<<(plan.maximum.z-plan.minimum.z)*100<<" cm.\r\n";
        for(const auto& note:plan.notes)s<<"\r\n"<<note;
        SetDlgItemText(IDC_SUMMARY,s.str().c_str());SetDlgItemText(IDC_SCALE,"100");
        static_cast<CEdit*>(GetDlgItem(IDC_SCALE))->SetLimitText(32);
        return TRUE;
    }
    void OnOK() override {
        CString value;GetDlgItemText(IDC_SCALE,value);
        std::istringstream input(value.GetString());input.imbue(std::locale::classic());
        input>>scale;const bool parsed=bool(input);input>>std::ws;
        if(!parsed||!input.eof()||!std::isfinite(scale)||scale<.001||scale>100000){
            MessageBox("Enter centimeters per GLB unit from 0.001 to 100000, using a decimal point.","GLB Import",MB_OK|MB_ICONWARNING);return;
        }
        mirror=IsDlgButtonChecked(IDC_MIRROR)==BST_CHECKED;CDialog::OnOK();
    }
};
using Point=std::array<float,3>;
using Quad=std::array<Point,4>;
Point Position(const Vector& p){return {p.x,p.y,p.z};}
std::unique_ptr<IEPolyModel> Prepare(const amglb::Part& part,const amglb::Plan& plan,double scale,bool mirror,std::multiset<Quad>& expected){
    auto model=std::make_unique<IEPolyModel>();
    model->SetNumVerts(static_cast<int>(part.vertices.size()));
    std::set<Point> unique;
    for(size_t i=0;i<part.vertices.size();++i){auto v=part.vertices[i]*scale;if(mirror)v.z=-v.z;
        if(std::max({std::abs(v.x),std::abs(v.y),std::abs(v.z)})>1000000)throw amglb::Error("Scaled coordinates exceed 1,000,000 cm.");
        Vector out(static_cast<float>(v.x),static_cast<float>(v.y),static_cast<float>(v.z));
        if(!unique.insert(Position(out)).second)throw amglb::Error("Scale and coordinate precision collapse distinct vertices. Recenter or simplify the mesh.");
        model->m_vertexlist[static_cast<int>(i)]=out;
    }
    model->m_attrlist.SetSize(static_cast<int>(plan.materials.size()));
    for(size_t i=0;i<plan.materials.size();++i){const auto& m=plan.materials[i];auto& a=model->m_attrlist.ElementAt(static_cast<int>(i));
        strcpy_s(a.m_name,_countof(a.m_name),m.name.c_str());
        a.m_diffusecolor.m_red=static_cast<float>(m.color[0]);a.m_diffusecolor.m_green=static_cast<float>(m.color[1]);a.m_diffusecolor.m_blue=static_cast<float>(m.color[2]);
        a.m_specularcolor.m_red=a.m_specularcolor.m_green=a.m_specularcolor.m_blue=1.F;
        a.m_diffusefalloff=1.F;a.m_ambiance=0.F;a.m_roughness=0.F;a.m_roughnessscale=0.F;
        a.m_specularsize=static_cast<float>(5+75*m.roughness);a.m_specularintensity=static_cast<float>(20+60*m.metallic);
        a.m_reflectivity=static_cast<float>(35*m.metallic);a.m_transparency=static_cast<float>(100*(1-m.color[3]));a.m_refraction=1.F;
    }
    model->SetNumFaces(static_cast<int>(part.faces.size()));model->SetNumNormals(static_cast<int>(part.faces.size()));
    for(size_t i=0;i<part.faces.size();++i){auto ids=part.faces[i].vertex;if(mirror)std::swap(ids[1],ids[3]);
        auto* face=model->m_polyarray[static_cast<int>(i)];
        face->SetVerts(static_cast<int>(ids[0]),static_cast<int>(ids[1]),static_cast<int>(ids[2]),static_cast<int>(ids[3]));
        face->m_attrid=static_cast<int>(part.faces[i].material);
        Quad key;std::array<amglb::Vec3,4> p;
        for(size_t k=0;k<4;++k){const auto& v=model->m_vertexlist[static_cast<int>(ids[k])];key[k]=Position(v);p[k]={v.x,v.y,v.z};face->m_normalid[k]=static_cast<int>(i);}
        const auto n=amglb::Cross(p[1]-p[0],p[2]-p[0]),n2=amglb::Cross(p[2]-p[0],p[3]-p[0]);
        if(amglb::Length(n)<1e-12||amglb::Length(n2)<1e-12||amglb::Dot(n,n2)<=0)throw amglb::Error("Scaled quad is degenerate at A:M precision.");
        const auto unit=amglb::Unit(n);model->m_normallist[static_cast<int>(i)]=Vector(static_cast<float>(unit.x),static_cast<float>(unit.y),static_cast<float>(unit.z));
        std::sort(key.begin(),key.end());expected.insert(key);
    }
    return model;
}
void PeakAndVerify(HModelCache* model,const std::multiset<Quad>& expected){
    std::set<HSpline*> splines;size_t total=0;
    for(auto* spline=model->GetHeadSpline();spline;spline=spline->GetNextSpline()){
        if(!splines.insert(spline).second||splines.size()>amglb::MaxOutputQuads*4)throw amglb::Error("Unexpected native spline structure.");
        auto* head=spline->GetHeadCP();std::set<HCP*> visited;
        for(auto* cp=head;cp;cp=cp->GetNext()){
            if(!visited.insert(cp).second){if(cp==head)break;throw amglb::Error("Unexpected native CP loop.");}
            if(++total>amglb::MaxOutputQuads*8)throw amglb::Error("Unexpected native control point count.");
            cp->SetPeaked();
        }
    }
    model->Update();model->FindPatches();
    const int count=model->GetPatchCount();
    if(count<0||static_cast<size_t>(count)!=expected.size()||model->GetHeadPatch5())throw amglb::Error("A:M patch count differs from the quad plan. Inspect or remove the incomplete model.");
    auto remaining=expected;
    for(int i=0;i<count;++i){auto* patch=model->GetPatch(i);if(!patch)throw amglb::Error("A:M returned a missing patch.");
        HCP* corners[]={patch->GetCP1(),patch->GetCP2(),patch->GetCP3(),patch->GetCP4()};Quad key;std::set<HCP*> heads;
        for(size_t k=0;k<4;++k){if(!corners[k]||!corners[k]->GetModelPosition())throw amglb::Error("Missing native patch corner.");
            heads.insert(corners[k]->GetHead());key[k]=Position(*corners[k]->GetModelPosition());}
        if(heads.size()!=4)throw amglb::Error("A:M created a triangular or collapsed patch.");
        std::sort(key.begin(),key.end());const auto found=remaining.find(key);
        if(found==remaining.end())throw amglb::Error("A:M patch corners differ from the quad plan. Inspect the incomplete model.");
        remaining.erase(found);
    }
}
}
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(uint32_t index,ObjectType& type){
    if(index>=_countof(Contexts))return FALSE;type=Contexts[index];return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject* object,uint32_t index,String& name,MenuCategory& category,BOOL& disabled){
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try{if(!ContextOK(object,index))return FALSE;name="GLB as Quad Patches...";category=MC_IMPORT;disabled=FALSE;return TRUE;}
    catch(CException* e){e->Delete();}catch(...){}return FALSE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject* object,uint32_t index){
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    HModelCache* created=nullptr;std::string failure;
    try{
        if(!ContextOK(object,index))return FALSE;
        CFileDialog file(TRUE,"glb",nullptr,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR,"Binary glTF (*.glb)|*.glb||",CWnd::FromHandle(GetMainApplicationWnd()));
        const auto chosen=file.DoModal();if(chosen==IDCANCEL)return TRUE;if(chosen!=IDOK)throw amglb::Error("Cannot open the GLB file dialog.");
        std::vector<uint8_t> bytes;
        {CFile input(file.GetPathName(),CFile::modeRead|CFile::shareDenyWrite|CFile::typeBinary);const auto size=input.GetLength();
            if(size<28||size>amglb::MaxFileBytes)throw amglb::Error("Select a complete GLB file, at most 32 MiB.");
            bytes.resize(static_cast<size_t>(size));
            if(input.Read(bytes.data(),static_cast<UINT>(bytes.size()))!=bytes.size())throw amglb::Error("Cannot read the complete GLB.");}
        amglb::Plan plan;{CWaitCursor busy;plan=amglb::ReadGLB(bytes);amglb::ConvertToQuads(plan);}
        ImportDialog dialog(plan);const auto result=dialog.DoModal();if(result==IDCANCEL)return TRUE;if(result!=IDOK)throw amglb::Error("Cannot open the import preview.");
        CWaitCursor busy;std::multiset<Quad> expected;std::vector<std::unique_ptr<IEPolyModel>> prepared;
        for(const auto& part:plan.parts)prepared.push_back(Prepare(part,plan,dialog.scale,dialog.mirror,expected));
        const auto name=amglb::SafeName(file.GetFileTitle().GetString(),"GLB Model");
        created=HModelCache::New(("GLB INCOMPLETE - "+name).c_str());if(!created)throw amglb::Error("A:M could not create a new model.");
        for(size_t i=0;i<prepared.size();++i)
            if(!created->MergeIEModel(prepared[i].get(),plan.parts[i].name.c_str(),0.F,TRUE,FALSE))throw amglb::Error("A:M could not convert part "+plan.parts[i].name+" to native splines.");
        PeakAndVerify(created,expected);created->SetName(name.c_str());created->SetChanged();created->Update();created->OpenView();created->ZoomFit();RefreshAllTrees();
        CString message;message.Format("Imported %zu named parts as %zu four-sided patches.\n\nCheck the model in shaded and wireframe views, then save it as an A:M model.",plan.parts.size(),plan.outputQuads);
        AfxMessageBox(message,MB_OK|MB_ICONINFORMATION);return TRUE;
    }catch(CException* e){char message[512]{};e->GetErrorMessage(message,_countof(message));failure=message;e->Delete();}
    catch(const std::exception& e){failure=e.what();}catch(...){failure="Unexpected import error.";}
    if(created){failure+="\n\nA model named GLB INCOMPLETE may remain. Inspect or remove that new model. Existing models were not edited.";
        try{created->SetChanged();created->Update();created->OpenView();RefreshAllTrees();}catch(CException* e){e->Delete();}catch(...){} }
    AfxMessageBox(failure.c_str(),MB_OK|MB_ICONERROR);return FALSE;
}
