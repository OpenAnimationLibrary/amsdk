#include "StdAfx.h"
#include "Hxt.h"
#include <vector>
#include "SDK/HProject.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include "SDK/Misc.h"

bool CHxtApp::Evaluate(HTreeObject *htreeobject) {
    if (!htreeobject)
        return TRUE;
    if (htreeobject->GetObjectType() != HOT_MODEL)
        return TRUE;
    auto *hmc = (HModelCache *)htreeobject;
    m_bonesfolder = hmc->GetChildBoneCacheContainer();

    if (m_bonesfolder) {
        EvaluateBoneChildren(m_bonesfolder);

        //	   HHashObject *hashobject = (HHashObject*)htreeobject;
        //	   HProject *project = (HProject*)hashobject->GetParentOfType(HOT_PROJECT);
        //	   project->UpdateAllViews(TRUE);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
    }
    return TRUE;
}

int CHxtApp::EvaluateBoneChildren(HTreeObject *htreeobject) const {
    //should extend HBoneCache to have a "Install as child of" property
    //should extend HBoneCache to have a delete on install property
    //should extend HBoneCache to have "Attach first child to parent on Install" property or "Attach to parent on Install" depending if the property is on the "INSTALL_" bone or not.
    //or
    //Add single category property "RigInstall setting" (Do Nothig, Move, Move and Delete, Move Delete and attach first child to parent)
#ifdef _DEBUG
    String test = htreeobject->GetMatchName();
#endif
    HTreeObject *nextchild;
    for (HTreeObject *child = htreeobject->GetTreeProgeny(); child; child = nextchild) {
        nextchild = child->GetTreeSibling();
        if (!EvaluateBoneChildren(child))
            return 0;
        if (child->GetObjectType() == HOT_SEGMENT) {
            auto *bone = (HBoneCache *)child;
            String name = bone->GetMatchName();
            static String installstr = "INSTALL";
            static String attachcommand = "(attached_to_parent)";
            static String geometrybonestr = "_geom";
            int installpos = name.Find(installstr);
            if (installpos != -1) {
                HBoneCache *attachbone = nullptr;
                installpos += installstr.GetLength();
                String parentname = name.Right(name.GetLength() - installpos);
                if (parentname[0] == '_')
                    parentname = parentname.Right(parentname.GetLength() - 1);
                static String commandstart = "(";
                const int commandpos = parentname.Find(commandstart);
                if (commandpos != -1) {
                    String command = parentname.Right(parentname.GetLength() - commandpos);
                    if (command == attachcommand) {
                        HTreeObject *prog = child->GetTreeProgeny();
                        if (prog)
                            attachbone = (HBoneCache *)prog->IsBone();
                    }
                    parentname = parentname.Left(commandpos);
                }
                int lastseporatorpos = parentname.ReverseFind('/');
                if (lastseporatorpos != -1)
                    parentname = parentname.Right(parentname.GetLength() - ++lastseporatorpos);
                HTreeObject *parent = m_bonesfolder->FindChildByName(parentname.Get());
                HBoneCache *parentbone;
                if (parent)
                    parentbone = (HBoneCache *)parent->IsBone();
                else
                    parentbone = nullptr;
                if (parentbone) {
                    bone->MoveWithChildren(parentbone, nullptr, FALSE);
                    delete bone;
                    if (attachbone)
                        attachbone->GetChained()->StoreValue(Time(), TRUE);
                } else {
                    if (lastseporatorpos != -1) {
                        String msg = "Warning could not find INSTALL bone parent for " + name;
                        AfxMessageBox(msg.Get());
                    } else {
                        auto *hsc = (HSegmentCache *)bone;
                        if (hsc) {
                            hsc->OnDelete(); //in the case cp are assigned to this bone
                        } else {
                            delete bone;
                        }
                    }
                }
            } else {
                HBoolProperty *hidden = ((HBone *)bone)->GetHidden();
                if (name.Find(geometrybonestr) != -1)
                    hidden->StoreValue(Time(), FALSE);
                else
                    hidden->StoreValue(Time(), TRUE);
            }
        }
    }
    return 1;
}
