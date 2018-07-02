// ChangePasswordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MiscTools.h"
#include "ChangePasswordDlg.h"
#include "afxdialogex.h"


// CChangePasswordDlg 对话框

IMPLEMENT_DYNAMIC(CChangePasswordDlg, CDialogEx)

CChangePasswordDlg::CChangePasswordDlg(LPCTSTR pUserName, LPCTSTR pUserPassword)
	: CDialogEx(CChangePasswordDlg::IDD, NULL)
	, mUserName(pUserName)
	, mUserPassword(pUserPassword)
	, mOldPassword(_T(""))
	, mNewPassword(_T(""))
	, mVerifyPassword(_T(""))
	, mShowChar(FALSE)
{

}

CChangePasswordDlg::~CChangePasswordDlg()
{
}

void CChangePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, mUserName);
	DDX_Text(pDX, IDC_OLD_PASSWORD, mOldPassword);
	DDX_Text(pDX, IDC_NEW_PASSWORD, mNewPassword);
	DDX_Text(pDX, IDC_REPEAT_PASSWORD, mVerifyPassword);
	DDX_Check(pDX, IDC_CHECK_SHOW_CHAR, mShowChar);
}


BEGIN_MESSAGE_MAP(CChangePasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangePasswordDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_SHOW_CHAR, &CChangePasswordDlg::OnBnClickedCheckShowChar)
END_MESSAGE_MAP()


// CChangePasswordDlg 消息处理程序
BOOL CChangePasswordDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE ;
		if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == GetDlgItem(IDC_OLD_PASSWORD)->GetSafeHwnd())
			{
				NextStep(1) ;
				return TRUE ;
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_NEW_PASSWORD)->GetSafeHwnd())
			{
				NextStep(2) ;
				return TRUE ;
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_REPEAT_PASSWORD)->GetSafeHwnd())
			{
				NextStep(3) ;
				return TRUE ;
			}
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


int CChangePasswordDlg::NextStep(int IdxStep)
{
	switch(IdxStep)
	{
	case 0:
		GetDlgItem(IDC_OLD_PASSWORD)->EnableWindow(TRUE) ;
		GetDlgItem(IDC_NEW_PASSWORD)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_REPEAT_PASSWORD)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_OLD_PASSWORD)->SetFocus() ;
		break ;
	case 1 :
		UpdateData(TRUE) ;
		if(mUserPassword == mOldPassword)
		{
			GetDlgItem(IDC_NEW_PASSWORD)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_NEW_PASSWORD)->SetFocus() ;
		}
		else
		{
			MessageBox(_T("原密码错误"), NULL, MB_ICONQUESTION) ;
			SetDlgItemText(IDC_OLD_PASSWORD, _T("")) ;
			GetDlgItem(IDC_OLD_PASSWORD)->SetFocus() ;
		}
		break ;
	case 2 :
		GetDlgItem(IDC_REPEAT_PASSWORD)->EnableWindow(TRUE) ;
		GetDlgItem(IDC_REPEAT_PASSWORD)->SetFocus() ;
		break ;
	case 3 :
		UpdateData(TRUE) ;
		if(mNewPassword != mVerifyPassword)
		{
			MessageBox(_T("两次输入密码不一致"), NULL, MB_ICONQUESTION) ;
			mNewPassword = _T("") ;
			mVerifyPassword = _T("") ;
			UpdateData(FALSE) ;
			GetDlgItem(IDC_NEW_PASSWORD)->SetFocus() ;
		}
		else
		{
			GetDlgItem(IDOK)->EnableWindow(TRUE) ;
			PostMessage(WM_COMMAND, IDOK) ;
		}
		break ;
	}
	return 0;
}


BOOL CChangePasswordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CheckDlgButton(IDC_CHECK_SHOW_CHAR, mShowChar) ;
	ShowPasswordChar(mShowChar) ;
	NextStep(0) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CChangePasswordDlg::OnBnClickedOk()
{
	UpdateData(TRUE) ;
	if(mNewPassword != mVerifyPassword)
	{
		MessageBox(_T("两次输入密码不一致"), NULL, MB_ICONQUESTION) ;
		return ;
	}
	CDialogEx::OnOK();
}


void CChangePasswordDlg::OnBnClickedCheckShowChar()
{
	mShowChar = IsDlgButtonChecked(IDC_CHECK_SHOW_CHAR) ;
	ShowPasswordChar(mShowChar) ;
}


void CChangePasswordDlg::ShowPasswordChar(BOOL Enable)
{
	if(Enable)
	{
		((CEdit*)GetDlgItem(IDC_OLD_PASSWORD))->SetPasswordChar(0) ;
		((CEdit*)GetDlgItem(IDC_NEW_PASSWORD))->SetPasswordChar(0) ;
		((CEdit*)GetDlgItem(IDC_REPEAT_PASSWORD))->SetPasswordChar(0) ;
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_OLD_PASSWORD))->SetPasswordChar('*') ;
		((CEdit*)GetDlgItem(IDC_NEW_PASSWORD))->SetPasswordChar('*') ;
		((CEdit*)GetDlgItem(IDC_REPEAT_PASSWORD))->SetPasswordChar('*') ;
	}
}
