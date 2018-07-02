#pragma once
#include "BlankWnd.h"
#include "MenuIcon.h"
#include "IconList.h"
#include "PubMacroDef.h"
#include "SysDef.h"

// CMenuPanel

class DllExport CMenuPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CMenuPanel)

public:
	CMenuPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CMenuPanel();
protected :
	// 上级基础按键
	CBaseIcon mParentIcon ;
	// 菜单栏按键列表
	CIconList mMenuBar ;
	// 单个按键参考尺寸
	CSize	  mIconRefSize ;
	// 菜单面板位置
	CRect	  mBarPos ;
	// 一级菜单按键数目及按键列表
	int	  mCntRootMenuIcon ;
	const STRUCT_ICON *mpRootMenu ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL LoadRootMenu(int CntIcon, const STRUCT_ICON * pRootMenu, int DefaultIconWidth, int DefaultIconHeight);
	// 该函数未使用
	void SetIconRefSize(int Width, int Height);
	// 计算合适的按键尺寸
	SIZE FindIconSize(int CntIcon, int DefaultWidth, int DefaultHeight);
	// 判断是否点击上一级菜单（用于返回上级菜单）
	BOOL CheckBackMenuLevel(STRUCT_ICON *pIcon)
	{
		return mParentIcon.id == pIcon->id ;
	}
	// 响应菜单按键单击发送的消息WM_MENU_ITEM_CLICKED，参数wParam为按键id，参数lParam为菜单按键指针
	afx_msg LRESULT OnMenuItemClicked(WPARAM wParam, LPARAM lParam);
};


