#include "StdAfx.h"
#include "MultiTexGrid.h"
#include "mlistctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl() {
    m_bDragging = FALSE;
    m_bOrderChanged = FALSE;
    m_pimageListDrag = nullptr;
    m_oldDNDStyle = NULL;
}

CMyListCtrl::~CMyListCtrl() = default;
/*
#ifndef ON_NOTIFY_REFLECT_T
#define WM_NOTIFY_T 0xBC4E
#define ON_NOTIFY_REFLECT_T(wNotifyCode, memberFxn) \
{ WM_NOTIFY_T, (WORD)(int)(wNotifyCode), 0, 0, AfxSigNotify_v, \
   (AFX_PMSG) \
   (static_cast<void (AFX_MSG_CALL CCmdTarget::*)(NMHDR*, LRESULT*) > \
   (memberFxn)) },
#endif
*/
BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
        //{{AFX_MSG_MAP(CMyListCtrl)
        ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CMyListCtrl::OnBeginDrag)
        ON_NOTIFY_REFLECT(LVN_BEGINRDRAG, &CMyListCtrl::OnBeginDrag)
        ON_WM_MOUSEMOVE()
        ON_WM_LBUTTONUP()
        ON_WM_RBUTTONUP()
        ON_WM_CONTEXTMENU()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void CMyListCtrl::OnBeginDrag(LPNMHDR pnmhdr, LRESULT * /*pResult*/) {
    CPoint ptItem, ptImage;
    NM_LISTVIEW *pnmListView = (NM_LISTVIEW *)pnmhdr;

    m_oldDNDStyle = GetExtendedStyle();
    if (m_oldDNDStyle != 0)
        SetExtendedStyle(0); // styles model original icon DND behavior

    ASSERT(!m_bDragging);
    m_bDragging = TRUE;
    m_iItemDrag = pnmListView->iItem;
    CPoint ptAction = pnmListView->ptAction;
    GetItemPosition(m_iItemDrag, &ptItem); // ptItem is relative to (0,0) and not the view origin
    GetOrigin(&m_ptOrigin);

    ASSERT(m_pimageListDrag == nullptr);
    m_pimageListDrag = CreateDragImage(m_iItemDrag, &ptImage);
    m_sizeDelta = ptAction - ptImage; // difference between cursor pos and image pos
    m_ptHotSpot = ptAction - ptItem + m_ptOrigin; // calculate hotspot for the cursor
    m_pimageListDrag->DragShowNolock(TRUE); // lock updates and show drag image
    m_pimageListDrag->SetDragCursorImage(0, CPoint(0, 0)); // define the hot spot for the new cursor image
    m_pimageListDrag->BeginDrag(0, CPoint(0, 0));
    ptAction -= m_sizeDelta;
    m_pimageListDrag->DragEnter(this, ptAction);
    m_pimageListDrag->DragMove(ptAction); // move image to overlap original icon
    m_iItemDrop = -1; // no drop target
    SetCapture();
}

void CMyListCtrl::OnMouseMove(const UINT nFlags, CPoint point) {
    int iItem;
    LV_ITEM lvitem;

    long lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    lStyle &= LVS_TYPEMASK; // drag will do different things in list and report mode
    if (m_bDragging) {
        ASSERT(m_pimageListDrag != nullptr);
        m_pimageListDrag->DragMove(point - m_sizeDelta); // move the image 
        if ((iItem = HitTest(point)) != -1) {
            lvitem.mask = LVIF_STATE;
            lvitem.stateMask = LVIS_DROPHILITED; // highlight the drop target
            if (m_iItemDrop != -1) // remove the drophighlighted from previous item
            {
                m_pimageListDrag->DragLeave(this);
                lvitem.iItem = m_iItemDrop;
                lvitem.iSubItem = 0;
                lvitem.state = 0; // sets drophighlighted to FALSE  

                SetItem(&lvitem);
            }

            m_iItemDrop = iItem;
            m_pimageListDrag->DragLeave(this); // unlock the window and hide drag image

            if (lStyle == LVS_REPORT || lStyle == LVS_LIST) {
                lvitem.iItem = iItem;
                lvitem.iSubItem = 0;
                lvitem.state = LVIS_DROPHILITED; // sets the drophighlighted

                SetItem(&lvitem);
                UpdateWindow();
            }
            point -= m_sizeDelta;
            m_pimageListDrag->DragEnter(this, point); // lock updates and show drag image
        }
    }
    CListCtrl::OnMouseMove(nFlags, point);
}

BOOL CMyListCtrl::MoveRow(const int from, const int to) {
    //Can't move to the same place, or from or to a negative index
    if (from == to || from < 0 || to < 0)
        return FALSE;

    //First Copy the row to the new location
    if (CopyRow(from, to)) {
        //If we have just inserted a row before
        //this one in the list, we need to increment
        //our index.
        if (from > to)
            DeleteItem(from + 1);
        else
            DeleteItem(from);

        return TRUE;
    }
    return FALSE;
}

BOOL CMyListCtrl::CopyRow(int from, const int to) {
    //Can't move to the same place, or from or to a negative index
    if (from == to || from < 0 || to < 0)
        return FALSE;

    //Copy the row to the new index
    InsertItem(to, GetItemText(from, 0));

    //If row has been inserted before original
    //increment the original
    if (from > to)
        from++;

    //Loop through subitems
    //	for(int i = 1; i < GetColumnCount(); ++i)
    for (int i = 1; i < 4; ++i) {
        SetItemText(to, i, GetItemText(from, i));
    }

    return TRUE;
}

void CMyListCtrl::OnButtonUp(CPoint point) {
    if (m_bDragging) // end of the drag operation
    {
//        CString cstr;

        const long lStyle = GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK;
        if (m_oldDNDStyle != 0)
            SetExtendedStyle(m_oldDNDStyle);
        m_bDragging = FALSE;
        ASSERT(m_pimageListDrag != nullptr);
        if (m_pimageListDrag) {
            m_pimageListDrag->DragLeave(this);

            SetItemState(m_iItemDrop, 0, LVIS_DROPHILITED); // remove the drophighlighted from last highlighted target

            m_pimageListDrag->EndDrag();
            delete m_pimageListDrag;
        }
        m_pimageListDrag = nullptr;

        // The drop target's sub-item text is replaced by the dragged item's
        // main text
        if (lStyle == LVS_REPORT && m_iItemDrop != m_iItemDrag) {
            MoveRow(m_iItemDrag, m_iItemDrop);
            m_bOrderChanged = TRUE;
        }
        ReleaseCapture();
    }
}

void CMyListCtrl::OnLButtonUp(const UINT nFlags, const CPoint point) {
    OnButtonUp(point);
    CListCtrl::OnLButtonUp(nFlags, point);
}

void CMyListCtrl::OnRButtonUp(const UINT nFlags, const CPoint point) {
    OnButtonUp(point);
    CListCtrl::OnRButtonUp(nFlags, point);
}

void CMyListCtrl::OnContextMenu(CWnd *pWnd, CPoint point) {
    if (point.x == -1 && point.y == -1) {
        // Keystroke invocation
        CRect rect;

        GetClientRect(rect);
        ClientToScreen(rect);

        point = rect.TopLeft();
        point.Offset(5, 5);
    }

    CMenu menu;
    VERIFY(menu.LoadMenu(IDR_MENU1));

    CMenu *pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != nullptr);
    CWnd *pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                           point.x,
                           point.y,
                           pWndPopupOwner);
}
