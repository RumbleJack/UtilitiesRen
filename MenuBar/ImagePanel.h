#pragma once
#include "BlankWnd.h"
#include "PubMacroDef.h"

// CImagePanel

class DllExport CImagePanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CImagePanel)

public:
	CImagePanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CImagePanel();

protected:
	DECLARE_MESSAGE_MAP()
};


