#include "StdAfx.h"
#include "MirrorBone.h"

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

bool NeedAttached(HSegmentCache *hsc, const HCP *cp) {
    HGroupCP *hgcp_org = hsc->GetGroupCP();
    if (!hgcp_org)
        return true; //segment has no cp's
    for (HGroupCP *hgroup = hgcp_org; hgroup; hgroup = hgroup->GetNext()) {
        if (cp == hgroup->GetCP())
            return false;
    }
    return true;
}

void GetBoneBranch(HBoneCache *hbc, CArrayEx<HBoneCache *, HBoneCache *> &bonearray) {
    for (; hbc; hbc = hbc->GetSiblingBoneCache()) {
        bonearray.Add(hbc);
        if (hbc->GetChildBoneCache())
            GetBoneBranch(hbc->GetChildBoneCache(), bonearray);
    }
}

void GetBoneBranchFirst(HBoneCache *hbc, CArrayEx<HBoneCache *, HBoneCache *> &bonearray) {
    if (hbc->GetChildBoneCache())
        GetBoneBranch(hbc->GetChildBoneCache(), bonearray);
}

void MirrorBone(HSegmentCache *hbc_org, HSegmentCache *hbc_dup, const bool isnull) {
    if (!hbc_org || !hbc_dup)
        return;
    //get original values
    Vector pivot = hbc_org->GetPivot()->GetValue();
    Vector end = hbc_org->GetEnd()->GetValue();
    const float bonelength = hbc_org->GetLength()->GetValue();
    Quaternion rotation = hbc_org->GetRotate()->GetValue();
    //mirror at the y axis
    pivot.x *= -1.F;
    end.x *= -1.F;
    Vector mirror_rot(rotation.GetX(),rotation.GetY(),rotation.GetZ());
    mirror_rot *= Vector(1.F, -1.F, -1.F);
    rotation.SetV(mirror_rot);
    //set mirrored values
    hbc_dup->GetPivot()->SetValue(pivot);
    hbc_dup->GetEnd()->SetValue(end);
    hbc_dup->GetLength()->SetValue(bonelength);
    hbc_dup->GetRotate()->SetValue(rotation);
    hbc_dup->GetPivot()->StoreValue(Time(), pivot, false);
    hbc_dup->GetEnd()->StoreValue(Time(), end, false);
    hbc_dup->GetLength()->StoreValue(Time(), bonelength, false);
    hbc_dup->GetRotate()->StoreValue(Time(), rotation, false);
    //set the other properties
    hbc_dup->GetChained()->SetValue(hbc_org->GetChained()->GetValue());
    hbc_dup->GetAllowXRotate()->SetValue(hbc_org->GetAllowXRotate()->GetValue());
    hbc_dup->GetAllowYRotate()->SetValue(hbc_org->GetAllowYRotate()->GetValue());
    hbc_dup->GetAllowZRotate()->SetValue(hbc_org->GetAllowZRotate()->GetValue());
    hbc_dup->GetAllowXScale()->SetValue(hbc_org->GetAllowXScale()->GetValue());
    hbc_dup->GetAllowYScale()->SetValue(hbc_org->GetAllowYScale()->GetValue());
    hbc_dup->GetAllowYScale()->SetValue(hbc_org->GetAllowYScale()->GetValue());
    hbc_dup->GetAllowXTranslate()->SetValue(hbc_org->GetAllowXTranslate()->GetValue());
    hbc_dup->GetAllowYTranslate()->SetValue(hbc_org->GetAllowYTranslate()->GetValue());
    hbc_dup->GetAllowZTranslate()->SetValue(hbc_org->GetAllowZTranslate()->GetValue());
    hbc_dup->GetLimitManipulators()->SetValue(hbc_org->GetLimitManipulators()->GetValue());
    hbc_dup->GetManipulationMethod()->SetValue(hbc_org->GetManipulationMethod()->GetValue());
    hbc_dup->GetRollMethod()->SetValue(hbc_org->GetRollMethod()->GetValue());
    hbc_dup->GetStop()->SetValue(hbc_org->GetStop()->GetValue());
    if (!isnull)
        hbc_dup->GetBoolCutter()->SetValue(hbc_org->GetBoolCutter()->GetValue());
    int i = 0;
    HProperty *property_org = hbc_org->GetPropertyAt(i);
    while (property_org) {
        String propertyname = property_org->GetFullName();
        if (propertyname.Find("EulerOrder") > -1 || propertyname.Find("Hidden") > -1 || propertyname.Find("Locked") > -1 || propertyname.Find("HasFalloff") > -1 || propertyname.Find("PreventCPAssignment") > -1) {
            HProperty *property_dup = hbc_dup->GetPropertyAt(i);
            if (property_dup)
                property_dup->Copy(property_org);
        }
        i++;
        property_org = hbc_org->GetPropertyAt(i);
    }
}

void CMirrorBoneApp::RemoveOldWeight(HCP *wcp) {
    CArray<HCPWeight *, HCPWeight *> weightlist;
    for (HCPWeight *cpweight = wcp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
        weightlist.Add(cpweight);
    }
    if (weightlist.GetSize() == 0)
        return;
    for (int i = 0; i < weightlist.GetSize(); ++i) {
        wcp->RemoveCPWeight(weightlist[i]);
    }
    weightlist.RemoveAll();
}

