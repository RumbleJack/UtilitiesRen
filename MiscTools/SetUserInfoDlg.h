#pragma once
#include "UserInfoDef.h"
#include "resource.h"

// CSetUserInfoDlg 对话框

class CSetUserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetUserInfoDlg)

public:
	CSetUserInfoDlg(LPCTSTR pUserName, LPCTSTR pPassword, ENUM_ACCOUNT_LEVEL Level, BOOL NewAccount = TRUE, BOOL FixLevel = FALSE, BOOL FixName = FALSE);   // 标准构造函数
	virtual ~CSetUserInfoDlg();

// 对话框数据
	enum { IDD = IDD_SET_USER_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mUserName;
	CString mPassword;
	BOOL mFixLevel ;
	BOOL mFixName ;
	ENUM_ACCOUNT_LEVEL mLevel ;
	BOOL mNewAccount ;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private :
	int LevelToRadioButton(ENUM_ACCOUNT_LEVEL Level)
	{
		int IdButton = IDC_RADIO_ADMIN ;
		switch(Level)
		{
		case ADMIN :
			IdButton = IDC_RADIO_ADMIN ;
			break ;
		case OPER :
			IdButton = IDC_RADIO_OPER ;
			break ;
		case VISIT :
			IdButton = IDC_RADIO_VISIT ;
			break ;
		case PROHIBIT :
		case ILLEGAL :
			IdButton = IDC_RADIO_PROHIB ;
			break ;
		}
		return IdButton ;
	}
	ENUM_ACCOUNT_LEVEL RadioButtonToLevel(int IdButton)
	{
		ENUM_ACCOUNT_LEVEL Level = ILLEGAL ;
		switch(IdButton)
		{
		case IDC_RADIO_PROHIB :
			Level = PROHIBIT ;
			break ;
		case IDC_RADIO_VISIT :
			Level = VISIT ;
			break ;
		case IDC_RADIO_OPER :
			Level = OPER ;
			break ;
		case IDC_RADIO_ADMIN :
			Level = ADMIN ;
			break ;
		}
		return Level ;
	}

	void ToFixLevel();
};
