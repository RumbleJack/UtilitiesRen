#pragma once
#include "PubMacroDef.h"

class DllExport CDateTimeFunc
{
public:
	CDateTimeFunc(void);
	~CDateTimeFunc(void);
	static DWORD GetCurrentPackedDate(void);
	static DWORD GetPackedCurrentTime(void);
	static BOOL CheckRemainedDay(int RefYear, int RefMonth, int RefDay, int &RemainDay) ;
	static int PassedDays(int Year, int Month, int Day) ;
	static int RemainedDaysInTheYear(int Year, int Month, int Day) ;
	static int GetDaysEachMonth(int Year, int *pDay) ;
};

