#include "StdAfx.h"
#include "ParamIconAttr.h"


CParamIconAttr::CParamIconAttr(const STRUCT_PARAM_ICON *pIcon)
{
	LoadData(pIcon) ;
}


CParamIconAttr::~CParamIconAttr(void)
{
}


int CParamIconAttr::LoadData(const STRUCT_PARAM_ICON * pDef)
{
	mID = pDef->id ;
	mStyle = pDef->Style ;
	//mBkBrush = pDef->BkBrush ;
	mParamType = pDef->ParamType ;
	mTitle = pDef->pTitle ;
	mValue.IntData = 0 ;
	return 0;
}

BOOL CParamIconAttr::UpdateParameter(UNION_DATA_TRANSFER val)
{
	switch(mParamType)
	{
	case STR_PTR :
		mStrBuf = val.pStr ;
		mValue.pStr = mStrBuf.GetBuffer() ;
		break ;
	default :
		mValue = val ;
		break ;
	}	
	return TRUE ;
}

LPCTSTR CParamIconAttr::GateIdxToString(STRUCT_GATE_DEF val)
{
	mStrBuf = _T("") ;
	if(val.GATE_I)
		mStrBuf = _T("I") ;
	if(val.GATE_A)
		mStrBuf += _T("A") ;
	if(val.GATE_B)
		mStrBuf += _T("B") ;
	if(val.GATE_C)
		mStrBuf += _T("C") ;

	return mStrBuf ;
}


void CParamIconAttr::SetIconTitle(const WCHAR * pTitle)
{
	mTitle = pTitle ;
}
