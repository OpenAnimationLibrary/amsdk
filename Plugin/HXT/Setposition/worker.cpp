#include "StdAfx.h"
#include "Setposition.h"

BOOL CSetpositionApp::SetPosition(HModelCache *hmc, HGroup *gh) const {

    HGroupCP *currentgroupcp;
    HCP *cp;
    Vector pos;

    CWaitCursor wait;
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }

    if (m_parameters.cp_group) {
        //groupmode
        for (currentgroupcp = gh->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
            cp = currentgroupcp->GetCP();
            pos = *cp->GetHead()->GetModelPosition();
            if (m_parameters.mirror_x) {
                pos.x *= -1;
            } else {
                if (m_parameters.m_x)
                    pos.x += m_parameters.translate_bone.x;
            }
            if (m_parameters.mirror_y) {
                pos.y *= -1;
            } else {
                if (m_parameters.m_y)
                    pos.y += m_parameters.translate_bone.y;
            }
            if (m_parameters.mirror_z) {
                pos.z *= -1;
            } else {
                if (m_parameters.m_z)
                    pos.z += m_parameters.translate_bone.z;
            }
            cp->SetPosition(&pos);
        }
    } else {
        for (currentgroupcp = gh->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
            cp = currentgroupcp->GetCP();
            pos = *cp->GetHead()->GetModelPosition();
            if (m_parameters.m_x)
                pos.x = m_parameters.translate_bone.x;
            if (m_parameters.m_y)
                pos.y = m_parameters.translate_bone.y;
            if (m_parameters.m_z)
                pos.z = m_parameters.translate_bone.z;
            cp->SetPosition(&pos);
        }
    }

    hmc->Update();
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

static void AddBones(HBone **b_bone, int &azb) {

    HBone *b_test = b_bone[azb - 1];
    if (b_test->GetChildBone() != nullptr) {
        for (HBone *b_temp = b_test->GetChildBone(); b_temp; b_temp = b_temp->GetSiblingBone()) {
            b_bone[azb] = b_temp;
            azb++;
            if (b_bone[azb - 1]->GetChildBone() != nullptr)
                AddBones(b_bone, azb);
        }
    }
}

