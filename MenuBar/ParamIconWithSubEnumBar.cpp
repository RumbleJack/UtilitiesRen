// ParamIconWithSubEnumBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ParamIconWithSubEnumBar.h"

// CParamIconWithSubEnumBar

IMPLEMENT_DYNAMIC(CParamIconWithSubEnumBar, CParamIcon)

CParamIconWithSubEnumBar::CParamIconWithSubEnumBar(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon)
: CParamIcon(pParentWnd, Pos, pIcon)
, mCntSubEnumItem(0)
, mpEnumBar(NULL)
{
	if(mStyle == CHECK_PARAM || mStyle == RADIO_PARAM)
		SetupSubEnumBar(pIcon->CntIcon_EnumItem, pIcon->SubIcon_EnumItem.pEnumItem) ;

}

CParamIconWithSubEnumBar::~CParamIconWithSubEnumBar()
{
	DESTROY_OBJECT(mpEnumBar) ;
}


BEGIN_MESSAGE_MAP(CParamIconWithSubEnumBar, CParamIcon)
END_MESSAGE_MAP()



// CParamIconWithSubEnumBar 消息处理程序



void CParamIconWithSubEnumBar::ProcLButtonDown(UINT nFlags, CPoint point)
{
	if(mStyle == CHECK_PARAM || mStyle == RADIO_PARAM)
	{
		if(mpEnumBar == NULL && mCntSubEnumItem > 0)
			CreateSubEnumBar(mCntSubEnumItem, mSubEnumItem.GetPtrToArray()) ;
		else
		{
			if(mpEnumBar != NULL)
				mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, mID, (LPARAM)GetAttrPtr()) ;
			DESTROY_OBJECT(mpEnumBar)
		}
	}

}

void CParamIconWithSubEnumBar::DrawIcon(CDC *pDC)
{
	DrawTitle(pDC) ;
	DrawParam(pDC) ;
}

const WCHAR * CParamIconWithSubEnumBar::FindEnumItemTitle(WORD id)
{
	for(int i = 0 ; i < mCntSubEnumItem ; ++i)
	{
		if(mSubEnumItem[i].id == id)
			return mSubEnumItem[i].pTitle ;
	}
	return NULL ;
}

void CParamIconWithSubEnumBar::DrawParam(CDC *pDC)
{
	CString ValStr ;
	switch(mParamType)
	{
	case ID_DEF :
		{
			const WCHAR *pTitle = FindEnumItemTitle(mValue.id) ;
			if(pTitle != NULL)
				ValStr = pTitle ;
		}
		break ;
	case ENUM_GATE_IDX :
		ValStr = GateIdxToString(mValue.GateIdx)  ;
		break ;
	}
	if(ValStr.GetLength() > 0)
		DrawSingleLineStr(pDC, GetParamRect(), ValStr, mDataFontClr, mDataFontSize, mDataFont.GetLength() > 0 ? mDataFont : NULL) ;
}

BOOL CParamIconWithSubEnumBar::CreateSubEnumBar(int CntItem, const STRUCT_ENUM_ITEM * pEnumItem)
{
	DESTROY_OBJECT(mpEnumBar) ;
	if(CntItem > 0 && pEnumItem != NULL)
	{
		mpEnumBar = new CEnumBar(this) ;
		CPoint BarPos(0, mWndRect.bottom) ;
		ClientToScreen(&BarPos) ;
		CSize ItemSize(WIDTH_POPUP_ENUM_ITEM, HEIGHT_POPUP_ENUM_ITEM) ;
		mpEnumBar->Setup(BarPos, ItemSize, CntItem, pEnumItem, TRUE, FALSE) ;
		return TRUE ;
	}
	else
		return FALSE ;
}

void CParamIconWithSubEnumBar::CallbackOnClicked(WPARAM CntSelItem, LPARAM pSelIDList)
{
	WORD *pIDList = (WORD *)pSelIDList ;
	switch(mStyle)
	{
	case  RADIO_PARAM :
		if(CntSelItem == 1)
		{
			mValue.id = *pIDList ;
			PostMessage(WM_LBUTTONDOWN) ;
		}
		break ;
	case CHECK_PARAM :
		{
			switch(mID)
			{
			case ID_PARAM_GATE_IDX :
				mValue.IntData = 0 ;
				for(int i = 0 ; i < (int)CntSelItem ; ++i)
				{
					switch(*(pIDList + i)) 
					{
					case ID_PARAM_GATE_I :
						mValue.GateIdx.GATE_I = 1 ;
						break ;
					case ID_PARAM_GATE_A :
						mValue.GateIdx.GATE_A = 1 ;
						break ;
					case ID_PARAM_GATE_B :
						mValue.GateIdx.GATE_B = 1 ;
						break ;
					case ID_PARAM_GATE_C :
						mValue.GateIdx.GATE_C = 1 ;
						break ;
					}
				}
				break ;
			}
		}
	}
	RedrawWindow() ;
}

int CParamIconWithSubEnumBar::SetupSubEnumBar(int CntItem, const STRUCT_ENUM_ITEM * pItem)
{
	if((mCntSubEnumItem = CntItem) > 0)
	{
		mSubEnumItem.Create(mCntSubEnumItem) ;
		mSubEnumItemTitle.Create(mCntSubEnumItem) ;
		for(int i = 0 ; i < mCntSubEnumItem ; ++i)
		{
			mSubEnumItemTitle[i] = (pItem+i)->pTitle ;
			mSubEnumItem[i].id = (pItem+i)->id ;
			mSubEnumItem[i].pTitle = (LPCTSTR)mSubEnumItemTitle[i] ;
		}
		return mCntSubEnumItem ;
	}
	else
		return 0;
}
