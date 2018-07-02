#include "StdAfx.h"
#include "TimeFunc.h"


CTimeFunc::CTimeFunc(void)
{
}


CTimeFunc::~CTimeFunc(void)
{
}


int CTimeFunc::GetAccumulativeDays(int Year, int month, int day)
{
	if(month >= IDX_JANUARY && month <= IDX_DECEMBER)
		return GetAccumulateMonthDay(Year, month) + day ;
	else
		return 0 ;
}


int CTimeFunc::GetDayElapsed(long BeginPackedDate, long EndPackedDate)
{
	int Sign = 1 ;
	if(EndPackedDate < BeginPackedDate)
	{
		Sign = -1 ;
		XchgData(BeginPackedDate, EndPackedDate) ;
	}

	int BeginYear, BeginMonth, BeginDay ;
	FIND_DATE(BeginPackedDate, BeginYear, BeginMonth, BeginDay) ;
	int EndYear, EndMonth, EndDay ;
	FIND_DATE(EndPackedDate, EndYear, EndMonth, EndDay) ;
	int CntDayToBeginYear = GetAccumulativeDays(BeginYear, BeginMonth, BeginDay) ;
	int CntDayToEndYear = GetAccumulativeDays(EndYear, EndMonth, EndDay) ;
	if(BeginYear == EndYear)
		return (CntDayToEndYear - CntDayToBeginYear) * Sign ;
	else
	{
		CntDayToEndYear += TOTAL_DAYS_THE_YEAR(BeginYear) - CntDayToBeginYear ;
		while(++BeginYear < EndYear)
			CntDayToEndYear += TOTAL_DAYS_THE_YEAR(BeginYear) ;
		return CntDayToEndYear * Sign ;
	}
}


long CTimeFunc::GetNewPackedDate(long ReferDay, int IntervalDays)
{
	if(IntervalDays == 0)
		return ReferDay ;

	int Year, Month, Day ;
	FIND_DATE(ReferDay, Year, Month, Day) ;
	if(IntervalDays > 0)
	{
		int AccumDay =  GetAccumulativeDays(Year, Month, Day) ;
		while(TOTAL_DAYS_THE_YEAR(Year) - AccumDay < IntervalDays)
		{
			IntervalDays -= TOTAL_DAYS_THE_YEAR(Year) - AccumDay ;
			++Year ;
			AccumDay = 1 ;
		}
		FindDateFromAccumulativeDays(Year, AccumDay+IntervalDays, Month, Day) ;
	}
	else
	{
		IntervalDays *= -1 ;
		int AccumDay = GetAccumulativeDays(Year, Month, Day) ;
		while(AccumDay <= IntervalDays)
		{
			IntervalDays -= AccumDay ;
			--Year ;
			AccumDay = TOTAL_DAYS_THE_YEAR(Year)  ;
		}
		FindDateFromAccumulativeDays(Year, AccumDay-IntervalDays, Month, Day) ;
	}
	return MAKE_DATE(Year, Month, Day) ;
}


BOOL CTimeFunc::FindDateFromAccumulativeDays(int Year, int AccumDay, int & Month, int & Day)
{
	if(AccumDay >= 1 && AccumDay <= TOTAL_DAYS_THE_YEAR(Year))
	{
		 Month = IDX_JANUARY +1 ; 
		while(Month <= IDX_DECEMBER && GetAccumulateMonthDay(Year, Month) < AccumDay)
			++Month ;
		--Month ;
		Day = AccumDay - GetAccumulateMonthDay(Year, Month) ;
		return TRUE ;
	}
	else
		return FALSE ;
}
