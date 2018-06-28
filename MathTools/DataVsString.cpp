#include "StdAfx.h"
#include "DataVsString.h"


CDataVsString::CDataVsString(void)
{
}


CDataVsString::~CDataVsString(void)
{
}


WCHAR * CDataVsString::IntToString(int val, int minCntChar )
{
	int IdxChar = MAX_SIZE_CHAR ;
	mCharBuf[--IdxChar] = '\0' ;
	bool Signed = false ;
	if(val < 0)
	{
		Signed = true ;
		val = -val ;
	}
	do
	{
		mCharBuf[--IdxChar] = (val % 10) + '0' ;
		val /= 10 ;
	} while(val != 0 && IdxChar > 1) ;
	if(Signed)
		mCharBuf[--IdxChar] = '-' ;
	while(MAX_SIZE_CHAR - IdxChar < minCntChar)
		mCharBuf[--IdxChar] = ' ' ;
	return mCharBuf + IdxChar ;
}

WCHAR * CDataVsString::HexToString(unsigned int val, int minCntChar)
{
	int IdxChar = MAX_SIZE_CHAR ;
	mCharBuf[--IdxChar] = '\0' ;

	do
	{
		int HalfByte = val & 0x0f ;
		mCharBuf[--IdxChar] = HalfByte + (HalfByte > 9 ? 'A'-10 : '0') ;
		val >>= 4 ;
	} while(val != 0 && IdxChar > 1) ;
	while(MAX_SIZE_CHAR - IdxChar < minCntChar)
		mCharBuf[--IdxChar] = '0' ;
	return mCharBuf + IdxChar ;
}


WCHAR * CDataVsString::FloatToString(double val, int precision, BOOL rounding, int minCntChar )
{
	if(precision == 0)
		return IntToString((int)val, minCntChar) ;
	else
	{
		bool Signed = false ;
		if(val < 0)
		{
			Signed = true ;
			val = -val ;
		}
		for(int i = 0 ; i < precision ; ++i)
			val *= 10 ;
		int	intVal = rounding ? ROUNDING(val) : (int)(val) ;

		int IdxChar = MAX_SIZE_CHAR ;
		mCharBuf[--IdxChar] = '\0' ;
		for(int i = 0 ; i < precision ; ++i)
		{
			mCharBuf[--IdxChar] = intVal % 10 + '0' ;
			intVal /= 10 ;
		}
		mCharBuf[--IdxChar] = '.' ;

		do
		{
			mCharBuf[--IdxChar] = (intVal % 10) + '0' ;
			intVal /= 10 ;
		} while(intVal != 0 && IdxChar > 1) ;
		if(Signed)
			mCharBuf[--IdxChar] = '-' ;
		while(MAX_SIZE_CHAR - IdxChar < minCntChar)
			mCharBuf[--IdxChar] = ' ' ;
		return mCharBuf + IdxChar ;
	}
}
