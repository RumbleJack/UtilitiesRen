// EditForDataInput.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "EditForDataInput.h"

// CEditForDataInput

IMPLEMENT_DYNAMIC(CEditForDataInput, CEdit)

CEditForDataInput::CEditForDataInput(ENUM_DATA_TYPE DataType, COLORREF TextClr, COLORREF BkClr, int Size, const WCHAR * pFont)
: mTextClr(TextClr)
, mBkClr(BkClr)
, mDataType(DataType)
{
	CreateTextFont(Size, pFont) ;
	m_brBackGnd.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
}

CEditForDataInput::~CEditForDataInput()
{
}


BEGIN_MESSAGE_MAP(CEditForDataInput, CEdit)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CEditForDataInput 消息处理程序


BOOL CEditForDataInput::CreateTextFont(int Size, const WCHAR *pFont)
{
	if(mTextFont.GetSafeHandle())
		mTextFont.DeleteObject();
	LOGFONT LogFont={0};
	if(pFont != NULL && wcslen(pFont) > 1)
		_tcsncpy_s(LogFont.lfFaceName, LF_FACESIZE, pFont , wcslen(pFont)) ;
	LogFont.lfHeight = Size;                      
	mTextFont.CreateFontIndirectW(&LogFont);

	return TRUE ;
}

void CEditForDataInput::SetFont(COLORREF TextClr, COLORREF BkClr, int Size, const WCHAR * pFont)
{
	mTextClr =TextClr ;
	mBkClr = BkClr ;
	
	if (m_brBackGnd.GetSafeHandle())
		m_brBackGnd.DeleteObject();
	//使用文字背景颜色创建新的画刷,使得文字框背景和文字背景一致
	CreateTextFont(Size, pFont) ;
	CEdit::SetFont(&mTextFont);		
	m_brBackGnd.CreateSolidBrush(mBkClr);
}

void CEditForDataInput::SetDataType(ENUM_DATA_TYPE DataType)
{
	mDataType = DataType ;
}

CEditForDataInput::ENUM_DATA_TYPE CEditForDataInput::GetDataType()
{
	return mDataType ;
}

void CEditForDataInput::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	GetClientRect(&mClientRect) ;
}


BOOL CEditForDataInput::SetInitDataValue(int val)
{
	if(mDataType == INT_DATA)
	{
		mDataVal.IntVal = val ;
		ConvertDataToString() ;
		return TRUE ;
	}
	return FALSE ;
}


BOOL CEditForDataInput::SetInitDataValue(float val)
{
	if(mDataType == FLOAT_DATA)
	{
		mDataVal.FltVal= val ;
		ConvertDataToString() ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CEditForDataInput::SetInitDataValue(const WCHAR *pVal)
{
	if(mDataType == STRING_DATA)
	{
		mText = pVal ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CEditForDataInput::ConvertDataToString()
{
	switch(mDataType)
	{
	case INT_DATA :
		mText.Format(_T("%d"), mDataVal.IntVal) ;
		break ;
	case FLOAT_DATA :
		mText.Format(_T("%f"), mDataVal.FltVal) ;
		break ;
	}
	return TRUE ;
}

HBRUSH CEditForDataInput::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(mTextClr);
	pDC->SetBkColor(mBkClr);

//返回画刷,用来绘制整个控件背景
	return m_brBackGnd;
}