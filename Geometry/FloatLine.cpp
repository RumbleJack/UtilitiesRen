#include "StdAfx.h"
#include "FloatLine.h"
#include <math.h>
using namespace std;

CFloatLine::CFloatLine(void)
{
	end1.x = end1.y = end2.x = end2.y = 0 ;
}


CFloatLine::~CFloatLine(void)
{
}


CFloatLine::CFloatLine(float xEnd1, float yEnd1, float xEnd2, float yEnd2)
{
	end1.x = xEnd1 ;
	end1.y = yEnd1 ;
	end2.x = xEnd2 ;
	end2.y = yEnd2 ;
}


CFloatLine::CFloatLine(FLOAT_POINT pt1, FLOAT_POINT pt2)
{
	end1 = pt1 ;
	end2 = pt2 ;
}


CFloatLine::CFloatLine(POINT pt1, POINT pt2)
{
	end1.x = pt1.x ;
	end1.y = pt1.y ;
	end2.x = pt2.x ;
	end2.y = pt2.y ;
}


CFloatLine::CFloatLine(FLOAT_LINE line)
{
	end1 = line.end1 ;
	end2 = line.end2 ;
}


void CFloatLine::Offset(double x, double y)
{
	end1.x += x ;
	end2.x += x ;
	end1.y += y ;
	end2.y += y ;
}


void CFloatLine::Offset(FLOAT_POINT pt)
{
	end1.x += pt.x ;
	end2.x += pt.x ;
	end1.y += pt.y ;
	end2.y += pt.y ;
}


double CFloatLine::Length(void)
{
	CFloatPoint vec(Vector()) ;
	return vec.Norm() ;
}


FLOAT_POINT CFloatLine::Vector(void)
{
	FLOAT_POINT vec = {end2.x-end1.x, end2.y-end1.y} ;
	return vec ;
}


BOOL CFloatLine::LinesCrossPoint(FLOAT_POINT &crossPt, FLOAT_LINE line)
{
	CFloatPoint thisVec(Vector()) ;
	CFloatPoint lnVec(line.end2.x - line.end1.x, line.end2.y-line.end1.y) ;
	double lengthThisVec = thisVec.Norm() ;
	double lengthLnVec = lnVec.Norm() ;
	if(lengthThisVec <= CLOSE_TO_ZERO || lengthLnVec <= CLOSE_TO_ZERO)
		return FALSE ;
	double crossMul = thisVec.x * lnVec.y - lnVec.x* thisVec.y ;
	if( fabs(crossMul) <= CLOSE_TO_ZERO)
		return FALSE ;
	double kThisVec = (lnVec.x  * (end1.y - line.end1.y) - (end1.x - line.end1.x) * lnVec.y) / crossMul * lengthThisVec ;
	double kLnVec = 0 ;
	if(fabs(lnVec.x) > CLOSE_TO_ZERO)
		kLnVec = (kThisVec * thisVec.x / lengthThisVec + (end1.x - line.end1.x)) / lnVec.x * lengthLnVec ;
	else
		kLnVec = (kThisVec * thisVec.y / lengthThisVec + (end1.y - line.end1.y)) / lnVec.y * lengthLnVec ;
	crossPt.x = kThisVec * thisVec.x / lengthThisVec + end1.x ;
	crossPt.y = kThisVec * thisVec.y / lengthThisVec + end1.y ;

	return (kThisVec >= 0 && kThisVec <= lengthThisVec && kLnVec >= 0 && kLnVec <= lengthLnVec) ;
}


BOOL CFloatLine::LinesCrossPoint(FLOAT_POINT & crossPt, FLOAT_POINT lnEnd1, FLOAT_POINT lnEnd2)
{
	FLOAT_LINE ln = {lnEnd1, lnEnd2} ;
	return LinesCrossPoint(crossPt, ln) ;
}


void CFloatLine::operator =(FLOAT_LINE line)
{
	end1 = line.end1 ;
	end2 = line.end2 ;
}
