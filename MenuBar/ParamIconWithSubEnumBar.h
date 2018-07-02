#pragma once

#include "ParamIcon.h"
#include "SysDef.h"
#include "GlobalMsgDef.h"
#include "BlankWnd.h"
#include "EnumBar.h"
// CParamIconWithSubEnumBar

class CParamIconWithSubEnumBar : public CParamIcon
{
	DECLARE_DYNAMIC(CParamIconWithSubEnumBar)

public:
	CParamIconWithSubEnumBar(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon);
	virtual ~CParamIconWithSubEnumBar();
protected :
	CEnumBar *mpEnumBar ;
	int mCntSubEnumItem ;
	CSafeArray <STRUCT_ENUM_ITEM> mSubEnumItem ;
	CSafeArray <CString> mSubEnumItemTitle ;	// ·ÀÖ¹pIconÖÐ×Ö·û´®ÄÚ´æÊ§Ð§

public :
	BOOL SetupIcon(const STRUCT_PARAM_ICON * pDef);
	BOOL CreateSubEnumBar(int CntItem, const STRUCT_ENUM_ITEM * pEnumItem);
	int SetupSubEnumBar(int CntItem, const STRUCT_ENUM_ITEM * pItem) ;
protected:
	DECLARE_MESSAGE_MAP()
protected:
	void CallbackOnClicked(WPARAM CntSelItem, LPARAM pSelIDList);
	void ProcLButtonDown(UINT nFlags, CPoint point) ;
	void DrawIcon(CDC *pDC) ;
	void DrawParam(CDC *pDC);
	const WCHAR *FindEnumItemTitle(WORD id) ;
};


