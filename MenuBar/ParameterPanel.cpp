// ParameterPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ParameterPanel.h"
#include "DataVsString.h"
#include "ParamIconWithSubEnumBar.h"
#include "ParamIconReadOnly.h"
#include "ParamEditIcon.h"

// CParameterPanel

IMPLEMENT_DYNAMIC(CParameterPanel, CBlankWnd)

CParameterPanel::CParameterPanel(CWnd *pParentWnd, RECT Rect)
: CBlankWnd(pParentWnd, Rect, FALSE, TRUE, FALSE, TRUE, WHITE_BRUSH)
, mIdxAppendBlock(0)
, mRect(Rect)
{
}

CParameterPanel::~CParameterPanel()
{
	Reset() ;
}


BEGIN_MESSAGE_MAP(CParameterPanel, CBlankWnd)
	ON_MESSAGE(WM_MENU_PARAM_MODIFIED, &CParameterPanel::OnParamModified)
END_MESSAGE_MAP()



// CParameterPanel 消息处理程序


void CParameterPanel::Reset(void)
{
	list <CParamIcon *>::iterator Idx ;
	for(Idx = mIcons.begin() ; Idx != mIcons.end(); Idx++)
	{
		if(*Idx != NULL)
			DESTROY_OBJECT(*Idx) ;
	}
	mIcons.clear() ;
	mIdxAppendBlock = 0 ;
}

POINT CParameterPanel::FindNewIconPos()
{
	return CPoint(mRect.left + mIdxAppendBlock * mIconSize.cx, mRect.top) ;
}


BOOL CParameterPanel::Append(int CntIcon, const STRUCT_PARAM_ICON * pIcon)
{
	for(int i = 0 ; i < CntIcon ; ++i)
		AppendIcon(pIcon+i) ;
	return TRUE ;
}

BOOL CParameterPanel::AppendIcon(const STRUCT_PARAM_ICON * pIconDef)
{
	if(pIconDef->Style == VERT_DIVIDED || pIconDef->Style == HORZ_DIVIDED)
	{
		return AppendSplitIcons(pIconDef->CntIcon_EnumItem, pIconDef->SubIcon_EnumItem.pSubIcon, pIconDef->Style == VERT_DIVIDED) ;
	}
	else
	{
		CRect	IconArea(FindNewIconPos(), mIconSize) ;
		++mIdxAppendBlock ;

		return AppendIcon(IconArea, pIconDef) ; 
	}
}

BOOL CParameterPanel::AppendIcon(RECT IconPos, const STRUCT_PARAM_ICON * pIconDef)
{
	CParamIcon *pNewIcon = NULL ;
	switch(pIconDef->Style)
	{
	case  CHECK_PARAM :
	case RADIO_PARAM :
		pNewIcon = new CParamIconWithSubEnumBar(this, IconPos, pIconDef) ;
		break ;
	case SHOW_PARAM_ONLY :
	case VERT_DIVIDED :
	case HORZ_DIVIDED :
		pNewIcon = new CParamIconReadOnly(this, IconPos, pIconDef) ;
		break ;
	case EDIT_PARAM :
		pNewIcon = new CParamEditIcon(this, IconPos, pIconDef) ;
		break ;
	default :
		pNewIcon = new CParamIcon(this, IconPos, pIconDef) ;
		break ;
	}

	if(pNewIcon != NULL)
		mIcons.push_back(pNewIcon) ;
	return TRUE ;
}

BOOL CParameterPanel::RemoveIcon(WORD IconID)
{
	int CntRemoved = 0 ;
	list <CParamIcon *>::iterator Idx ;
	for(Idx = mIcons.begin() ; Idx != mIcons.end(); Idx++)
	{
		if((*Idx)->CheckID(IconID))
		{
			DESTROY_OBJECT(*Idx) ;
			mIcons.erase(Idx) ;
			++CntRemoved ;
		}
	}
	return CntRemoved > 0 ;
}


BOOL CParameterPanel::CreateLine(int CntIcon)
{
	Reset() ;
	GetClientRect(&mRect) ;
	mIconSize.cx = mRect.Width() / CntIcon ;
	mIconSize.cy = mRect.Height() ;
	mIdxAppendBlock = 0 ;
	return TRUE ;
}

BOOL CParameterPanel::CreateLine(int CntIcon, const STRUCT_ACCEL_ICON * pIconList)
{
	if(CntIcon > 0 && pIconList != NULL)
	{
		CSafeArray <STRUCT_PARAM_ICON> mIconBuf(CntIcon) ;

		for(int i = 0 ; i < CntIcon ; ++i)
		{
			STRUCT_PARAM_ICON &ParamIcon = mIconBuf[i] ;
			ParamIcon.id = (pIconList+i)->id ;
			ParamIcon.Style = RADIO_PARAM ;
			ParamIcon.ParamType = ID_DEF ;
			ParamIcon.pTitle = (pIconList+i)->pTitle ;
			ParamIcon.BkBrush = BK_DEFAULT ;
			ParamIcon.CntIcon_EnumItem = (pIconList+i)->CntEnumItem ;
			ParamIcon.SubIcon_EnumItem.pEnumItem = (pIconList+i)->pEnumItem ;
		}
		return CParameterPanel::CreateLine(CntIcon, mIconBuf.GetPtrToArray()) ;
	}
	else
		return FALSE ;
}

