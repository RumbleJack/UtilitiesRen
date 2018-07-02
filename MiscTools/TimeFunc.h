#pragma once
#include "PubMacroDef.h"


#define CNT_MONTH  12
#define FIRST_DAY		1
#define IDX_JANUARY 1
#define IDX_DECEMBER	12
#define IDX_MONTH_TO_ARRAY(x) ((x)-IDX_JANUARY)

const int CNT_MONTH_DAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;
const int CNT_MONTH_DAY_LEAP_YEAR[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;
const int ACCUMULATIVE_DAY[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 373, 304, 334} ; 
const int ACCUMULATIVE_DAY_LEAP_YEAR[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335} ;

#define CHECK_LEAP_YEAR(yy) (((yy)&3) ? 0 : 1)
#define TOTAL_DAYS_THE_YEAR(yy) (365+CHECK_LEAP_YEAR(yy))
class DllExport CTimeFunc
{
public:
	CTimeFunc(void);
	~CTimeFunc(void);
private :
	template <class T_DATA>
	static void XchgData(T_DATA &src, T_DATA &dst)
	{
		T_DATA tmp = src ;
		src = dst ;
		dst = tmp ;
	}

	static int GetAccumulateMonthDay(int year, int month)
	{
		if(month >= IDX_JANUARY && month <= IDX_DECEMBER)
		{
			int idxMonth = IDX_MONTH_TO_ARRAY(month) ;
			return CHECK_LEAP_YEAR(year) ? ACCUMULATIVE_DAY_LEAP_YEAR[idxMonth] : ACCUMULATIVE_DAY[idxMonth] ;
		}
		else return 0 ;
	}

	static int GetMonthDay(int year, int month)
	{
		if(month >= IDX_JANUARY && month <= IDX_DECEMBER)
		{
			int idxMonth = IDX_MONTH_TO_ARRAY(month) ;
			return CHECK_LEAP_YEAR(year) ? CNT_MONTH_DAY_LEAP_YEAR[idxMonth] : CNT_MONTH_DAY[idxMonth] ;
		}
		else return 0 ;
	}

public :
	static int GetAccumulativeDays(int Year, int month, int day) ;
	static int GetDayElapsed(long BeginPackedDate, long EndPackedDate);
	static long GetNewPackedDate(long ReferDay, int IntervalDays);
	static BOOL FindDateFromAccumulativeDays(int Year, int AccumDay, int & Month, int & Day);
};

