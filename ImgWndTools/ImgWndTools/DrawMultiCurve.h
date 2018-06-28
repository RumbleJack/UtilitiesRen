#pragma once
#include "drawcurve.h"
#define MAX_CNT_CURVE	20

template <class T_XData, class T_YData>
class CDrawMultiCurve :
	virtual public CDrawCurve <T_XData, T_YData>
{
public:
	CDrawMultiCurve(void)
		: CDrawCurve <T_XData, T_YData> ()
	{
		for(int i = 0 ; i < MAX_CNT_CURVE ; ++i)
			mCurveLineStyle[i].idx = -1 ;
	}
	~CDrawMultiCurve(void)
	{
	}
protected :
	typedef struct
	{
		int			idx ;
		COLORREF	Clr ;
		int					Style ;
		int					Width ;
	} LINE_STYLE ;
	LINE_STYLE	mCurveLineStyle[MAX_CNT_CURVE] ;

public:	

	void SetCurveStyle(ENUM_CURVE_DRAW_STYLE Style)
	{
		mCurveStyle = Style ;
	}

	int InsertCurveLineStyle(COLORREF Clr, int width, int LnStyle)
	{
		for(int i = 0 ; i < MAX_CNT_CURVE ; ++i)
		{
			if(mCurveLineStyle[i].idx < 0)
			{
				mCurveLineStyle[i].idx = i ;
				mCurveLineStyle[i].Clr = Clr ;
				mCurveLineStyle[i].Style = LnStyle ;
				mCurveLineStyle[i].Width = width ;
				return i ;
			}
		}
		return -1 ;
	}

	BOOL RemoveCurveLineStyle(int idxStyle)
	{
		if(idxStyle >= 0 && idxStyle < MAX_CNT_CURVE)
		{
			if(mCurveLineStyle[idxStyle] == idxStyle)
			{
				mCurveLineStyle[idxStyle] = -1 ;
				return TRUE ;
			}
		}
		return FALSE ;
	}

	void DrawCurve(CDC * pDC, int idxStyle, int SizeArray, T_XData * pX, T_YData * pY)
	{
		if(idxStyle >= 0 && idxStyle < MAX_CNT_CURVE)
		{
			if(mCurveLineStyle[idxStyle].idx == idxStyle)
			{
				CPen Pen(mCurveLineStyle[idxStyle].Style, mCurveLineStyle[idxStyle].Width, mCurveLineStyle[idxStyle].Clr) ;
				CPen *pOldPen = pDC->SelectObject(&Pen) ;
				int	Rop = pDC->SetROP2(R2_COPYPEN) ;

				DrawBarOnly(pDC, SizeArray, pX, pY) ;

				pDC->SelectObject(pOldPen) ;
				pDC->SetROP2(Rop) ;
			}
		}
	}
};

