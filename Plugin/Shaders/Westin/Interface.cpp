// Yves  2005/11/24  \Master13.0\Plugin\Shaders\Westin\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Matrix34.h"
#include "SDK/HModel.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_IsPerpendicular;
        case 1:
            return m_Alignment;
        case 2:
            return m_IsIsotropic;
        case 3:
            return m_AxisBone;
        default:
            return nullptr;
    }
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

bool CustomShader::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, Time time) {
    switch (ptrmessage) {
        case PTM_VALUECHANGED: // 2
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_AxisBone) {
                switch (m_ObjType) {
                    case HOT_CHOR:
                    {
                        auto *ModelBone = (HBone *)m_AxisBone->GetValue();
                        if (!ModelBone)
                            return true; // Might be a better strategy to use the model bone in this situation
                        HModel *ChorModel = GetModel();
                        if (HBoneContainer *ChorBoneContainer = ChorModel->GetChildBoneContainer())
                            m_RefBone = MatchChorBone(ModelBone, ChorBoneContainer);
                        else
                            m_RefBone = (HBone *)ChorModel;
                        return true;
                    }
                    case HOT_MODEL:
                        m_RefBone = (HBone *)m_AxisBone->GetValue();
                        break;
                    default:
                        break;
                }
                return true;
            }
        }
        default:
            break;
        //    case PTM_VALUESTORED:      // 3
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

void CustomShader::Copy(const DLLPlugin &other) {
//    ASSERT(false);
    m_Original = (CustomShader *)&other;
    m_RefBone = m_Original->m_RefBone;
}
