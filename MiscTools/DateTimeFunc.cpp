#include "StdAfx.h"
#include "DateTimeFunc.h"


CDateTimeFunc::CDateTimeFunc(void)
{
}


CDateTimeFunc::~CDateTimeFunc(void)
{
}


DWORD CDateTimeFunc::GetCurrentPackedDate(void)
{
	SYSTEMTIME	tm ;	
	::GetLocalTime(&tm) ;
	return MAKE_DATE(tm.wYear, tm.wMonth, tm.wDay) ;
}


DWORD CDateTimeFunc::GetPackedCurrentTime(void)
{
	SYSTEMTIME	tm ;	
	::GetLocalTime(&tm) ;
	return MAKE_TIME(tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds/10);
}

int CDateTimeFunc::GetDaysEachMonth(int Year, int *pDay)
{	
	*pDay++ = 31 ;
	*pDay++ = Year % 4 == 0 ? 29 : 28 ;
	*pDay++ = 31 ;
	*pDay++ = 30 ;
	*pDay++ = 31 ;
	*pDay++ = 30 ;
	*pDay++ = 31 ;
	*pDay++ = 31 ;
	*pDay++ = 30 ;
	*pDay++ = 31 ;
	*pDay++ = 30 ;
	*pDay = 31 ;

	return Year % 4 == 0 ? 366 : 365 ;
}

int CDateTimeFunc::PassedDays(int Year, int Month, int Day)
{
	int Days[12] ;
	GetDaysEachMonth(Year, Days) ;
	int CntDays = 0 ;
	for(int i = 1 ; i <= Month - 1 ; ++i)
		CntDays += Days[i-1] ;
	CntDays += Day ;
	return CntDays ;
}

int CDateTimeFunc::RemainedDaysInTheYear(int Year, int Month, int Day)
{
	return (Year % 4 == 0 ? 366 : 365) - PassedDays(Year, Month, Day) ;
}

BOOL CDateTimeFunc::CheckRemainedDay(int RefYear, int RefMonth, int RefDay, int &RemainDay) 
{
	SYSTEMTIME	tm ;	
	::GetLocalTime(&tm) ;

	int PassedDaysThisYear = PassedDays(tm.wYear, tm.wMonth, tm.wDay) ;
	int CntDaysRefYear = PassedDays(RefYear, RefMonth, RefDay) ;
	for(int i = tm.wYear ; i < RefYear ; ++i)
		CntDaysRefYear += i % 4 == 0 ? 366 : 365 ;
	RemainDay = CntDaysRefYear - PassedDaysThisYear ;
	return RemainDay >= 0 ;
}