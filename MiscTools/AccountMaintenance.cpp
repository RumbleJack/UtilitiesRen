#include "StdAfx.h"
#include "AccountMaintenance.h"
#include "AdminUserDlg.h"
#include "ChangePasswordDlg.h"
#include "SetUserInfo.h"

CAccountMaintenance::CAccountMaintenance(void)
	: mCntUser(0)
	, mUserList(MAX_CNT_USER)
	, mIdxItem(0)
	, mIdxCurrentUser(-1)
{
}


CAccountMaintenance::~CAccountMaintenance(void)
{
}


int CAccountMaintenance::AddUserList(LPCTSTR pName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level)
{
	if(mCntUser < MAX_CNT_USER)
	{
		mUserList[mCntUser].Name = pName ;
		mUserList[mCntUser].Password = pPassword ;
		mUserList[mCntUser].Level = Level ;
		mUserList[mCntUser].Modified = FALSE ;
		return mCntUser++ ;
	}
	else
		return -1 ;
}


ENUM_ACCOUNT_LEVEL CAccountMaintenance::LoginAccount(LPCTSTR pName, LPCTSTR pPassword)
{
	mIdxCurrentUser = CheckUserInfo(pName, pPassword) ;
	if(mIdxCurrentUser < 0)
		return ILLEGAL ;
	else
	{
		return mUserList[mIdxCurrentUser].Level ;
	}
}

int CAccountMaintenance::CheckUserInfo(LPCTSTR pName, LPCTSTR pPassword)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Name == pName && mUserList[i].Password == pPassword)
			return i ;
	}
	return -1 ;
}

BOOL CAccountMaintenance::CreateAdmin()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSetUserInfo NewUser(NULL, NULL, ADMIN, TRUE, TRUE, FALSE) ;
	CString UserName, Password ;
	ENUM_ACCOUNT_LEVEL Level ;
	if(NewUser.Doing(UserName, Password, Level))
	{
		mUserList[mCntUser].Name = UserName ;
		mUserList[mCntUser].Password = Password ;
		mUserList[mCntUser].Level = Level ;
		mUserList[mCntUser].Modified = TRUE ;
		++mCntUser ;
		return TRUE ;
	}
	else
		return FALSE ;
}

BOOL CAccountMaintenance::ManagingAccount(void)
{
	BOOL Modified = FALSE ;
	if(mCntUser == 0)
	{
		if(CreateAdmin())
			mIdxCurrentUser = 0 ;
		else
			return FALSE ;
	}

	if(CheckValidIdx(mIdxCurrentUser))
	{
		if(mUserList[mIdxCurrentUser].Level == ADMIN)
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			CAdminUserDlg dlg ;
			for(int i = 0 ; i < mCntUser ; ++i)
				dlg.AddUser(mUserList[i].Name, mUserList[i].Password, mUserList[i].Level) ;
			dlg.SetLoginUser(mUserList[mIdxCurrentUser].Name) ;
			if(dlg.DoModal() == IDOK)
			{
				dlg.ResetLoadPos() ;
				STRUCT_ACCOUNT_INFO UserInfo ;
				while(dlg.GetNextUserInfo(UserInfo.Name, UserInfo.Password, UserInfo.Level))
				{
					UpdateUserList(UserInfo) ;
				}
				Modified = TRUE ;
			}
		}
		else if(mUserList[mIdxCurrentUser].Level == OPER || mUserList[mIdxCurrentUser].Level == VISIT)
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			CChangePasswordDlg dlg(mUserList[mIdxCurrentUser].Name,mUserList[mIdxCurrentUser].Password) ;
			if(dlg.DoModal() == IDOK)
			{
				mUserList[mIdxCurrentUser].Password = dlg.mNewPassword ;
				mUserList[mIdxCurrentUser].Modified = TRUE ;
				Modified = TRUE ;
			}
		} 
	}
	return Modified ;
}

BOOL CAccountMaintenance::UpdateUserList(STRUCT_ACCOUNT_INFO UserInfo)
{
	int IdxItem = FindUser(UserInfo.Name) ;
	if(CheckValidIdx(IdxItem))
	{
		if(mUserList[IdxItem].Password != UserInfo.Password || mUserList[IdxItem].Level != UserInfo.Level)
		{
			mUserList[IdxItem] = UserInfo ;
			mUserList[IdxItem].Modified = TRUE ;
			return TRUE ;
		}
		else
			return FALSE ;
		
	}
	else
	{
		IdxItem = AddUserList(UserInfo.Name, UserInfo.Password, UserInfo.Level) ;
		mUserList[IdxItem].Modified = TRUE ;
		return TRUE ;
	}

}

int CAccountMaintenance::FindUser(LPCTSTR pName)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Name == pName)
			return i ;
	}
	return -1 ;
}

ENUM_ACCOUNT_LEVEL CAccountMaintenance::GetCurrentUserLevel(void)
{
	if(mIdxCurrentUser < 0)
		return ILLEGAL ;
	else
	{
		return mUserList[mIdxCurrentUser].Level ;
	}
}


BOOL CAccountMaintenance::CheckUserListModified(void)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Modified)
			return TRUE ;
	}
	return FALSE ;
}

BOOL CAccountMaintenance::GetCurrentUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	
	if(CheckValidIdx(mIdxCurrentUser))
	{
		Name = mUserList[mIdxCurrentUser].Name ;
		Password = mUserList[mIdxCurrentUser].Password ;
		Level = mUserList[mIdxCurrentUser].Level ;
		return TRUE ;
	}
	else
		return FALSE;
}


int CAccountMaintenance::GetCntUser(void)
{
	return mCntUser ;
}



int CAccountMaintenance::GetCntModifiedUser(void)
{
	int CntModified = 0 ;
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Modified)
			++CntModified ;
	}
	return CntModified ;
}



BOOL CAccountMaintenance::GetUserInfo(int IdxItem, CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	if(CheckValidIdx(IdxItem))
	{
		Name = mUserList[IdxItem].Name ;
		Password = mUserList[IdxItem].Password ;
		Level = mUserList[IdxItem].Level ;
		return TRUE ;
	}
	else
		return FALSE ;
}

BOOL CAccountMaintenance::GetNextModifiedUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	while(CheckValidIdx(++mIdxItem))
	{
		if(mUserList[mIdxItem].Modified)
			return GetUserInfo(mIdxItem, Name, Password, Level) ;
	}
	return FALSE;
}


BOOL CAccountMaintenance::GetNextUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	if(CheckValidIdx(++mIdxItem))
		return GetUserInfo(mIdxItem, Name, Password, Level) ;
	else
		return FALSE;
}


void CAccountMaintenance::ResetUserList(void)
{
	mCntUser = 0 ;
	mIdxCurrentUser = -1 ;
}
