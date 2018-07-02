#pragma once
#include "PubMacroDef.h"

class DllExport CColorConversion
{
public:
	#define MAX_CLR_VAL 255

	CColorConversion(void);
	~CColorConversion(void);
	static void HSV_TO_RGB(int hue, float sat, float val, BYTE * pRed, BYTE * pGreen, BYTE * pBlue);
	static void RGB_TO_HSV(BYTE red, BYTE green, BYTE blue, int * pHue, float * pSat, float * pVal);
	static void HLS_TO_RGB(int hue, float level, float sat, BYTE * pRed, BYTE * pGreen, BYTE * pBlue);
	static void RGB_TO_HLS(BYTE red , BYTE green , BYTE blue , int * pHue, float * pLevel, float * pSat);
	static void RGB_TO_HSV_HLS(BYTE red, BYTE green, BYTE blue, int * pHue, float * pSat_HSV, float * pValue, float * pSat_HLS, float * pLevel);
};

