#pragma once
#include "ParamIcon.h"
#include "EditForDataInput.h"
// CParamEditIcon

class CParamEditIcon : public CParamIcon
{
	DECLARE_DYNAMIC(CParamEditIcon)

public:
	CParamEditIcon(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon);
	virtual ~CParamEditIcon();
protected :
	CRect	mTitlePos ;
	CRect	mEditBoxPos ;
	CEditForDataInput  mEditBox ;

	void ArrangePosition() ;
public :
	void DrawIcon(CDC *pDC) ;
	void ProcLButtonDown(UINT nFlags, CPoint point);
protected:
	DECLARE_MESSAGE_MAP()
};


