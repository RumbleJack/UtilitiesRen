#include "StdAfx.h"
#include "FloatRect.h"

CFloatRect::CFloatRect(void)
{
	left = right = top = bottom = 0 ;
}


CFloatRect::~CFloatRect(void)
{
}


CFloatRect::CFloatRect(double l, double t, double r, double b)
{
	left = l ;
	right = r ;
	top = t ;
	bottom = b ;
}


CFloatRect::CFloatRect(FLOAT_RECT rect)
{
	left = rect.left ;
	right = rect.right ;
	top = rect.top ;
	bottom = rect.bottom ;
}


CFloatRect::CFloatRect(RECT rect)
{
	left = rect.left ;
	right = rect.right ;
	top = rect.top ;
	bottom = rect.bottom ;
}


CFloatRect::CFloatRect(FLOAT_POINT TopLeft, FLOAT_POINT BottomRight)
{
	left = TopLeft.x ;
	top = TopLeft.y ;
	right = BottomRight.x ;
	bottom = BottomRight.y ;
}


CFloatRect::CFloatRect(POINT TopLeft, POINT BottomRight)
{
	left = TopLeft.x ;
	top = TopLeft.y ;
	right = BottomRight.x ;
	bottom = BottomRight.y ;
}


CFloatRect::CFloatRect(FLOAT_POINT TopLeft, FLOAT_SIZE size)
{
	left = TopLeft.x ;
	top = TopLeft.y ;
	right = left + size.cx ;
	bottom = top + size.cy ;
}


CFloatRect::CFloatRect(POINT TopLeft, SIZE size)
{
	left = TopLeft.x ;
	top = TopLeft.y ;
	right = left + size.cx ;
	bottom = top + size.cy ;
}


RECT CFloatRect::Rounding(void)
{
	RECT rect = {ROUNDING(left), ROUNDING(top), ROUNDING(right), ROUNDING(bottom)} ;
	return rect ;
}


RECT CFloatRect::Truncating(void)
{
	RECT rect = {(int)left, (int)top, (int)right, (int)bottom} ;
	return rect ;
}


double CFloatRect::Width(void)
{
	return right - left;
}


double CFloatRect::Height(void)
{
	return bottom - top;
}


double CFloatRect::Area(void)
{
	return Width() * Height() ;
}


FLOAT_POINT CFloatRect::CenterPoint(void)
{
	FLOAT_POINT Pt = {(right + left) / 2, (bottom + top) / 2} ;
	return Pt ;
}


FLOAT_POINT CFloatRect::TopLeft(void)
{
	FLOAT_POINT Pt = {left, top} ;
	return Pt ;
}


FLOAT_POINT CFloatRect::TopRight(void)
{
	FLOAT_POINT Pt = {right, top} ;
	return Pt ;
}


FLOAT_POINT CFloatRect::BottomLeft(void)
{
	FLOAT_POINT Pt = {left, bottom} ;
	return Pt ;
}


FLOAT_POINT CFloatRect::BottomRight(void)
{
	FLOAT_POINT Pt = {right, bottom} ;
	return Pt ;
}


void CFloatRect::operator =(FLOAT_RECT rect)
{
	left = rect.left ;
	right = rect.right ;
	top = rect.top ;
	bottom = rect.bottom ;
}


void CFloatRect::operator =(RECT rect)
{
	left = rect.left ;
	right = rect.right ;
	top = rect.top ;
	bottom = rect.bottom ;
}


void CFloatRect::InflateRect(double cx, double cy)
{
	left -= cx ;
	right += cx ;
	top -= cy ;
	bottom += cy ;
}


void CFloatRect::InflateRect(FLOAT_SIZE size)
{
	left -= size.cx ;
	right += size.cx ;
	top -= size.cy ;
	bottom += size.cy ;
}


void CFloatRect::InflateRect(double l, double t, double r, double b)
{
	left -= l ;
	right += r ;
	top -= t ;
	bottom += b ;
}


void CFloatRect::InflateRect(FLOAT_RECT rect)
{
	left -= rect.left ;
	right += rect.right ;
	top -= rect.top ;
	bottom += rect.bottom ;
}


void CFloatRect::DeflateRect(double cx, double cy)
{
	left += cx ;
	right -= cx ;
	top += cy ;
	bottom -= cy ;
}


void CFloatRect::DeflateRect(FLOAT_SIZE size)
{
	left += size.cx ;
	right -= size.cx ;
	top += size.cy ;
	bottom -= size.cy ;
}


void CFloatRect::DeflateRect(double l, double t, double r, double b)
{
	left += l ;
	right -= r ;
	top += t ;
	bottom -= b ;
}


void CFloatRect::DeflateRect(FLOAT_RECT rect)
{
	left += rect.left ;
	right -= rect.right ;
	top += rect.top ;
	bottom -= rect.bottom ;
}


void CFloatRect::MoveTo(double x, double y)
{
	right = x + Width() ;
	bottom = y + Height() ;
	left = x ;
	top = y ;
}


void CFloatRect::MoveTo(FLOAT_POINT Pt)
{
	right = Pt.x + Width() ;
	bottom = Pt.y + Height() ;
	left = Pt.x ;
	top = Pt.y ;
}


void CFloatRect::Offset(double x, double y)
{
	left += x ;
	right += x ;
	top += y ;
	bottom += y ;
}


