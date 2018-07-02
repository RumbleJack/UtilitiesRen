#pragma once
#include "BlankWnd.h"
#include "PubMacroDef.h"


// CLogoPanel

class DllExport CLogoPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CLogoPanel)

public:
	CLogoPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CLogoPanel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


