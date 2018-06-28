#pragma once
#include "DrawMultiCurve.h"
#include "Draw1DArray.h"

template <class T_Value>
class CDrawMulti1DArray :  virtual public CDrawMultiCurve <T_Value, int> ,
											  virtual public CDraw1DArray <T_Value>
{
public:
	CDrawMulti1DArray(void)
		: CDrawMultiCurve <T_Value, int> ()
		, CDraw1DArray <T_Value> ()
	{
	}
	~CDrawMulti1DArray(void)
	{
	}

	void DrawArray(CDC *pDC, int idxStyle, int SizeArray, T_Value *pY)
	{
		if(idxStyle >= 0 && idxStyle < MAX_CNT_CURVE)
		{
			if(mCurveLineStyle[idxStyle].idx == idxStyle)
			{
				CPen Pen(mCurveLineStyle[idxStyle].Style, mCurveLineStyle[idxStyle].Width, mCurveLineStyle[idxStyle].Clr) ;
				CPen *pOldPen = pDC->SelectObject(&Pen) ;
				int	Rop = pDC->SetROP2(R2_COPYPEN) ;

				DrawArrayOnly(pDC, SizeArray, pY) ;

				pDC->SelectObject(pOldPen) ;
				pDC->SetROP2(Rop) ;
			}
		}

	}
};

