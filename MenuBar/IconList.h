#pragma once
#include "MenuIcon.h"
#include "BaseObjectList.h"
using namespace std ;

// 按键列表
class DllExport CIconList
{
public:
	CIconList(CWnd *pParentWnd = NULL);
	~CIconList(void);
public :
	// 按键列表
	CBaseObjectList <CMenuIcon *> mIconList ;
	// 父窗口
	CWnd *mpParentWnd ;
public :
	void SetParentWnd(CWnd *pWnd)
	{
		mpParentWnd = pWnd ;
	}
	void DestroyAllIcons(void);
	// 重新构建按键列表
	BOOL Reload(POINT PosMenu, SIZE IconSize, STRUCT_ICON *pParentIcon, int CntIcon, const STRUCT_ICON * pMenu, BOOL VertAlign = TRUE) ;
	// 为选中一级、二级菜单项指定背景色
	void ModifyIconBkClr(WORD ParentIcon, WORD HotIcon, COLORREF HotIconClr, COLORREF UnselectedIconClr);
};

