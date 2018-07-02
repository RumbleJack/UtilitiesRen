#pragma once
#include "BlankWnd.h"
#include "PubMacroDef.h"
#include "SysDef.h"
#include "MenuDef.h"
#include "ParamIconWithSubEnumBar.h"
// CAccelButtonPanel

class DllExport CAccelButtonPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CAccelButtonPanel)

public:
	CAccelButtonPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CAccelButtonPanel();
protected :
	list <CParamIconWithSubEnumBar *> mIcons ;
	CRect	mRect ;
	CSize	mIconSize ;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int AppendIcons(int CntIcon, STRUCT_ACCEL_ICON * pIcons);
};


