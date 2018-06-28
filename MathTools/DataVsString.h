#pragma once
#include "PubMacroDef.h"
#define MAX_SIZE_CHAR	50

class DllExport CDataVsString
{
public:
	CDataVsString(void);
	~CDataVsString(void);

protected :
	WCHAR mCharBuf[MAX_SIZE_CHAR] ;
public:
	WCHAR * IntToString(int val, int minCntChar = 0);
	WCHAR * FloatToString(double val, int precision, BOOL rounding = TRUE, int minCntChar = 0);
	WCHAR * HexToString(unsigned int val, int minCntChar = 2) ;
};

