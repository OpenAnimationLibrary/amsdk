// Yves  2006-05-15  \Master13.0\Plugin\Shaders\Environment\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Matrix34.h"
#include "SDK/HModel.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_Clip;
        case 1:
            return m_Mapping;
        case 2:
            return m_Exposure;
        case 3:
            return m_AxisBone;
        default:
            return nullptr;
    }
}

bool CustomShader::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, Time time) {
    switch (ptrmessage) {
        case PTM_VALUECHANGED: // 2
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_AxisBone) {
                switch (m_ObjType) {
                    case HOT_CHOR:
                    {
                        auto *AxisBone = (HBone *)m_AxisBone->GetValue();
                        if (!AxisBone)
                            return true; // Might be a better strategy to use the model bone in this situation
                        HModel *ChorModel = GetModel();
                        if (HBoneContainer *ChorBoneContainer = ChorModel->GetChildBoneContainer())
                            m_RefBone = MatchChorBone(AxisBone, ChorBoneContainer);
                        else
                            m_RefBone = (HBone *)ChorModel;
                        return true;
                    }
                    case HOT_MODEL:
                        m_RefBone = (HBone *)m_AxisBone->GetValue();
                        break;
                    default:
                        break;
                    //          HModel *mo = GetModel();
                }
                return true;
            }
        }
        default:
            break;
        /*    case PTM_VALUESTORED:      // 3
                  {
                     HProperty *dueto = (HProperty *)lparam;
                     if ( dueto == m_Material ) {
                        int index = m_Material->GetValue();
                        if ( index < NPRESETS - 2 ) {
                           m_RoughnessX->SetValue( presets[index][0] );
                           m_RoughnessY->SetValue( presets[index][1] );
                        }
                        return TRUE;
                     }
                     if ( dueto == m_RoughnessX || dueto == m_RoughnessY ) {
                        int index = m_Material->GetValue();
                        if ( index < NPRESETS - 2 )
                           m_Material->SetValue( NPRESETS - 2 );
                        return TRUE;
                     }
                  } */
        //    case PTM_GETPOINTERLIST:   // 5
        //    case PTM_SELECTIONCHANGED: // 7
        //    case PTM_ENDLOAD:          // 10
    }
    return false;
}

void CustomShader::RecurseBoneList(HObjectListNode **previous, HBone *parentbone) {
    for (HBone *bone = parentbone->GetChildBone(); bone; bone = (HBone *)bone->GetSibling()) {
        HObjectListNode *current = HObjectListNode::New(bone, nullptr);
        (*previous)->SetSibling(current);
        *previous = current;
        RecurseBoneList(previous, bone);
    }
}

HObjectListNode *CustomShader::GetPointerList(HPointerPropertyBase *prop) // build a list of the bones in the model to populate the pointer property list with
{
    if ((HPointerProperty *)prop != m_AxisBone)
        return nullptr;
    // NOTE: Since a shader is a model surface property, we will only allow orienting the environment
    //       according to a model bone. This forces the user to constraint the selected model bone
    //       to translate and orient to one Chor bone. It might be a good idea to allow orienting
    //       the environment according to any chor bone when the model is in a chor.
    HModel *model = GetModel();
    if (!model)
        return nullptr;
    HObjectListNode *previous;
    HObjectListNode *head = previous = HObjectListNode::New(model, nullptr);
    if (HBoneContainer *bones = model->GetChildBoneContainer())
        for (HBone *bone = bones->GetChildBone(); bone; bone = (HBone *)bone->GetSibling()) {
            HObjectListNode *current = HObjectListNode::New(bone, nullptr);
            previous->SetSibling(current);
            previous = current;
            RecurseBoneList(&previous, bone);
        }
    return head;
}

HBone *CustomShader::MatchChorBone(HBone *ModelBone, HBoneContainer *ChorBoneContainer) {
    HTreeObject *to = ModelBone->GetParent();
    HBone *MatchBone;
    HBone *SearchBone;
    if (to->GetObjectType() == HOT_BONES) {
        MatchBone = ((HBoneContainer *)to)->GetChildBone();
        SearchBone = ChorBoneContainer->GetChildBone();
    } else {
        SearchBone = MatchChorBone((HBone *)to, ChorBoneContainer);
        MatchBone = ((HBone *)to)->GetChildBone();
        SearchBone = SearchBone->GetChildBone();
    }
    while (MatchBone != ModelBone) {
        MatchBone = MatchBone->GetSiblingBone();
        SearchBone = SearchBone->GetSiblingBone();
    }
    return SearchBone;
}

void CustomShader::Copy(const DLLPlugin &other) {
//    ASSERT(false);
    m_Original = (CustomShader *)&other;
    m_RefBone = m_Original->m_RefBone;
    m_Chor = m_Original->m_Chor;
}
