#pragma once
#include "BlankPopupWnd.h"
#include "EnumItem.h"
#include "BaseObjectList.h"
#include "MenuDef.h"
#include "GlobalMsgDef.h"
#include "SafeArray.h"
// CEnumBar
class DllExport CEnumBar : public CBlankPopupWnd
{
	DECLARE_DYNAMIC(CEnumBar)

public:
	CEnumBar(CWnd *pParentWnd);
	virtual ~CEnumBar();
protected :
	int	mCntItem ;
	BOOL mMultiSel ;
	CBaseObjectList <CEnumItem *> mItemList ;
	int		mCntSelItem ;
	CSafeArray <WORD> mSelItemID ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	int Setup(POINT BarPos, SIZE ItemSize, int CntItem, const STRUCT_ENUM_ITEM * pItem, BOOL DownAlign = TRUE, BOOL MultiSel = TRUE);
	afx_msg LRESULT OnItemClicked(WPARAM wParam, LPARAM lParam);
	int FindSelectedItem(void);
};


