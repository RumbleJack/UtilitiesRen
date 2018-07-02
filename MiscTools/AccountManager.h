#pragma once
#include "UserDef.h"
#include "SafeArray.h"

class __declspec(dllexport) CAccountManager
{
public:
	CAccountManager(void);
	~CAccountManager(void);
public :
private :
	CSafeArray <STRUCT_USER_INFO> mUserList ;
	int mIdxCurrentUser ;
	int mCntUser ;
	int	mIdxItem ;
public :
	int AddUserList(LPCTSTR pName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level);
	ENUM_ACCOUNT_LEVEL LoginAccount(LPCTSTR pName, LPCTSTR pPassword);
	BOOL ManagingAccount(void);
	ENUM_ACCOUNT_LEVEL GetCurrentUserLevel(void);
	BOOL CheckUserListModified(void);
	BOOL GetCurrentUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level);
	int GetCntUser(void);
	int GetCntModifiedUser(void);
	BOOL GetModifiedUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level);
	BOOL GetNextModifiedUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level);
	BOOL GetFirstUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level);
	BOOL GetNextUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level);
	void ResetUserList(void);
	BOOL GetUserInfo(int IdxItem, CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level) ;
private :
	int CheckUserInfo(LPCTSTR pName, LPCTSTR pPassword) ;
	BOOL UpdateUserList(STRUCT_USER_INFO UserInfo) ;
	int FindUser(LPCTSTR pName) ;
};

