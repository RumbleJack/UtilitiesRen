#pragma once
#include "MenuDef.h"
#include "SafeArray.h"
#include "SysDef.h"
class CParamIconAttr
{
public:
	CParamIconAttr(const STRUCT_PARAM_ICON *pIcon);
	~CParamIconAttr(void);
protected :
	WORD	mID ;
	ENUM_PARAM_ICON_STYLE	mStyle ;
	//ENUM_BK_BRUSH_STYLE	mBkBrush ;
	ENUM_PARAM_TYPE		mParamType ;
	CString mTitle ;
	UNION_DATA_TRANSFER mValue ;
	CString mStrBuf ;
public:
	BOOL CheckID(WORD id)
	{
		return id == mID ;
	}

	int LoadData(const STRUCT_PARAM_ICON * pDef);
	int SetupSubEnumBar(int CntItem, const STRUCT_ENUM_ITEM * pItem);
	virtual BOOL UpdateParameter(UNION_DATA_TRANSFER val) ;

	LPCTSTR GateIdxToString(STRUCT_GATE_DEF val);
	void GetData(UNION_DATA_TRANSFER *pDataBuf)
	{
		memcpy(pDataBuf, &mValue, sizeof(UNION_DATA_TRANSFER)) ;
	}
	ENUM_PARAM_TYPE GetDataType()
	{
		return mParamType ;
	}
	CParamIconAttr *GetAttrPtr()
	{
		return this ;
	}
	void SetIconTitle(const WCHAR * pTitle);
};

