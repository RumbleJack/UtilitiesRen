#pragma once


// CBlankPopupWnd

class __declspec( dllexport ) CBlankPopupWnd : public CWnd
{
	DECLARE_DYNAMIC(CBlankPopupWnd)

public:
	CBlankPopupWnd(CWnd *pParentWnd);
	CBlankPopupWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled = FALSE, BOOL Framed = TRUE, COLORREF Brush = RGB(255, 255, 255), LPCTSTR  pCursor = IDC_ARROW);
	 ~CBlankPopupWnd();

	BOOL CreateWnd(RECT Pos, BOOL Titled = FALSE, BOOL Framed = TRUE, int Brush = RGB(255, 255, 255), LPCTSTR pCursor = IDC_ARROW) ;
	BOOL RedrawBackgroundColor(CDC * pDC, COLORREF BkClr) ;
	void DrawCenteredTitle(CDC * pDC, COLORREF TextClr, const WCHAR * pTitle) ;
	void DrawCenteredTitle(CDC * pDC, RECT DrawPos, COLORREF TextClr, const WCHAR * pTitle) ;
public :
	CWnd *mpParentWnd ;
	CRect mWndRect ;

protected:
	DECLARE_MESSAGE_MAP()
public:
	void Resize(RECT Pos);
};


