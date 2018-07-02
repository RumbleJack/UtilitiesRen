// AccelPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "AccelPanel.h"


// CAccelPanel

IMPLEMENT_DYNAMIC(CAccelPanel, CParameterPanel)

CAccelPanel::CAccelPanel(CWnd *pParentWnd, RECT Rect)
: CParameterPanel(pParentWnd, Rect)
{

}

CAccelPanel::~CAccelPanel()
{
}


BEGIN_MESSAGE_MAP(CAccelPanel, CParameterPanel)
END_MESSAGE_MAP()


BOOL CAccelPanel::CreateLine(int CntIcon, const STRUCT_ACCEL_ICON * pIconList)
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
// CAccelPanel 消息处理程序

void CAccelPanel::ParamModifiedCallback(WORD ItemID,  CParamIconAttr *pItemAttr)
{
	UNION_DATA_TRANSFER Data ;
	pItemAttr->GetData(&Data) ;
	mpParentWnd->PostMessageW(WM_MENU_ACCEL_KEY_CLICKED, ItemID, (LPARAM)Data.id) ;
}

