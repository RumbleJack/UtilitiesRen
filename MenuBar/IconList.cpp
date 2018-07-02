#include "StdAfx.h"
#include "IconList.h"


CIconList::CIconList(CWnd *pParentWnd)
	: mpParentWnd(pParentWnd)
{
}


CIconList::~CIconList(void)
{
	DestroyAllIcons() ;
}


void CIconList::DestroyAllIcons(void)
{
	mIconList.DestroyAll() ;
}

BOOL CIconList::Reload(POINT PosMenu, SIZE IconSize, STRUCT_ICON *pParentIcon, int CntIcon, const STRUCT_ICON * pMenu, BOOL VertAlign)
{
	// 清空现有按键
	DestroyAllIcons() ;
	// 首个按键位置
	CRect IconPos(PosMenu, IconSize) ;
	// 下一按键横纵偏移量
	SIZE OffsetToNextIcon = {VertAlign ? 0 : IconSize.cx, VertAlign ? IconSize.cy : 0} ;

	// 初始化空按键
	CMenuIcon *pIcon = new CMenuIcon(mpParentWnd);

	// 如果存在上级按键，则加入按键列表
	if(pParentIcon != NULL && pParentIcon->id != ID_ICON_EMPTY)
	{
		if(pIcon->CreateIcon(pParentIcon, IconPos, HOT_ICON_BK_CLR))
		{
			mIconList.push_back(pIcon) ;
			IconPos.OffsetRect(OffsetToNextIcon) ;
		}
		else
			delete pIcon ;
	}
	// 将当前级别按键全部加入按键列表
	for(int i = 0 ; i < CntIcon ; ++i)
	{
		if(pIcon->CreateIcon(pMenu+i, IconPos, UNSELECTED_ICON_BK_CLR))
		{
			mIconList.push_back(pIcon) ;
			IconPos.OffsetRect(OffsetToNextIcon) ;
		}
		else
			delete pIcon ;
	}
	return 0;
}


void CIconList::ModifyIconBkClr(WORD ParentIcon, WORD HotIcon, COLORREF HotIconClr, COLORREF UnselectedIconClr)
{
	list <CMenuIcon *>::iterator Idx ;

	for(Idx = mIconList.begin() ; Idx != mIconList.end() ; Idx++)
	{
		if(*Idx != NULL)
		{
			if((*Idx)->id == ParentIcon || (*Idx)->id == HotIcon)
				(*Idx)->ModifyBkColor(HotIconClr) ;
			else
				(*Idx)->ModifyBkColor(UnselectedIconClr) ;
		}
	}

}
