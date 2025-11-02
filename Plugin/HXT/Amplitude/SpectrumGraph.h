#if !defined(AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_)
#define AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumGraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph window

class CFrequencyGraph final : public CWnd {
    // Construction
public:
    CFrequencyGraph();
    ~CFrequencyGraph() override;
    void Clear();
    void Repaint();

    //   void Test1();

    [[nodiscard]] COLORREF GetLowColor() const {
        return m_clrLow;
    }

    [[nodiscard]] COLORREF GetMediumColor() const {
        return m_clrMedium;
    }

    [[nodiscard]] COLORREF GetHighColor() const {
        return m_clrHigh;
    }

    [[nodiscard]] int GetMediumLevel() const {
        return m_nMediumLevel;
    }

    [[nodiscard]] int GetHighLevel() const {
        return m_nHighLevel;
    }

    void SetYRange(const int nMin, const int nMax) {
        m_nMinValue = nMin;
        m_nMaxValue = nMax;
    }

    void Update(int nNumber, const double *dArray); //Takes Intensity after FFT is performed on Wave Data

protected:
    int m_nLength;
    double *m_dArray;
    int m_nMinValue;
    int m_nMaxValue;
    int m_nHighLevel;
    int m_nMediumLevel;
    COLORREF m_clrLow;
    COLORREF m_clrMedium;
    COLORREF m_clrHigh;

    // Generated message map functions
    //{{AFX_MSG(CFrequencyGraph)
    afx_msg void OnPaint();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_)