BOOL CMirrorBoneApp::CheckPositionBone(const int bone1, const int bone2) {
    if (bone_list[bone1].start == bone_list[bone2].m_start && bone_list[bone1].end == bone_list[bone2].m_end)
        return TRUE;
    if (para->use_tolerance_bones) {
        const float distance = hash_math::abs(Distance(bone_list[bone1].start, bone_list[bone2].m_start));
        const float distance2 = hash_math::abs(Distance(bone_list[bone1].end, bone_list[bone2].m_end));
        if (distance < para->tolerance_bones && distance2 < para->tolerance_bones) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

BOOL CMirrorBoneApp::CheckPositionBoneX0(const Vector pos_start, const Vector pos_end) const {
    if (hash_math::abs(pos_start.x) < para->tolerance_midbone && hash_math::abs(pos_end.x) < para->tolerance_midbone)
        return TRUE;
    return FALSE;
}

/*
CString CMirrorBoneApp::ReformatBoneName(CString oldname,bool always) {
   CString cbonename,ctemp;
   ctemp = oldname;
   if (ctemp.Find(para->removestring) != -1) {
      ctemp.Replace(para->removestring,para->addstring);
      cbonename.Format("%s",ctemp);
   } else {
      if (always) {
      cbonename.Format("%s%s",para->addstring,ctemp);
      } else {
         ctemp.Empty();
         return ctemp;
      }
   }
   return cbonename;
}
*/
void CMirrorBoneApp::ReformatBoneName(const CString &oldname, CString &newname, const bool always) const {
    CString ctemp_case;
    CString ctemp = ctemp_case = oldname;
    if (!para->casesensitive)
        ctemp_case.MakeLower();
    if (ctemp_case.Find(para->removestring) != -1) {
        if (para->casesensitive) {
            ctemp.Replace(para->removestring, para->addstring);
        } else {
            CString ctemp_mid, ctemp_right;
            const int pos = ctemp_case.Find(para->removestring);
            const int len = ctemp.GetLength();
            const int len_remove = para->removestring.GetLength();
            if (pos == 0) {
                ctemp_right = ctemp.Right(len - len_remove);
                ctemp_mid = para->addstring + ctemp_right;
            } else {
                const CString ctemp_left = ctemp.Left(pos);
                const int len_left = ctemp_left.GetLength();
                ctemp_right = ctemp.Right(len - (len_remove + len_left));
                ctemp_mid = ctemp_left + para->addstring + ctemp_right;
            }
            ctemp = ctemp_mid;
        }
        newname.Format("%s", ctemp.GetBuffer());
    } else {
        if (always) {
            newname.Format("%s%s", para->addstring.GetBuffer(), ctemp.GetBuffer());
        } else {
            newname.Empty();
            //			return ctemp;
        }
    }
    //	return cbonename;
}

HBoneCache *GetParentNotNullObject(HBoneCache *hbc) {
    if (hbc->GetObjectType() != HOT_NULLOBJECT)
        return hbc;
    HBoneCache *parent = hbc;
    do {
        parent = parent->GetParentBoneCache();
    } while (parent != nullptr && parent->GetObjectType() != HOT_NULLOBJECT);
    return parent;
}

HBoneCache *GetChildNotNullObject(HBoneCache *hbc) {
    if (hbc->GetObjectType() != HOT_NULLOBJECT)
        return hbc;
    HBoneCache *child = hbc;
    do {
        child = child->GetSiblingBoneCache();
    } while (child != nullptr && child->GetObjectType() != HOT_NULLOBJECT);
    if (child == nullptr) {
        child = hbc->GetChildBoneCache();
        if (child) {
            do {
                child = child->GetSiblingBoneCache();
            } while (child != nullptr && child->GetObjectType() != HOT_NULLOBJECT);
        }
    }
    return child;
}

void CMirrorBoneApp::FillBoneList(HModelCache *hmc) {
    CArrayEx<HBoneCache *, HBoneCache *> bctemp;

    HBoneCache *hbc_master = hmc->GetChildBoneCacheContainer()->GetChildBoneCache();
    auto *temp_hbc = (HBoneCache *)hmc;
    bctemp.Add(temp_hbc);
    GetBoneBranch(hbc_master, bctemp);

    if (!bone_list.IsEmpty())
        bone_list.RemoveAll();

    Vector pivot_p, pivot_c;
    CString mirror_name, ctemp;
    HBoneCache *temp_mainbone = temp_hbc;
    for (int i = 0; i < bctemp.GetSize(); ++i) {
        MB_BONE bonetemp;
        if (bctemp[i] == temp_mainbone)
            bonetemp.ismodelbone = TRUE;
        else
            bonetemp.ismodelbone = FALSE;
        bonetemp.mirror = -1;
        Vector pivot = bctemp[i]->GetPivot()->GetValue();
        Vector end = bctemp[i]->GetEnd()->GetValue();
        if (bctemp[i]->GetObjectType() == HOT_NULLOBJECT) {
            bonetemp.hbc = bctemp[i];
            bonetemp.hsc = (HSegmentCache *)bctemp[i];
            bonetemp.hnoc = (HNullObjectCache *)bctemp[i];
            bonetemp.isnullbone = true;
        } else {
            bonetemp.hbc = bctemp[i];
            bonetemp.hsc = (HSegmentCache *)bctemp[i];
            bonetemp.hnoc = nullptr;
            bonetemp.isnullbone = false;
        }
        bonetemp.parent = bonetemp.hbc->GetParentBoneCache();
        bonetemp.child = bonetemp.hbc->GetChildBoneCache();
        bonetemp.ismidbone = CheckPositionBoneX0(pivot, end);
        if (bonetemp.ismidbone && !bonetemp.isnullbone) {
            bonetemp.issource = true;
        } else {
            if (bonetemp.isnullbone) {
                bonetemp.ismidbone = false;
                if (bonetemp.parent)
                    temp_hbc = GetParentNotNullObject(bonetemp.parent);
                if (temp_hbc) {
                    pivot_p = temp_hbc->GetPivot()->GetValue();
                } else {
                    pivot_p.Set(0.F);
                }
                if (bonetemp.child)
                    temp_hbc = GetChildNotNullObject(bonetemp.child);
                if (temp_hbc) {
                    pivot_c = temp_hbc->GetPivot()->GetValue();
                } else {
                    pivot_c.Set(0.F);
                }
                //changed 08.01.07 name_only zweig 
                if (para->name_only) {
                    ctemp = bonetemp.hbc->GetName();
                    if (!para->casesensitive)
                        ctemp.MakeLower();
                    if (ctemp.Find(para->removestring) != -1) {
                        bonetemp.issource = true;
                    } else {
                        bonetemp.issource = false;
                    }
                } else {
                    if (para->sourceside) {
                        if (pivot_p.x < 0.F || pivot_c.x < 0.F) {
                            bonetemp.issource = true;
                        } else {
                            bonetemp.issource = false;
                        }
                    } else {
                        if (pivot_p.x > 0.F || pivot_c.x > 0.F) {
                            bonetemp.issource = true;
                        } else {
                            bonetemp.issource = false;
                        }
                    }
                }
                //end change								
            } else {
                //changed 08.01.07 name_only zweig
                if (para->name_only) {
                    ctemp = bonetemp.hbc->GetName();
                    if (!para->casesensitive)
                        ctemp.MakeLower();
                    if (ctemp.Find(para->removestring) != -1) {
                        bonetemp.issource = true;
                    } else {
                        bonetemp.issource = false;
                    }
                } else {
                    if (para->sourceside) {
                        if (pivot.x < 0.F) {
                            bonetemp.issource = true;
                        } else {
                            bonetemp.issource = false;
                        }
                    } else {
                        if (pivot.x > 0.F) {
                            bonetemp.issource = true;
                        } else {
                            bonetemp.issource = false;
                        }
                    }
                }
                //end change								
            }
        }
        bonetemp.start = pivot;
        bonetemp.end = end;
        pivot.x *= -1.F;
        end.x *= -1.F;
        bonetemp.m_start = pivot;
        bonetemp.m_end = end;
        bonetemp.ischanged = false;
        bone_list.Add(bonetemp);
    }
    bctemp.RemoveAll();
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        //mirror search
        if (!bone_list[i].issource)
            continue;
        CString org_name = bone_list[i].hbc->GetName();
        if (!para->casesensitive)
            org_name.MakeLower();
        ReformatBoneName(org_name, mirror_name, false);
        //		mirror_name = ReformatBoneName(org_name,false);
        for (int j = 0; j < bone_list.GetSize(); ++j) {
            if (i == j)
                continue;
            //Name check
            CString temp_name = bone_list[j].hbc->GetName();
            if (!para->casesensitive)
                temp_name.MakeLower();
            if (mirror_name == temp_name) {
                bone_list[i].mirror = j;
                break;
            }
        }
    }

    if (!para->name_only) {
        for (int i = 0; i < bone_list.GetSize(); ++i) {
            //mirror search
            if (bone_list[i].ismidbone || bone_list[i].isnullbone || !bone_list[i].issource || bone_list[i].mirror != -1)
                continue;
            for (int j = 0; j < bone_list.GetSize(); ++j) {
                if (i == j)
                    continue;
                //Pos check
                if (CheckPositionBone(i, j)) {
                    bone_list[i].mirror = j;
                    break;
                }
            }
        }
    }
}

bool CheckParent(HBoneCache *hbc, const HBoneCache *hbc_tofind) {

    if (!hbc)
        return false;
    HBoneCache *hbc_parent = hbc->GetParentBoneCache();
    if (!hbc_parent)
        return false;
    if (hbc_parent == hbc_tofind)
        return true;
    do {
        hbc_parent = hbc_parent->GetParentBoneCache();
        if (hbc_parent == hbc_tofind)
            return true;
    } while (hbc_parent);
    return false;
}

void CMirrorBoneApp::FillBoneList(HModelCache *hmc, HBoneCache *hbc_start) {
    CArrayEx<HBoneCache *, HBoneCache *> bctemp;
    MB_BONE bonetemp;

    HBoneCache *hbc_master = hmc->GetChildBoneCacheContainer()->GetChildBoneCache();
    auto *temp_hbc = (HBoneCache *)hmc;
    bctemp.Add(temp_hbc);
    GetBoneBranch(hbc_master, bctemp);

    if (!bone_list.IsEmpty())
        bone_list.RemoveAll();

    Vector pivot_p, pivot_c;
    CString mirror_name;
    HBoneCache *temp_mainbone = temp_hbc;
    for (int i = 0; i < bctemp.GetSize(); ++i) {
        if (bctemp[i] == temp_mainbone)
            bonetemp.ismodelbone = TRUE;
        else
            bonetemp.ismodelbone = FALSE;
        bonetemp.mirror = -1;
        Vector pivot = bctemp[i]->GetPivot()->GetValue();
        Vector end = bctemp[i]->GetEnd()->GetValue();
        if (bctemp[i]->GetObjectType() == HOT_NULLOBJECT) {
            bonetemp.hbc = bctemp[i];
            bonetemp.hsc = (HSegmentCache *)bctemp[i];
            bonetemp.hnoc = (HNullObjectCache *)bctemp[i];
            bonetemp.isnullbone = true;
        } else {
            bonetemp.hbc = bctemp[i];
            bonetemp.hsc = (HSegmentCache *)bctemp[i];
            bonetemp.hnoc = nullptr;
            bonetemp.isnullbone = false;
        }
        bonetemp.parent = bonetemp.hbc->GetParentBoneCache();
        bonetemp.child = bonetemp.hbc->GetChildBoneCache();
        bonetemp.start = pivot;
        bonetemp.end = end;
        pivot.x *= -1.F;
        end.x *= -1.F;
        bonetemp.m_start = pivot;
        bonetemp.m_end = end;
        bonetemp.ischanged = false;
        bonetemp.issource = false;
        bonetemp.ismidbone = false;
        bone_list.Add(bonetemp);
    }
    bctemp.RemoveAll();
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if (bone_list[i].hbc == hbc_start || bone_list[i].parent == hbc_start) {
            bone_list[i].issource = true;
        } else {
            [[maybe_unused]] String name = bone_list[i].hbc->GetName();
            if (CheckParent(bone_list[i].parent, hbc_start))
                bone_list[i].issource = true;
        }
    }

    for (int i = 0; i < bone_list.GetSize(); ++i) {
        //Now checking the boneside
        if (bone_list[i].issource) {
            bonetemp = bone_list[i];
            //check mid
            if (bonetemp.isnullbone) {
                if (bonetemp.parent)
                    temp_hbc = GetParentNotNullObject(bonetemp.parent);
                if (temp_hbc) {
                    pivot_p = temp_hbc->GetPivot()->GetValue();
                } else {
                    pivot_p.Set(0.F);
                }
                if (bonetemp.child)
                    temp_hbc = GetChildNotNullObject(bonetemp.child);
                if (temp_hbc) {
                    pivot_c = temp_hbc->GetPivot()->GetValue();
                } else {
                    pivot_c.Set(0.F);
                }
                //changed 08.01.07	name_only check	
                if (!para->name_only) {
                    if (para->sourceside) {
                        if (pivot_p.x > 0.F || pivot_c.x > 0.F)
                            bonetemp.issource = false;
                    } else {
                        if (pivot_p.x < 0.F || pivot_c.x < 0.F)
                            bonetemp.issource = false;
                    }
                }
            } else {
                //midbone checking
                bonetemp.ismidbone = CheckPositionBoneX0(bonetemp.start, bonetemp.end);
                //side checking
                if (!bonetemp.ismidbone) {
                    //changed 08.01.07	 name_only check			
                    if (!para->name_only) {
                        if (para->sourceside) {
                            if (bonetemp.start.x > 0.F)
                                bonetemp.issource = false;
                        } else {
                            if (bonetemp.start.x < 0.F)
                                bonetemp.issource = false;
                        }
                    }
                }
            }
            bone_list[i] = bonetemp;
        }
    }

    for (int i = 0; i < bone_list.GetSize(); ++i) {
        //mirror search
        if (!bone_list[i].issource)
            continue;
        const CString org_name = bone_list[i].hbc->GetName();
        ReformatBoneName(org_name, mirror_name, false);
        //		mirror_name = ReformatBoneName(org_name,false);
        for (int j = 0; j < bone_list.GetSize(); ++j) {
            if (i == j)
                continue;
            //Name check
            if (mirror_name == bone_list[j].hbc->GetName()) {
                bone_list[i].mirror = j;
                break;
            }
        }
    }

    if (!para->name_only) {
        for (int i = 0; i < bone_list.GetSize(); ++i) {
            //mirror search
            if (bone_list[i].ismidbone || bone_list[i].isnullbone || !bone_list[i].issource || bone_list[i].mirror != -1)
                continue;
            for (int j = 0; j < bone_list.GetSize(); ++j) {
                if (i == j)
                    continue;
                //Pos check
                if (CheckPositionBone(i, j)) {
                    bone_list[i].mirror = j;
                    break;
                }
            }
        }
    }
}

