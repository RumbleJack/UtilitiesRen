#include "StdAfx.h"
#include "AccountManager.h"
#include "AdminUserDlg.h"
#include "ChangePasswordDlg.h"
CAccountManager::CAccountManager(void)
	: mCntUser(0)
	, mUserList(MAX_CNT_USER)
	, mIdxItem(0)
	, mIdxCurrentUser(-1)
{
}


CAccountManager::~CAccountManager(void)
{
}


int CAccountManager::AddUserList(LPCTSTR pName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level)
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


ENUM_ACCOUNT_LEVEL CAccountManager::LoginAccount(LPCTSTR pName, LPCTSTR pPassword)
{
	int mIdxCurrentUser = CheckUserInfo(pName, pPassword) ;
	if(mIdxCurrentUser < 0)
		return ILLEGAL ;
	else
	{
		return mUserList[mIdxCurrentUser].Level ;
	}
}

int CAccountManager::CheckUserInfo(LPCTSTR pName, LPCTSTR pPassword)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Name == pName && mUserList[i].Password == pPassword)
			return i ;
	}
	return -1 ;
}

BOOL CAccountManager::ManagingAccount(void)
{
	if(mIdxCurrentUser >= 0 && mIdxCurrentUser < mCntUser)
	{
		if(mUserList[mIdxCurrentUser].Level == ADMIN)
		{
			CAdminUserDlg dlg ;
			for(int i = 0 ; i < mCntUser ; ++i)
				dlg.AddUser(mUserList[i].Name, mUserList[i].Password, mUserList[i].Level) ;
			if(dlg.DoModal() == IDOK)
			{
				STRUCT_USER_INFO UserInfo ;
				while(dlg.GetNextUserInfo(UserInfo.Name, UserInfo.Password, UserInfo.Level))
				{
					UpdateUserList(UserInfo) ;
				}
				return TRUE ;
			}
			else
				return FALSE ;
		}
		else if(mUserList[mIdxCurrentUser].Level == OPER || mUserList[mIdxCurrentUser].Level == VISIT)
		{
			CChangePasswordDlg dlg(mUserList[mIdxCurrentUser].Name,mUserList[mIdxCurrentUser].Password) ;
			if(dlg.DoModal() == IDOK)
			{
				mUserList[mIdxCurrentUser].Password = dlg.mNewPassword ;
				mUserList[mIdxCurrentUser].Modified = TRUE ;
				return TRUE ;
			}
			else
				return FALSE ;
		} 
	}
	else
		return FALSE ;
}

BOOL CAccountManager::UpdateUserList(STRUCT_USER_INFO UserInfo)
{
	int IdxItem = FindUser(UserInfo.Name) ;
	if(IdxItem >= 0 && IdxItem < mCntUser)
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

int CAccountManager::FindUser(LPCTSTR pName)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Name == pName)
			return i ;
	}
	return -1 ;
}

ENUM_ACCOUNT_LEVEL CAccountManager::GetCurrentUserLevel(void)
{
	if(mIdxCurrentUser < 0)
		return ILLEGAL ;
	else
	{
		return mUserList[mIdxCurrentUser].Level ;
	}
}


BOOL CAccountManager::CheckUserListModified(void)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Modified)
			return TRUE ;
	}
	return FALSE ;
}

BOOL CAccountManager::GetCurrentUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	
	if(mIdxCurrentUser >= 0 && mIdxCurrentUser < mCntUser)
	{
		Name = mUserList[mIdxCurrentUser].Name ;
		Password = mUserList[mIdxCurrentUser].Password ;
		Level = mUserList[mIdxCurrentUser].Level ;
		return TRUE ;
	}
	else
		return FALSE;
}


int CAccountManager::GetCntUser(void)
{
	return mCntUser ;
}



int CAccountManager::GetCntModifiedUser(void)
{
	int CntModified = 0 ;
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Modified)
			++CntModified ;
	}
	return CntModified ;
}



BOOL CAccountManager::GetModifiedUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	for(int i = 0 ; i < mCntUser ; ++i)
	{
		if(mUserList[i].Modified)
		{
			mIdxItem = i ;
			return GetUserInfo(mIdxItem, Name, Password, Level) ;
		}
	}
	return FALSE ;
}

BOOL CAccountManager::GetUserInfo(int IdxItem, CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	if(IdxItem >= 0 && IdxItem < mCntUser)
	{
		Name = mUserList[IdxItem].Name ;
		Password = mUserList[IdxItem].Password ;
		Level = mUserList[IdxItem].Level ;
		return TRUE ;
	}
	else
		return FALSE ;
}

BOOL CAccountManager::GetNextModifiedUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	while(++mIdxItem < mCntUser)
	{
		if(mUserList[mIdxItem].Modified)
			return GetUserInfo(mIdxItem, Name, Password, Level) ;
	}
	return FALSE;
}


BOOL CAccountManager::GetFirstUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	if(mCntUser > 0)
	{
		mIdxItem = 0 ;
		return GetUserInfo(mIdxItem, Name, Password, Level) ;
	}
	else
		return FALSE ;
}


BOOL CAccountManager::GetNextUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL &Level)
{
	if(++mIdxItem < mCntUser)
		return GetUserInfo(mIdxItem, Name, Password, Level) ;
	else
		return FALSE;
}


void CAccountManager::ResetUserList(void)
{
	mCntUser = 0 ;
	mIdxCurrentUser = -1 ;
}
