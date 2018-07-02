#pragma once
#include "ParameterPanel.h"

// CAccelPanel

class DllExport CAccelPanel : public CParameterPanel
{
	DECLARE_DYNAMIC(CAccelPanel)

public:
	CAccelPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CAccelPanel();

	BOOL CreateLine(int CntIcon, const STRUCT_ACCEL_ICON * pIconList) ;
protected:
	DECLARE_MESSAGE_MAP()
	void ParamModifiedCallback(WORD ItemID,  CParamIconAttr *pItemAttr);
};