void CMirrorBoneApp::FillCPSList(HModelCache *hmc) {
    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!cp->IsHook()) {
                MB_CPS tempcp;
                //new
                tempcp.cp = cp;
                tempcp.pos = *cp->GetHead()->GetModelPosition();
                tempcp.m_pos = tempcp.pos;
                if (tempcp.m_pos.x != 0.F)
                    tempcp.m_pos.x *= -1;
                tempcp.isassigned = false;
                tempcp.weightsource = false;
                if (para->sourceside) {
                    if (tempcp.pos.x <= 0.F) {
                        tempcp.isassigned = true;
                        tempcp.weightsource = true;
                    }
                } else {
                    if (tempcp.pos.x >= 0.F) {
                        tempcp.isassigned = true;
                        tempcp.weightsource = true;
                    }
                }
                cps_list.Add(tempcp);
            }
            if (cp->IsLoop())
                break;
        }
    }
}

bool CMirrorBoneApp::CPIsValidAssigned(HCP *cp) {
    const HBoneCache *hbc = cp->GetSegmentCache();
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if (bone_list[i].hbc == hbc)
            return true;
    }
    return false;
}

HBoneCache *CMirrorBoneApp::FindParentByName(CArrayEx<HBoneCache *, HBoneCache *> bcdup, HBoneCache *parent_org, const bool isnullbone) const {
    CString searchname;
    if (!parent_org)
        return nullptr;
    if (isnullbone) {
        ReformatBoneName(parent_org->GetName(), searchname, false);
        //		searchname = ReformatBoneName(parent_org->GetName(),false);
    } else {
        ReformatBoneName(parent_org->GetName(), searchname, true);
        //		searchname = ReformatBoneName(parent_org->GetName(),true);
    }
    if (searchname.IsEmpty()) {
        return parent_org;
    }
    for (int i = 0; i < bcdup.GetSize(); ++i) {
        if (bcdup[i]->GetName() == searchname)
            return bcdup[i];
    }
    return parent_org;
}

