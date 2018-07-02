// AdminUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MiscTools.h"
#include "AdminUserDlg.h"
#include "afxdialogex.h"
#include "DataVsString.h"
#include "SetUserInfo.h"

// CAdminUserDlg 对话框

IMPLEMENT_DYNAMIC(CAdminUserDlg, CDialogEx)

CAdminUserDlg::CAdminUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminUserDlg::IDD, pParent)
	, mIdxItem(-1)
	, mCntItem(0)
	, mUserList(MAX_CNT_USER)
	, mIdxLogin(-1)
{

}

CAdminUserDlg::~CAdminUserDlg()
{
}

void CAdminUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_USER, &CAdminUserDlg::OnBnClickedButtonAddUser)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER_LIST, &CAdminUserDlg::OnNMClickListUserList)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CAdminUserDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CAdminUserDlg 消息处理程序


int CAdminUserDlg::AddUser(LPCTSTR pName , LPCTSTR pPassword , ENUM_ACCOUNT_LEVEL Level)
{
	if(mCntItem >= 0 && mCntItem < mUserList.GetArraySize())
	{
		mUserList[mCntItem].Name = pName ;
		mUserList[mCntItem].Password = pPassword ;
		mUserList[mCntItem].Level = Level ;
		mUserList[mCntItem].Modified = FALSE ;
		return ++mCntItem ;
	}
	return -1 ;
}


BOOL CAdminUserDlg::GetNextUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL & Level)
{
	if(++mIdxItem < mCntItem)
	{
		Name = mUserList[mIdxItem].Name ;
		Password = mUserList[mIdxItem].Password ;
		Level = mUserList[mIdxItem].Level ;
		return TRUE ;
	}
	return FALSE;
}


void CAdminUserDlg::ShowUserList(void)
{
	CListCtrl *pList =(CListCtrl *)GetDlgItem(IDC_LIST_USER_LIST) ;
	pList->DeleteAllItems() ;
	CDataVsString Tool ;
	for(int i = 0 ; i < mCntItem && i < mUserList.GetArraySize(); ++i)
	{
		pList->InsertItem(i, Tool.IntToString(i+1, 2)) ;
		pList->SetItemText(i, 1, mUserList[i].Name) ;
		CString LevelName = LevelToStr(mUserList[i].Level) ;
		pList->SetItemText(i, 2, LevelName) ;
	}
}

LPCTSTR CAdminUserDlg::LevelToStr(ENUM_ACCOUNT_LEVEL Level)
{
	static CString Note ;
	switch(Level)
	{
	case ADMIN :
		Note = _T("管理员") ;
		break ;
	case OPER :
		Note = _T("操作员") ;
		break ;
	case VISIT :
		Note = _T("访客") ;
		break ;
	case PROHIBIT :
		Note = _T("禁用") ;
		break ;
	}
	return Note ;
}

BOOL CAdminUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CListCtrl *pList =(CListCtrl *)GetDlgItem(IDC_LIST_USER_LIST) ;
	CRect rectList ;
	pList->GetClientRect(rectList) ;

	pList->InsertColumn(0, _T("序号"), LVCFMT_CENTER, rectList.Width() / 5) ;
	pList->InsertColumn(1, _T("用户名"), LVCFMT_CENTER, rectList.Width() * 3 / 5) ;
	pList->InsertColumn(2, _T("权限"), LVCFMT_CENTER, rectList.Width() / 5) ;
	ShowUserList() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAdminUserDlg::OnBnClickedButtonAddUser()
{
	CSetUserInfo NewUser(NULL, NULL, OPER, TRUE, FALSE, FALSE) ;
	CString Name, Password ;
	ENUM_ACCOUNT_LEVEL Level ;
	if(NewUser.Doing(Name, Password, Level))
	{
		AddUser(Name, Password, Level) ;
		ShowUserList() ;
	}
		
}

void CAdminUserDlg::OnNMClickListUserList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CListCtrl *pList =(CListCtrl *)GetDlgItem(IDC_LIST_USER_LIST) ;
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		mIdxItem = pList->GetNextSelectedItem(pos);
		PostMessage(WM_COMMAND, IDC_BUTTON_MODIFY) ;
	}
	*pResult = 0;
}


void CAdminUserDlg::OnBnClickedButtonModify()
{
	if(CheckValidUserIdx(mIdxLogin) && CheckValidUserIdx(mIdxItem))
	{
		if(mIdxItem == mIdxLogin || CHECK_THIS_HIGHER_LEVEL(mUserList[mIdxLogin].Level, mUserList[mIdxItem].Level)>0)
		{
			CSetUserInfo NewUser(mUserList[mIdxItem].Name, mUserList[mIdxItem].Password, mUserList[mIdxItem].Level, FALSE, FALSE, TRUE) ;
			CString Name, Password ;
			ENUM_ACCOUNT_LEVEL Level ;
			if(NewUser.Doing(Name, Password, Level))
			{
				mUserList[mIdxItem].Name = Name ;
				mUserList[mIdxItem].Password = Password ;
				mUserList[mIdxItem].Level = Level ;
				mUserList[mIdxItem].Modified = TRUE ;
				ShowUserList() ;
			}
		}
	}
}


BOOL CAdminUserDlg::SetLoginUser(LPCTSTR pName)
{
	for(int i = 0 ; i < mCntItem; ++i)
	{
		if(mUserList[i].Name == pName)
		{
			mIdxLogin = i ;
			return TRUE ;
		}
	}
	mIdxLogin = -1 ;
	return  FALSE ;
}
