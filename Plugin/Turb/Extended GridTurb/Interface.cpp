// Yves  2004/11/17  \Plugin\Turb\Extended GridTurb\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"

extern CTurbApp theApp;

void CustomTurbulence::UpdateUI() {
    m_UIDirty = FALSE;
    if (m_TypeDirty) {
        const int GridType = m_GridType->GetValue();
        m_UseX->Show(GridType == GRID_CUBICAL);
        m_UseY->Show(GridType == GRID_CUBICAL);
        m_UseAzimuth->Show(GridType != GRID_CUBICAL);
        m_UseElevation->Show(GridType == GRID_SPHERICAL);
        m_UseRadial->Show(GridType == GRID_CYLINDRICAL);
        m_TypeDirty = FALSE;
        return;
    }
    if (m_UseXDirty) {
        const BOOL UseX = m_UseX->GetValue();
        m_XSize->Show(!UseX);
        m_XSize->Show(UseX);
        m_XRatio->Show(UseX);
        m_XBlur->Show(UseX);
        m_UseXDirty = FALSE;
    }
}

BOOL CustomTurbulence::IsUpdatePtr(const int at, HProperty *dueto) const {
    switch (at) {
        case IDS_GRIDTYPE:
            if (dueto == (HProperty *)m_GridType)
                return TRUE;
        case IDS_XGRIDS:
            if (dueto == (HProperty *)m_UseX)
                return TRUE;
        default:
            break;
    }
    if (m_CopyOf && m_CopyOf->IsUpdatePtr(at, dueto))
        return TRUE;
    return FALSE;
}

bool CustomTurbulence::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, Time time) {
    switch (ptrmessage) {
        case PTM_ENDLOAD:
        case PTM_VALUECHANGED:
        case PTM_VALUESTORED:
        {
            if (IsUpdatePtr(IDS_GRIDTYPE, (HProperty *)lparam)) {
                m_UIDirty = m_TypeDirty = TRUE;
                if ((HProperty *)lparam == (HProperty *)m_GridType)
                    UpdateUI();
            }
            if (IsUpdatePtr(IDS_XGRIDS, (HProperty *)lparam)) {
                m_UIDirty = m_UseXDirty = TRUE;
                if ((HProperty *)lparam == (HProperty *)m_UseX)
                    UpdateUI();
            }
            return TRUE;
        }
        default: ;
    }
    return FALSE;
}
