#include "StdAfx.h"
#include "Export-Xforms.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
//#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HChor.h"
#include "SDK/HProject.h"
#include "SDK/Entry.h"
#include "F_Protos.h"
#include "ObjType.h"
#include "ExportXformsDialog.h"
#include "Matrix34.h"

struct bone_ref {
    HBone *anim_bone{};
    int parent{};
    char name[128]{};
    Vector loc;
    Quaternion rot;
};

// globals
CString g_str_menu_name = G_STRPLUGNAME;
ExportXformsApp theApp;

// other declarations
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *tree, UINT index);
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(UINT index, ObjectType &objtype);
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *tree, UINT index, String &menuname, MenuCategory &mc, BOOL &disabled);

/*
Plugin implementation
*/

HModel *get_current_object(HTreeObject *tree) {
    return (HModel *)tree;
}

int count_bones(HBone *bone) {
    if (!bone) {
        return 0;
    }
    return 1 + count_bones(bone->GetChildBone()) + count_bones(bone->GetSiblingBone());
}

void fill_in_refs(bone_ref **ppbr, HBone *bone, const int par_i, int *pli) {
    bone_ref *pbr = *ppbr;
    auto *bc = (HBoneCache *)bone->GetCache();
    const Vector loc = bc->GetPivot()->GetValue();
    const Quaternion rot = bc->GetRotate()->GetValue();
    strcpy_s(pbr->name,128, bc->GetName());
    pbr->anim_bone = bone;
    pbr->parent = par_i;
    pbr->loc = loc;
    pbr->rot = rot;
    HBone *child = bone->GetChildBone();
    HBone *sibling = bone->GetSiblingBone();
    if (child) {
        ++*ppbr;
        const int old_li = *pli;
        ++*pli;
        fill_in_refs(ppbr, child, old_li, pli);
    }
    if (sibling) {
        ++*ppbr;
        ++*pli;
        fill_in_refs(ppbr, sibling, par_i, pli);
    }
}

void fill_in_header(void **ppfc, const int start_frame, const int num_bones, const int num_frames) {
    const main_header hdr = {"XFORM", {0, 1}, num_bones, num_frames, start_frame};
    auto *phdr = (struct main_header *)*ppfc;
    *phdr = hdr;
    ++phdr;
    *ppfc = (void *)phdr;
}

void fill_in_bone_defs(void **ppfc, const int num_bones, bone_ref *pbr) {
    auto *pbd = (struct bone_def *)*ppfc;
    for (int i = 0; i < num_bones; ++i) {
        strcpy_s(pbd->name,128, pbr->name);
        pbd->parent = pbr->parent;
        pbd->base_translation[0] = pbr->loc[0];
        pbd->base_translation[1] = pbr->loc[1];
        pbd->base_translation[2] = pbr->loc[2];
        pbd->base_quat[0] = pbr->rot[0];
        pbd->base_quat[1] = pbr->rot[1];
        pbd->base_quat[2] = pbr->rot[2];
        pbd->base_quat[3] = pbr->rot[3];
        ++pbd;
        ++pbr;
    }
    *ppfc = (void *)pbd;
}

void fill_in_xforms(void **ppfc, const int start_frame, const int num_bones, const int num_frames, const bone_ref *refs, const double fps, HChor *chor) {
    const frame_header fh{num_bones};
    Time time = chor->GetTime();
    const Time go_back = time;
    time.SetFrame(start_frame, fps);
    for (int i = 0; i < num_frames; ++i) {
        auto *pfh = (struct frame_header *)*ppfc;
        *pfh = fh;
        ++pfh;
        auto *pxf = (struct xforms *)pfh;
        chor->SetTime(time);
        GetHProject()->UpdateAllViews(TRUE);
        for (int j = 0; j < num_bones; ++j) {
            const bone_ref ref = refs[j];
            HBone *b = ref.anim_bone;
            const TSQ btsq = b->GetTransform()->GetTSQ();
            Vector l = btsq.translate;
            Quaternion q = btsq.quat;
            Vector s = btsq.scale;
            pxf->bone_index = j;
            pxf->translation[0] = l[0];
            pxf->translation[1] = l[1];
            pxf->translation[2] = l[2];
            pxf->quat[0] = q[3]; // xyzw --> wxyz
            pxf->quat[1] = q[0];
            pxf->quat[2] = q[1];
            pxf->quat[3] = q[2];
            pxf->scale[0] = s[0];
            pxf->scale[1] = s[1];
            pxf->scale[2] = s[2];
            ++pxf;
        }
        *ppfc = (void *)pxf;
        time.StepFrame(fps);
    }
    chor->SetTime(go_back);
    GetHProject()->UpdateAllViews(TRUE);
}