BOOL CParameterPanel::CreateLine(int CntIcon, const STRUCT_PARAM_ICON * pIconList)
{
	CreateLine(CntIcon) ;
	for(int i = 0 ; i < CntIcon ; ++i)
	{
		if(!AppendIcon(pIconList+i))
			return FALSE ;
	}
	return TRUE ;
}


BOOL CParameterPanel::UpdateParameter(WORD id, UNION_DATA_TRANSFER val)
{
	CParamIcon *pIcon = FindIcon(id) ;
	if(pIcon != NULL)
	{
		pIcon->UpdateParameter(val) ;
		return TRUE ;
	}
	return FALSE ;
}

void CParameterPanel::ParamModifiedCallback(WORD ItemID,  CParamIconAttr *pItemAttr)
{
	UNION_DATA_TRANSFER Data ;
	pItemAttr->GetData(&Data) ;
	switch(pItemAttr->GetDataType())
	{
	case INT_DATA :
		mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, ItemID, (LPARAM)Data.IntData) ;
		break ;
	case FLOAT_DATA :
		mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, ItemID, (LPARAM)Data.FltData) ;
		break ;
	case ID_DEF :
		mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, ItemID, (LPARAM)Data.id) ;
		break ;
	case ENUM_GATE_IDX :
		mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, ItemID, (LPARAM)Data.IntData) ;
		break ;
	default :
		mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, ItemID, (LPARAM)Data.IntData) ;
	}
}

afx_msg LRESULT CParameterPanel::OnParamModified(WPARAM ItemID, LPARAM pItem)
{
	ParamModifiedCallback((WORD)ItemID, (CParamIconAttr *)pItem) ;

	return 0 ;
}

BOOL CParameterPanel::SetIconTitle(WORD IconID, const WCHAR * pTitle)
{
	CParamIcon *pIcon = FindIcon(IconID) ;
	if(pIcon != NULL)
	{
		pIcon->SetIconTitle(pTitle) ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CParameterPanel::SetIconTitle(CParamIconAttr * pIcon, const WCHAR * pTitle)
{
	if(pIcon != NULL)
	{
		pIcon->SetIconTitle(pTitle) ;
		return TRUE ;
	}
	return FALSE ;
}


BOOL CParameterPanel::UpdateParameter(CParamIconAttr * pIcon, UNION_DATA_TRANSFER val)
{
	return 0;
}


BOOL CParameterPanel::AppendSplitIcons(int CntIcon, const STRUCT_PARAM_ICON * pIconDef, BOOL VertAlign)
{
	CPoint IconPos = FindNewIconPos() ;
	++mIdxAppendBlock ;

	CSize IconSize = mIconSize ;
	CPoint OffsetIcon(0, 0) ;

	if(VertAlign)
		OffsetIcon.y = IconSize.cy /= CntIcon ;
	else
		OffsetIcon.x = IconSize.cx /= CntIcon ;
	CRect IconArea(IconPos, IconSize) ;
	BOOL RetState = TRUE ;
	for(int i = 0 ; i < CntIcon ; ++i)
	{
		if(!(RetState = AppendIcon(IconArea, pIconDef + i)))
			break ;
		IconArea.OffsetRect(OffsetIcon) ;
	}
	return RetState ;
}

BOOL CParameterPanel::SetIconTitleFont(WORD id, int FontSize, COLORREF FontClr, const WCHAR *pFont)
{
	CParamIcon *pIcon = FindIcon(id) ;
	return SetIconTitleFont(pIcon, FontSize, FontClr, pFont) ;
}

BOOL CParameterPanel::SetIconTitleFont(CParamIcon * pIcon, int FontSize, COLORREF FontClr, const WCHAR *pFont) 
{
	if(pIcon != NULL)
	{
		pIcon->SetTitleFont(FontSize, FontClr, pFont) ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CParameterPanel::SetIconParamFont(WORD id, int FontSize, COLORREF FontClr, const WCHAR *pFont)
{
	CParamIcon *pIcon = FindIcon(id) ;
	return SetIconParamFont(pIcon, FontSize, FontClr, pFont) ;
}

BOOL CParameterPanel::SetIconParamFont(CParamIcon * pIcon, int FontSize, COLORREF FontClr, const WCHAR *pFont)
{
	if(pIcon != NULL)
	{
		pIcon->SetParamFont(FontSize, FontClr, pFont) ;
		return TRUE ;
	}

	return FALSE ;
}

CParamIcon *CParameterPanel::FindIcon(WORD id)
{
	CParamIcon *pIcon = NULL ;
	list <CParamIcon *>::iterator Idx ;
	for(Idx = mIcons.begin() ; Idx != mIcons.end(); Idx++)
	{
		if((pIcon = *Idx)->CheckID(id))
			break ;
	}
	return pIcon ;
}