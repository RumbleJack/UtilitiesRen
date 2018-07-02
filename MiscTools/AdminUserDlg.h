#pragma once
#include "resource.h"
#include "UserInfoDef.h"
#include "SafeArray.h"
// CAdminUserDlg 对话框

class CAdminUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminUserDlg)

public:
	CAdminUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminUserDlg();

// 对话框数据
	enum { IDD = IDD_ADMIN_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int	mIdxItem ;
	int		mIdxLogin ;
	CSafeArray <STRUCT_ACCOUNT_INFO> mUserList ;
	int mCntItem ;
	DECLARE_MESSAGE_MAP()
public:
	int AddUser(LPCTSTR pName , LPCTSTR pPassword , ENUM_ACCOUNT_LEVEL Level);
	void ResetLoadPos()
	{
		mIdxItem = -1 ;
	}
	BOOL GetNextUserInfo(CString & Name, CString & Password, ENUM_ACCOUNT_LEVEL & Level);
	virtual BOOL OnInitDialog();
private:
	void ShowUserList(void);
	LPCTSTR LevelToStr(ENUM_ACCOUNT_LEVEL Level) ;
	BOOL CheckValidUserIdx(int Idx)
	{
		return Idx >= 0 && Idx < mCntItem ;
	}
public:
	afx_msg void OnBnClickedButtonAddUser();
	afx_msg void OnNMClickListUserList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModify();
	BOOL SetLoginUser(LPCTSTR pName);

};