HBoneCache *CMirrorBoneApp::FindParentFromList(HBoneCache *parent_org, const bool isnullbone) {
    CString searchname;
    if (!parent_org)
        return nullptr;
    if (isnullbone) {
        ReformatBoneName(parent_org->GetName(), searchname, false);
        //		searchname = ReformatBoneName(parent_org->GetName(),false);
    } else {
        ReformatBoneName(parent_org->GetName(), searchname, true);
        //		searchname = ReformatBoneName(parent_org->GetName(),true);
    }
    if (searchname.IsEmpty()) {
        return parent_org;
    }
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if (bone_list[i].hbc->GetName() == searchname)
            return bone_list[i].hbc;
    }
    return parent_org;
}

int CMirrorBoneApp::FindBoneFromList(const HBoneCache *bonetofind) {
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if (bone_list[i].hbc == bonetofind)
            return i;
    }
    return -1;
}

HSegmentCache *CMirrorBoneApp::FindBoneFromList(const HSegmentCache *bonetofind) {
    for (int i = 0; i < bone_list.GetSize(); ++i) {
//        const MB_BONE test = bone_list[i];
        if (bone_list[i].hsc == bonetofind) {
//            [[maybe_unused]] String t = test.hsc->GetName();
            if (bone_list[i].ismidbone)
                return bone_list[i].hsc;
            if (bone_list[i].mirror != -1)
                return bone_list[bone_list[i].mirror].hsc;

        }
    }
    return nullptr;
}

bool CMirrorBoneApp::FindBoneFromList(const String &bonename) {
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if ((String)bone_list[i].hbc->GetName() == bonename)
            return true;
    }
    return false;
}

BOOL CMirrorBoneApp::CheckPosition(const Vector pos_tocheck, const Vector pos) const {
    if (pos_tocheck == pos)
        return true;
    if (para->use_tolerance_cps) {
        const float distance = hash_math::abs(Distance(pos_tocheck, pos));
        if (distance < para->tolerance_cps) {
            return true;
        }
        return false;
    }
    return false;
}

void CMirrorBoneApp::MirrorSegmentBone(HSegmentCache *hsc_org, HSegmentCache *hsc_dup) {
    CArray<HCP *, HCP *> groupcp;
    Vector mirror_pos;
    if (hsc_org->GetObjectType() == HOT_NULLOBJECT || hsc_dup->GetObjectType() == HOT_NULLOBJECT)
        return;
    HGroupCP *hgcp_org = hsc_org->GetGroupCP();
    if (!hgcp_org)
        return; //segment has no cp's

    for (HGroupCP *hgroup = hgcp_org; hgroup; hgroup = hgroup->GetNext()) {
        groupcp.Add(hgroup->GetCP());
    }

    for (int a = 0; a < groupcp.GetSize(); ++a) {
        HCP *org_cp = groupcp[a];
        Vector org_pos = mirror_pos = *org_cp->GetHead()->GetModelPosition();
        if (mirror_pos.x != 0.F)
            mirror_pos.x *= -1;
        if (org_pos != mirror_pos) {
            //prevent cp's on the mirror axis
            for (int i = 0; i < cps_list.GetSize(); ++i) {
                if (cps_list[i].isassigned)
                    continue;
                if (CheckPosition(mirror_pos, cps_list[i].pos)) {
                    if (NeedAttached(hsc_dup, cps_list[i].cp)) {
                        hsc_dup->AquireCP(cps_list[i].cp);
                        cps_list[i].isassigned = true;
                        break;
                    }
                }
            }
        }
    }
    groupcp.RemoveAll();
}

