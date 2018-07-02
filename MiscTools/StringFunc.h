#pragma once
#include "PubMacroDef.h"

class DllExport CStringFunc
{
public:
	CStringFunc(void);
	~CStringFunc(void);
public :
	typedef struct
	{
		unsigned Year : 1 ;
		unsigned Month : 1 ;
		unsigned Day : 1 ;
		unsigned Hour : 1 ;
		unsigned Minute : 1 ;
		unsigned Second : 1 ;
		unsigned DeciSecond : 1 ;
		unsigned CentiSecond : 1 ;
	} STYLE_DATE_TIME_TO_STRING ;

	static LPCTSTR CurrentDateTimeToString(STYLE_DATE_TIME_TO_STRING style, LPCTSTR pPrefix, LPCTSTR pPostfix, LPCTSTR pDateSeparator, LPCTSTR pTimeSeparator);
	static LPCTSTR DateTimeToString(long PackedDate, long PackedTime, STYLE_DATE_TIME_TO_STRING style, LPCTSTR pPrefix, LPCTSTR pPostfix, LPCTSTR pDateSeparator, LPCTSTR pTimeSeparator);
	static int ConvertCharToWChar(const char * pSrc, WCHAR * pDst, int MaxSizeDst);
	static int ConvertWCharToChar(const WCHAR * pSrc, char * pDst, int MaxSizeDst);
	template <class T_SRC, class T_DST>
	static BOOL  CompareStringWithMixCharType(T_SRC *pSrc, T_DST *pDst)
	{
		BOOL Equ = TRUE ;
		while((*pSrc & 0xff) != 0 && (*pDst & 0xff) != 0)
		{
			if((*pSrc++ & 0xff) != (*pDst++ & 0xff))
			{
				Equ = FALSE ;
				break ;
			}
		}
		if((*pSrc & 0xff) == 0 && (*pDst & 0xff) == 0)
			return Equ ;
		else
			return FALSE ;
	}
	static int GetDecIntFromString(LPCTSTR pStr, long * pData, int MaxCntInt);
	static int GetHexIntFromString(LPCTSTR pStr, long * pData, int MaxCntInt);
	static int GetFloatFromString(LPCTSTR pStr, float * pData, int MaxCntData);
	static void ShowIntArrayInHex(int CntByte , BYTE * pData, CString & str);
	static void ShowIntArrayInHex(int CntByte , WORD * pData, CString & str);
};

