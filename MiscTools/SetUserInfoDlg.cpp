// SetUserInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MiscTools.h"
#include "SetUserInfoDlg.h"
#include "afxdialogex.h"


// CSetUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CSetUserInfoDlg, CDialogEx)

CSetUserInfoDlg::CSetUserInfoDlg(LPCTSTR pUserName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level, BOOL NewAccount, BOOL FixLevel, BOOL FixName)
	: CDialogEx(CSetUserInfoDlg::IDD, NULL)
	, mUserName(pUserName == NULL ? _T("") : pUserName)
	, mPassword(pPassword == NULL ? _T("") : pPassword)
	, mLevel(Level)
	, mNewAccount(NewAccount)
	, mFixLevel(FixLevel)
	, mFixName(FixName)
{

}

CSetUserInfoDlg::~CSetUserInfoDlg()
{
}

void CSetUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, mUserName);
	DDX_Text(pDX, IDC_PASSWORD, mPassword);
}


BEGIN_MESSAGE_MAP(CSetUserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetUserInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetUserInfoDlg 消息处理程序

BOOL CSetUserInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//if(mUserName.GetLength() > 0)
	//	((CEdit *)GetDlgItem(IDC_EDIT_USER_NAME))->SetReadOnly(TRUE) ;
	CheckRadioButton(IDC_RADIO_ADMIN, IDC_RADIO_PROHIB, LevelToRadioButton(mLevel)) ;
	if(mFixLevel)
		ToFixLevel() ;
	if(mFixName)
		GetDlgItem(IDC_USER_NAME)->EnableWindow(FALSE) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSetUserInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE ;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSetUserInfoDlg::OnBnClickedOk()
{
	mLevel = RadioButtonToLevel(GetCheckedRadioButton(IDC_RADIO_ADMIN, IDC_RADIO_PROHIB)) ;
	CDialogEx::OnOK();
}



void CSetUserInfoDlg::ToFixLevel()
{
	GetDlgItem(IDC_RADIO_ADMIN)->EnableWindow(FALSE) ;
	GetDlgItem(IDC_RADIO_OPER)->EnableWindow(FALSE) ;
	GetDlgItem(IDC_RADIO_VISIT)->EnableWindow(FALSE) ;
	GetDlgItem(IDC_RADIO_PROHIB)->EnableWindow(FALSE) ;
	
}
