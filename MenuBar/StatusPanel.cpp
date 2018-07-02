// StatusPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "StatusPanel.h"


// CStatusPanel

IMPLEMENT_DYNAMIC(CStatusPanel, CBlankWnd)

CStatusPanel::CStatusPanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, TRUE, FALSE, TRUE, WHITE_BRUSH)

{

}

CStatusPanel::~CStatusPanel()
{
}


BEGIN_MESSAGE_MAP(CStatusPanel, CBlankWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStatusPanel 消息处理程序




void CStatusPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	COLORREF OldClr = dc.SetTextColor(RGB(0, 0, 255)) ;
	int BkMode = dc.SetBkMode(TRANSPARENT) ;
	CString Note = _T("状态图标区") ;
	RECT ClientRect ;
	GetClientRect(&ClientRect) ;
	dc.DrawText(Note, &ClientRect, DT_VCENTER | DT_CENTER) ;
}


BOOL CStatusPanel::ArrangStatusIcon(void)
{
	return 0;
}