BOOL CSetpositionApp::SetBone(HModelCache *hmc, HBone *hb) {
    PParameters *Pp = &m_parameters;
    int azbones = 0, azbones1 = 0, i;
    Quaternion b_rotate;
    Vector v_bone_end, v_bone_pivot, v_temp;
    HSegmentCache *hsg = nullptr;
    HGroupCP *hgcp = nullptr, *hgroup = nullptr, *accumgroup = nullptr, *accumgroup1 = nullptr, *accumgroupcp;
    HCP *cp = nullptr;
    Time wtime;

    CWaitCursor wait;

    azbones = hmc->CountBones();
    auto **b_bones = new HBone *[azbones];
    b_bones[0] = hb;
    azbones1 = 1;

    AddBones(b_bones, azbones1);
    hmc->SaveAllToUndo();

    if (Pp->rotate) {
        for (i = 0; i < azbones1; ++i) {
            if (b_bones[i]->GetObjectType() == HOT_SEGMENT) {
                hsg = (HSegmentCache *)b_bones[i];
                hgcp = hsg->GetGroupCP();
                for (hgroup = hgcp; hgroup; hgroup = hgroup->GetNext()) {
                    //				    hgroup->GetCP()->AddToGroup( &accumgroup );
                    hgroup->GetCP()->GetHead()->AddToGroup(&accumgroup);
                }
            }
        }
        Quaternion do_rotate = XYZRotateQ(Pp->rotate_bone.x, Pp->rotate_bone.y, Pp->rotate_bone.z);

        // RootBone
        Vector v_rootbone_pivot = b_bones[0]->GetBoneCache()->GetPivot()->GetValue();
        v_bone_end = b_bones[0]->GetBoneCache()->GetEnd()->GetValue();

        b_rotate = b_bones[0]->GetBoneCache()->GetRotate()->GetValue();
        b_rotate *= do_rotate;
        b_bones[0]->GetBoneCache()->GetRotate()->SetValue(b_rotate);
        b_bones[0]->GetBoneCache()->GetRotate()->StoreValue(wtime, b_rotate,FALSE);

        /*
                 v_temp = v_bone_end - v_rootbone_pivot; 
                v_temp *= do_rotate;
                v_temp += v_rootbone_pivot;
                b_bones[0]->GetBoneCache()->GetEnd()->StoreValue(wtime,v_temp,FALSE);
        */
        // ChildBones
        for (i = 1; i < azbones1; ++i) {
            v_bone_pivot = b_bones[i]->GetBoneCache()->GetPivot()->GetValue();
            v_bone_end = b_bones[i]->GetBoneCache()->GetEnd()->GetValue();

            v_temp = v_bone_pivot - v_rootbone_pivot;
            v_temp *= do_rotate;
            v_temp += v_rootbone_pivot;
            b_bones[i]->GetBoneCache()->GetPivot()->StoreValue(wtime, v_temp,FALSE);

            v_temp = v_bone_end - v_rootbone_pivot;
            v_temp *= do_rotate;
            v_temp += v_rootbone_pivot;
            b_bones[i]->GetBoneCache()->GetEnd()->StoreValue(wtime, v_temp,FALSE);
        }

        // CP's
        if (accumgroup) {
            accumgroupcp = accumgroup;
            while (accumgroupcp) {
                cp = accumgroupcp->GetCP();
                v_temp = *cp->GetModelPosition() - v_rootbone_pivot;
                v_temp *= do_rotate;
                v_temp += v_rootbone_pivot;
                cp->SetPosition(&v_temp);
                accumgroupcp = accumgroupcp->GetNext();
            }
            hmc->AddToTemporaryGroup(accumgroup);
        }
    }

    if (Pp->translate) {
        Vector v_offset;
        for (i = 0; i < azbones1; ++i) {
            if (b_bones[i]->GetObjectType() == HOT_SEGMENT) {
                hsg = (HSegmentCache *)b_bones[i];
                hgcp = hsg->GetGroupCP();
                for (hgroup = hgcp; hgroup; hgroup = hgroup->GetNext()) {
                    //					hgroup->GetCP()->AddToGroup( &accumgroup1 );
                    hgroup->GetCP()->GetHead()->AddToGroup(&accumgroup1);
                }
            }
        }
        v_offset.Set(0.F);
        if (Pp->modus) {
            // absolut
            v_bone_pivot = b_bones[0]->GetBoneCache()->GetPivot()->GetValue();
            if (Pp->translate_bone.x != 0) {
                v_offset.x = Pp->translate_bone.x - v_bone_pivot.x;
            }
            if (Pp->translate_bone.y != 0) {
                v_offset.y = Pp->translate_bone.y - v_bone_pivot.y;
            }
            if (Pp->translate_bone.z != 0) {
                v_offset.z = Pp->translate_bone.z - v_bone_pivot.z;
            }
        } else {
            // relativ
            if (Pp->translate_bone.x != 0) {
                v_offset.x = Pp->translate_bone.x;
            }
            if (Pp->translate_bone.y != 0) {
                v_offset.y = Pp->translate_bone.y;
            }
            if (Pp->translate_bone.z != 0) {
                v_offset.z = Pp->translate_bone.z;
            }
        }

        // Bones
        for (i = 0; i < azbones1; ++i) {
            b_rotate = b_bones[i]->GetBoneCache()->GetRotate()->GetValue(); //new
            v_bone_end = b_bones[i]->GetBoneCache()->GetEnd()->GetValue();
            v_bone_pivot = b_bones[i]->GetBoneCache()->GetPivot()->GetValue();
            v_bone_pivot += v_offset;
            v_bone_end += v_offset;
            b_bones[i]->GetBoneCache()->GetPivot()->StoreValue(wtime, v_bone_pivot,FALSE);
            b_bones[i]->GetBoneCache()->GetEnd()->StoreValue(wtime, v_bone_end,FALSE);
            b_bones[i]->GetBoneCache()->GetRotate()->SetValue(b_rotate); //new
            b_bones[i]->GetBoneCache()->GetRotate()->StoreValue(wtime, b_rotate,FALSE); //new
        }
        // CP's
        if (accumgroup1) {
            accumgroupcp = accumgroup1;
            while (accumgroupcp) {
                cp = accumgroupcp->GetCP();
                v_temp = *cp->GetModelPosition();
                v_temp += v_offset;
                cp->SetPosition(&v_temp);
                accumgroupcp = accumgroupcp->GetNext();
            }
            hmc->AddToTemporaryGroup(accumgroup1);
        }
    }

    delete [] b_bones;
    hmc->Update();
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}
