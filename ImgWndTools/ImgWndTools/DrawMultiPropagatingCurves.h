#pragma once
#include "drawpropagatingcurve.h"
#include "DrawMulti1DArray.h"
template <class T_DATA> 
class CDrawMultiPropagatingCurves :
	virtual public CDrawPropagatingCurve <T_DATA>,
	virtual public CDrawMulti1DArray <T_DATA>
{
public:
	CDrawMultiPropagatingCurves(void)
		: CDrawPropagatingCurve <T_DATA> ()
		, CDrawMulti1DArray <T_DATA> ()
	{
	}

	~CDrawMultiPropagatingCurves(void)
	{
	}
protected :
	T_DATA mPrevValue[MAX_CNT_CURVE] ;
	
protected :
	void ResetPrevValue(int cntCurve, int *pStyleList, T_DATA *pValueList) 
	{
		for(int i = 0 ; i < cntCurve ; ++i)
		{
			int idxStyle = *(pStyleList + i) ;
			if(mCurveLineStyle[idxStyle].idx == idxStyle)
				mPrevValue[idxStyle] = *(pValueList + i) ;
		}
	}

public :
	void DrawNewDot(CDC *pDC, int cntCurve, int *pStyleList, T_DATA *pValueList, BOOL *pMeetRightMargin, BOOL Progress = FALSE) 
	{
		if(mIdxPrevDot < 0)
			mIdxPrevDot = 0 ;
		else
		{
			if(++mIdxPrevDot < mMaxX)
			{
				for(int i = 0 ; i < cntCurve ; ++i)
				{
					int idxStyle = *(pStyleList + i) ;
					if(mCurveLineStyle[idxStyle].idx == idxStyle)
						DrawPieceCurveWithPenStyle(pDC, mIdxPrevDot-1, mPrevValue[idxStyle], mIdxPrevDot, *(pValueList+i), mCurveLineStyle[idxStyle].Style, mCurveLineStyle[idxStyle].Width, mCurveLineStyle[idxStyle].Clr) ;
				}
				*pMeetRightMargin = FALSE ;
				if(mProgressBar && Progress)
				{
					DrawProgressBar(pDC, mIdxPrevDot-1, mIdxPrevDot) ;
				}
			}
			else
			{
				if(mRestartMeetingRightMargin)
					mIdxPrevDot = 0 ;
				*pMeetRightMargin = TRUE ;
			}
		}
		ResetPrevValue(cntCurve, pStyleList, pValueList) ;
	}

};

