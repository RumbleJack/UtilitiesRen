#pragma once
#include "UserInfoDef.h"
class __declspec(dllexport) CSetUserInfo
{
public:
	CSetUserInfo(LPCTSTR pName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level, BOOL NewAccount = TRUE, BOOL FixLevel = FALSE, BOOL FixName = FALSE);
	~CSetUserInfo(void);
private :
	CString mUserName ;
	CString mPassword ;
	ENUM_ACCOUNT_LEVEL	mLevel ;
	BOOL mNewAccount ;
	BOOL mFixLevel ;
	BOOL mFixName ;
public:
	BOOL Doing(CString &UserName, CString &Password, ENUM_ACCOUNT_LEVEL &Level);
};

