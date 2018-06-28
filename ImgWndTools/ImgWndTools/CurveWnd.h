#pragma once

#include "BlankWnd.h"
#include "DrawCurve.h"
#include "CoordinateAxis.h"

// CCurveWnd

class __declspec( dllexport ) CCurveWnd : public CDrawCurve, public CBlankWnd
{
	DECLARE_DYNAMIC(CCurveWnd)

public:
	CCurveWnd(CWnd *pParentWnd, RECT Pos, BOOL Titled = TRUE, BOOL Sizing = TRUE, BOOL Visiable = FALSE, BOOL AutoCoord = TRUE);
	virtual ~CCurveWnd();

protected :
	BOOL mAutoCoord ;
	float		mMinIdx ;
	float		mMaxIdx ;
	float		mMinVal ;
	float		mMaxVal ;

	CCoordinateAxis <int, int> mAxis ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


