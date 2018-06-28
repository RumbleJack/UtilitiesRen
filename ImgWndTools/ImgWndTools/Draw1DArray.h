#pragma once
#include "drawcurve.h"
template <class T_Value>
class DllExport CDraw1DArray :
	virtual public CDrawCurve <T_Value, int>
{
public:
	CDraw1DArray(void)
		: CDrawCurve <T_Value, int> ()
	{
	}

	~CDraw1DArray(void)
	{
	}

	void DrawArrayBarOnly(CDC *pDC, int SizeArray, T_Value *pY)
	{
		for(int i = max(0, mMinX) ; i < min(SizeArray, mMaxX) ; ++i)
			DrawLine(pDC, i, (T_Value)0,i, *(pY + i)) ;
	}

	void DrawPieceCurve(CDC *pDC, int x0, T_Value y0, int x1, T_Value y1)
	{
		DrawLine(pDC, XValueToDrawPos(x0), YValueToDrawPos(y0), XValueToDrawPos(x1), YValueToDrawPos(y1)) ;
	}

	void DrawPieceCurveWithPenStyle(CDC *pDC, int x0, T_Value y0, int x1, T_Value y1, int style, int width, COLORREF clr)
	{
			CPen Pen(style, width, clr) ;
			CPen *pOldPen = pDC->SelectObject(&Pen) ;
			int	Rop = pDC->SetROP2(R2_COPYPEN) ;
			DrawPieceCurve(pDC, x0, y0, x1, y1) ;
			pDC->SelectObject(pOldPen) ;
			pDC->SetROP2(Rop) ;
	}

	void DrawProgressBar(CDC *pDC, int idxBegin, int idxEnd) 
	{
			CPen Pen(PS_SOLID, mProgressBarWidth, mProgressBarColor) ;
			CPen *pOldPen = pDC->SelectObject(&Pen) ;
			int	Rop = pDC->SetROP2(R2_COPYPEN) ;
			DrawLine(pDC, XValueToDrawPos(idxBegin), mOriginPos.y, XValueToDrawPos(idxEnd), mOriginPos.y) ;
			pDC->SelectObject(pOldPen) ;
			pDC->SetROP2(Rop) ;
	}

	void DrawArrayCurveOnly(CDC *pDC, int SizeArray, T_Value *pY)
	{
		for(int i = max(0, mMinX) + 1 ; i < min(SizeArray, mMaxX) ; ++i)
			DrawPieceCurve(pDC, i-1, *(pY+i-1), i, *(pY+i)) ;
	}

	void DrawArrayOnly(CDC *pDC, int SizeArray, T_Value *pY)
	{
		if(mCurveStyle == BAR)
			DrawArrayBarOnly(pDC, SizeArray, pY) ;
		else if(mCurveStyle == CURVE)
			DrawArrayCurveOnly(pDC, SizeArray, pY) ;
	}

public :
	void DrawArray(CDC *pDC, int SizeArray, T_Value *pY)
	{
		CPen Pen(mLineStyle, mCurveWidth, mCurveColor) ;
		CPen *pOldPen = pDC->SelectObject(&Pen) ;
		int	Rop = pDC->SetROP2(R2_COPYPEN) ;

		DrawArrayOnly(pDC, SizeArray, pY) ;

		pDC->SelectObject(pOldPen) ;
		pDC->SetROP2(Rop) ;
	}
};