HBone *get_top_bone(HModel *model) {
    HBoneContainer *bones = model->GetChildBoneContainer();
    if (!bones) {
        return nullptr;
    }
    HBone *bone = bones->GetChildBone();
    if (!bone) {
        return nullptr;
    }
    while (bone->GetParentBone()) {
        bone = bone->GetParentBone();
    }
    return bone->GetChildBone(); // hierarchy top is not a real bone, go down a notch
}

BOOL export_xforms(HModel *model) {
    if (!model) {
        return FALSE;
    }
    CExportXformsDialog cdlg(model->GetName());
    if (cdlg.DoModal() != IDOK) {
        return TRUE;
    }
    CWaitCursor wait;
    HBone *bone = get_top_bone(model);
    if (!bone) {
        AfxMessageBox("This model has no animated bones.");
        return TRUE;
    }
    const int num_bones = count_bones(bone);
    auto *refs = new struct bone_ref[num_bones];
    int last_index = 0;
    bone_ref *pbr = refs;
    //fill_in_refs(refs, bone, -1, &last_index);
    fill_in_refs(&pbr, bone, -1, &last_index);
    float fps = GetHProject()->GetFPS();
    if (fps == 0.0) {
        fps = 30.0;
    }
    const String spath = GetRegistryString("Export Transforms Plugin", "File Path", ".\\animation-master-export.xform");
    const int start_frame = GetRegistryValue("Export Transforms Plugin", "Start Frame", 0);
    const int end_frame = GetRegistryValue("Export Transforms Plugin", "End Frame", 30);
    const int num_frames = 1 + end_frame - start_frame;
    const int file_size = sizeof(struct main_header) + sizeof(struct bone_def) * num_bones + sizeof(struct frame_header) * num_frames + sizeof(struct xforms) * num_frames * num_bones;
    void *xf_file_contents = malloc(file_size);
    void *off = xf_file_contents;
    fill_in_header(&off, start_frame, num_bones, num_frames);
    fill_in_bone_defs(&off, num_bones, refs);
    fill_in_xforms(&off, start_frame, num_bones, num_frames, refs, fps, model->GetChor());
    BOOL written = FALSE;
    FILE *file;
    if (fopen_s(&file, spath.Get(), "wb") == 0) {
        fwrite(xf_file_contents, file_size, 1, file);
        fclose(file);
        written = TRUE;
    }
    free(xf_file_contents);
    delete[] refs;
    return written;
}

/****/

ExportXformsApp::ExportXformsApp() = default;

ExportXformsApp::~ExportXformsApp() = default;

// Hash SDK's command loading by object type
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (!index) {
        objtype = HOT_MODEL;
        return TRUE;
    }
    return FALSE;
}

// Hash SDK's menu loading
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *tree, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    if (!index) {
        if (!((HAnimObject *)tree)->IsCache()) {
            menuname = g_str_menu_name;
            disabled = FALSE;
            mc = MC_EXPORT;
            return TRUE;
        }
    }
    return FALSE;
}

// Hash SDK's actual command
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *tree, UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    HModel *obj = get_current_object(tree);
    if (obj) {
        return export_xforms(obj);
    }
    return FALSE;
}

BOOL ExportXformsApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int ExportXformsApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
