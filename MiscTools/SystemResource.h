#pragma once
#include "PubMacroDef.h"
class DllExport CSystemResource
{
public:
	CSystemResource(void);
	~CSystemResource(void);
public :
	static int GetValidCommPort(CString * pNameList, CString * pPortList, int MaxCnt);
	int PipeSystemCommand(const WCHAR *pCmdStr, BYTE *pBuf, int MaxBufSize);
};

