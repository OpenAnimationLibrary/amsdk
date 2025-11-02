// Conform.cpp : Defines the initialization routines for the DLL.
//

#include "StdAfx.h"
#include "Conform.h"

//AM SDK Includes
#include "ConformDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

#define PLUGIN_CHOR_NAME "DressMe"

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState())
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CConformApp

BEGIN_MESSAGE_MAP(CConformApp, CWinApp)
    //{{AFX_MSG_MAP(CConformApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConformApp construction

CConformApp::CConformApp() = default;

CConformApp::~CConformApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CConformApp object

CConformApp theApp;

BOOL CConformApp::OnConformPlugin(HModel *hm) {
    CString message = " ";
    m_Chor = hm->GetChor();
    if (!m_Chor) {
        message.Format("No Choreography Found");
        AfxMessageBox(message);
        return TRUE;
    }
    m_ModelClothing = hm;

    CConformDialog dlg(m_Chor, m_ModelClothing);
    if (dlg.DoModal() != IDOK)
        return TRUE;

    //Create a new Choreography Action for placing the Clothing
    //with a Blend Mode.
    hm->GetTransform()->GetTranslate()->StoreValue(Time(), hm->GetTransform()->GetTranslate()->GetValue(Time()), false); //Steffen's magic code to create new ChorAction
    auto *hca = (HChorAction *)hm->GetCurrentChorAction();
    hca->SetName(PLUGIN_CHOR_NAME);

    HTypeProperty *htp = hca->GetBlendMethod();
    if (htp) {
        htp->SetValue(2); //0 = REPLACE, 1 = ADD, 2 = BLEND
        htp->StoreValue(Time(), 2, false);
    }

    m_ChorAction = hca;
    m_ModelBody = dlg.m_ModelBody;
    //Now Conform bones together and match relationship poses
    if (DoConform()) {
        //DoConformRelationship();  //I am currently unable to work out how to do this.
        m_ModelClothing->SetIsActionDeleted(true); //this triggers A:M to refresh the model (including 
        // actions ,constraints,poses  etc.) completely
        m_ModelClothing->RefreshInProjectBar();
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
    }
    return TRUE;
}

BOOL CConformApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();

}

