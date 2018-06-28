#pragma once


// CBlankWnd

class  __declspec( dllexport ) CBlankWnd : public CWnd
{
	DECLARE_DYNAMIC(CBlankWnd)

public:
	CBlankWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled = TRUE, BOOL Framed = TRUE, BOOL Sizing = TRUE, BOOL Visiable = TRUE, int Brush = DKGRAY_BRUSH, LPCTSTR pCursor = IDC_ARROW);
	CBlankWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, COLORREF Brush, LPCTSTR pCursor = IDC_ARROW);
	CBlankWnd(CWnd *pParentWnd) ;
	BOOL CreateWnd(RECT Pos, BOOL Titled = TRUE, BOOL Framed = TRUE, BOOL Sizing = TRUE, BOOL Visiable = TRUE, int Brush = DKGRAY_BRUSH, LPCTSTR pCursor = IDC_ARROW) ;
	BOOL CreateWnd(RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, COLORREF Brush, LPCTSTR pCursor = IDC_ARROW) ;
	 ~CBlankWnd();
public :
	CWnd *mpParentWnd ;
	CRect mWndRect ;
protected :
	int mHorzPos;
	int mVertPos;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	BOOL RedrawBackgroundColor(CDC * pDC, COLORREF BkClr);
	void DrawCenteredTitle(CDC * pDC, COLORREF TextClr, const WCHAR * pTitle);
	void DrawCenteredTitle(CDC * pDC, RECT DrawPos, COLORREF TextClr, const WCHAR * pTitle) ;
	void Resize(RECT Pos);
};


