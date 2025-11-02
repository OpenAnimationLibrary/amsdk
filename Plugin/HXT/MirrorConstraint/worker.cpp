#include "MirrorConstraint.h"

void CMirrorConstraintApp::DuplicateConstraint(HTreeObject *hto, HAnimObjectShortcut *haos) {
    HPointerProperty *hpp;
    HTreeObject *hto_parent = hto->GetTreeParent();

    String temp = hto_parent->GetMatchName();
    temp.Replace(para->search, para->replace);
    auto *boneShortcut = (HAnimObjectShortcut *)haos->GetChild();
    while (boneShortcut) {
        String m_name = boneShortcut->GetMatchName();
        if (m_name == temp)
            break;
        auto *boneShortcut1 = (HAnimObjectShortcut *)boneShortcut->GetSibling();
        if (boneShortcut1 != boneShortcut)
            boneShortcut = boneShortcut1;
        else
            break;
    }
    if (!boneShortcut) {
        boneShortcut = HAnimObjectShortcut::New(temp.Get(), TRUE);
        haos->InsertChildAfterObject(boneShortcut, (HAnimObjectShortcut *)hto_parent);
        boneShortcut->ExpandInProjectBar(FALSE);
    } else {
#ifdef _DEBUG
        fsd << "Error boneshortcut already exist" << nl;
#endif
//        haos->InsertChildAfterObject(boneShortcut, (HAnimObjectShortcut *)hto_parent, FALSE);
//        boneShortcut->ExpandInProjectBar(FALSE);
        return;
    }

    std::vector<HTreeObject *> tree_vec;
    while (hto) {
        tree_vec.push_back(hto);
        hto = hto->GetTreeSibling();
    }

    for (size_t i = 0; i < tree_vec.size(); ++i) {
        HTreeObject *hto1 = tree_vec[i];
#ifdef _DEBUG
        fsd << hto1->GetFullName() << " | " << hto1->GetObjectType() << nl;
#endif
        switch (hto1->GetObjectType()) {
            case HOT_EULERLIMITS:
            {
                auto *hc0 = (HEulerLimits *)hto1;
                HEulerLimits *hc1 = HEulerLimits::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_SPHERICALLIMITS:
            {
                auto *hc0 = (HSphericalLimits *)hto1;
                HSphericalLimits *hc1 = HSphericalLimits::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_TRANSLATELIMITS:
            {
                auto *hc0 = (HTranslateLimits *)hto1;
                HTranslateLimits *hc1 = HTranslateLimits::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_ORIENTLIKECONSTRAINT:
            {
                auto *hc0 = (HOrientLikeConstraint *)hto1;
                HOrientLikeConstraint *hc1 = HOrientLikeConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
                hc0->Interpolate(Time());
                hc0->Interpolate(Time(100));
                Quaternion oldrotate = hc0->GetRotateOffset()->GetValue();
                Vector bonedir = oldrotate * Vector(0.F, 0.F, 1.F);
                Vector rolldir = oldrotate * Vector(0.F, 1.F, 0.F);
                bonedir.x = -bonedir.x;
                rolldir.x = -rolldir.x;
                Quaternion invertxrotateoffset = VectorsToStandardQ(bonedir, rolldir).Inverse();
                hc1->GetRotateOffset()->StoreValue(Time(100), invertxrotateoffset);
                hc0->Interpolate(Time());
                hc0->Interpolate(Time(100));
                hc1->Interpolate(Time());
                hc1->Interpolate(Time(100));
            }
            break;
            case HOT_AIMATCONSTRAINT:
            {
                auto *hc0 = (HAimAtConstraint *)hto1;
                HAimAtConstraint *hc1 = HAimAtConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_KINEMATICCONSTRAINT:
            {
                auto *hc0 = (HKinematicConstraint *)hto1;
                HKinematicConstraint *hc1 = HKinematicConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_TRANSLATETOCONSTRAINT:
            {
                auto *hc0 = (HTranslateToConstraint *)hto1;
                HTranslateToConstraint *hc1 = HTranslateToConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
                hc0->Interpolate(Time(100));
                Vector pos = hc0->GetTranslateOffset()->GetValue();
                pos.x = -pos.x;
                hc1->GetTranslateOffset()->StoreValue(Time(100), pos);
                hc1->Interpolate(Time(100));
            }
            break;
            case HOT_ROLLLIKECONSTRAINT:
            {
                auto *hc0 = (HRollLikeConstraint *)hto1;
                HRollLikeConstraint *hc1 = HRollLikeConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_AIMROLLATCONSTRAINT:
            {
                auto *hc0 = (HAimRollAtConstraint *)hto1;
                HAimRollAtConstraint *hc1 = HAimRollAtConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
                hc1->GetRollOffset()->StoreValue(Time(), hc0->GetRollOffset()->GetValue() * -1.F, FALSE);
            }
            break;
            case HOT_SCALELIKECONSTRAINT:
            {
                auto *hc0 = (HScaleLikeConstraint *)hto1;
                HScaleLikeConstraint *hc1 = HScaleLikeConstraint::New();
                hc1->Copy(hc0);
                boneShortcut->InsertChildAtTail(hc1);
                hc1->AddSelfAppliedDrivers();
                hpp = hc0->GetTarget1();
                temp = hpp->GetDescription();
                temp.Replace(para->search, para->replace);
                hpp = hc1->GetTarget1();
                hpp->SetDescription(temp);
                CopyPropertyDrivers(hc0, hc1);
            }
            break;
            case HOT_TIMEBASEDDRIVER:
            {
                auto *src = (HPropertyDriver *)hto1;
                HPropertyDriver *dst = src->MakeCopy();
                if (dst) {
                    dst->Copy(src);
                    boneShortcut->InsertChildAtTail(dst);
                    dst->AddSelfAppliedDrivers();
                    dst->CopyKeys(src);
                }
            }
            break;
            default:
                break;
        }
    }
}

/*
ab 15d
 HOT_AIMLIKETWOCONSTRAINT          = 22,
 HOT_AIMROLLLIKETWOCONSTRAINT      = 23,
 HOT_SURFACECONSTRAINT             = 78,
*/

BOOL CMirrorConstraintApp::GetBranch(HHashObject *hho) {
//    HTreeObject *hto;
//    HAnimObjectShortcut *haos;
    for (; hho; hho = hho->GetSibling()) {
#ifdef _DEBUG
        fsd << "Relation " << hho->GetName() << nl;
#endif
        if (hho->GetTreeProgeny()) {
            HTreeObject *hto = hho->GetTreeProgeny()->FindChildByName("Bones");
            if (hto) {
                auto *haos = (HAnimObjectShortcut *)hto;
                hto = hto->GetTreeProgeny();
                std::vector<HTreeObject *> tree_vec;
                for (HTreeObject *hto1 = hto; hto1; hto1 = hto1->GetTreeSibling()) {
                    tree_vec.push_back(hto1);
                }
                for (size_t i = 0; i < tree_vec.size(); ++i) {
                    HTreeObject *hto1 = tree_vec[i];
                    String temp = hto1->GetMatchName();
                    if (temp.Find(0, para->search) != -1) {
                        hto = hto1->GetTreeProgeny();
                        if (hto)
                            DuplicateConstraint(hto, haos);
                    } else {
                        String temp1 = hto1->GetTreeName();
                        if (temp1.Find(0, para->search) != -1) {
                            const String msg = "MatchName \"" + temp + "\" and Name \"" + temp1 + "\" different\nAborting";
                            AfxMessageBox(msg.Get(), MB_OK | MB_ICONSTOP);
                            return FALSE;
//                            hto = hto1->GetTreeProgeny();
//                            if (hto)
//                                DuplicateConstraint(hto, haos);
                        }
                    }
                }

            }
        }
        if (hho->GetChild())
            GetBranch(hho->GetChild());
    }
    return TRUE;
}

BOOL CMirrorConstraintApp::Work() {
    HUserCategoryProperty *hucp = para->hmc->GetUserCategoryProperty();
    if (!hucp) {
        return FALSE;
    }
    HActionCache *hac = HActionCache::New("temp_action", TRUE, FALSE);
    hac->SetDefaultModelCache(para->hmc);
    HModel *hm = hac->EditWithModelCache(para->hmc);
#ifdef _DEBUG
    fsd.Open("e:\\AM_Debug\\Constraint.txt", FileMode::HS_ASCII);
#endif
    int h = 0;
    HPropertyShortcut *hpo1;
    CWaitCursor wait;
    BOOL rc_value = TRUE;
    if (para->poses.GetSize() == 0) {
        while (hucp->GetPropertyAt(h) && rc_value) {
            HProperty *hpo = hucp->GetPropertyAt(h);
#ifdef _DEBUG
            fsd << "Pose " << hpo->GetName() << nl;
#endif
            hpo1 = hpo->FindEmptyRelation();
            if (hpo1) {
                rc_value = GetBranch(hpo1);
            }
            ++h;
        }
    } else {
        for (h = 0; h < para->poses.GetSize() && rc_value; ++h) {
            hpo1 = para->poses[h];
            rc_value = GetBranch(hpo1);
        }
    }
    hac->EndEditWithModelCache(hm);
    delete hac;
#ifdef _DEBUG
    fsd.Close();
#endif
    return rc_value;
}

BOOL CMirrorConstraintApp::WorkAction(HActionCache *hac) {
    HUserCategoryProperty *hucp = para->hmc->GetUserCategoryProperty();
    if (!hucp)
        return FALSE;
    HModel *hm = hac->EditWithModelCache(para->hmc);
#ifdef _DEBUG
    fsd.Open("e:\\AM_Debug\\Constraint.txt", FileMode::HS_ASCII);
#endif
    int h = 0;
    HPropertyShortcut *hpo1;
    CWaitCursor wait;
    BOOL rc_value = TRUE;
    if (para->poses.GetSize() == 0) {
        while (hucp->GetPropertyAt(h) && rc_value) {
            const HProperty *hpo = hucp->GetPropertyAt(h);
            hpo1 = hpo->FindEmptyRelation();
            if (hpo1) {
                rc_value = GetBranch(hpo1);
            }
            ++h;
        }
    } else {
        for (h = 0; h < para->poses.GetSize() && rc_value; ++h) {
            hpo1 = para->poses[h];
            rc_value = GetBranch(hpo1);
        }
    }
    hac->EndEditWithModelCache(hm);
#ifdef _DEBUG
    fsd.Close();
#endif
    return rc_value;
}

BOOL CMirrorConstraintApp::HandleSpecial(HPropertyDriver *src, HPropertyDriver *dst) {
    if (dst->IsConstraint()) {
        if (dst->IsStorageDriver())
            dst->CopyKeys(src);
        else
            CopyPropertyDrivers(src, dst);
        return TRUE;
    }
    if (dst->GetObjectType() == HOT_EXPRESSION) {
        String temp = ((HExpression *)dst)->GetExpressionString();
        temp.Replace(para->search, para->replace);
        [[maybe_unused]] int error = ((HExpression *)dst)->SetExpressionString(temp);
        return TRUE;
    }
    return FALSE;
}

void CMirrorConstraintApp::CopyPropertyDrivers(HHashObject *srcparent, HHashObject *dstparent) {
    for (auto *src = (HPropertyDriver *)srcparent->GetChild(); src; src = (HPropertyDriver *)src->GetSibling()) {
        HPropertyDriver *dst = src->MakeCopy();
        if (dst == nullptr)
            continue;
        dst->Copy(src);

        dstparent->InsertChildAtTail(dst);
        dst->AddSelfAppliedDrivers();

        if (!HandleSpecial(src, dst)) {
            if (dst->IsStorageDriver())
                dst->CopyKeys(src);
            else
                CopyPropertyDrivers(src, dst);
        }
    }
}
