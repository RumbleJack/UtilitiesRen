#include "StdAfx.h"
#include "StringFunc.h"
#include "TimeFunc.h"

CStringFunc::CStringFunc(void)
{
}


CStringFunc::~CStringFunc(void)
{
}

LPCTSTR CStringFunc::DateTimeToString(long PackedDate, long PackedTime, STYLE_DATE_TIME_TO_STRING style, LPCTSTR pPrefix, LPCTSTR pPostfix, LPCTSTR pDateSeparator, LPCTSTR pTimeSeparator)
{
	static CString outStr ;
	outStr = _T("") ;
	if(pPrefix != NULL)
		outStr = pPrefix ;
	CString SubItem ;
	if(style.Year)
	{
		SubItem.Format(_T("%02d"), GET_YEAR(PackedDate) % 100) ;
		outStr += SubItem ;
		if(pDateSeparator != NULL)
			outStr += pDateSeparator ;
	}
	if(style.Month)
	{
		SubItem.Format(_T("%02d"), GET_MONTH(PackedDate)) ;
		outStr += SubItem ;
		if(pDateSeparator != NULL)
			outStr += pDateSeparator ;
	}
	if(style.Day)
	{
		SubItem.Format(_T("%02d"), GET_DAY(PackedDate)) ;
		outStr += SubItem ;
		if(pDateSeparator != NULL)
			outStr += pDateSeparator ;
	}
	if(style.Hour)
	{
		SubItem.Format(_T("%02d"), GET_HOUR(PackedTime)) ;
		outStr += SubItem ;
	}
	if(style.Minute)
	{
		if(pTimeSeparator != NULL)
			outStr += pTimeSeparator ;
		SubItem.Format(_T("%02d"), GET_MINUTE(PackedTime)) ;
		outStr += SubItem ;
	}
	if(style.Second)
	{
		if(pTimeSeparator != NULL)
			outStr += pTimeSeparator ;
		SubItem.Format(_T("%02d"), GET_SECOND(PackedTime)) ;
		outStr += SubItem ;
	}
	if(style.DeciSecond)
	{
		if(pTimeSeparator != NULL)
			outStr += pTimeSeparator ;
		SubItem.Format(_T("%0d"), GET_CENTISECOND(PackedTime)/10) ;
		outStr += SubItem ;
	}
	else if(style.CentiSecond)
	{
		if(pTimeSeparator != NULL)
			outStr += pTimeSeparator ;
		SubItem.Format(_T("%0d"), GET_CENTISECOND(PackedTime)) ;
		outStr += SubItem ;
	}
	if(pPostfix != NULL)
		outStr += pPostfix ;
	return outStr ;
}

LPCTSTR CStringFunc::CurrentDateTimeToString(STYLE_DATE_TIME_TO_STRING style, LPCTSTR pPrefix, LPCTSTR pPostfix, LPCTSTR pDateSeparator, LPCTSTR pTimeSeparator)
{
	SYSTEMTIME	tm ;
	::GetLocalTime(&tm) ;
	long Date = MAKE_DATE(tm.wYear, tm.wMonth, tm.wDay) ;
	long Time = MAKE_TIME(tm.wHour, tm.wMinute, tm.wSecond, (tm.wMilliseconds / 10)) ;
	return DateTimeToString(Date, Time, style, pPrefix, pPostfix, pDateSeparator, pTimeSeparator) ;
}


int CStringFunc::ConvertCharToWChar(const char * pSrc, WCHAR * pDst, int MaxSizeDst)
{
	int CntChar = 0 ;
	while(*pSrc != '\0' && CntChar < MaxSizeDst)
	{
		*pDst++ = *pSrc++ ;
		++CntChar ;
	}
	if(CntChar < MaxSizeDst)
		*pDst = 0 ;

	return CntChar ;
}


int CStringFunc::ConvertWCharToChar(const WCHAR * pSrc, char * pDst, int MaxSizeDst)
{
	int CntChar = 0 ;
	while(*pSrc != _T('\0') && CntChar < MaxSizeDst)
	{
		*pDst++ = (*pSrc++) & 0xff ;
		++CntChar ;
	}
	if(CntChar < MaxSizeDst)
		*pDst = 0 ;
	return CntChar ;
}


