// AMGLBImport 0.1.7. Developed for Rodney Baker with OpenAI Codex assistance.
#include "StdAfx.h"
#include "ImportCore.h"
#include "MaterialSurface.h"
#include "resource.h"
#include "SDK/Entry.h"
#include "SDK/HModel.h"
#include "SDK/HPropert.h"
#include "RGBFloat.h"
#include "HashTime.h"
#include "SDK/HPatch.h"
#include "SDK/HCP.h"
#include "SDK/Misc.h"
#include <algorithm>
#include <locale>
#include <map>
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
    const amglb::Plan& source;
    bool initialized=false,dirty=true;
public:
    amglb::Plan plan;
    double scale=100;
    bool mirror=false;
    explicit ImportDialog(const amglb::Plan& p):CDialog(IDD_IMPORT,CWnd::FromHandle(GetMainApplicationWnd())),source(p){}
protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        SetDlgItemText(IDC_SCALE,"100");SetDlgItemText(IDC_TARGET,"0");
        static_cast<CEdit*>(GetDlgItem(IDC_SCALE))->SetLimitText(32);
        static_cast<CEdit*>(GetDlgItem(IDC_TARGET))->SetLimitText(6);
        initialized=true;UpdatePreview();return TRUE;
    }
    BOOL OnCommand(WPARAM wParam,LPARAM lParam) override {
        const auto id=LOWORD(wParam),notification=HIWORD(wParam);
        if(initialized&&id==IDC_PREVIEW&&notification==BN_CLICKED){UpdatePreview();return TRUE;}
        if(initialized&&((id==IDC_TARGET&&notification==EN_CHANGE)||(id==IDC_OMIT&&notification==BN_CLICKED))){
            dirty=true;GetDlgItem(IDOK)->EnableWindow(FALSE);
            SetDlgItemText(IDC_SUMMARY,"Options changed. Click Update preview to calculate the new patch count and omitted regions.");
        }
        return CDialog::OnCommand(wParam,lParam);
    }
    void UpdatePreview(){
        dirty=true;GetDlgItem(IDOK)->EnableWindow(FALSE);
        CString value;GetDlgItemText(IDC_TARGET,value);
        std::istringstream input(value.GetString());input.imbue(std::locale::classic());amglb::ImportOptions options;
        input>>options.targetPatches;const bool parsed=bool(input);input>>std::ws;
        if(!parsed||!input.eof()||options.targetPatches>amglb::MaxOutputQuads){
            SetDlgItemText(IDC_SUMMARY,"Enter a target patch count from 0 to 100000. Zero preserves full density.");return;
        }
        options.omitUnpaired=IsDlgButtonChecked(IDC_OMIT)==BST_CHECKED;
        try{CWaitCursor busy;plan=amglb::BuildImportPlan(source,options);}
        catch(const std::exception& e){SetDlgItemText(IDC_SUMMARY,(std::string("Preview unavailable: ")+e.what()+"\r\n\r\nAdjust the options and update the preview.").c_str());return;}
        std::ostringstream s;s.imbue(std::locale::classic());
        s<<plan.parts.size()<<" of "<<source.parts.size()<<" named parts retained; "<<plan.inputTriangles<<" source triangles\r\n";
        if(options.targetPatches)s<<"Target: "<<options.targetPatches<<" patches; actual: "<<plan.outputQuads<<". "<<plan.reducedTriangles<<" source triangles reduced.\r\n";
        if(options.omitUnpaired)s<<"Omitted "<<plan.omittedTriangles<<" unpaired triangles and "<<plan.omittedParts<<" empty parts. Omitted surfaces remain holes.\r\n";
        s
         <<plan.pairedQuads<<" triangle pairs reconstructed ("<<plan.curvedPairs<<" curved); "<<plan.subdividedComponents<<" regions subdivided\r\n"
         <<plan.outputQuads<<" four-sided faces; "<<plan.vertices<<" mesh vertices\r\n\r\n"
         <<"Creates a new editable model with peaked control points and basic colors.\r\n"
         <<"Dimensions at 100 cm/unit: "<<(plan.maximum.x-plan.minimum.x)*100<<" x "
         <<(plan.maximum.y-plan.minimum.y)*100<<" x "<<(plan.maximum.z-plan.minimum.z)*100<<" cm.\r\n";
        s<<"\r\nFour-sided patches only. Each CP attachment uses at most two splines. Part selection groups have no surface overrides.\r\n";
        if(plan.seamCopies)s<<"\r\nTopology fallback/cutouts: "<<plan.seamEdges<<" unwelded seam edges in "<<plan.seamedParts
            <<" parts ("<<plan.seamCopies<<" separate vertex copies). Surfaces meet in place, but seam sides move separately when edited. See each part's Seam points selection group.\r\n";
        for(const auto& note:plan.notes)s<<"\r\n"<<note;
        if(!plan.outputQuads)s<<"\r\nNo four-point patches remain. Disable omission or adjust density to retain geometry.";
        SetDlgItemText(IDC_SUMMARY,s.str().c_str());dirty=false;GetDlgItem(IDOK)->EnableWindow(plan.outputQuads!=0);
    }
    void OnOK() override {
        if(dirty){UpdatePreview();return;} // Never import a stale preview.
        if(!plan.outputQuads)return;
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
using Quad=std::array<uint32_t,4>;
Point Position(const Vector& p){return {p.x,p.y,p.z};}
struct PreparedPart {
    std::vector<Vector> vertices;
    amglb::SplinePlan routing;
    std::vector<amglb::MaterialGroup> materials;
};
PreparedPart Prepare(const amglb::Part& part,double scale,bool mirror){
    PreparedPart out;out.routing=amglb::RouteSplines(part);out.materials=amglb::GroupMaterials(part);out.vertices.reserve(part.vertices.size());
    for(const auto& p:amglb::PreparePositions(part,scale,mirror))out.vertices.emplace_back(p[0],p[1],p[2]);
    return out;
}
void SetFloat(HFloatProperty* property,double value){
    if(!property)throw amglb::Error("A:M returned a missing surface property.");
    property->SetNull(FALSE);property->StoreValue(Time(0),static_cast<float>(value),FALSE);
}
void SetPercentage(HFloatProperty* property,double fraction){
    if(!std::isfinite(fraction)||fraction<0||fraction>1)
        throw amglb::Error("Material percentage is outside the supported range.");
    SetFloat(property,fraction);
    const auto stored=property->GetValue(Time(0));
    if(!std::isfinite(stored)||std::abs(stored-fraction)>1e-5)
        throw amglb::Error("A:M did not retain a material percentage.");
}
void SetColor(HColorProperty* property,const RGBFloat& value){
    if(!property)throw amglb::Error("A:M returned a missing surface color.");
    property->SetNull(FALSE);property->StoreValue(Time(0),value,FALSE);
}
void ApplyMaterial(HGroup* group,const amglb::Material& m){
    // HPatch::GetAttr() is a nullable read of existing attributes, not a surface
    // allocator. A:M applies the persistent HGroup surface to its member patches.
    auto* attr=group->GetAttr();if(!attr)throw amglb::Error("A:M returned a missing material-group surface.");
    attr->SetNull(FALSE);
    SetColor(attr->GetDiffuseColor(),RGBFloat(static_cast<float>(m.color[0]),static_cast<float>(m.color[1]),static_cast<float>(m.color[2])));
    SetColor(attr->GetSpecularColor(),RGBFloat(1.F));
    SetFloat(attr->GetDiffuseFallOff(),1);SetFloat(attr->GetAmbiance(),0);
    SetFloat(attr->GetRoughness(),0);SetFloat(attr->GetRoughnessScale(),0);
    const auto surface=amglb::SurfaceForMaterial(m);
    SetPercentage(attr->GetSpecularSize(),surface.specularSize);SetPercentage(attr->GetSpecularIntensity(),surface.specularIntensity);
    SetPercentage(attr->GetReflectivity(),surface.reflectivity);SetPercentage(attr->GetTransparency(),surface.transparency);
    SetFloat(attr->GetRefraction(),1);
    group->OnModified();
}
struct ExpectedPatch { uint32_t material;amglb::Vec3 normal;std::string partName; };
struct NativeMaterialGroup {
    std::string partName;
    uint32_t material;
    std::vector<HCP*> points;
    std::vector<Quad> faces;
};
void AddGroupPoints(HGroup* group,const std::vector<HCP*>& points){
    for(auto* cp:points){group->AddCP(cp);if(!group->IsCPInGroup(cp))throw amglb::Error("A:M could not populate a group.");}
}
struct NativePlan {
    std::map<Quad,ExpectedPatch> patches;
    std::map<uint32_t,std::pair<Point,size_t>> vertices;
    std::set<std::pair<uint32_t,uint32_t>> edges;
    std::vector<HGroup*> groups;
    std::vector<NativeMaterialGroup> materialGroups;
    std::set<HSpline*> closed;
};
void CreatePart(HModelCache* model,const amglb::Part& part,const PreparedPart& prepared,bool mirror,NativePlan& expected){
    std::vector<HCP*> heads(part.vertices.size(),nullptr);
    std::vector<std::pair<uint32_t,HCP*>> occurrences;
    for(const auto& path:prepared.routing.paths){
        Vector first=prepared.vertices[path.vertex[0]],second=prepared.vertices[path.vertex[1]];
        auto* spline=model->StartSpline(&first,&second);if(!spline)throw amglb::Error("A:M could not create a spline.");
        auto* one=spline->GetHeadCP();auto* two=one?one->GetNext():nullptr;
        if(!one||!two)throw amglb::Error("A:M returned an incomplete spline.");
        one->SetPeaked();two->SetPeaked();occurrences.emplace_back(path.vertex[0],one);occurrences.emplace_back(path.vertex[1],two);
        for(size_t k=2;k<path.vertex.size();++k){auto* cp=spline->CreateCPAtTail(prepared.vertices[path.vertex[k]]);
            if(!cp)throw amglb::Error("A:M could not create a control point.");
            cp->SetPeaked();occurrences.emplace_back(path.vertex[k],cp);
        }
        if(path.closed){spline->MakeLooped(TRUE);expected.closed.insert(spline);}
    }
    for(const auto& occurrence:occurrences){auto*& head=heads[occurrence.first];
        if(!head)head=occurrence.second;
        // AttachCPs TRUE means the second CP was deleted (SDK Grid contract),
        // not success. Closed paths are already looped, so no deletion is planned.
        else if(model->AttachCPs(head,occurrence.second))throw amglb::Error("A:M unexpectedly merged spline control points.");
    }
    for(size_t v=0;v<heads.size();++v){
        if(!heads[v])throw amglb::Error("A:M omitted a planned vertex.");
        heads[v]=heads[v]->GetHead();
        if(!expected.vertices.emplace(heads[v]->GetID(),std::make_pair(Position(prepared.vertices[v]),prepared.routing.occurrences[v])).second)
            throw amglb::Error("A:M unexpectedly welded separate vertices.");
    }
    for(const auto& f:part.faces){Quad key;std::array<amglb::Vec3,4> p;
        for(size_t k=0;k<4;++k){key[k]=heads[f.vertex[k]]->GetID();const auto& v=prepared.vertices[f.vertex[k]];p[k]={v.x,v.y,v.z};}
        for(size_t k=0;k<4;++k)expected.edges.insert(std::minmax(key[k],key[(k+1)%4]));
        auto normal=amglb::Unit(amglb::Cross(p[1]-p[0],p[2]-p[0])+amglb::Cross(p[2]-p[0],p[3]-p[0]));
        if(mirror)normal=normal*-1;
        std::sort(key.begin(),key.end());
        if(!expected.patches.emplace(key,ExpectedPatch{f.material,normal,part.name}).second)throw amglb::Error("Duplicate native patch identity.");
    }
    std::vector<std::vector<HCP*>> stacks(heads.size());std::vector<HCP*> allPoints;
    for(const auto& occurrence:occurrences){stacks[occurrence.first].push_back(occurrence.second);allPoints.push_back(occurrence.second);}
    for(const auto& source:prepared.materials){
        NativeMaterialGroup material;material.partName=part.name;material.material=source.material;
        // Include the complete attachment stack, as the SDK TexturedGrid sample
        // does. A patch may reference either spline's CP at a shared vertex.
        for(auto v:source.vertices)material.points.insert(material.points.end(),stacks[v].begin(),stacks[v].end());
        for(auto i:source.faces){Quad corners;
            for(size_t k=0;k<4;++k)corners[k]=heads[part.faces[i].vertex[k]]->GetID();
            std::sort(corners.begin(),corners.end());material.faces.push_back(corners);
        }
        expected.materialGroups.push_back(std::move(material));
    }
    // Part selection groups have no surface override. Separate material groups
    // will cover only patches with the matching source material.
    auto* group=model->CreateGroup(part.name.c_str());if(!group)throw amglb::Error("A:M could not create a named selection group.");
    AddGroupPoints(group,allPoints);
    if(auto* attr=group->GetAttr()){attr->SetNullable(TRUE);attr->SetNull(TRUE);}
    expected.groups.push_back(group);
    if(!part.seamSource.empty()){
        std::vector<size_t> copies(heads.size());for(auto source:part.seamSource)++copies[source];
        std::vector<HCP*> points;
        for(size_t v=0;v<stacks.size();++v)if(copies[part.seamSource[v]]>1)points.insert(points.end(),stacks[v].begin(),stacks[v].end());
        if(!points.empty()){
            auto* seams=model->CreateGroup((part.name.substr(0,75)+" / Seam points").c_str());
            if(!seams)throw amglb::Error("A:M could not create a seam selection group.");
            AddGroupPoints(seams,points);
            if(auto* attr=seams->GetAttr()){attr->SetNullable(TRUE);attr->SetNull(TRUE);}
            expected.groups.push_back(seams);
        }
    }
}
Quad PatchKey(HPatch* patch){
    if(!patch)throw amglb::Error("A:M returned a missing patch.");
    HCP* corners[]={patch->GetCP1(),patch->GetCP2(),patch->GetCP3(),patch->GetCP4()};Quad key;
    for(size_t k=0;k<4;++k){if(!corners[k]||!corners[k]->GetHead())throw amglb::Error("Missing native patch corner.");key[k]=corners[k]->GetHead()->GetID();}
    std::sort(key.begin(),key.end());return key;
}
void VerifyAndColor(HModelCache* model,const NativePlan& expected,const amglb::Plan& plan){
    std::set<HSpline*> splines;std::map<uint32_t,size_t> actualVertices;
    std::multiset<std::pair<uint32_t,uint32_t>> actualEdges;
    size_t total=0;
    for(auto* spline=model->GetHeadSpline();spline;spline=spline->GetNextSpline()){
        if(!splines.insert(spline).second||splines.size()>amglb::MaxOutputQuads*4)throw amglb::Error("Unexpected native spline structure.");
        auto* first=spline->GetHeadCP();std::set<HCP*> visited;
        for(auto* cp=first;cp;cp=cp->GetNext()){
            if(!visited.insert(cp).second){if(cp==first)break;throw amglb::Error("Unexpected native CP loop.");}
            if(++total>amglb::MaxOutputQuads*8)throw amglb::Error("Unexpected native control point count.");
            auto* head=cp->GetHead();if(!head||!cp->GetModelPosition())throw amglb::Error("Missing native point.");
            const auto id=head->GetID();const auto found=expected.vertices.find(id);
            if(found==expected.vertices.end()||found->second.first!=Position(*cp->GetModelPosition()))throw amglb::Error("Native vertex differs from the spline plan.");
            if(++actualVertices[id]>2)throw amglb::Error("A:M attached more than two spline CPs at one junction.");
            if(auto* next=cp->GetNext())actualEdges.insert(std::minmax(id,next->GetHead()->GetID()));
            else if(expected.closed.count(spline)){
                if(!cp->IsLoop()&&!first->IsLoop()&&first->GetPrev()!=cp)throw amglb::Error("A:M did not close a planned spline.");
                actualEdges.insert(std::minmax(id,first->GetHead()->GetID()));
            }
        }
    }
    for(const auto& v:expected.vertices)if(actualVertices[v.first]!=v.second.second)
        throw amglb::Error("A:M junction has an unexpected number of spline CPs.");
    if(actualEdges!=std::multiset<std::pair<uint32_t,uint32_t>>(expected.edges.begin(),expected.edges.end()))
        throw amglb::Error("A:M spline edges differ from the plan, or an edge is duplicated.");
    model->Update();model->FindPatches();
    const int count=model->GetPatchCount();
    if(count<0||static_cast<size_t>(count)>amglb::MaxOutputQuads*2)throw amglb::Error("A:M returned an invalid patch count.");
    auto remaining=expected.patches;size_t unexpected=0;
    for(int i=0;i<count;++i){auto* patch=model->GetPatch(i);const auto found=remaining.find(PatchKey(patch));
        if(found==remaining.end())++unexpected;
        else remaining.erase(found);
    }
    if(!remaining.empty()||unexpected||model->GetHeadPatch5()){
        std::ostringstream message;
        message<<"A:M found "<<count<<" patches; expected "<<expected.patches.size()<<".\n"
               <<"Missing: "<<remaining.size()<<"; unexpected or duplicate: "<<unexpected<<".";
        if(!remaining.empty())message<<"\nFirst missing patch belongs to '"<<remaining.begin()->second.partName<<"'.";
        if(model->GetHeadPatch5())message<<"\nA:M also created an unexpected five-point patch.";
        message<<"\n\nColors were not assigned because patch verification failed.";
        throw amglb::Error(message.str());
    }
    for(int i=0;i<count;++i){auto* patch=model->GetPatch(i);const auto& wanted=expected.patches.at(PatchKey(patch));
        Vector normal;patch->GetPointNormalOnPatch(.5F,.5F,normal);
        if(amglb::Dot(wanted.normal,{normal.x,normal.y,normal.z})<0)patch->ReverseNormal();
    }
    std::vector<HGroup*> materialGroups;materialGroups.reserve(expected.materialGroups.size());
    for(const auto& source:expected.materialGroups){
        const auto& material=plan.materials[source.material];
        const auto name=source.partName.substr(0,35)+" / "+material.name.substr(0,35)+" ["+std::to_string(materialGroups.size()+1)+"]";
        auto* group=model->CreateGroup(name.c_str());if(!group)throw amglb::Error("A:M could not create a material group.");
        AddGroupPoints(group,source.points);ApplyMaterial(group,material);materialGroups.push_back(group);
    }
    model->OnModified();model->Update();
    // Reacquire patch handles after the host processes the group changes.
    std::map<Quad,HPatch*> coloredPatches;
    if(model->GetPatchCount()!=count||model->GetHeadPatch5())throw amglb::Error("A:M changed patch topology while assigning materials.");
    for(int i=0;i<count;++i){auto* patch=model->GetPatch(i);const auto key=PatchKey(patch);
        if(!expected.patches.count(key)||!coloredPatches.emplace(key,patch).second)throw amglb::Error("A:M changed patch identity while assigning materials.");
    }
    for(size_t i=0;i<materialGroups.size();++i){
        auto* group=materialGroups[i];const auto& source=expected.materialGroups[i];
        const int patches=group->GetPatchCount();
        if(patches<0||static_cast<size_t>(patches)!=source.faces.size())throw amglb::Error("A:M material-group patch coverage differs from the color plan.");
        for(const auto& key:source.faces)if(!group->IsPatchInGroup(coloredPatches.at(key)))throw amglb::Error("A:M omitted a patch from its material group.");
        auto* attr=group->GetAttr();auto* diffuse=attr?attr->GetDiffuseColor():nullptr;
        if(!diffuse||attr->IsNull()||diffuse->IsNull())throw amglb::Error("A:M did not retain a material-group surface.");
        const auto color=diffuse->GetNormalizedRGBFloat();const auto& wanted=plan.materials[source.material].color;
        if(std::abs(color.m_red-wanted[0])>1e-5||std::abs(color.m_green-wanted[1])>1e-5||std::abs(color.m_blue-wanted[2])>1e-5)
            throw amglb::Error("A:M material-group color differs from the imported color.");
    }
    for(auto* group:expected.groups)if(auto* attr=group->GetAttr();attr&&!attr->IsNull())throw amglb::Error("A named selection group has an unexpected surface override.");
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
        amglb::Plan source;{CWaitCursor busy;source=amglb::ReadGLB(bytes);amglb::ValidateSource(source);}
        ImportDialog dialog(source);const auto result=dialog.DoModal();if(result==IDCANCEL)return TRUE;if(result!=IDOK)throw amglb::Error("Cannot open the import preview.");
        const auto& plan=dialog.plan;
        CWaitCursor busy;NativePlan expected;std::vector<PreparedPart> prepared;
        for(const auto& part:plan.parts)prepared.push_back(Prepare(part,dialog.scale,dialog.mirror));
        const auto name=amglb::SafeName(file.GetFileTitle().GetString(),"GLB Model");
        created=HModelCache::New(("GLB INCOMPLETE - "+name).c_str());if(!created)throw amglb::Error("A:M could not create a new model.");
        for(size_t i=0;i<prepared.size();++i)
            CreatePart(created,plan.parts[i],prepared[i],dialog.mirror,expected);
        VerifyAndColor(created,expected,plan);created->SetName(name.c_str());created->SetChanged();created->Update();created->OpenView();created->ZoomFit();RefreshAllTrees();
        CString message;message.Format("Imported %zu named parts as %zu four-sided patches.\n\nCheck the model in shaded and wireframe views, then save it as an A:M model.",plan.parts.size(),plan.outputQuads);
        if(plan.seamEdges){CString seamMessage;seamMessage.Format("\n\n%zu unwelded seam edges in %zu parts. Seam sides move separately; use the Seam points selection groups to inspect them.",plan.seamEdges,plan.seamedParts);message+=seamMessage;}
        if(plan.omittedTriangles){CString omitted;omitted.Format("\n\n%zu unpaired triangles were omitted, leaving holes.",plan.omittedTriangles);message+=omitted;}
        AfxMessageBox(message,MB_OK|MB_ICONINFORMATION);return TRUE;
    }catch(CException* e){char message[512]{};e->GetErrorMessage(message,_countof(message));failure=message;e->Delete();}
    catch(const std::exception& e){failure=e.what();}catch(...){failure="Unexpected import error.";}
    if(created){failure+="\n\nA model named GLB INCOMPLETE may remain. Inspect or remove that new model. Existing models were not edited.";
        try{created->SetChanged();created->Update();created->OpenView();RefreshAllTrees();}catch(CException* e){e->Delete();}catch(...){} }
    failure="GLB Import 0.1.7\n\n"+failure;
    AfxMessageBox(failure.c_str(),MB_OK|MB_ICONERROR);return FALSE;
}
