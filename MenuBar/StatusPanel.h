#pragma once
#include "BlankWnd.h"
#include "PubMacroDef.h"


// CStatusPanel

class DllExport CStatusPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CStatusPanel)

public:
	CStatusPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CStatusPanel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	BOOL ArrangStatusIcon(void);
};


