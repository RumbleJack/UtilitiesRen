// MenuIcon.cpp : ʵ���ļ�
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



// CMenuIcon ��Ϣ�������




void CMenuIcon::OnLButtonDown(UINT nFlags, CPoint point)
{
	// ����Ϣ���͵�������
	mpParentWnd->PostMessageW(WM_MENU_ITEM_CLICKED, id, (LPARAM)this) ;
	CBlankWnd::OnLButtonDown(nFlags, point);
}


BOOL CMenuIcon::CreateIcon(const STRUCT_ICON * pIconDef, RECT Pos, COLORREF BkClr, BOOL Visible)
{
	mBkClr = BkClr ;
	Load(pIconDef) ;
	// ���ﴴ�����ڵ�ͬʱ��Ӧ���ͻ���ʾ������Ҫ����Ļ��ƴ���
	return CreateWnd(Pos, FALSE, TRUE, FALSE, Visible, BkClr) ;
}


void CMenuIcon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	ShowIcon(&dc) ;
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� __super::OnPaint()
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
	// RedrawWindow()Ӧ�ûᷢ����Ϣ�����յ���OnEraseBkgnd()
	RedrawWindow() ;
}


BOOL CMenuIcon::OnEraseBkgnd(CDC* pDC)
{
	return RedrawBackgroundColor(pDC, mBkClr) ;
}
