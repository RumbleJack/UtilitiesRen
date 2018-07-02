#pragma once
#include "ParamIcon.h"

// CParamIconReadOnly

class CParamIconReadOnly : public CParamIcon
{
	DECLARE_DYNAMIC(CParamIconReadOnly)

public:
	CParamIconReadOnly(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon);
	virtual ~CParamIconReadOnly();

public :
	void DrawIcon(CDC *pDC) ;
protected:
	DECLARE_MESSAGE_MAP()
};