int CStringFunc::GetDecIntFromString(LPCTSTR pStr, long * pData, int MaxCntInt)
{
	int CntInt = 0 ;
	int Sign = 1 ;
	int	Value = -1 ;
	while(*pStr != 0 && CntInt < MaxCntInt)
	{
		if(*pStr == _T('-'))
			Sign = -1 ;
		else if(*pStr >= _T('0') && *pStr <= _T('9'))
			Value = Value < 0 ? (*pStr - _T('0'))  : Value * 10 + (*pStr - _T('0')) ;
		else
		{
			if(Value >= 0)
				*(pData + CntInt++) = Value * Sign ;
			Value = -1 ;
			Sign = 1 ;
		}
		++pStr ;
	}
	if(Value >= 0 && CntInt < MaxCntInt)
		*(pData +CntInt++) = Value * Sign ;
	return CntInt;
}


int CStringFunc::GetHexIntFromString(LPCTSTR pStr, long * pData, int MaxCntInt)
{
	int CntInt = 0 ;
	int Sign = 1 ;
	int	Value = -1 ;
	while(*pStr != 0 && CntInt < MaxCntInt)
	{
		if(*pStr == _T('-'))
			Sign = -1 ;
		else if(*pStr >= _T('0') && *pStr <= _T('9'))
			Value = Value < 0 ? (*pStr - _T('0')) : Value * 16 + (*pStr - _T('0')) ;
		else if(*pStr >= _T('a') && *pStr <= _T('f'))
			Value = Value < 0 ? (*pStr - _T('a')+10) : Value * 16 + (*pStr - _T('a')+10) ;
		else if(*pStr >= _T('A') && *pStr <= _T('F'))
			Value = Value < 0 ? (*pStr - _T('A')+10)  : Value * 16 + (*pStr - _T('A')+10) ;
		else
		{
			if(Value >= 0)
				*(pData + CntInt++) = Value * Sign ;
			Value = -1 ;
			Sign = 1 ;
		}
		++pStr ;
	}
	if(Value >= 0 && CntInt < MaxCntInt)
		*(pData +CntInt++) = Value * Sign ;
	return CntInt;
}


int CStringFunc::GetFloatFromString(LPCTSTR pStr, float * pData, int MaxCntData)
{
	int CntInt = 0 ;
	int Sign = 1 ;
	float	Value = -1 ;
	float Fraction = 1.0f ;
	while(*pStr != 0 && CntInt < MaxCntData)
	{
		if(*pStr == _T('-'))
			Sign = -1 ;
		else if(*pStr == _T('.') && Fraction > 0.5f)
		{
			Fraction = 0.1f ;
			if(Value < 0)
				Value = 0.0f ;
		}
		else if(*pStr >= _T('0') && *pStr <= _T('9'))
		{
			if(Fraction > 0.5f)
				Value = Value < 0 ? (*pStr - _T('0')) : Value * 10 + (*pStr - _T('0')) ;
			else
			{
				Value +=   (*pStr - _T('0')) * Fraction ;
				Fraction /= 10.0f ;
			}
		}
		else
		{
			if(Value >= 0)
				*(pData + CntInt++) = Value * Sign ;
			Value = -1 ;
			Sign = 1 ;
			Fraction = 1.0f ;
		}
		++pStr ;
	}
	if(Value >= 0 && CntInt < MaxCntData)
		*(pData +CntInt++) = Value * Sign ;
	return CntInt;
}


void CStringFunc::ShowIntArrayInHex(int CntByte , BYTE * pData, CString & str)
{
	str = _T("") ;
	for(int i = 0 ; i < CntByte ; ++i)
	{
		CString sub ;
		sub.Format(_T("%02X "), *(pData + i)) ;
		str += sub ;
	}
}

void CStringFunc::ShowIntArrayInHex(int CntByte , WORD * pData, CString & str)
{
	str = _T("") ;
	for(int i = 0 ; i < CntByte ; ++i)
	{
		CString sub ;
		sub.Format(_T("%04X "), *(pData + i)) ;
		str += sub ;
	}
}
