#pragma once
#include "PubMacroDef.h"
#include "FloatPoint.h"
#include "FloatLine.h"
typedef struct
{
	double left, top, right, bottom ;
} FLOAT_RECT ;

typedef struct
{
	double cx, cy ;
} FLOAT_SIZE ;

class DllExport CFloatRect : public FLOAT_RECT
{
public:
	CFloatRect(void);
	CFloatRect(double l, double t, double r, double b);
	CFloatRect(FLOAT_RECT rect);
	CFloatRect(RECT rect);
	CFloatRect(FLOAT_POINT TopLeft, FLOAT_POINT BottomRight);
	CFloatRect(POINT TopLeft, POINT BottomRight);
	CFloatRect(FLOAT_POINT TopLeft, FLOAT_SIZE size);
	CFloatRect(POINT TopLeft, SIZE size);
	~CFloatRect(void);
private :
	void Exchange(double &x, double &y)
	{
		double z = x ;
		x = y ;
		y = z ;
	}

public :
	RECT Rounding(void);
	RECT Truncating(void);
	double Width(void);
	double Height(void);
	double Area(void);
	FLOAT_POINT CenterPoint(void);
	FLOAT_POINT TopLeft(void);
	FLOAT_POINT TopRight(void);
	FLOAT_POINT BottomLeft(void);
	FLOAT_POINT BottomRight(void);
	void operator =(FLOAT_RECT rect);
	void operator =(RECT rect);
	void InflateRect(double cx, double cy);
	void InflateRect(FLOAT_SIZE size);
	void InflateRect(double l, double t, double r, double b);
	void InflateRect(FLOAT_RECT rect);
	void DeflateRect(double cx, double cy);
	void DeflateRect(FLOAT_SIZE size);
	void DeflateRect(double l, double t, double r, double b);
	void DeflateRect(FLOAT_RECT rect);
	void MoveTo(double x, double y);
	void MoveTo(FLOAT_POINT Pt);
	void Offset(double x, double y);
	void Offset(FLOAT_POINT Pt);
	void Offset(FLOAT_RECT rect);
	FLOAT_SIZE Size(void);
	void Normalize(void);
	BOOL PtInRect(double x, double y);
	BOOL PtInRect(FLOAT_POINT pt);
	BOOL Intersect(FLOAT_RECT rect1, FLOAT_RECT rect2);
	void Union(FLOAT_RECT rect1, FLOAT_RECT rect2);
	void operator += (FLOAT_POINT pt);
	void operator +=(FLOAT_RECT rect);
	void operator -=(FLOAT_POINT pt);
	void operator -=(FLOAT_RECT rect);
	FLOAT_RECT operator +(FLOAT_POINT pt);
	FLOAT_RECT operator +(FLOAT_RECT rect);
	FLOAT_RECT operator -(FLOAT_RECT rect);
	FLOAT_RECT operator -(FLOAT_POINT pt);
	BOOL IntersectLine(FLOAT_LINE & lnInRect, FLOAT_LINE refLn);
	int IntersectLine(FLOAT_POINT * pCrossPt, FLOAT_POINT lnEnd1 , FLOAT_POINT lnEnd2);
};

