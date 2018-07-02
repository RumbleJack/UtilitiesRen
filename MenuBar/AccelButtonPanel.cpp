// AccelButtonPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MenuBar.h"
#include "AccelButtonPanel.h"


// CAccelButtonPanel

IMPLEMENT_DYNAMIC(CAccelButtonPanel, CBlankWnd)

CAccelButtonPanel::CAccelButtonPanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, TRUE, FALSE, TRUE, WHITE_BRUSH)

{

}

CAccelButtonPanel::~CAccelButtonPanel()
{
}


BEGIN_MESSAGE_MAP(CAccelButtonPanel, CBlankWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CAccelButtonPanel ��Ϣ�������




void CAccelButtonPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	COLORREF OldClr = dc.SetTextColor(RGB(0, 0, 255)) ;
	int BkMode = dc.SetBkMode(TRANSPARENT) ;
	CString Note = _T("��ݼ���") ;
	RECT ClientRect ;
	GetClientRect(&ClientRect) ;
	dc.DrawText(Note, &ClientRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE) ;
}


int CAccelButtonPanel::AppendIcons(int CntIcon, STRUCT_ACCEL_ICON * pIcons)
{
	return 0;
}
