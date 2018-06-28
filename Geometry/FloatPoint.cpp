#include "StdAfx.h"
#include "FloatPoint.h"
#include <math.h>

CFloatPoint::CFloatPoint(void)
{
	x = y = 0 ;
}


CFloatPoint::~CFloatPoint(void)
{
}


CFloatPoint::CFloatPoint(int xx, int yy)
{
	x = xx ;
	y = yy ;
}


CFloatPoint::CFloatPoint(double xx, double yy)
{
	x = xx ;
	y = yy ;
}


CFloatPoint::CFloatPoint(FLOAT_POINT Pt)
{
	x = Pt.x ;
	y = Pt.y ;
}


CFloatPoint::CFloatPoint(POINT Pt)
{
	x = Pt.x ;
	y = Pt.y ;
}


POINT CFloatPoint::Rounding(void)
{
	POINT Pt = {ROUNDING(x), ROUNDING(y)} ;
	return Pt ;
}


POINT CFloatPoint::Truncating(void)
{
	POINT Pt = {(int)x, (int)y} ;
	return Pt ;
}


void CFloatPoint::operator =(FLOAT_POINT Pt)
{
	x = Pt.x ;
	y = Pt.y ;
}


void CFloatPoint::operator =(POINT Pt)
{
	x = Pt.x ;
	y = Pt.y ;
}


void CFloatPoint::operator +=(FLOAT_POINT Pt)
{
	x += Pt.x ;
	y += Pt.y ;
}


void CFloatPoint::operator +=(POINT Pt)
{
	x += Pt.x ;
	y += Pt.y ;
}


FLOAT_POINT CFloatPoint::operator +(FLOAT_POINT Pt)
{
	FLOAT_POINT OutPt = {x+Pt.x, y+Pt.y} ;
	return OutPt ;
}


FLOAT_POINT CFloatPoint::operator +(POINT Pt)
{
	FLOAT_POINT OutPt = {x+Pt.x, y+Pt.y} ;
	return OutPt ;
}


void CFloatPoint::operator -=(FLOAT_POINT Pt)
{
	x -= Pt.x ;
	y -= Pt.y ;
}


void CFloatPoint::operator -=(POINT Pt)
{
	x -= Pt.x ;
	y -= Pt.y ;
}


FLOAT_POINT CFloatPoint::operator -(FLOAT_POINT Pt)
{
	FLOAT_POINT OutPt = {x-Pt.x, y-Pt.y} ;
	return OutPt ;
}


FLOAT_POINT CFloatPoint::operator -(POINT Pt)
{
	FLOAT_POINT OutPt = {x-Pt.x, y-Pt.y} ;
	return OutPt ;
}


double CFloatPoint::Norm(void)
{
	return sqrt(x * x + y * y) ;
}


BOOL CFloatPoint::Normalize(void)
{
	double norm = Norm() ;
	if(norm > CLOSE_TO_ZERO)
	{
		x /= norm ;
		y /= norm ;
		return TRUE ;
	}
	else
		return FALSE ;
}


BOOL CFloatPoint::CrossPointOfLines(FLOAT_POINT *pCrossPt, FLOAT_POINT DtOnLn1, double SlopeLn1, FLOAT_POINT DtOnLn2, double SlopeLn2)
{
	if(fabs(SlopeLn1 - SlopeLn2) < 0.001)
		return FALSE ;
	pCrossPt->x = (DtOnLn1.x * SlopeLn1 - DtOnLn2.x * SlopeLn2 + DtOnLn2.y - DtOnLn1.y) / (SlopeLn1 - SlopeLn2) ;
	pCrossPt->y = (pCrossPt->x - DtOnLn1.x) * SlopeLn1 + DtOnLn1.y;
	return TRUE ;
}


double CFloatPoint::DistanceBetweenPts(FLOAT_POINT Pt1 , FLOAT_POINT Pt2)
{
	return sqrt((Pt1.x-Pt2.x) * (Pt1.x - Pt2.x) + (Pt1.y - Pt2.y) * (Pt1.y - Pt2.y)) ;
}
