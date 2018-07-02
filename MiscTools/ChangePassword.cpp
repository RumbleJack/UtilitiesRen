#include "StdAfx.h"
#include "ChangePassword.h"
#include "ChangePasswordDlg.h"

CChangePassword::CChangePassword(LPCTSTR pName, LPCTSTR pPassword)
	: mUserName(pName)
	, mPassword(pPassword)
{
}


CChangePassword::~CChangePassword(void)
{
}


BOOL CChangePassword::Doing(CString & NewPassword)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CChangePasswordDlg dlg(mUserName, mPassword) ;
	if(dlg.DoModal() == IDOK)
	{
		NewPassword = dlg.mNewPassword ;
		return TRUE ;
	}
	else
		return FALSE ;
}
