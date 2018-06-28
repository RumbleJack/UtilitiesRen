#pragma once
#include "CoordinateAxis.h"

template <class T_XData, class T_YData>
class CDrawCurve : virtual public CCoordinateAxis <T_XData, T_YData>
{
public:
	CDrawCurve()
		: CCoordinateAxis <T_XData, T_YData> ()
	{
	}

	~CDrawCurve(void)
	{
	}

public :
	typedef enum
	{
		CURVE,
		BAR
	} ENUM_CURVE_DRAW_STYLE ;
	
protected :
	ENUM_CURVE_DRAW_STYLE mCurveStyle ;
	COLORREF	mCurveColor ;
	int					mCurveWidth ;
	int					mLineStyle ;

protected :
	void DrawLine(CDC *pDC, int prevXPos, int prevYPos, int nextXPos, int nextYPos)
	{
		if(GetLineSegmentWithinDrawRange(prevXPos, prevYPos, nextXPos, nextYPos))
		{
			pDC->MoveTo(prevXPos, prevYPos) ;
			pDC->LineTo(nextXPos, nextYPos) ;
		}
	}

	BOOL GetLineSegmentWithinDrawRange(int &prevXPos, int &prevYPos, int &nextXPos, int &nextYPos)
	{
		FLOAT_POINT end1 = {(double)prevXPos, (double)prevYPos} ;
		FLOAT_POINT end2 = {(double)nextXPos, (double)nextYPos} ;
		FLOAT_POINT crossPt[2] ;
		if(mDrawRange.IntersectLine(crossPt, end1, end2) == 2)
		{
			prevXPos = ROUNDING(crossPt[0].x) ;
			prevYPos = ROUNDING(crossPt[0].y) ;
			nextXPos = ROUNDING(crossPt[1].x) ;
			nextYPos = ROUNDING(crossPt[1].y) ;
			return TRUE ;
		}
		else
			return FALSE ;
	}

	void DrawOnly(CDC *pDC, int SizeArray, T_XData *pX, T_YData *pY)
	{
		if(mCurveStyle == BAR)
			DrawBarOnly(pDC, SizeArray, pX, pY) ;
		else if(mCurveStyle == CURVE)
			DrawCurveOnly(pDC, SizeArray, pX, pY) ;
	}

	void DrawBarOnly(CDC *pDC, int SizeArray, T_XData *pX, T_YData *pY)
	{
		for(int i = 0 ; i < SizeArray ; ++i)
		{
			if(*(pX + i) >= mMinX && *(pX + i) < mMaxX)
			{
				int xPos = XValueToDrawPos(*(pX + i)) ;
				int yPos = YValueToDrawPos(*(pY + i)) ;
				if(yPos < mDrawRange.top)
					yPos = ROUNDING(mDrawRange.top) ;
				if(yPos >= mDrawRange.bottom)
					yPos = ROUNDING(mDrawRange.bottom) ;
				pDC->MoveTo(xPos, mOriginPos.y) ;
				pDC->LineTo(xPos, yPos) ;
			}
		}
	}

	void DrawCurveOnly(CDC *pDC, int SizeArray, T_XData *pX, T_YData *pY)
	{
		int nextXPos = XValueToDrawPos(*pX) ;
		int nextYPos = YValueToDrawPos(*pY) ;
		for(int i = 1 ; i < SizeArray ; ++i)
		{
			int prevXPos = nextXPos ;
			int prevYPos = nextYPos ;
			nextXPos = XValueToDrawPos(*(pX + i)) ;
			nextYPos = YValueToDrawPos(*(pY + i)) ;
			DrawLine(pDC, prevXPos, prevYPos, nextXPos, nextYPos) ;
		}
	}

public :
	void SetCurveStyle(ENUM_CURVE_DRAW_STYLE Style, COLORREF Clr, int Width, int LineStyle)
	{
		mCurveStyle = Style ;
		mCurveColor = Clr ;
		mCurveWidth = Width ;
		mLineStyle = LineStyle ;
	}


	void DrawCurve(CDC *pDC, int SizeArray, T_XData *pX, T_YData *pY)
	{
		CPen Pen(mLineStyle, mCurveWidth, mCurveColor) ;
		CPen *pOldPen = pDC->SelectObject(&Pen) ;
		int	Rop = pDC->SetROP2(R2_COPYPEN) ;

		DrawBarOnly(pDC, SizeArray, pX, pY) ;

		pDC->SelectObject(pOldPen) ;
		pDC->SetROP2(Rop) ;
	}


};
