#pragma once
#include "resource.h"

// CChangePasswordDlg 对话框

class CChangePasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePasswordDlg)

public:
	CChangePasswordDlg(LPCTSTR pUserName, LPCTSTR pUserPassword);   // 标准构造函数
	virtual ~CChangePasswordDlg();

// 对话框数据
	enum { IDD = IDD_CHANGE_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	int NextStep(int IdxStep);
public:
	CString mUserName;
	CString	mUserPassword ;
	CString mOldPassword;
	CString mNewPassword;
	CString mVerifyPassword;
	BOOL mShowChar;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckShowChar();
private:
	void ShowPasswordChar(BOOL Enable);
};
