#pragma once
class __declspec(dllexport) CChangePassword
{
public:
	CChangePassword(LPCTSTR pName, LPCTSTR pPassword);
	~CChangePassword(void);
	BOOL Doing(CString & NewPassword);
private :
	CString mUserName ;
	CString mPassword ;
};

