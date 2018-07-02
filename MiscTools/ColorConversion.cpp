#include "StdAfx.h"
#include "ColorConversion.h"
#include <math.h>

CColorConversion::CColorConversion(void)
{
}


CColorConversion::~CColorConversion(void)
{
}


void CColorConversion::HSV_TO_RGB(int hue, float sat, float val, BYTE * pRed, BYTE * pGreen, BYTE * pBlue)
{
	hue = (hue + 360) % 360 ;
	int intH = hue / 60 ;
	float fltH = (float)(hue % 60) / 60.0f ;
	BYTE p = (BYTE)(val * (1.0f - sat) * MAX_CLR_VAL) ;
	BYTE q = (BYTE)(val * (1.0f - fltH * sat) * MAX_CLR_VAL) ;
	BYTE t = (BYTE)(val * (1.0f - (1.0f - fltH) * sat) * MAX_CLR_VAL) ;
	BYTE v =  (BYTE)(val* MAX_CLR_VAL) ;
	switch(intH)
	{
	case 0 :
		*pRed = v ;
		*pGreen = t ;
		*pBlue = p ;
		break ;
	case 1 :
		*pRed = q ;
		*pGreen = v ;
		*pBlue = p ;
		break ;
	case 2 :
		*pRed = p ;
		*pGreen = v ;
		*pBlue = t ;
		break ;
	case 3 :
		*pRed = p ;
		*pGreen = q ;
		*pBlue = v ;
		break ;
	case 4 :
		*pRed = t ;
		*pGreen = p ;
		*pBlue = v ;
		break ;
	case 5 :
		*pRed = v ;
		*pGreen = p ;
		*pBlue = q ;
		break ;
	default :
		*pRed = *pGreen = *pBlue = v ;
		break ;
	}
}


void CColorConversion::RGB_TO_HSV(BYTE red, BYTE green, BYTE blue, int * pHue, float * pSat, float * pVal)
{
	RGB_TO_HSV_HLS(red, green, blue, pHue, pSat, pVal, NULL, NULL) ;
}


void CColorConversion::HLS_TO_RGB(int hue, float level, float sat, BYTE * pRed, BYTE * pGreen, BYTE * pBlue)
{
	float q = level < 0.5f ? (level * (1.0f + sat)) : (level + sat * (1.0f - level)) ;
	float p = 2.0f * level - q ;
	hue = (hue + 360) % 360 ;
	float red, green, blue ;

	int tR = (hue + 120) % 360 ;
	if(tR < 60)
		red = p + ((q - p)  * tR / 60) ;
	else if(tR < 180)
		red = q ;
	else if(tR < 240)
		red = p + ((q-p) * (240 - tR) / 60) ;
	else
		red = p ;
	
	int tG = hue ;
	if(tG < 60)
		green = p + ((q - p)  * tG / 60) ;
	else if(tG < 180)
		green = q ;
	else if(tG < 240)
		green = p + ((q-p) * (240 - tG) / 60) ;
	else
		green = p ;
	
	int tB = (hue - 120 + 360) % 360 ;
	if(tB < 60)
		blue = p + ((q - p)  * tB / 60) ;
	else if(tB < 180)
		blue = q ;
	else if(tB < 240)
		blue = p + ((q-p) * (240 - tB) / 60) ;
	else
		blue = p ;

	//if(red < 0.0f)
	//	pRed = 0 ;
	//else if(red > 1.0f)
	//	*pRed = MAX_CLR_VAL ;
	//else
		*pRed = (BYTE)(red * MAX_CLR_VAL) ;
	//if(green < 0.0f)
	//	*pGreen = 0 ;
	//else if(green > 1.0f)
	//	*pGreen = MAX_CLR_VAL ;
	//else
		*pGreen = (BYTE)(green * MAX_CLR_VAL) ;
	//if(blue < 0.0f)
	//	*pBlue = 0 ;
	//else if(blue > 1.0f)
	//	*pBlue = MAX_CLR_VAL ;
	//else
		*pBlue = (BYTE)(blue * MAX_CLR_VAL) ;
}


void CColorConversion::RGB_TO_HLS(BYTE red , BYTE green , BYTE blue , int * pHue, float * pLevel, float * pSat)
{
	RGB_TO_HSV_HLS(red, green, blue, pHue, NULL, NULL, pSat, pLevel) ;
}


void CColorConversion::RGB_TO_HSV_HLS(BYTE red, BYTE green, BYTE blue, int * pHue, float * pSat_HSV, float * pValue, float * pSat_HLS, float * pLevel)
{

	int maxChnl = red > green ? (red > blue ? red : blue) : (green > blue ? green : blue) ;
	int minChnl = red < green ? (red < blue ? red : blue) : (green < blue ? green : blue) ;
	if(maxChnl == minChnl)
		*pHue = 0 ;
	else 
	{
		if(maxChnl == red)
		{
			if(green >= blue)
				*pHue = 60 * (green - blue) / (maxChnl - minChnl) ;
			else
				*pHue = 360 + 60 * (green - blue) / (maxChnl - minChnl) ;
		}
		else if(maxChnl == green)
			*pHue = 120 + 60 * (blue - red) / (maxChnl - minChnl) ;
		else
			*pHue = 240 + 60 * (red - green) / (maxChnl - minChnl) ;
	}
	float lev = (maxChnl + minChnl) / 2.0f ;

	if(pLevel != NULL)
		*pLevel = lev / (float)MAX_CLR_VAL ;
	if(pSat_HLS != NULL)
	{
		if(maxChnl == minChnl)
			*pSat_HLS = 0.0f ;
		else if(lev <= MAX_CLR_VAL / 2)
			*pSat_HLS = (float)(maxChnl - minChnl) / (float)(maxChnl + minChnl) ;
		else
			*pSat_HLS = (float)(maxChnl - minChnl) / (2.0f * MAX_CLR_VAL - (maxChnl + minChnl)) ;
	}

	if(pValue != NULL)
		*pValue = (float)maxChnl / (float)MAX_CLR_VAL ;
	if(pSat_HSV != NULL)
	{
		if(maxChnl == 0)
			*pSat_HSV = 0.0f ;
		else
			*pSat_HSV = (float)(maxChnl - minChnl) / (float)maxChnl ;
	}
}
