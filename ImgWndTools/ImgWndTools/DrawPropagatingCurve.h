#pragma once
#include "draw1darray.h"
template <class T_DATA>
class CDrawPropagatingCurve :
	virtual public CDraw1DArray <T_DATA>
{
public:
	CDrawPropagatingCurve(void)
		: CDraw1DArray <T_DATA> ()
		, mIdxPrevDot(-1)
	{
	}

	~CDrawPropagatingCurve(void)
	{
	}

protected :
	int		mIdxPrevDot ;
	T_DATA	mValuePrevDot ;
	BOOL	mRestartMeetingRightMargin ;

	void Restart(T_DATA value)
	{
		mIdxPrevDot = 0 ;
		mValuePrevDot = value ;
	}

public :
	void EnableRestartWhenMeetRightMargin(BOOL enable)
	{
		mRestartMeetingRightMargin = enable ;
	}

	void DrawNewDot(CDC *pDC, T_DATA value, BOOL *pMeetRightMargin, BOOL Progress = FALSE)
	{
		if(mIdxPrevDot < 0)
		{
			Restart(value) ;
		}
		else
		{
			if(++mIdxPrevDot < mMaxX)
			{
				DrawPieceCurveWithPenStyle(pDC, mIdxPrevDot-1, mValuePrevDot, mIdxPrevDot, value, mLineStyle, mCurveWidth, mCurveColor) ;
				*pMeetRightMargin = FALSE ;
				if(mProgressBar && Progress)
				{
					DrawProgressBar(pDC, mIdxPrevDot-1, mIdxPrevDot) ;
				}
			}
			else
			{
				if(mRestartMeetingRightBoard)
				{
					mIdxPrevDot = 0 ;
				}
				*pMeetRightMargin = TRUE ;
			}
			mValuePrevDot = value ;
		}
	}
};

