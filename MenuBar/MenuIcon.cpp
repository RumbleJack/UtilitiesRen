// MenuIcon.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "MenuIcon.h"


// CMenuIcon

IMPLEMENT_DYNAMIC(CMenuIcon, CBlankWnd)

CMenuIcon::CMenuIcon(CWnd *pParentWnd)
: CBlankWnd(pParentWnd)
, mBkClr(RGB(255, 255, 255))
{
}

CMenuIcon::~CMenuIcon()
{
}


BEGIN_MESSAGE_MAP(CMenuIcon, CBlankWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMenuIcon 消息处理程序




void CMenuIcon::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 将消息发送到父窗口
	mpParentWnd->PostMessageW(WM_MENU_ITEM_CLICKED, id, (LPARAM)this) ;
	CBlankWnd::OnLButtonDown(nFlags, point);
}


BOOL CMenuIcon::CreateIcon(const STRUCT_ICON * pIconDef, RECT Pos, COLORREF BkClr, BOOL Visible)
{
	mBkClr = BkClr ;
	Load(pIconDef) ;
	// 这里创建窗口的同时，应当就会显示，不需要额外的绘制代码
	return CreateWnd(Pos, FALSE, TRUE, FALSE, Visible, BkClr) ;
}


void CMenuIcon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	ShowIcon(&dc) ;
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
}


void CMenuIcon::ShowIcon(CDC * pDC)
{
	if(pTitle != NULL)
	{
		DrawCenteredTitle(pDC, ICON_TEXT_COLOR, pTitle) ;
	}
}


void CMenuIcon::ModifyBkColor(COLORREF BkClr)
{
	mBkClr = BkClr ;
	// RedrawWindow()应该会发出消息，最终调用OnEraseBkgnd()
	RedrawWindow() ;
}


BOOL CMenuIcon::OnEraseBkgnd(CDC* pDC)
{
	return RedrawBackgroundColor(pDC, mBkClr) ;
}
