// Yves Poissant  2004/03/21  \My Plugins\Shaders\WardAnisotropic\Interface.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"
#include "Matrix34.h"
#include "SDK/HModel.h"

// @formatter:off
namespace {
    float presets[30][2] = {
       {0.050f, 0.160f}, //  0 "Rolled Brass"
       {0.040f, 0.090f}, //  1 "Rolled Aluminum"
       {0.088f, 0.130f}, //  2 "Lightly Brushed Aluminum"
       {0.040f, 0.110f}, //  3 "Varnished Plywood"
       {0.080f, 0.096f}, //  4 "Enamel Finished Metal"
       {0.076f, 0.085f}, //  5 "Painted Cardboard Box"
       {0.037f, 0.064f}, //  6 "Brushed Semi Gloss Latex on Metal"
       {0.078f, 0.120f}, //  7 "Brushed Semi Gloss Latex on Sheetrock"
       {0.097f, 0.240f}, //  8 "Brushed Semi Gloss Latex on Wood"
       {0.037f, 0.063f}, //  9 "Brushed Gloss Latex on Metal"
       {0.100f, 0.100f}, // 10 "Brushed Gloss Latex on Sheetrock"
       {0.130f, 0.220f}, // 11 "Brushed Gloss Latex on Wood"
       {0.045f, 0.068f}, // 12 "Rolled Semi Gloss Latex on Metal"
       {0.083f, 0.120f}, // 13 "Rolled Semi Gloss Latex on Sheetrock"
       {0.120f, 0.260f}, // 14 "Rolled Semi Gloss Latex on Wood"
       {0.054f, 0.080f}, // 15 "Rolled Gloss Latex on Metal"
       {0.120f, 0.120f}, // 16 "Rolled Gloss Latex on Sheetrock"
       {0.130f, 0.200f}, // 17 "Rolled Gloss Latex on Wood"
       {0.041f, 0.055f}, // 18 "Sprayed Semi Gloss Latex on Metal"
       {0.096f, 0.110f}, // 19 "Sprayed Semi Gloss Latex on Sheetrock"
       {0.099f, 0.260f}, // 20 "Sprayed Semi Gloss Latex on Wood"
       {0.038f, 0.054f}, // 21 "Sprayed Gloss Latex on Metal"
       {0.100f, 0.100f}, // 22 "Sprayed Gloss Latex on Sheetrock"
       {0.120f, 0.170f}, // 23 "Sprayed Gloss Latex on Wood"
       {0.071f, 0.071f}, // 24 "Ceramic Tile"
       {0.082f, 0.082f}, // 25 "Glossy Paper"
       {0.130f, 0.130f}, // 26 "Computer Plastic"
       {0.092f, 0.092f}, // 27 "Plastic Laminate"
       {0.000f, 0.000f}, // 28 "Custom"
       {0.000f, 0.000f}, // 29 "Based on Specularity"
    };
}
// @formatter:on 

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_Material;
        case 1:
            return m_RoughnessX;
        case 2:
            return m_RoughnessY;
        case 3:
            return m_Alignment;
        case 4:
            return m_IsIsotropic;
        case 5:
            return m_IsBRDF;
        case 6:
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
                    //          HModel *mo = GetModel();
                }
                return true;
            }
        }
        case PTM_VALUESTORED: // 3
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_Material) {
                const int index = m_Material->GetValue();
                if (index < NPRESETS - 2) {
                    m_RoughnessX->SetValue(presets[index][0]);
                    m_RoughnessY->SetValue(presets[index][1]);
                }
                return true;
            }
            if (dueto == m_RoughnessX || dueto == m_RoughnessY) {
                const int index = m_Material->GetValue();
                if (index < NPRESETS - 2)
                    m_Material->SetValue(NPRESETS - 2);
                return true;
            }
        }
        default:
            break;
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
