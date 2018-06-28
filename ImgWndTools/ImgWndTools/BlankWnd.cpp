// BlankWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "BlankWnd.h"


// CBlankWnd

IMPLEMENT_DYNAMIC(CBlankWnd, CWnd)

CBlankWnd::CBlankWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, int Brush, LPCTSTR  pCursor)
: CWnd()
, mHorzPos(0)
, mVertPos(0)
{
	mpParentWnd = pParentWnd ;
	CreateWnd(Pos, Titled, Framed, Sizing, Visiable, Brush, pCursor) ;
}

CBlankWnd::CBlankWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, COLORREF Brush, LPCTSTR  pCursor)
: CWnd()
, mHorzPos(0)
, mVertPos(0)
, mpParentWnd(pParentWnd)
{
	CreateWnd(Pos, Titled, Framed, Sizing, Visiable, Brush, pCursor) ;
}

CBlankWnd::CBlankWnd(CWnd *pParentWnd) 
	: CWnd()
	, mpParentWnd(pParentWnd)
{
}

BOOL CBlankWnd::CreateWnd(RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, int Brush, LPCTSTR pCursor)
{
	DWORD dwStyle = WS_CHILD ; //| WS_CLIPSIBLINGS ;
	if(Titled)
		dwStyle |= WS_CAPTION ;
	if(Framed)
		dwStyle |= WS_BORDER ;
	else
		dwStyle &= ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME) ;

	if(Sizing)
		dwStyle |=  WS_SIZEBOX ;
	if(Visiable)
		dwStyle |=  WS_VISIBLE ;
	mWndRect = Pos ;
	return CreateEx(Framed ? WS_EX_WINDOWEDGE/*WS_EX_OVERLAPPEDWINDOW*/ : WS_EX_TRANSPARENT, 
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, 
		::LoadCursor(NULL, pCursor),(HBRUSH) ::GetStockObject(Brush)),
	  NULL,  dwStyle, Pos, mpParentWnd, 0);
	//ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_FRAMECHANGED);  
	//return TRUE ;
}

BOOL CBlankWnd::CreateWnd(RECT Pos, BOOL Titled, BOOL Framed, BOOL Sizing, BOOL Visiable, COLORREF Brush, LPCTSTR pCursor)
{
	DWORD dwStyle = WS_CHILD ; //| WS_CLIPSIBLINGS ;
	if(Titled)
		dwStyle |= WS_CAPTION ;
	if(Framed)
		dwStyle |= WS_BORDER ;
	else
		dwStyle &= ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME) ;

	if(Sizing)
		dwStyle |=  WS_SIZEBOX ;
	if(Visiable)
		dwStyle |=  WS_VISIBLE ;
	mWndRect = Pos ;

	CBrush BkBrush(Brush) ;

	return CreateEx(Framed ? WS_EX_WINDOWEDGE/*WS_EX_OVERLAPPEDWINDOW*/ : WS_EX_TRANSPARENT, 
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, 
		::LoadCursor(NULL, pCursor),(HBRUSH)BkBrush),
	  NULL,  dwStyle, Pos, mpParentWnd, 0);
	//ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_FRAMECHANGED);  
	//return TRUE ;
}
CBlankWnd::~CBlankWnd()
{
	if(m_hWnd != NULL)
		DestroyWindow() ;
}


BEGIN_MESSAGE_MAP(CBlankWnd, CWnd)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// CBlankWnd 消息处理程序



void CBlankWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
	int maxpos;
	GetScrollRange(SB_HORZ, &minpos, &maxpos); 

    // Determine the new position of scroll box.
    switch (nSBCode)
    {
    case SB_LEFT:      // Scroll to far left.
	   mHorzPos = minpos;
	   break;

    case SB_RIGHT:      // Scroll to far right.
 	   mHorzPos = maxpos;
	   break;

    case SB_ENDSCROLL:   // End scroll.
	   break;

    case SB_LINELEFT:      // Scroll left.
	   if (mHorzPos > minpos)
	 	  mHorzPos--;
	   break;

    case SB_LINERIGHT:   // Scroll right.
	   if (mHorzPos < maxpos-1)
		  mHorzPos++;
	   break;

    case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
       mHorzPos = nPos;      // of the scroll box at the end of the drag operation.
       break;

    case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
       mHorzPos = nPos;     // position that the scroll box has been dragged to.
       break;
    }

   // Set the new position of the thumb (scroll box).
    SetScrollPos(SB_HORZ, mHorzPos);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW) ;
}

void CBlankWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
	int maxpos;
	GetScrollRange(SB_VERT, &minpos, &maxpos); 

    // Determine the new position of scroll box.
    switch (nSBCode)
    {
    case SB_LEFT:      // Scroll to far left.
	   mVertPos = minpos;
	   break;

    case SB_RIGHT:      // Scroll to far right.
 	   mVertPos = maxpos;
	   break;

    case SB_ENDSCROLL:   // End scroll.
	   break;

    case SB_LINELEFT:      // Scroll left.
	   if (mVertPos > minpos)
	 	  mVertPos--;
	   break;

    case SB_LINERIGHT:   // Scroll right.
	   if (mVertPos < maxpos-1)
		  mVertPos++;
	   break;

    case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
       mVertPos = nPos;      // of the scroll box at the end of the drag operation.
       break;

    case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
       mVertPos = nPos;     // position that the scroll box has been dragged to.
       break;
    }

   // Set the new position of the thumb (scroll box).
    SetScrollPos(SB_VERT, mVertPos);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW) ;
}


BOOL CBlankWnd::RedrawBackgroundColor(CDC * pDC, COLORREF BkClr)
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


//void CBlankWnd::DrawCenteredTitle(CDC * pDC, COLORREF TextClr, const WCHAR * pTitle)
//{
//	COLORREF OldClr = pDC->SetTextColor(TextClr) ;
//	int BkMode = pDC->SetBkMode(TRANSPARENT) ;
//	CString Note = pTitle ;
//	RECT ClientRect ;
//	GetClientRect(&ClientRect) ;
//	pDC->DrawText(Note, &ClientRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE) ;
//}
//
void CBlankWnd::DrawCenteredTitle(CDC * pDC, COLORREF TextClr, const WCHAR * pTitle)
{
	RECT ClientRect ;
	GetClientRect(&ClientRect) ;
	DrawCenteredTitle(pDC, ClientRect, TextClr, pTitle) ;
}

void CBlankWnd::DrawCenteredTitle(CDC * pDC, RECT DrawPos, COLORREF TextClr, const WCHAR * pTitle)
{
	COLORREF OldClr = pDC->SetTextColor(TextClr) ;
	int BkMode = pDC->SetBkMode(TRANSPARENT) ;

	CString Note = pTitle ;
	pDC->DrawText(pTitle, wcslen(pTitle), &DrawPos, DT_VCENTER | DT_CENTER | DT_SINGLELINE) ;

	pDC->SetBkMode(BkMode) ;
	pDC->SetTextColor(OldClr) ;

}



void CBlankWnd::Resize(RECT Pos)
{
	mWndRect = Pos ;
	MoveWindow(&Pos) ;
}