void CMirrorBoneApp::MirrorBoneBranch(HModelCache *hmc, HBoneCache *start_hbc) {
    CArrayEx<HBoneCache *, HBoneCache *> bcdup;
    HBoneCache *parentbone, *hbc_dup;
    String bonename;
    CString cbonename;
    ColorBuf bonecolor;
    HSegmentCache *current_sc;
    int bone_nr;

    if (para->write_log)
        fs_log << "   MirrorBoneBranch" << nl;
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        if (bone_list[i].issource) {
            if (bone_list[i].isnullbone) {
                if (bone_list[i].mirror != -1) {
                    if (para->correct_pos_mirrorbone) {
                        MirrorBone(bone_list[i].hsc, bone_list[bone_list[i].mirror].hsc, false);
                        if (para->write_log)
                            fs_log << "MirrorPropertyNull " << bone_list[i].hbc->GetName() << nl;
                    }
                } else {
                    if (bcdup.IsEmpty()) {
                        parentbone = FindParentFromList(bone_list[i].parent, true);
                    } else {
                        parentbone = FindParentByName(bcdup, bone_list[i].parent, true);
                        if (para->excludestartbone) {
                            if (parentbone == nullptr)
                                parentbone = start_hbc;
                        }
                    }
                    if (bone_list[i].child) {
                        cbonename.Empty();
                        bone_nr = FindBoneFromList(GetChildNotNullObject(bone_list[i].child));
                        if (bone_nr == -1) {
                            ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                            //								cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                        } else {
                            if (!bone_list[bone_nr].ismidbone && bone_list[bone_nr].issource) {
                                ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, true);
                                //									cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),true);
                            } else {
                                ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                                //									cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                            }
                        }
                    } else {
                        ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                        //							cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                    }
                    if (!cbonename.IsEmpty() && bone_list[i].issource) {
                        bonename.Set(cbonename, cbonename.GetLength());
                        if (!FindBoneFromList(bonename)) {
                            HNullObjectCache *current_no = hmc->AddNullObjectCache(parentbone, nullptr, bonename);
                            hbc_dup = (HBoneCache *)current_no->GetCurrentBone()->GetCache();
                            current_sc = (HSegmentCache *)current_no;
                            bonecolor = bone_list[i].hbc->GetBoneColor();
                            current_sc->SetBoneColor(bonecolor);
                            MirrorBone(bone_list[i].hsc, current_sc, true);
                            bcdup.Add(hbc_dup);
                            if (para->write_log)
                                fs_log << "AddNull " << bonename << " <- " << bone_list[i].hbc->GetName() << nl;
                        }
                    }
                }
            } else {
                if (bone_list[i].ismidbone) {
                    MirrorSegmentBone(bone_list[i].hsc, bone_list[i].hsc);
                    if (para->write_log)
                        fs_log << "MirrorSegment Midbone " << bone_list[i].hbc->GetName() << nl;
                } else {
                    if (bone_list[i].mirror != -1) {
                        //mirror exist
                        if (para->correct_pos_mirrorbone) {
                            MirrorBone(bone_list[i].hsc, bone_list[bone_list[i].mirror].hsc, false);
                            if (para->write_log)
                                fs_log << "MirrorProperty " << bone_list[i].hbc->GetName() << nl;
                        }
                        if (para->write_log)
                            fs_log << "MirrorSegment " << bone_list[i].hbc->GetName() << nl;
                        MirrorSegmentBone(bone_list[i].hsc, bone_list[bone_list[i].mirror].hsc);
                    } else {
                        if (bcdup.IsEmpty()) {
                            parentbone = FindParentFromList(bone_list[i].parent, false);
                        } else {
                            parentbone = FindParentByName(bcdup, bone_list[i].parent, false);
                            if (para->excludestartbone) {
                                if (parentbone == nullptr)
                                    parentbone = bone_list[i].parent;
                            }
                        }
                        if (bone_list[i].child) {
                            cbonename.Empty();
                            bone_nr = FindBoneFromList(GetChildNotNullObject(bone_list[i].child));
                            if (bone_nr == -1) {
                                //Fehler ?
                                ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                                //									cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                            } else {
                                if (bone_list[bone_nr].issource) {
                                    ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, true);
                                    //										cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),true);
                                } else {
                                    ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                                    //										cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                                }
                            }
                        } else {
                            ReformatBoneName(bone_list[i].hbc->GetName(), cbonename, false);
                            //								cbonename = ReformatBoneName(bone_list[i].hbc->GetName(),false);
                        }
                        if (!cbonename.IsEmpty()) {
                            bonename.Set(cbonename, cbonename.GetLength());
                            bonecolor = bone_list[i].hbc->GetBoneColor();
                            current_sc = hmc->AddSegment(parentbone, nullptr, bonename, bonecolor);
                            hbc_dup = (HBoneCache *)current_sc->GetCurrentBone()->GetCache();
                            MirrorBone(bone_list[i].hsc, current_sc, false);
                            MirrorSegmentBone(bone_list[i].hsc, current_sc);
                            bcdup.Add(hbc_dup);
                            if (para->write_log)
                                fs_log << "AddBone " << bonename << " <- " << bone_list[i].hbc->GetName() << nl;
                        }
                    }
                }
            }
        }
    }
    if (para->write_log)
        fs_log << nl;
    bcdup.RemoveAll();
}

void CMirrorBoneApp::GroupUnassigned(HModelCache *hmc) {

    if (para->write_log)
        fs_log << "   CPID from unassigned CP's" << nl;
    const auto*temp_main = (HSegmentCache *)hmc;
    HGroup *hg = nullptr;
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        HSegmentCache *hsc = cps_list[i].cp->GetSegmentCache();
        if (hsc != temp_main) {
            if (!hsc->GetParentBoneCache()) {
                if (hg == nullptr)
                    hg = hmc->CreateGroup("Unassigned CPs");
                hg->AddCP(cps_list[i].cp);
                if (para->write_log)
                    fs_log << cps_list[i].cp->GetID() << nl;
            }
        }
    }
    if (para->write_log)
        fs_log << nl;
}

void CMirrorBoneApp::GroupNoMirrors(HModelCache *hmc) {
    HGroup *hg = nullptr;
    if (para->write_log)
        fs_log << "   CPID from CP's, where no mirror can found" << nl;
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        if (!cps_list[i].isassigned)
            continue;
        if (CheckPosition(cps_list[i].pos, cps_list[i].m_pos))
            continue;
        bool found = false;
        for (int j = 0; j < cps_list.GetSize(); ++j) {
            if (CheckPosition(cps_list[i].m_pos, cps_list[j].pos)) {
                found = true;
                break;
            }
        }
        if (!found) {
            if (hg == nullptr)
                hg = hmc->CreateGroup("CPs without Mirror");
            hg->AddCP(cps_list[i].cp);
            if (para->write_log)
                fs_log << cps_list[i].cp->GetID() << nl;
        }
    }
    if (para->write_log)
        fs_log << nl;
}

void CMirrorBoneApp::FillWeightList(HModelCache *hmc, const bool afterweighting) {
    CArrayEx<MB_WEIGHT, MB_WEIGHT> weightlist;
    HCPWeight *cpweight;

    cpw_list.RemoveAll();
    FillBoneList(hmc);
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        MB_CPW tempcpw;
        if (!cps_list[i].weightsource && !afterweighting)
            continue;
        weightlist.RemoveAll();
        HSegmentCache *hsc = cps_list[i].cp->GetSegmentCache();
        tempcpw.cp = cps_list[i].cp;
        tempcpw.pos = cps_list[i].pos;
        tempcpw.m_pos = cps_list[i].m_pos;
//        tempcpw.haveweight = false;
        if (hsc) {
            if (tempcpw.cp == tempcpw.cp->GetHead()) {
                MB_WEIGHT tempweight;
                if ((cpweight = tempcpw.cp->GetCPWeightHead())) {
                    tempcpw.haveweight = true;
                    tempweight.hsc = hsc;
                    tempweight.weight = 1.F;
                    tempcpw.weightlist.Add(tempweight);
                    for (cpweight = tempcpw.cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                        hsc = cpweight->GetSegmentCache();
                        tempweight.hsc = hsc;
                        tempweight.weight = cpweight->GetWeight();
                        tempcpw.weightlist.Add(tempweight);
                    }
                    for (int j = 1; j < tempcpw.weightlist.GetSize(); ++j) {
                        tempcpw.weightlist[0].weight -= tempcpw.weightlist[j].weight;
                    }
                    cpw_list.Add(tempcpw);
                    tempcpw.weightlist.RemoveAll();
                } else {
                    tempcpw.haveweight = false;
                    tempweight.hsc = tempcpw.cp->GetSegmentCache();
                    tempweight.weight = 1.F;
                    tempcpw.weightlist.Add(tempweight);
                    cpw_list.Add(tempcpw);
                    tempcpw.weightlist.RemoveAll();
                }
            }
        }
    }
}

