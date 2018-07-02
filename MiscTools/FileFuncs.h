#pragma once
#include "PubMacroDef.h"

class DllExport CFileFuncs
{
public:
	CFileFuncs(void);
	~CFileFuncs(void);
	static BOOL BrowseAndGetPathName(CString & PathName);
};

