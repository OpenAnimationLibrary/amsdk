// Brick.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Brick.h"
#include "PDialog.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrickApp

BEGIN_MESSAGE_MAP(CBrickApp, CWinApp)
        //{{AFX_MSG_MAP(CBrickApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrickApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBrickApp-Objekt

CBrickApp theApp;

BOOL CBrickApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CBrickApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

void GetBoundsModel(HModelCache *hmc, Vector &min, Vector &max, Vector &extents, Vector &size) {
    const Vector *bounds = hmc->GetBounds();
    min.Set(hash_constants::max_float);
    max.Set(-hash_constants::max_float);
    for (int j = 0; j < 8; ++j) {
        bounds[j].PushMinMax(min,max);
    }
    size.x = hash_math::abs(min.x) + hash_math::abs(max.x);
    size.y = hash_math::abs(min.y) + hash_math::abs(max.y);
    size.z = hash_math::abs(min.z) + hash_math::abs(max.z);
    extents = size * 0.5F;
}

BOOL CBrickApp::OnChor(HChor *hchor) {

    HModel *hm;
    para = new PParameter;

    para->hproject = GetHProject();
    para->hmc = nullptr;
    para->row = GetRegistryValue("Brick HXT", "Rows", 5);
    para->column = GetRegistryValue("Brick HXT", "Columns", 10);
    para->space_x = GetRegistryValue("Brick HXT", "Space_X", 0.01F);
    para->space_y = GetRegistryValue("Brick HXT", "Space_Y", 0.01F);
    para->position_z = GetRegistryValue("Brick HXT", "Pos_Z", 0.F);
    para->scale = GetRegistryValue("Brick HXT", "Scaling", FALSE);
    para->add_bullet = GetRegistryValue("Brick HXT", "AddBullet", FALSE);
    para->b_bounce = GetRegistryValue("Brick HXT", "B_Bounce", 0.5F);
    para->b_friction = GetRegistryValue("Brick HXT", "B_Friction", 0.5F);
    para->b_density = GetRegistryValue("Brick HXT", "B_Density", 0.9998F);
    para->b_weight = GetRegistryValue("Brick HXT", "B_Weight", 1.F);
    para->b_calcweight = GetRegistryValue("Brick HXT", "B_CalcWeight", FALSE);
    para->b_shape = GetRegistryValue("Brick HXT", "B_Shape", 0);
    para->userfolder = GetRegistryValue("Brick HXT", "UseFolder", TRUE);

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        para->hproject->UpdateAllViews(true);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }

    CWaitCursor wait;

    SetRegistryValue("Brick HXT", "Rows", para->row);
    SetRegistryValue("Brick HXT", "Columns", para->column);
    SetRegistryValue("Brick HXT", "Space_X", para->space_x);
    SetRegistryValue("Brick HXT", "Space_Y", para->space_y);
    SetRegistryValue("Brick HXT", "Pos_Z", para->position_z);
    SetRegistryValue("Brick HXT", "Scaling", para->scale);
    SetRegistryValue("Brick HXT", "AddBullet", para->add_bullet);
    SetRegistryValue("Brick HXT", "B_Bounce", para->b_bounce);
    SetRegistryValue("Brick HXT", "B_Friction", para->b_friction);
    SetRegistryValue("Brick HXT", "B_Density", para->b_density);
    SetRegistryValue("Brick HXT", "B_Weight", para->b_weight);
    SetRegistryValue("Brick HXT", "B_CalcWeight", para->b_calcweight);
    SetRegistryValue("Brick HXT", "B_Shape", para->b_shape);
    SetRegistryValue("Brick HXT", "UseFolder", para->userfolder);

    //Calculate Extends
    Vector min, max, extents, size;
    GetBoundsModel(para->hmc, min, max, extents, size);
    Vector start, start_versatz, pos;

    start.x = ((para->column * size.x + (para->column - 1) * para->space_x) * 0.5F - extents.x) * -1.F;
    start_versatz.x = ((para->column * size.x + (para->column - 2) * para->space_x) * 0.5F - size.x) * -1.F;
    start.y = start_versatz.y = extents.y + para->space_y;

    std::vector<void *> workingset;
    workingset.reserve(10000);
    pos.z = para->position_z;
    HHashObject *usercontainer{nullptr};
    HHashObject *rowcontainer{nullptr};
    HModel *sibling{nullptr};

    if (para->userfolder) {
        usercontainer = hchor->InsertUserFolder();
        usercontainer->SetName("Brick");
    }

    if (para->scale) {
        for (int j = 0; j < para->row; ++j) {
            if (para->userfolder) {
                rowcontainer = usercontainer->InsertUserFolder();
                String rowname = "Row " + (String)j;
                rowcontainer->SetName(rowname.Get());
                sibling = nullptr;
            }
            pos.y = j * (size.y + para->space_y) + start.y;
            if (j % 2 == 0) {
                for (int i = 0; i < para->column; ++i) {
                    hm = para->hmc->NewInstance(hchor);
                    if (hm) {
                        pos.x = i * (size.x + para->space_x) + start.x;
                        hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                        workingset.push_back(hm);
                        if (para->userfolder) {
                            hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                            sibling = hm;
                        }
                    }
                }
            } else {
                hm = para->hmc->NewInstance(hchor);
                if (hm) {
                    pos.x = start.x - extents.x * 0.5F;
                    hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                    hm->GetTransform()->GetScale()->StoreValue(Time(), Vector(0.5, 1, 1), FALSE);
                    workingset.push_back(hm);
                    if (para->userfolder) {
                        hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                        sibling = hm;
                    }
                }
                for (int i = 0; i < para->column - 1; ++i) {
                    hm = para->hmc->NewInstance(hchor);
                    if (hm) {
                        pos.x = i * (size.x + para->space_x) + start_versatz.x;
                        hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                        workingset.push_back(hm);
                        if (para->userfolder) {
                            hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                            sibling = hm;
                        }
                    }
                }
                hm = para->hmc->NewInstance(hchor);
                if (hm) {
                    pos.x = (para->column - 1) * (size.x + para->space_x) + start.x + extents.x * 0.5F;
                    hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                    hm->GetTransform()->GetScale()->StoreValue(Time(), Vector(0.5, 1, 1), FALSE);
                    workingset.push_back(hm);
                    if (para->userfolder) {
                        hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                        sibling = hm;
                    }
                }
            }
        }
    } else {
        for (int j = 0; j < para->row; ++j) {
            if (para->userfolder) {
                rowcontainer = usercontainer->InsertUserFolder();
                String rowname = "Row " + (String)j;
                rowcontainer->SetName(rowname.Get());
                sibling = nullptr;
            }
            pos.y = j * (size.y + para->space_y) + start.y;
            if (j % 2 == 0) {
                for (int i = 0; i < para->column; ++i) {
                    hm = para->hmc->NewInstance(hchor);
                    if (hm) {
                        pos.x = i * (size.x + para->space_x) + start.x;
                        hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                        workingset.push_back(hm);
                        if (para->userfolder) {
                            hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                            sibling = hm;
                        }
                    }
                }
            } else {
                for (int i = 0; i < para->column - 1; ++i) {
                    hm = para->hmc->NewInstance(hchor);
                    if (hm) {
                        pos.x = i * (size.x + para->space_x) + start_versatz.x;
                        hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, FALSE);
                        workingset.push_back(hm);
                        if (para->userfolder) {
                            hm->MoveWithChildren(rowcontainer, sibling, FALSE);
                            sibling = hm;
                        }
                    }
                }
            }
        }
    }

    if (para->add_bullet) {
        int wsize = workingset.size();
        for (int i = 0; i < wsize; ++i) {
            hm = (HModel *)workingset[i];
            HBulletConstraint *hb1 = HBulletConstraint::New(hm);
            if (hb1) {
                hb1->GetBounce()->SetValue(para->b_bounce);
                hb1->GetFriction()->SetValue(para->b_friction);
                hb1->GetDensity()->SetValue(para->b_density);
                hb1->GetWeight()->SetValue(para->b_weight);
                HTypeCategoryProperty *hcp = hb1->GetShapeHull();
                hcp->SetValue(para->b_shape);
                hb1->AddSelfAppliedDrivers();
                if (para->b_calcweight)
                    hb1->CalculateWeight();
            }
        }
    }

    para->hproject->UpdateAllViews(TRUE);
    RefreshAllTrees();
    delete para;
    return TRUE;

}