bool CMirrorBoneApp::WeightAdd(const int i, const int k) {
    HCPWeight *cpweight = nullptr;
    CArrayEx<MB_WEIGHT_S, MB_WEIGHT_S> w_list;
    bool needrecalculate = false;
    HCP *cp = cps_list[k].cp->GetHead();
    if (cp != cps_list[k].cp)
        return false;
    if (CheckPosition(cpw_list[i].m_pos, cps_list[k].pos)) {
        int w_listsize = 0;
        for (int j = 0; j < cpw_list[i].weightlist.GetSize(); ++j) {
            MB_WEIGHT_S w_temp;
            w_temp.hsc = cpw_list[i].weightlist[j].hsc;
            w_temp.weight = cpw_list[i].weightlist[j].weight;
            w_temp.mirror = -1;
            w_temp.ismirror = false;
            w_list.Add(w_temp);
            w_listsize++;
            if (HSegmentCache *hsc = FindBoneFromList(cpw_list[i].weightlist[j].hsc); hsc) {
                bool dontadd = false;
                for (int h = 0; h < cpw_list[i].weightlist.GetSize(); ++h) {
                    if (hsc == cpw_list[i].weightlist[h].hsc)
                        dontadd = true;
                }
                if (!dontadd) {
                    w_list[w_listsize - 1].mirror = w_listsize;
                    w_list[w_listsize - 1].weight = w_list[w_listsize - 1].weight / 2.F;
                    w_temp.hsc = hsc;
                    w_temp.weight = w_list[w_listsize - 1].weight;
                    w_temp.mirror = w_listsize - 1;
                    w_temp.ismirror = true;
                    w_list.Add(w_temp);
                    w_listsize++;
                    needrecalculate = true;
                }
            }
        }
    }
    if (!needrecalculate) {
        w_list.RemoveAll();
        if (cpw_list[i].weightlist.GetSize() > 1)
            return true;
        return false;
    }
    if (para->write_log) {
        fs_log << "   CPWeight Recalculation for CP " << cp->GetID() << " needed" << nl << "   Old Weighting" << nl;
        for (int j = 0; j < w_list.GetSize(); ++j) {
            if (w_list[j].mirror == -1) {
                fs_log << w_list[j].hsc->GetName() << " Weight " << w_list[j].weight * 100.F << nl;
            } else {
                if (!w_list[j].ismirror) {
                    fs_log << w_list[j].hsc->GetName() << " Weight " << w_list[j].weight * 200.F << nl;
                }
            }
        }
        fs_log << "   New Weighting" << nl;
    }
    float weight = 0.F;
    for (int j = 0; j < w_list.GetSize(); ++j) {
        weight += w_list[j].weight;
    }
    if (weight < 1.F) {
        weight = (1.F - weight) / (w_list.GetSize() - 1);
        for (int j = 0; j < w_list.GetSize(); ++j) {
            w_list[j].weight += weight;
        }
    }

    RemoveOldWeight(cp);
    for (int j = 0; j < w_list.GetSize(); ++j) {
        if (para->write_log)
            fs_log << w_list[j].hsc->GetName() << " Weight " << w_list[j].weight * 100.F << nl;
        if (j == 0) {
            cpweight = cp->AddCPWeight();
            cpweight->SetSegmentCache(w_list[j].hsc);
            cpweight->SetWeight(w_list[j].weight);
        } else {
            if (j == 1) {
                cpweight->SetSegmentCache(w_list[j].hsc);
                cpweight->SetWeight(w_list[j].weight);
            } else {
                cpweight = cp->AddCPWeight();
                cpweight->SetSegmentCache(w_list[j].hsc);
                cpweight->SetWeight(w_list[j].weight);
            }
        }
    }
    w_list.RemoveAll();
    if (para->write_log)
        fs_log << nl;
    return true;
}

void CMirrorBoneApp::CheckUnWeighted(const int i) {
    if (hash_math::abs(cpw_list[i].pos.x) > para->tolerance_midbone)
        return;
    HSegmentCache *hsc = cpw_list[i].cp->GetSegmentCache();
    if (!hsc)
        return;
    const int bone_nr = FindBoneFromList((HBoneCache *)hsc);
    if (bone_nr == -1)
        return;
    if (!bone_list[bone_nr].issource)
        return;
    HSegmentCache *hsc_mirror = FindBoneFromList(hsc);
    if (!hsc_mirror)
        return;
    if (hsc == hsc_mirror)
        return;
    if (para->write_log) {
        fs_log << "   CPWeight new Weight for CP " << cpw_list[i].cp->GetID() << " createt" << nl;
        fs_log << hsc->GetName() << " Weight 50.0" << nl;
        fs_log << hsc_mirror->GetName() << " Weight 50.0" << nl << nl;
    }
    HCPWeight *cpweight = cpw_list[i].cp->AddCPWeight();
    cpweight->SetSegmentCache(hsc);
    cpweight->SetWeight(0.5F);
    cpweight->SetSegmentCache(hsc_mirror);
    cpweight->SetWeight(0.5F);
}

void CMirrorBoneApp::MirrorWeight() {
    HSegmentCache *hsc;
    HCPWeight *cpweight = nullptr;

    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        if (cpw_list[i].haveweight) {
            for (int k = 0; k < cps_list.GetSize(); ++k) {
                if (cpw_list[i].cp == cps_list[k].cp) {
                    if (WeightAdd(i, k))
                        continue;
                }
                HCP *cp = cps_list[k].cp->GetHead();
                if (cp != cps_list[k].cp)
                    continue;
                if (CheckPosition(cpw_list[i].m_pos, cps_list[k].pos) && CPIsValidAssigned(cp)) {
                    bool firstweight = false;
                    bool secondweight = false;
                    float weight = 0.F;
                    for (int j = 0; j < cpw_list[i].weightlist.GetSize(); ++j) {
                        hsc = FindBoneFromList(cpw_list[i].weightlist[j].hsc);
                        if (hsc) {
                            if (!firstweight) {
                                RemoveOldWeight(cp);
                                cpweight = cp->AddCPWeight();
                                firstweight = true;
                            } else {
                                if (secondweight)
                                    cpweight = cp->AddCPWeight();
                                if (firstweight)
                                    secondweight = true;
                            }
                            cpweight->SetSegmentCache(hsc);
                            cpweight->SetWeight(cpw_list[i].weightlist[j].weight);
                            weight += cpw_list[i].weightlist[j].weight;
                        }
                    }
                    if (cpweight && weight < 1.F) {
                        hsc = (HSegmentCache *)para->hmc;
                        if (secondweight)
                            cpweight = cp->AddCPWeight();
                        cpweight->SetSegmentCache(hsc);
                        cpweight->SetWeight(1.F - weight);
                    }
                    break;
                }
            }
        } else {
            if (para->weight_unweighted)
                CheckUnWeighted(i);
        }
    }
}

void CMirrorBoneApp::ClearTargetWeight() {
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        if (para->sourceside) {
            if (cps_list[i].pos.x > 0.F) {
                RemoveOldWeight(cps_list[i].cp);
            }
        } else {
            if (cps_list[i].pos.x < 0.F) {
                RemoveOldWeight(cps_list[i].cp);
            }
        }
    }
}

