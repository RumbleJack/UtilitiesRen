#pragma once
#include "PubMacroDef.h"
#include "FloatPoint.h"

typedef struct
{
	FLOAT_POINT end1, end2 ;
} FLOAT_LINE ;

class DllExport CFloatLine : public FLOAT_LINE
{
public:
	CFloatLine(void);
	~CFloatLine(void);
	CFloatLine(float xEnd1, float yEnd1, float xEnd2, float yEnd2);
	CFloatLine(FLOAT_POINT pt1, FLOAT_POINT pt2);
	CFloatLine(POINT pt1, POINT pt2);
	CFloatLine(FLOAT_LINE line);
	void Offset(double x, double y);
	void Offset(FLOAT_POINT pt);
	double Length(void);
	FLOAT_POINT Vector(void);
	BOOL LinesCrossPoint(FLOAT_POINT &crossPt, FLOAT_LINE line);
	BOOL LinesCrossPoint(FLOAT_POINT & crossPt, FLOAT_POINT lnEnd1, FLOAT_POINT lnEnd2);
	void operator =(FLOAT_LINE line);
};

