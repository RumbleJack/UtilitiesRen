#pragma once
#include "PubMacroDef.h"

typedef struct
{
	double x, y ;
} FLOAT_POINT ;

class DllExport CFloatPoint : public FLOAT_POINT
{
public:
	CFloatPoint(void);
	~CFloatPoint(void);
	CFloatPoint(int xx, int yy);
	CFloatPoint(double xx, double yy);
	CFloatPoint(FLOAT_POINT Pt);
	CFloatPoint(POINT Pt);
	POINT Rounding(void);
	POINT Truncating(void);
	void operator =(FLOAT_POINT Pt);
	void operator =(POINT Pt);
	void operator +=(FLOAT_POINT Pt);
	void operator +=(POINT Pt);
	FLOAT_POINT operator +(FLOAT_POINT Pt);
	FLOAT_POINT operator +(POINT Pt);
	void operator -=(FLOAT_POINT Pt);
	void operator -=(POINT Pt);
	FLOAT_POINT operator -(FLOAT_POINT Pt);
	FLOAT_POINT operator -(POINT Pt);
	double Norm(void);
	BOOL Normalize(void);
	static BOOL CrossPointOfLines(FLOAT_POINT *pCrossPt, FLOAT_POINT DtOnLn1, double SlopeLn1, FLOAT_POINT DtOnLn2, double SlopeLn2);
	static double DistanceBetweenPts(FLOAT_POINT Pt1 , FLOAT_POINT Pt2);
};