void CMirrorBoneApp::CheckAssignment() {
    HSegmentCache *hsc;
    if (para->write_log)
        fs_log << "   Check CPAssignment" << nl;
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        if (CheckPosition(cps_list[i].m_pos, cps_list[i].pos))
            continue;
        if (cps_list[i].isassigned) {
            hsc = cps_list[i].cp->GetSegmentCache();
            if (hsc) {
                HSegmentCache *hsc_mirror = FindBoneFromList(hsc);
                if (hsc_mirror) {
                    for (int k = 0; k < cps_list.GetSize(); ++k) {
                        if (CheckPosition(cps_list[i].m_pos, cps_list[k].pos)) {
                            HSegmentCache *hsc1 = cps_list[k].cp->GetSegmentCache();
                            if (hsc1 != hsc_mirror) {
                                if (para->write_log) {
                                    fs_log << "CP " << cps_list[k].cp->GetID() << " reassigned from ";
                                    fs_log << hsc1->GetName() << " to ";
                                    fs_log << hsc_mirror->GetName() << nl;
                                }
                                hsc_mirror->AquireCP(cps_list[k].cp);
                            }
                        }
                    }
                }
            }
        } else {
            hsc = cps_list[i].cp->GetSegmentCache();
            if (hsc) {
                cps_list[i].isassigned = TRUE;
            } else {
                if (para->write_log)
                    fs_log << "CP " << cps_list[i].cp->GetID() << " unassigned" << nl;
            }
        }
    }
    if (para->write_log)
        fs_log << nl;
}

bool CMirrorBoneApp::ConflictsWeights() {
    FileStream fs1;

    String filename = para->path + "mbw_conflicts_" + logname_ext.GetNameOnlyWithoutSuffix() + ".txt";

    FillWeightList(para->hmc, true);
    bool conflicts_exist = false;
    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        if (cpw_list[i].haveweight) {
            for (int j = 0; j < cpw_list[i].weightlist.GetSize() - 1; ++j) {
                for (int h = j + 1; h < cpw_list[i].weightlist.GetSize(); ++h) {
                    if (cpw_list[i].weightlist[j].hsc == cpw_list[i].weightlist[h].hsc) {
                        if (!conflicts_exist) {
                            fs1.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
                            conflicts_exist = true;
                            String temp = "False Weighting detected !\nLook into\n" + filename + "\nfor more information";
                            AfxMessageBox(temp.Get(), MB_OK | MB_ICONERROR);
                        }
                        if (conflicts_exist) {
                            fs1 << nl << "CP ID " << cpw_list[i].cp->GetID() << " weightet to " << nl;
                            fs1 << "  Bone \"" << cpw_list[i].weightlist[j].hsc->GetName();
                            fs1 << "\" " << cpw_list[i].weightlist[j].weight * 100.F << nl;
                            fs1 << "  Bone \"" << cpw_list[i].weightlist[h].hsc->GetName();
                            fs1 << "\" " << cpw_list[i].weightlist[h].weight * 100.F << nl;
                        }
                    }
                }
            }
        }
    }
    if (conflicts_exist)
        fs1.Close();
    return conflicts_exist;
}

void CMirrorBoneApp::DebugWeightsBefore() {
    FileStream fs1;

    String filename = logname_ext.GetPathOnly() + "\\mbw_before_" + logname_ext.GetNameOnlyWithoutSuffix() + ".txt";

    fs1.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        fs1 << "CPID " << cpw_list[i].cp->GetID() << nl;
        if (cpw_list[i].cp->GetSegmentCache()) {
            fs1 << "  Assigned to \"" << cpw_list[i].cp->GetSegmentCache()->GetName() << "\"" << nl;
        } else {
            fs1 << "  Not assigned" << nl;
        }
        fs1 << "  Attached cp ";
        for (HCP *cp = cpw_list[i].cp->GetHead(); cp; cp = cp->GetNextAttached()) {
            fs1 << cp->GetID() << ";";
        }
        fs1 << nl;
        if (cpw_list[i].haveweight) {
            fs1 << "  CP is weightet" << nl;
            for (int j = 0; j < cpw_list[i].weightlist.GetSize(); ++j) {
                fs1 << "    Bone \"" << cpw_list[i].weightlist[j].hsc->GetName() << "\" " << cpw_list[i].weightlist[j].weight * 100.F << nl;
            }
        } else {
            fs1 << "  CP is unweightet" << nl;
        }
        fs1 << nl;
    }
    fs1.Close();
}

void CMirrorBoneApp::DebugWeightsAfter() {
    FileStream fs1;

    String filename = logname_ext.GetPathOnly() + "\\mbw_after_" + logname_ext.GetNameOnlyWithoutSuffix() + ".txt";

    FillWeightList(para->hmc, true);
    fs1.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        fs1 << "CPID " << cpw_list[i].cp->GetID() << nl;
        if (cpw_list[i].cp->GetSegmentCache()) {
            fs1 << "  Assigned to \"" << cpw_list[i].cp->GetSegmentCache()->GetName() << "\"" << nl;
        } else {
            fs1 << "  Not assigned" << nl;
        }
        fs1 << "  Mirror cp ";
        for (int j = 0; j < cpw_list.GetSize(); ++j) {
            if (cpw_list[i].cp == cpw_list[j].cp)
                continue;
            if (CheckPosition(cpw_list[i].m_pos, cpw_list[j].pos)) {
                fs1 << cpw_list[j].cp->GetID() << ";";
            }
        }
        fs1 << nl;
        fs1 << "  Attached cp ";
        for (HCP *cp = cpw_list[i].cp->GetHead(); cp; cp = cp->GetNextAttached()) {
            fs1 << cp->GetID() << ";";
        }
        fs1 << nl;
        if (cpw_list[i].haveweight) {
            fs1 << "  CP is weightet" << nl;
            for (int j = 0; j < cpw_list[i].weightlist.GetSize(); ++j) {
                fs1 << "    Bone \"";
                if (cpw_list[i].weightlist[j].hsc)
                    fs1 << cpw_list[i].weightlist[j].hsc->GetName();
                fs1 << "\" " << cpw_list[i].weightlist[j].weight * 100.F << nl;
            }
        } else {
            fs1 << "  CP is unweightet" << nl;
        }
        fs1 << nl;
    }
    fs1.Close();
}

#ifdef _DEBUG
void CMirrorBoneApp::Debug() {
    fs << "Weightet cp's " << nl;
    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        if (cpw_list[i].haveweight)
            fs << cpw_list[i].cp->GetID() << nl;
    }
    fs << nl;
    for (int i = 0; i < bone_list.GetSize(); ++i) {
        fs << "Num " << i << nl;
        fs << bone_list[i].hbc->GetName() << nl;
        fs << "Mirror   " << bone_list[i].mirror << nl;
        fs << "Source   " << bone_list[i].issource << nl;
        fs << "Nullbone " << bone_list[i].isnullbone << nl;
        fs << "Midbone  " << bone_list[i].ismidbone << nl;
        if (bone_list[i].parent)
            fs << "Parent   " << bone_list[i].parent->GetName() << nl;
        if (bone_list[i].child)
            fs << "Child    " << bone_list[i].child->GetName() << nl;
        fs << nl;
    }
}
#endif

