#pragma once


class DllExport CScanIconTest
{
public:
	CScanIconTest();
	~CScanIconTest();

	void TestAScanDataBegin(CScanPanel* );
	void TestAScanDataEnd();
	static UINT AFX_CDECL TestAScanData(LPVOID lpParam = NULL);

	void TestSScanDataBegin(CScanPanel*);
	void TestSScanDataEnd();
	static UINT AFX_CDECL TestSScanData(LPVOID lpParam = NULL);

public:
	CWinThread * mpWorkThread_TestAScanData;
	CWinThread * mpWorkThread_TestSScanData;
};