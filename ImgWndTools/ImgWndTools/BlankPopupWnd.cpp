// BlankPopupWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "BlankPopupWnd.h"


// CBlankPopupWnd

IMPLEMENT_DYNAMIC(CBlankPopupWnd, CWnd)

CBlankPopupWnd::CBlankPopupWnd(CWnd *pParentWnd)
	: CWnd()
	, mpParentWnd(pParentWnd)
{

}

CBlankPopupWnd::CBlankPopupWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled, BOOL Framed, COLORREF Brush, LPCTSTR  pCursor)
	: CWnd()
	, mpParentWnd(pParentWnd)
	, mWndRect(Pos)
{
	CreateWnd(Pos, Titled, Framed, Brush, pCursor) ;
}

CBlankPopupWnd::~CBlankPopupWnd()
{
	if(m_hWnd != NULL)
		DestroyWindow() ;
}

BOOL CBlankPopupWnd::CreateWnd(RECT Pos, BOOL Titled, BOOL Framed, int Brush, LPCTSTR pCursor)
{
	DWORD dwStyle = WS_POPUP ;
	if(Titled)
		dwStyle |= WS_CAPTION ;
	if(Framed)
		dwStyle |= WS_BORDER ;
	else
		dwStyle &= ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME) ;
	dwStyle |=  WS_VISIBLE ;
	mWndRect = Pos ;
	CBrush BkBrush(Brush) ;

	return CreateEx(Framed ? WS_EX_WINDOWEDGE : WS_EX_TRANSPARENT, 
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, 
		::LoadCursor(NULL, pCursor),(HBRUSH)BkBrush),
			  NULL,  dwStyle, Pos, mpParentWnd, 0);


}

BEGIN_MESSAGE_MAP(CBlankPopupWnd, CWnd)
END_MESSAGE_MAP()



// CBlankPopupWnd 消息处理程序
BOOL CBlankPopupWnd::RedrawBackgroundColor(CDC * pDC, COLORREF BkClr)
{
	CBrush BkBrush(BkClr) ;
	CBrush* pOldBrush = pDC->SelectObject(&BkBrush) ;
	CRect rect;
	pDC->GetClipBox(&rect);

	//画需要的区域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE ;
}

void CBlankPopupWnd::DrawCenteredTitle(CDC * pDC, COLORREF TextClr, const WCHAR * pTitle)
{
	RECT ClientRect ;
	GetClientRect(&ClientRect) ;
	DrawCenteredTitle(pDC, ClientRect, TextClr, pTitle) ;
}

void CBlankPopupWnd::DrawCenteredTitle(CDC * pDC, RECT DrawPos, COLORREF TextClr, const WCHAR * pTitle)
{
	COLORREF OldClr = pDC->SetTextColor(TextClr) ;
	int BkMode = pDC->SetBkMode(TRANSPARENT) ;
	CString Note = pTitle ;
	pDC->DrawText(Note, &DrawPos, DT_VCENTER | DT_CENTER | DT_SINGLELINE) ;
}



void CBlankPopupWnd::Resize(RECT Pos)
{
	mWndRect = Pos ;
	MoveWindow(&Pos) ;
}
