#pragma once
#include "FloatRect.h"

template <class T_XData, class T_YData>
class  CCoordinateAxis
{
public:
	CCoordinateAxis(void)
		: mDrawRange(0, 0, 0, 0)
		, mOriginStyle(ORG_LB)
		, mCoordStyle(AXIS)
		, mProgressBar(RGB(255, 0, 0))
		, mProgressBarWidth(3)
	{
	}
	~CCoordinateAxis(void)
	{
	}
public :
	typedef enum
	{
		ORG_LT,
		ORG_LB
	} ENUM_ORIGIN ;

	typedef enum
	{
		GRID,
		AXIS
	} ENUM_COORDINATE_STYLE ;

protected :
	ENUM_ORIGIN	mOriginStyle ;
	ENUM_COORDINATE_STYLE		mCoordStyle ;

	CFloatRect	mDrawRange ;
	CPoint	mOriginPos ;

	T_XData mMinX, mMaxX ;
	T_YData mMinY, mMaxY  ;
	T_XData mXCoordStep, mXLabelStep ;
	T_YData mYCoordStep, mYLabelStep ;

	BOOL	mProgressBar ;
	COLORREF	mProgressBarColor ;
	int		mProgressBarWidth ;

	COLORREF	mAxisColor ;
	COLORREF	mGridColor ;
	int				mAxisWidth ;
	int				mGridWidth ;
	int				mGridLineStyle ;
	COLORREF	mAxisMarkColor ;
	int				mAxisMarkWidth ;
	int				mAxisMarkLength ;
	COLORREF	mAxisLabelColor ;
	int	mAxisXPrecision ;
	int	mAxisYPrecision ;
	int	mLabelDistanceToXAxis ;
	int	mLabelDistanceToYAxis ;


	double	mXScale, mYScale ;
	T_XData		mMinGridX ;
	T_YData		mMinGridY ;
	T_XData		mMinLabeledX ;
	T_YData		mMinLabeledY ;
	
	CString	mBufStr ;

protected :
	void ReInitializeParameters()
	{
		mXScale = (double)mDrawRange.Width() / (double)(mMaxX - mMinX) ;
		mYScale = (double)mDrawRange.Height() / (double)(mMaxY - mMinY) ;
		if(mMinX >= 0)
			mOriginPos.x = XValueToDrawPos(mMinX) ;
		else
			mOriginPos.x = XValueToDrawPos(0) ;
		if(mMinY >= 0)
			mOriginPos.y = YValueToDrawPos(mMinY) ;
		else
			mOriginPos.y = YValueToDrawPos(0) ;

		if(mMinX <= 0)
		{
			mMinGridX = -(T_XData)((int)(-mMinX / mXCoordStep) * mXCoordStep) ;
			mMinLabeledX = -(T_XData)((int)(-mMinX / mXLabelStep) * mXLabelStep) ;
		}
		else
		{
			mMinGridX = (T_XData)((int)(mMinX / mXCoordStep) * mXCoordStep) ;
			mMinLabeledX = (T_XData)((int)(mMinX / mXLabelStep) * mXLabelStep) ;
		}
		if(mMinGridX < mMinX)
			mMinGridX += mXCoordStep ;
		if(mMinLabeledX < mMinX)
			mMinLabeledX += mXLabelStep ;
		if(mMinY <= 0)
		{
			mMinGridY = -(T_YData)((int)(-mMinY / mYCoordStep) * mYCoordStep) ;
			mMinLabeledY = -(T_YData)((int)(-mMinY / mYLabelStep) * mYLabelStep) ;
		}
		else
		{
			mMinGridY = (T_YData)((int)(mMinY / mYCoordStep) * mYCoordStep) ;
			mMinLabeledY = (T_YData)((int)(mMinY / mYLabelStep) * mYLabelStep) ;
		}
		if(mMinGridY < mMinY)
			mMinGridY += mYCoordStep ;
		if(mMinLabeledY < mMinY)
			mMinLabeledY += mYLabelStep ;
	}

	int	XValueToDrawPos(T_XData x)
	{
		return ROUNDING((x - mMinX) * mXScale + mDrawRange.left);
	}

	int YValueToDrawPos(T_YData y)
	{
		double RefY =  (y - mMinY) * mYScale   ;
		return mOriginStyle == ORG_LT ? ROUNDING(RefY + mDrawRange.top) : ROUNDING(mDrawRange.bottom - RefY) ;
	}

