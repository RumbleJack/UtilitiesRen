// EnumItem.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "EnumItem.h"
#include "SysDef.h"

// CEnumItem

IMPLEMENT_DYNAMIC(CEnumItem, CBlankPopupWnd)

CEnumItem::CEnumItem(CWnd *pParentWnd, RECT WndPos, WORD id, const WCHAR *pTitle, BOOL Selected, COLORREF UnselectedBrush, COLORREF SelectedBrush)
: CBlankPopupWnd(pParentWnd, WndPos, FALSE, TRUE)
, mSelected(Selected)
, mUnselectedBrush(UnselectedBrush)
, mSelectedBrush(SelectedBrush)
, mTitle(pTitle)
, mID(id)
{

}

CEnumItem::~CEnumItem()
{
}


BEGIN_MESSAGE_MAP(CEnumItem, CBlankPopupWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CEnumItem 消息处理程序




void CEnumItem::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawCenteredTitle(&dc, ICON_TEXT_COLOR, mTitle) ;
}


void CEnumItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	mSelected = !mSelected ;

	if(mpParentWnd != NULL)
		mpParentWnd->PostMessageW(WM_CLICKED_MSG_TO_PARENT_WND, mSelected, (LPARAM)this) ;
	RedrawWindow() ;
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CEnumItem::OnEraseBkgnd(CDC* pDC)
{
	return RedrawBackgroundColor(pDC, mSelected ? mSelectedBrush : mUnselectedBrush) ;

	//return CBlankWnd::OnEraseBkgnd(pDC);
}
