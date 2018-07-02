// ImagePanel.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ImagePanel.h"


// CImagePanel

IMPLEMENT_DYNAMIC(CImagePanel, CBlankWnd)

CImagePanel::CImagePanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, TRUE, FALSE, TRUE, WHITE_BRUSH)
{

}

CImagePanel::~CImagePanel()
{
}


BEGIN_MESSAGE_MAP(CImagePanel, CBlankWnd)
END_MESSAGE_MAP()



// CImagePanel 消息处理程序