BOOL CMirrorBoneApp::Worker(HModelCache *hmc, HBoneCache *hbc) {
    FillCPSList(hmc);
    if (para->groupnotmirrors)
        GroupNoMirrors(hmc);
    FillBoneList(hmc, hbc);
    if (bar) {
        bar->SetMessage2("Mirror Bones");
        bar->SetProgress(20);
    }
    MirrorBoneBranch(hmc, hbc);
    FillBoneList(hmc);
    //	FillBoneList(hmc,hbc);
    if (bar) {
        bar->SetMessage2("Check CPAssignment");
        bar->SetProgress(40);
    }
    CheckAssignment();
    if (para->groupunassigned)
        GroupUnassigned(hmc);
    if (bar) {
        bar->SetMessage2("Collect Weights");
        bar->SetProgress(60);
    }
    hmc->SetChanged(true);
    if (para->clear_target)
        ClearTargetWeight();
    FillWeightList(hmc, false);
#ifdef _DEBUG
    Debug();
#endif
    if (para->extended_log)
        DebugWeightsBefore();
    if (bar) {
        bar->SetMessage2("Mirror Weights");
        bar->SetProgress(80);
    }
    MirrorWeight();
    hmc->SetChanged(true);
    if (para->extended_log)
        DebugWeightsAfter();
    ConflictsWeights();
    if (bar) {
        bar->SetMessage2("Finish");
        bar->SetProgress(100);
    }
    return true;
}

BOOL CMirrorBoneApp::WorkerGroup(HModelCache *hmc, HGroup *hg) {
    HBoneCache *hbc_start;
    CArrayEx<HBoneCache *, HBoneCache *> hbc_list;
//    CArrayEx<MB_WEIGHT, MB_WEIGHT> weightlist;
    HCPWeight *cpweight;

    bool weightet_cps = false;
    for (HGroupCP *currentgroupcp = hg->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
        HCP *cp = currentgroupcp->GetCP()->GetHead();
        bool issource = false;
        for (int i = 0; i < cpw_list.GetSize(); ++i) {
            if (cpw_list[i].cp == cp) {
                issource = true;
                break;
            }
        }
        if (!issource) {
            MB_CPW tempcpw;
            HSegmentCache *hsc = cp->GetSegmentCache();
            tempcpw.cp = cp;
            tempcpw.pos = *cp->GetModelPosition();
            tempcpw.m_pos = tempcpw.pos;
            if (tempcpw.m_pos.x != 0.F)
                tempcpw.m_pos.x *= -1.F;
//            tempcpw.haveweight = false;
            issource = false;
            if (para->sourceside) {
                if (tempcpw.pos.x <= 0.F) {
                    issource = true;
                }
            } else {
                if (tempcpw.pos.x >= 0.F) {
                    issource = true;
                }
            }
            if (hsc && issource) {
                bool found = false;
                for (int i = 0; i < hbc_list.GetSize(); ++i) {
                    if ((HBoneCache *)hsc == hbc_list[i]) {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    hbc_list.Add(hsc);
#ifdef _DEBUG
                fs << "CP " << tempcpw.cp->GetID() << " added to cpw_list" << nl;
#endif
                if (tempcpw.cp == tempcpw.cp->GetHead()) {
                    MB_WEIGHT tempweight;
                    if ((cpweight = tempcpw.cp->GetCPWeightHead())) {
                        tempcpw.haveweight = true;
                        tempweight.hsc = hsc;
                        tempweight.weight = 1.F;
                        tempcpw.weightlist.Add(tempweight);
                        for (cpweight = tempcpw.cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                            hsc = cpweight->GetSegmentCache();
                            tempweight.hsc = hsc;
                            tempweight.weight = cpweight->GetWeight();
                            tempcpw.weightlist.Add(tempweight);
                        }
                        for (int j = 1; j < tempcpw.weightlist.GetSize(); ++j) {
                            tempcpw.weightlist[0].weight -= tempcpw.weightlist[j].weight;
                        }
                        cpw_list.Add(tempcpw);
                        tempcpw.weightlist.RemoveAll();
                        weightet_cps = true;
                    } else {
                        tempcpw.haveweight = false;
                        tempweight.hsc = tempcpw.cp->GetSegmentCache();
                        tempweight.weight = 1.F;
                        tempcpw.weightlist.Add(tempweight);
                        cpw_list.Add(tempcpw);
                        tempcpw.weightlist.RemoveAll();
                    }
                }
            }
        }
    }

    if (hbc_list.IsEmpty())
        return false;

    const int bone_az = hbc_list.GetSize();

    if (bone_az == 1) {
        hbc_start = hbc_list[0]->GetParentBoneCache();
        if (!hbc_start)
            hbc_start = hbc_list[0];
    } else {
        int k = 0;
        int parent_az;
        do {
            parent_az = 0;
            hbc_start = hbc_list[k]->GetParentBoneCache();
            if (!hbc_start)
                hbc_start = hbc_list[k];
            for (int i = 0; i < hbc_list.GetSize(); ++i) {
                if (CheckParent(hbc_list[i], hbc_start))
                    parent_az++;
            }
            k++;
        } while (bone_az != parent_az && k < bone_az);
    }

    hbc_list.RemoveAll();
    if (!hbc_start || !weightet_cps) {
        AfxMessageBox("No weightet cp's found", MB_OK | MB_ICONINFORMATION);
        if (para->write_log)
            fs_log << nl << "Nothing to do" << nl;
        return false;
    }

    if (para->write_log)
        fs_log << "   StartBone  " << hbc_start->GetName() << nl << nl;

    GetHProject()->DeselectAll();

    FillCPSList(hmc);
    if (para->groupnotmirrors)
        GroupNoMirrors(hmc);
    FillBoneList(hmc, hbc_start);
    if (bar) {
        bar->SetMessage2("Mirror Bones (if needed)");
        bar->SetProgress(20);
    }
    MirrorBoneBranch(hmc, hbc_start);
    FillBoneList(hmc);
    if (bar) {
        bar->SetMessage2("Check CPAssignment");
        bar->SetProgress(40);
    }
    CheckAssignment();
    if (para->groupunassigned)
        GroupUnassigned(hmc);
    if (bar) {
        bar->SetMessage2("Collect Weights");
        bar->SetProgress(60);
    }
    hmc->SetChanged(true);
    if (para->clear_target)
        ClearTargetWeight();
#ifdef _DEBUG
    Debug();
#endif
    if (para->extended_log)
        DebugWeightsBefore();
    if (bar) {
        bar->SetMessage2("Mirror Weights");
        bar->SetProgress(80);
    }
    MirrorWeight();
    hmc->SetChanged(true);
    if (para->extended_log)
        DebugWeightsAfter();
    ConflictsWeights();
    if (bar) {
        bar->SetMessage2("Finish");
        bar->SetProgress(100);
    }
    return true;
}