	int	GetXPosReferToOrigin(T_XData x)
	{
		return XValueToDrawPos(x) - mOriginPos.x ;
	}

	int GetYPosReferToOrigin(T_YData y)
	{
		return YValueToDrawPos(y) - mOriginPos.y ;
	}

	template <class T_DATA>
	LPCTSTR GetLabelString(T_DATA Data, int Precision)
	{
		mBufStr.Format(_T("%d"), (int)Data) ;
		if(Precision > 0)
		{
			mBufStr += _T(".") ;
			float fraction = (float)abs(Data) ;
			fraction -= (int)fraction ;
			while(Precision-- > 0)
			{
				fraction *= 10 ;
				mBufStr.AppendChar(_T('0'+(int)fraction)) ;
			}
		}
		return mBufStr ;
	}

	void ShowHorzAxisLabel(CDC *pDC, T_XData x, CString &Label)
	{
		CSize SizeStr = pDC->GetTextExtent(Label) ;
		int xPos = XValueToDrawPos(x)  - SizeStr.cx / 2;
		int yPos = (mCoordStyle == GRID ? (int)mDrawRange.bottom : mOriginPos.y) + mLabelDistanceToXAxis ;
		pDC->TextOutW(xPos, yPos, Label) ;
	}

	void ShowVertAxisLabel(CDC *pDC, T_XData y, CString &Label)
	{
		CSize SizeStr = pDC->GetTextExtent(Label) ;
		int yPos = YValueToDrawPos(y) - SizeStr.cy/2  ;
		int xPos = mOriginPos.x + mLabelDistanceToYAxis - SizeStr.cx ;
		pDC->TextOutW(xPos, yPos, Label) ;
	}

public :
	void SetDrawRange(RECT Range)
	{
		mDrawRange = Range ;
	}

	void SetStyle(ENUM_ORIGIN OriginStyle, ENUM_COORDINATE_STYLE CoordStyle)
	{
		mOriginStyle = OriginStyle ;
		mCoordStyle = CoordStyle ;
	}

	void SetDrawCurveRange(T_XData MinX, T_XData MaxX, T_YData MinY, T_YData MaxY)
	{
		mMinX = MinX ;
		mMaxX = MaxX ;
		mMinY = MinY ;
		mMaxY = MaxY ;
	}

	void SetCoordinateDefinition(T_XData XStep, T_XData XLabelStep, T_YData YStep, T_YData YLabelStep)
	{
		mXCoordStep = XStep ;
		mXLabelStep = XLabelStep ;

		mYCoordStep = YStep ;
		mYLabelStep = YLabelStep ;
	}


	void SetPaintAxisStyle(COLORREF Clr, int Width)
	{
		mAxisColor = Clr ;
		mAxisWidth = Width ;
	}

	void SetPaintGridStyle(COLORREF Clr, int Width, int Style)
	{
		mGridColor = Clr ;
		mGridWidth = Width ;
		mGridLineStyle = Style ;
	}

	void SetAxisMarkStyle(COLORREF Clr, int	Width, int Length)
	{
		mAxisMarkColor = Clr ;
		mAxisMarkWidth = Width ;
		mAxisMarkLength = Length ;
	}

	void SetAxisLabelStyle(COLORREF Clr, int XPrecision = 0, int YPrecision = 0)
	{
		mAxisLabelColor = Clr ;
		mAxisXPrecision = XPrecision ;
		mAxisYPrecision = YPrecision ;
	}

	void SetAxisLabelPosition(int DistanceToXAxis, int DistanceToYAxis)
	{
		if(mOriginStyle == ORG_LT)
			mLabelDistanceToXAxis = -DistanceToXAxis ;
		else
			mLabelDistanceToXAxis = DistanceToXAxis ;
		mLabelDistanceToYAxis = -DistanceToYAxis ;
	}

	void DrawAxis(CDC *pDC)
	{
		ReInitializeParameters() ;
		CPen PenAxis(PS_SOLID, mAxisWidth, mAxisColor) ;
		CPen *pOldPen = pDC->SelectObject(&PenAxis) ;
		int	R2 = pDC->SetROP2(R2_COPYPEN) ;
		pDC->MoveTo(mOriginPos) ;
		pDC->LineTo(ROUNDING(mDrawRange.right), mOriginPos.y) ;
		pDC->MoveTo(mOriginPos.x, ROUNDING(mDrawRange.top)) ;
		pDC->LineTo(mOriginPos.x, ROUNDING(mDrawRange.bottom)) ;
		if(mCoordStyle == GRID)
			DrawGrid(pDC) ;
		else
			DrawAxisMark(pDC) ;
		LabelAxis(pDC) ;

		pDC->SelectObject(pOldPen) ;
		pDC->SetROP2(R2) ;
	}

