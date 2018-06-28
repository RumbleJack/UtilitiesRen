#pragma once
class CTimeCost
{
public :
	CTimeCost()
		: mAccumClick.QuadPart(0)
	{
		QueryPerformanceFrequency(&mFreq) ;
	}
	~CTimeCost()
	{
	}
	void StartTiming()
	{
			QueryPerformanceCounter(&mBeginClick) ;
	}
	void StopTiming()
	{
		LARGE_INTEGER		EndClick ;

		QueryPerformanceCounter(&EndClick) ;
		mAccumClick.QuadPart += EndClick.QuadPart - mBeginClick.QuadPart ;
	}
	double GetTimeCostInuS()
	{
		return (double)mAccumClick.QuadPart / (double)Freq.QuadPart * 1000000.0 ;
	}
	void Reset()
	{
		mAccumClick.QuadPart = 0 ;
	}
private :
	LARGE_INTEGER mFreq ;
	LARGE_INTEGER		mAccumClick ;
	LARGE_INTEGER		mBeginClick ;

} ;