void CFloatRect::Offset(FLOAT_POINT Pt)
{
	left += Pt.x ;
	right += Pt.x ;
	top += Pt.y ;
	bottom += Pt.y ;
}


FLOAT_SIZE CFloatRect::Size(void)
{
	FLOAT_SIZE size = {right - left, bottom - top} ;
	return size ;
}


void CFloatRect::Normalize(void)
{
	if(left > right)
		Exchange(left, right) ;
	if(top > bottom)
		Exchange(top, bottom) ;
}


BOOL CFloatRect::PtInRect(double x, double y)
{
	return (x >= left && x < right && y >= top && y < bottom) ;
}


BOOL CFloatRect::PtInRect(FLOAT_POINT pt)
{
	return (pt.x >= left && pt.x < right && pt.y >= top && pt.y < bottom) ;
}


BOOL CFloatRect::Intersect(FLOAT_RECT rect1, FLOAT_RECT rect2)
{
	left = max(min(rect1.left, rect1.right), min(rect2.left, rect2.right)) ;
	right = min(max(rect1.left, rect1.right), max(rect2.left, rect2.right)) ;
	top = max(min(rect1.top, rect1.bottom), min(rect2.top, rect2.bottom)) ;
	bottom = min(max(rect1.top, rect1.bottom), max(rect2.top, rect2.bottom)) ;
	return (right > left && bottom > top) ;
}


void CFloatRect::Union(FLOAT_RECT rect1, FLOAT_RECT rect2)
{
	left = min(min(rect1.left, rect1.right), min(rect2.left, rect2.right)) ;
	right = max(max(rect1.left, rect1.right), max(rect2.left, rect2.right)) ;
	top = min(min(rect1.top, rect1.bottom), min(rect2.top, rect2.bottom)) ;
	bottom = max(max(rect1.top, rect1.bottom), max(rect2.top, rect2.bottom)) ;
}


void CFloatRect::operator += (FLOAT_POINT pt)
{
	Offset(pt) ;
}


void CFloatRect::operator += (FLOAT_RECT rect)
{
	Offset(rect) ;
}


void CFloatRect::Offset(FLOAT_RECT rect)
{
	left += rect.left ;
	right += rect.right ;
	top += rect.top ;
	bottom += rect.bottom ;
}


void CFloatRect::operator -=(FLOAT_POINT pt)
{
	left -= pt.x ;
	right -= pt.x ;
	top -= pt.y ;
	bottom -= pt.y ;
}


void CFloatRect::operator -=(FLOAT_RECT rect)
{
	left -= rect.left ;
	right -= rect.right ;
	top -= rect.top ;
	bottom -= rect.bottom ;
}


FLOAT_RECT CFloatRect::operator +(FLOAT_POINT pt)
{
	FLOAT_RECT outRect = {left + pt.x, top + pt.y, right + pt.x, bottom + pt.y} ;
	return outRect ;
}


FLOAT_RECT CFloatRect::operator +(FLOAT_RECT rect)
{
	FLOAT_RECT outRect = {left + rect.left, top + rect.top, right + rect.right, bottom + rect.bottom} ;
	return outRect ;
}


FLOAT_RECT CFloatRect::operator -(FLOAT_RECT rect)
{
	FLOAT_RECT outRect = {left - rect.left, top - rect.top, right - rect.right, bottom - rect.bottom} ;
	return outRect ;
}


FLOAT_RECT CFloatRect::operator -(FLOAT_POINT pt)
{
	FLOAT_RECT outRect = {left - pt.x, top - pt.y, right - pt.x, bottom - pt.y} ;
	return outRect ;
}

const int CROSS_PT = 2 ;
BOOL CFloatRect::IntersectLine(FLOAT_LINE & lnInRect, FLOAT_LINE refLn)
{
	FLOAT_POINT  crossPt[CROSS_PT] ;
	if(IntersectLine(crossPt, refLn.end1, refLn.end2) < CROSS_PT)
		return FALSE ;
	else
	{
		lnInRect.end1 = crossPt[0] ;
		lnInRect.end2 = crossPt[1] ;
		return TRUE ;
	}
}


int CFloatRect::IntersectLine(FLOAT_POINT * pCrossPt, FLOAT_POINT lnEnd1 , FLOAT_POINT lnEnd2)
{
	int	cntCrossPt = 0 ;
	if(PtInRect(lnEnd1))
		pCrossPt[cntCrossPt++] = lnEnd1 ;
	if(PtInRect(lnEnd2))
		pCrossPt[cntCrossPt++] = lnEnd2 ;
	if(cntCrossPt < CROSS_PT)
	{
		CFloatLine line(lnEnd1, lnEnd2) ;
		if(line.LinesCrossPoint(pCrossPt[cntCrossPt], TopLeft(), TopRight()))
			++cntCrossPt ;
		if(cntCrossPt < CROSS_PT && line.LinesCrossPoint(pCrossPt[cntCrossPt], TopLeft(), BottomLeft()))
			++cntCrossPt ;
		if(cntCrossPt < CROSS_PT && line.LinesCrossPoint(pCrossPt[cntCrossPt], BottomLeft(), BottomRight()))
			++cntCrossPt ;
		if(cntCrossPt < CROSS_PT && line.LinesCrossPoint(pCrossPt[cntCrossPt], TopRight(), BottomRight()))
			++cntCrossPt ;
	}
	return cntCrossPt ;

}
