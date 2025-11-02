// SpectrumGraph.cpp : implementation file
//

#include "StdAfx.h"
#include "SpectrumGraph.h"
//#include <math.h>
#include "MemoryDC.h"
#include "Macros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph

CFrequencyGraph::CFrequencyGraph() {
    m_nLength = 0;
    m_dArray = nullptr;
    m_nHighLevel = 79;
    m_nMediumLevel = 49;
    m_nMinValue = 0;
    m_nMaxValue = 256;
    m_clrLow = RGB(0, 0, 255);
    m_clrMedium = RGB(0, 255, 0);
    m_clrHigh = RGB(255, 0, 0);
}

CFrequencyGraph::~CFrequencyGraph() {
    delete[] m_dArray;
    m_nLength = 0;
}

BEGIN_MESSAGE_MAP(CFrequencyGraph, CWnd)
        //{{AFX_MSG_MAP(CFrequencyGraph)
        ON_WM_PAINT()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph message handlers
void CFrequencyGraph::OnPaint() {
    CRect rct;
    GetClientRect(&rct);
    //Needs to use CMemoryDC or else CMemDC...
    //using either class will get ride of the 
    //flicker problem that otherwise presents itself...
    //	CPaintDC dc(this);
    //	CMemDC dc(&paintdc,&rct);
    CPaintDC paintdc(this);
    CMemDC dc(&paintdc, &rct);
    dc.FillSolidRect(rct, GetSysColor(COLOR_BTNFACE));
    // graph
    if (m_nLength == 0)
        return;

    CRect stepRect;
    constexpr int nBars = 11;
    int pos = 0;
    const int xRight = (int)hash_math::ceil((float)rct.Width() / (float)nBars);
//    int nDiv = m_nLength / (nBars);
//    double *data = m_dArray;

    const float scalefactor = (float)rct.Height() / (m_nMaxValue + 1);
    for (WORD w = 0; w < nBars; ++w) {
        stepRect.top = rct.bottom;
        int tot = RoundValue(m_dArray[pos]);
        tot = RoundValue(scalefactor * tot);
        stepRect.left = rct.left + (xRight * (w + 1) - xRight) + 5;
        stepRect.right = xRight * (w + 1) - 5;
        stepRect.bottom = stepRect.top;
        stepRect.top = rct.bottom - tot;
        CBrush br1;
        if (tot > m_nHighLevel)
            br1.CreateSolidBrush(GetHighColor());
        else if (tot > m_nMediumLevel)
            br1.CreateSolidBrush(GetMediumColor());
        else
            br1.CreateSolidBrush(GetLowColor());

        dc.FillRect(&stepRect, &br1);

        stepRect.bottom = stepRect.top;
        stepRect.top = 0;
        pos++;
    }
}

void CFrequencyGraph::Repaint() {
    CRect rct;
    GetClientRect(&rct);
    CPaintDC paintdc(this);
    CMemDC dc(&paintdc, &rct);

    // graph
    if (m_nLength == 0)
        return;

    CRect stepRect;
    constexpr int nBars = 11;
    int pos = 0;
    const int xRight = (int)hash_math::ceil((float)rct.Width() / (float)nBars);
//    int nDiv = m_nLength / (nBars);
//    double *data = m_dArray;
    dc.FillSolidRect(rct, GetSysColor(COLOR_BTNFACE));

    const float scalefactor = (float)rct.Height() / (m_nMaxValue + 1);
    for (WORD w = 0; w < nBars; ++w) {
        stepRect.top = rct.bottom;
        int tot = RoundValue(m_dArray[pos]);
        tot = RoundValue(scalefactor * tot);
        stepRect.left = rct.left + (xRight * (w + 1) - xRight) + 5;
        stepRect.right = xRight * (w + 1) - 5;
        stepRect.bottom = stepRect.top;
        stepRect.top = rct.bottom - tot;
        CBrush br1;
        if (tot > m_nHighLevel)
            br1.CreateSolidBrush(GetHighColor());
        else if (tot > m_nMediumLevel)
            br1.CreateSolidBrush(GetMediumColor());
        else
            br1.CreateSolidBrush(GetLowColor());

        dc.FillRect(&stepRect, &br1);

        stepRect.bottom = stepRect.top;
        stepRect.top = 0;
        pos++;
    }
}

void CFrequencyGraph::Clear() {
    delete[] m_dArray;
    m_nLength = 0;
    m_dArray = nullptr;
    Invalidate(FALSE);
}

void CFrequencyGraph::Update(const int nNumber, const double *dArray) {
    if (m_nLength != nNumber) {
        m_nLength = nNumber;
        delete[] m_dArray;
        m_dArray = new double[m_nLength];
    }
    memcpy(m_dArray, dArray, nNumber * sizeof(double));
    Repaint();
    Invalidate(FALSE);
}
