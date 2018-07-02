// ParamEditIcon.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ParamEditIcon.h"
#include "DataVsString.h"
#include "StringFunc.h"
#include "GlobalMsgDef.h"
// CParamEditIcon

IMPLEMENT_DYNAMIC(CParamEditIcon, CParamIcon)
CParamEditIcon::CParamEditIcon(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon)
: CParamIcon(pParentWnd, Pos, pIcon)
{
	ArrangePosition() ;
	DWORD Style = ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER ;
	mEditBox.Create(Style , mEditBoxPos, this, 1) ;
	mEditBox.SetFont(PARAM_ICON_EDIT_DATA_COLOR, PARAM_ICON_EDIT_BK_COLOR, PARAM_ICON_PARAM_CHAR_SIZE, PARAM_ICON_FONT) ;
	mEditBox.SetDataType(CEditForDataInput::FLOAT_DATA) ;
	mEditBox.SetInitDataValue(0.0f) ;
}

CParamEditIcon::~CParamEditIcon()
{
}

void CParamEditIcon::ArrangePosition()
{
	mTitlePos = GetTitlePos() ;
	mEditBoxPos = GetParamRect() ;
	int FrameSize = (mEditBoxPos.Height() - PARAM_ICON_PARAM_CHAR_SIZE - 2) / 2 ;
	mEditBoxPos.top += FrameSize ;
	mEditBoxPos.bottom -= FrameSize ;
}

BEGIN_MESSAGE_MAP(CParamEditIcon, CParamIcon)
END_MESSAGE_MAP()

void CParamEditIcon::DrawIcon(CDC *pDC)
{
	DrawTitle(pDC) ;
	//if(mTitle.GetLength() > 0)
	//{
	//	DrawCenteredTitle(pDC, mTitlePos, ICON_TEXT_COLOR, mTitle) ;
	//}
	//CString ValStr ;
	//CDataVsString mTool ;
	//switch(mParamType)
	//{
	//case INT_DATA :
	//	ValStr = mTool.IntToString(mValue.IntData) ;
	//	break ;
	//case FLOAT_DATA :
	//	ValStr = mTool.FloatToString(mValue.FltData, FLOAT_PRECISION) ;
	//	break ;
	//}
	//mEditBox.SetWindowTextW(ValStr) ;
}

void CParamEditIcon::ProcLButtonDown(UINT nFlags, CPoint point)
{
#define MAX_DIGIT_BIT 7
	WCHAR StrBuf[MAX_DIGIT_BIT] ;
	int CntRead = mEditBox.GetWindowTextW(StrBuf, MAX_DIGIT_BIT) ;
	switch(mParamType)
	{
	case INT_DATA :
		CStringFunc::GetDecIntFromString(StrBuf, &mValue.IntData, MAX_DIGIT_BIT) ;
		break ;
	case FLOAT_DATA :
		CStringFunc::GetFloatFromString(StrBuf, &mValue.FltData,MAX_DIGIT_BIT) ;
		break ;
	}
	mpParentWnd->PostMessageW(WM_MENU_PARAM_MODIFIED, mID, (LPARAM)GetAttrPtr()) ;
}



