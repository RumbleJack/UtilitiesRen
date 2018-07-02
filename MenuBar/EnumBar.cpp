// EnumBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "EnumBar.h"
#include "SysDef.h"
#include "PubMacroDef.h"
// CEnumBar

IMPLEMENT_DYNAMIC(CEnumBar, CBlankPopupWnd)

CEnumBar::CEnumBar(CWnd *pParentWnd)
: CBlankPopupWnd(pParentWnd)
, mCntItem(0)
, mCntSelItem(0)

{

}

CEnumBar::~CEnumBar()
{
	mItemList.DestroyAll() ;
}


BEGIN_MESSAGE_MAP(CEnumBar, CBlankPopupWnd)
	ON_MESSAGE(WM_CLICKED_MSG_TO_PARENT_WND, &CEnumBar::OnItemClicked)
END_MESSAGE_MAP()



// CEnumBar 消息处理程序




int CEnumBar::Setup(POINT BarPos, SIZE ItemSize, int CntItem, const STRUCT_ENUM_ITEM * pItem, BOOL DownAlign, BOOL MultiSel)
{
	mCntItem = CntItem ;
	mMultiSel = MultiSel ;
	mCntSelItem = 0 ;
	mSelItemID.Create(mCntItem) ;

	CRect BarRect(BarPos.x, BarPos.y, BarPos.x+ItemSize.cx, BarPos.y+ItemSize.cy*mCntItem) ;
	CreateWnd(BarRect, FALSE, TRUE) ;

	CRect ItemRect(BarPos, ItemSize) ;
	int VertOffset = DownAlign ? ItemSize.cy : -ItemSize.cy ;

	for(int i = 0 ; i < mCntItem ; ++i)
	{
		CEnumItem *pItemBox = new CEnumItem(this, ItemRect, (pItem+i)->id, (pItem+i)->pTitle, FALSE, UNSELECTED_ICON_BK_CLR, HOT_ICON_BK_CLR) ;
		mItemList.push_back(pItemBox) ;
		ItemRect.OffsetRect(0, VertOffset) ;
	}
	return 0;
}


LRESULT CEnumBar::OnItemClicked(WPARAM wParam, LPARAM lParam)
{
	FindSelectedItem() ;
	mpParentWnd->PostMessageW(WM_MENU_ITEM_CLICKED, mCntSelItem, (LPARAM)mSelItemID.GetPtrToArray()) ;

	return 0;
}


int CEnumBar::FindSelectedItem(void)
{
	list <CEnumItem *>::iterator Idx = mItemList.begin() ;
	mCntSelItem = 0 ;
	while(Idx != mItemList.end())
	{
		if(*Idx != NULL && (*Idx)->IsSelected())
			mSelItemID[mCntSelItem++] = (*Idx)->GetID() ;
		Idx++ ;
	}
	return mCntSelItem ;
}