// AM SDK
int CConformApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CConformApp::DoConform() const {
    //This function traverses all bones in the item of clothing,
    //and tries to locate a bone of the same name in the figure.
    //If it finds one, it creates an Orient-Like and Translate-To constraint.
    //Eventually it will also traverse all Poses, and create an expression so that 
    //the pose of the clothing will match the pose of the figure.

    CString message = " ";

    //Start traverse bones
    try {
        auto *m_ModelCache = (HModelCache *)m_ModelClothing;

        HBoneCacheContainer *boneFolder = m_ModelCache->GetChildBoneCacheContainer();
        if (boneFolder == nullptr)
            throw std::exception("ERROR: Clothing has not been rigged.");

        message = " ";
        HTreeObject *tmpTObj = boneFolder->GetChildBoneCache();
        HTreeObject *holdChild = nullptr;
        if (tmpTObj == nullptr)
            throw std::exception("ERROR: Could not get Tree Object.");

        HBone *rbone = tmpTObj->IsBone();
        bool isParent = FALSE;
        int iLevel = 0;
        if (rbone == nullptr)
            throw std::exception("ERROR: Could not get a root level bone.");

        do {
            holdChild = tmpTObj;
            do {
                holdChild = tmpTObj;
                if (!isParent) {
                    do {
                        iLevel++;
                        holdChild = tmpTObj;
                        rbone = tmpTObj->IsBone();
                        HBone *boneBody = m_ModelBody->FindBone(rbone->GetName());
                        if (boneBody) {

                            //Locate "Bones" Folder under the Choreography Action, create new as necessary.							
                            HTreeObject *boneCont = m_ChorAction->FindChildByName("Bones");
                            if (boneCont == nullptr) {
                                boneCont = HAnimObjectShortcut::New("Bones", FALSE);
                                m_ChorAction->InsertChildAtHead((HHashObject *)boneCont);
                            }

                            //Locate Bone Name under "Bones" Folder, create new as necessary
                            HTreeObject *boneName = boneCont->FindChildByName(rbone->GetName());

                            if (boneName == nullptr) {
                                boneName = HAnimObjectShortcut::New(rbone->GetName(), FALSE);
                                ((HHashObject *)boneCont)->InsertChildAtTail((HHashObject *)boneName, TRUE);
                            }

                            //Create Orient Like Constraint on Clothing using boneBody as the Target.
                            HOrientLikeConstraint *orient = HOrientLikeConstraint::New();
                            auto *hoBoneName = (HHashObject *)boneName;
                            hoBoneName->InsertChildAtTail(orient);

                            HPointerProperty *ppTarget = orient->GetTarget1();
                            ppTarget->SetValue(boneBody);
                            ppTarget->StoreValue(Time(), boneBody, TRUE);

                            //End Create Orient Like Constraint

                            //Set up Transform Property - Doing this causes the Target dropdown to appear correctly.
                            HTransformProperty *ppProperty = HTransformProperty::New();
                            if (ppProperty == nullptr)
                                throw std::exception("ERROR: No Transform Property Available");

                            HUserCategoryProperty *userCategory = rbone->CreateUserCategoryProperty();
                            if (userCategory == nullptr)
                                throw std::exception("ERROR: No User Category Created");

                            if (!userCategory->AddUserProperty(ppProperty, "Transform", TRUE))
                                throw std::exception("ERROR: No User Property Added");
                            orient->SetProperty(ppProperty);

                            //End Setup Transform Property

                            //Create Translate To Constraint on Clothing using boneBody as the Target.
                            HTranslateToConstraint *translate = HTranslateToConstraint::New();
                            auto *htBoneName = (HHashObject *)boneName;
                            htBoneName->InsertChildAtTail(translate);

                            ppTarget = translate->GetTarget1();
                            ppTarget->SetValue(boneBody);
                            ppTarget->StoreValue(Time(), boneBody, TRUE);
                            //End Create Translate To Constraint

                            //Set up Transform Property - Doing this causes the Target dropdown to appear correctly.
                            if (ppProperty == nullptr)
                                throw std::exception("ERROR: No Transform Property Available");

                            userCategory = rbone->CreateUserCategoryProperty();
                            if (userCategory == nullptr)
                                throw std::exception("ERROR: No User Category Created");

                            if (!userCategory->AddUserProperty(ppProperty, "Transform", TRUE))
                                throw std::exception("ERROR: No User Property Added");
                            translate->SetProperty(ppProperty);

                            //End Setup Transform Property
                        }
                    } while ((tmpTObj = holdChild->GetTreeProgeny()) != nullptr);
                }
                iLevel--;
                isParent = FALSE;
            } while ((tmpTObj = holdChild->GetTreeSibling()) != nullptr);
            isParent = TRUE;
        } while ((tmpTObj = holdChild->GetTreeParent()) != nullptr && iLevel > 0);
    }
    catch (char *e) {
        message = e;
        AfxMessageBox(message);
        return FALSE;
    }
    //end traverse bones
    return TRUE;
}

BOOL CConformApp::DoConformRelationship() const {
    //This function traverses all bones in the item of clothing,
    //and tries to locate a bone of the same name in the figure.
    //If it finds one, it creates an Orient-Like and Translate-To constraint.
    //Eventually it will also traverse all Poses, and create an expression so that 
    //the pose of the clothing will match the pose of the figure.

    //Start traverse bones
    try {
        HUserCategoryProperty *UserCategoryClothing = m_ModelClothing->GetUserCategoryProperty();
        HUserCategoryProperty *UserCategoryBody = m_ModelBody->GetUserCategoryProperty();
        if (UserCategoryClothing && UserCategoryBody) {
            for (int i = 0; ; ++i) {
                HProperty *hpClothing = UserCategoryClothing->GetPropertyAt(i);
                if (hpClothing) {
                    CString clothingName = hpClothing->GetName();
                    for (int j = 0; ; ++j) {
                        HProperty *hpBody = UserCategoryBody->GetPropertyAt(j);
                        if (hpBody) {
                            CString bodyName = hpBody->GetName();
                            if (bodyName == clothingName) {
                                //Create new expression here

                                //end create new expression
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }
        }

    }
    catch (char *e) {
        const CString message = e;
        AfxMessageBox(message);
        return FALSE;
    }
    //end traverse bones
    return TRUE;
}