	void DrawGrid(CDC *pDC)
	{
		CPen PenGrid(mGridLineStyle, mGridWidth, mGridColor) ;
		CPen *pOldPen = pDC->SelectObject(&PenGrid) ;
		int Rop = pDC->SetROP2(R2_COPYPEN) ;
		
		T_XData x = mMinGridX ;
		int minYPos = YValueToDrawPos(mMinY) ;
		int maxYPos = YValueToDrawPos(mMaxY) ;
		while(x <= mMaxX)
		{
			int xPos = XValueToDrawPos(x) ;
			pDC->MoveTo(xPos, minYPos) ;
			pDC->LineTo(xPos, maxYPos) ;
			x += mXCoordStep ;
		}
		int xPos = XValueToDrawPos(mMaxX) ;
		pDC->MoveTo(xPos, minYPos) ;
		pDC->LineTo(xPos, maxYPos) ;
		

		T_YData y = mMinGridY ;
		int minXPos = XValueToDrawPos(mMinX) ;
		int maxXPos = XValueToDrawPos(mMaxX) ;
		while(y <= mMaxY)
		{
			int yPos = YValueToDrawPos(y) ;
			pDC->MoveTo(minXPos, yPos) ;
			pDC->LineTo(maxXPos, yPos) ;
			y += mYCoordStep ;
		}
		int yPos = YValueToDrawPos(mMaxY) ;
		pDC->MoveTo(minXPos, yPos) ;
		pDC->LineTo(maxXPos, yPos) ;

		pDC->SelectObject(pOldPen) ;
		pDC->SetROP2(Rop) ;
	}

	void DrawAxisMark(CDC *pDC)
	{
		CPen PenGrid(PS_SOLID, mAxisMarkWidth, mAxisMarkColor) ;
		CPen *pOldPen = pDC->SelectObject(&PenGrid) ;
		int Rop = pDC->SetROP2(R2_COPYPEN) ;

		T_XData x = mMinGridX ;
		int minYPos = mOriginPos.y - mAxisMarkLength / 2 ;
		int maxYPos = mOriginPos.y + mAxisMarkLength / 2 ;
		while(x <= mMaxX)
		{
			int xPos = XValueToDrawPos(x) ;
			pDC->MoveTo(xPos, minYPos) ;
			pDC->LineTo(xPos, maxYPos) ;
			x += mXCoordStep ;
		}

		T_YData y = mMinGridY ;
		int minXPos = mOriginPos.x - mAxisMarkLength / 2 ;
		int maxXPos = mOriginPos.x + mAxisMarkLength / 2 ;
		while(y <= mMaxY)
		{
			int yPos = YValueToDrawPos(y) ;
			pDC->MoveTo(minXPos, yPos) ;
			pDC->LineTo(maxXPos, yPos) ;
			y += mYCoordStep ;
		}

		pDC->SelectObject(pOldPen) ;
		pDC->SetROP2(Rop) ;
	}

	void LabelAxis(CDC *pDC) 
	{
		COLORREF OldClr = pDC->SetTextColor(mAxisLabelColor) ;
		int BkMode = pDC->SetBkMode(TRANSPARENT) ;

		T_XData x = mMinLabeledX ;
		while(x <= mMaxX)
		{
			CString Label = GetLabelString(x, mAxisXPrecision) ;
			ShowHorzAxisLabel(pDC, x, Label) ;
			x += mXLabelStep ;
		}

		T_YData y = mMinLabeledY ;
		while(y <= mMaxY)
		{
			CString Label = GetLabelString(y, mAxisYPrecision) ;
			ShowVertAxisLabel(pDC, y, Label) ;
			y += mYLabelStep ;
		}


		pDC->SetTextColor(OldClr) ;
		pDC->SetBkMode(BkMode) ;
	}

	void SetProgressBarColor(COLORREF Clr, int Width = 3)
	{
		mProgressBarColor = Clr ;
		mProgressBarWidth = Width ;
	}

	void EnableProgressBar(BOOL Enable)
	{
		mProgressBar = Enable ;
	}
};

