#include "StdAfx.h"
#include "SetUserInfo.h"
#include "SetUserInfoDlg.h"

CSetUserInfo::CSetUserInfo(LPCTSTR pName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level, BOOL NewAccount, BOOL FixLevel, BOOL FixName)
	: mNewAccount(NewAccount)
	, mUserName(pName == NULL || NewAccount ? _T("") : pName)
	, mPassword(pPassword == NULL || NewAccount ? _T("") : pPassword)
	, mLevel(Level)
	, mFixLevel(FixLevel)
	, mFixName(FixName)
{
}


CSetUserInfo::~CSetUserInfo(void)
{
}


BOOL CSetUserInfo::Doing(CString &UserName, CString &Password, ENUM_ACCOUNT_LEVEL &Level)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSetUserInfoDlg dlg(mUserName, mPassword, mLevel, mNewAccount, mFixLevel, mFixName) ;
	if(dlg.DoModal() == IDOK)
	{
		UserName = dlg.mUserName ;
		Password = dlg.mPassword ;
		Level = dlg.mLevel ;
		return UserName.GetLength() > 0 ;
	}
	else
		return FALSE ;
}
