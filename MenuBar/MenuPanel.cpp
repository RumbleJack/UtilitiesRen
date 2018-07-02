// MenuPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "MenuPanel.h"
#include "GlobalMsgDef.h"

// CMenuPanel

IMPLEMENT_DYNAMIC(CMenuPanel, CBlankWnd)

CMenuPanel::CMenuPanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, FALSE, FALSE, TRUE, WHITE_BRUSH)
, mParentIcon()
, mMenuBar(this)
, mIconRefSize(10, 10)
, mBarPos(Rect)
, mCntRootMenuIcon(0)
, mpRootMenu(NULL)
{
}

CMenuPanel::~CMenuPanel()
{
}


BEGIN_MESSAGE_MAP(CMenuPanel, CBlankWnd)
	ON_MESSAGE(WM_MENU_ITEM_CLICKED, &CMenuPanel::OnMenuItemClicked) 
END_MESSAGE_MAP()



// CMenuPanel 消息处理程序




BOOL CMenuPanel::LoadRootMenu(int CntIcon, const STRUCT_ICON * pRootMenu, int DefaultIconWidth, int DefaultIconHeight)
{
	// 为按键参考尺寸与一级菜单按键数、按键列表赋值
	mIconRefSize.cx = DefaultIconWidth ;
	mIconRefSize.cy = DefaultIconHeight ;
	if(CntIcon > 0 && pRootMenu != NULL)
	{
		mParentIcon.Reset() ;
		mCntRootMenuIcon = CntIcon ;
		mpRootMenu = pRootMenu ;
		// 计算合适的按键尺寸，并构建按键列表
		SIZE IconSize = FindIconSize(CntIcon, mIconRefSize.cx, mIconRefSize.cy) ; 
		POINT	BarPos = {0, 0} ;
		return mMenuBar.Reload(BarPos, IconSize, &mParentIcon, CntIcon, pRootMenu) ;
	}
	else
		return FALSE ;
}


void CMenuPanel::SetIconRefSize(int Width, int Height)
{
	mIconRefSize.cx = Width ;
	mIconRefSize.cy = Height ;
}


SIZE CMenuPanel::FindIconSize(int CntIcon, int DefaultWidth, int DefaultHeight)
{
	CSize IconSize(DefaultWidth, DefaultHeight) ;
	if(CntIcon <= 0)
		return IconSize ;
	if(mParentIcon.CheckDefined())
		++CntIcon ;

	if(mBarPos.Width() > mBarPos.Height())
		IconSize.cx = mBarPos.Width() / CntIcon ;
	else
		IconSize.cy = mBarPos.Height() / CntIcon ;

	if(IconSize.cx > DefaultWidth)
		IconSize.cx = DefaultWidth ;
	if(IconSize.cy > DefaultHeight)
		IconSize.cy = DefaultHeight ; // to limit icon size

	return IconSize ;
}

LRESULT CMenuPanel::OnMenuItemClicked(WPARAM wParam, LPARAM lParam)
{
	CMenuIcon *pHotIcon = (CMenuIcon *)lParam ;
	// 检查是否点击上级按键
	if(CheckBackMenuLevel(pHotIcon))
		LoadRootMenu(mCntRootMenuIcon, mpRootMenu, mIconRefSize.cx, mIconRefSize.cy) ;
	else
	{
		// 若点击子菜单项或该菜单无子菜单，则将消息继续发送到父窗口
		if(pHotIcon->CntSubMenu <= 0 || pHotIcon->pSubMenu == NULL)	// action
		{
			mMenuBar.ModifyIconBkClr(mParentIcon.id, pHotIcon->id, HOT_ICON_BK_CLR, UNSELECTED_ICON_BK_CLR) ;
			mpParentWnd->PostMessageW(WM_MENU_ITEM_CLICKED, pHotIcon->id, (LPARAM)pHotIcon) ;
		}
		else// 若点击非子菜单项，则将绘制子菜单
		{
			mParentIcon.Load(pHotIcon) ;
			SIZE IconSize = FindIconSize(pHotIcon->CntSubMenu, mIconRefSize.cx, mIconRefSize.cy) ;
			POINT	BarPos = {0, 0} ;
			return mMenuBar.Reload(BarPos, IconSize, &mParentIcon, pHotIcon->CntSubMenu, pHotIcon->pSubMenu) ;
		}
	}
	return 0 ;
}

