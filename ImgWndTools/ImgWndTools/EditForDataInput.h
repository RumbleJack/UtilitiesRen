#pragma once

// CEditForDataInput

class  __declspec( dllexport ) CEditForDataInput : public CEdit
{
	DECLARE_DYNAMIC(CEditForDataInput)
public:
	typedef enum
	{
		INT_DATA,
		FLOAT_DATA,
		STRING_DATA
	} ENUM_DATA_TYPE ;

	CEditForDataInput(ENUM_DATA_TYPE DataType = FLOAT_DATA, COLORREF TextClr = RGB(128, 128, 128), COLORREF BkClr = RGB(0, 0, 0), int Size = 20, const WCHAR * pFont = NULL);
	virtual ~CEditForDataInput();

protected :
	ENUM_DATA_TYPE mDataType ;
	COLORREF	mTextClr ;
	COLORREF	mBkClr ;
	CFont		mTextFont ;

	CBrush m_brBackGnd ;
	CRect		mClientRect ;
	typedef union
	{
		int	IntVal ;
		float FltVal ;
	} UNION_DATA ;
	UNION_DATA	mDataVal ;
	CString		mText ;

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetFont(COLORREF TextClr, COLORREF BkClr, int Size, const WCHAR * pFont = NULL);
	void SetDataType(ENUM_DATA_TYPE DataType) ;
	ENUM_DATA_TYPE GetDataType() ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	BOOL SetInitDataValue(int val);
	BOOL SetInitDataValue(float val);
	BOOL SetInitDataValue(const WCHAR *pVal);
	BOOL ConvertDataToString() ;
	BOOL CreateTextFont(int Size, const WCHAR *pFont) ;
};


