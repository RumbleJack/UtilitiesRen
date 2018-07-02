// LogoPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MenuBar.h"
#include "LogoPanel.h"
#include "GlobalMsgDef.h"

// CLogoPanel

IMPLEMENT_DYNAMIC(CLogoPanel, CBlankWnd)

CLogoPanel::CLogoPanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, TRUE, FALSE, TRUE, WHITE_BRUSH)
{

}

CLogoPanel::~CLogoPanel()
{
}


BEGIN_MESSAGE_MAP(CLogoPanel, CBlankWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CLogoPanel ��Ϣ�������




void CLogoPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawCenteredTitle(&dc, RGB(0, 0, 255), _T("LOGOͼƬ")) ;
}


void CLogoPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(mpParentWnd != NULL)
		mpParentWnd->PostMessageW(WM_MENU_EXIT) ;

	CBlankWnd::OnLButtonDblClk(nFlags, point);
}
