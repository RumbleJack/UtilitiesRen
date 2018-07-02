// ParamIcon.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ParamIcon.h"
#include "SysDef.h"
#include "GlobalMsgDef.h"
#include "DataVsString.h"
// CParamIcon

IMPLEMENT_DYNAMIC(CParamIcon, CBlankWnd)

CParamIcon::CParamIcon(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon)
: CParamIconAttr(pIcon)
, CBlankWnd(pParentWnd, Pos, FALSE, TRUE, FALSE, TRUE, UNSELECTED_ICON_BK_CLR)
, mTitleFont(PARAM_ICON_FONT)
, mDataFont(PARAM_ICON_FONT)
, mTitleFontClr(PARAM_ICON_TITLE_COLOR)
, mDataFontClr(PARAM_ICON_DATA_COLOR)
, mTitleFontSize(PARAM_ICON_TITLE_CHAR_SIZE)
, mDataFontSize(PARAM_ICON_PARAM_CHAR_SIZE)
{
	SetupIcon(pIcon) ;
}

CParamIcon::~CParamIcon()
{
}


BEGIN_MESSAGE_MAP(CParamIcon, CBlankWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MENU_ITEM_CLICKED, &CParamIcon::OnClicked)
END_MESSAGE_MAP()



// CParamIcon 消息处理程序


BOOL CParamIcon::SetupIcon(const STRUCT_PARAM_ICON * pDef)
{
	return 0;
}


void CParamIcon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawIcon(&dc) ;
}


void CParamIcon::OnLButtonDown(UINT nFlags, CPoint point)
{
	ProcLButtonDown(nFlags, point) ;
	CBlankWnd::OnLButtonDown(nFlags, point);
}

void CParamIcon::DrawIcon(CDC *pDC)
{
	DrawCenteredTitle(pDC, ICON_TEXT_COLOR, mTitle) ;
}

void CParamIcon::ProcLButtonDown(UINT nFlags, CPoint point)
{
}

LRESULT CParamIcon::OnClicked(WPARAM wParam, LPARAM lParam)
{
	CallbackOnClicked(wParam, lParam) ;
	return 0 ;

}

void CParamIcon::CallbackOnClicked(WPARAM wParam, LPARAM lParam)
{
}


void CParamIcon::SetParamFont(int FontSize, COLORREF FontClr, const WCHAR *pFont)
{
	mDataFontSize = FontSize ;
	mDataFontClr = FontClr ;
	if(pFont != NULL)
		mDataFont = pFont ;
}


void CParamIcon::SetTitleFont(int FontSize, COLORREF FontClr, const WCHAR *pFont)
{
	mTitleFontSize = FontSize ;
	mTitleFontClr = FontClr ;
	if(pFont != NULL)
		mTitleFont = pFont ;
}

void CParamIcon::DrawSingleLineStr(CDC *pDC, RECT Pos, const WCHAR * pStr, COLORREF Clr, int FontSize, const WCHAR * pFont)
{
	LOGFONT LogFont={0};
	if(pFont != NULL && wcslen(pFont) > 1)
		_tcsncpy_s(LogFont.lfFaceName, LF_FACESIZE, pFont , wcslen(pFont)) ;
	LogFont.lfHeight = FontSize ;                      
	CFont Font ;
	Font.CreateFontIndirectW(&LogFont);
	CFont *pOldFont = pDC->SelectObject(&Font) ;

	DrawCenteredTitle(pDC, Pos, Clr, pStr) ;
	pDC->SelectObject(pOldFont) ;

}

void CParamIcon::DrawMultiLineStr(CDC * pDC, RECT Pos, const WCHAR * pStr, COLORREF Clr, int FontSize, const WCHAR * pFont)
{
	int BkMode = pDC->SetBkMode(TRANSPARENT) ;
	COLORREF OldClr = pDC->SetTextColor(Clr) ;

	LOGFONT LogFont={0};
	if(pFont != NULL && wcslen(pFont) > 1)
		_tcsncpy_s(LogFont.lfFaceName, LF_FACESIZE, pFont , wcslen(pFont)) ;
	LogFont.lfHeight = FontSize ;                      
	CFont Font ;
	Font.CreateFontIndirectW(&LogFont);
	CFont *pOldFont = pDC->SelectObject(&Font) ;

#define MAX_CNT_LINE 3
	CString LineStr[MAX_CNT_LINE] ;
	int IdxLn = 0 ;
	int IdxChr = 0 ;
	int CntChr = wcslen(pStr) ;
	while(IdxChr < CntChr && *(pStr + IdxChr) != '\0')
	{
		if(*(pStr + IdxChr) != '\n')
			LineStr[IdxLn] += *(pStr + IdxChr) ;
		else
		{
			if(++IdxLn >= MAX_CNT_LINE)
				break ;
		}
		++IdxChr ;
	}

	++IdxLn ;
	int LineHeight = (Pos.bottom - Pos.top) / IdxLn ;
	int yCenter = Pos.top + LineHeight / 2 ;
	int xCenter = (Pos.left + Pos.right) / 2 ;
	for(int i = 0 ; i < IdxLn ; ++i)
	{
		CSize SizeStr = pDC->GetTextExtent(LineStr[i]) ;
		pDC->TextOutW(xCenter-SizeStr.cx/2, yCenter+LineHeight*i-SizeStr.cy/2, LineStr[i]) ;
	}
	
	pDC->SetBkMode(BkMode) ;
	pDC->SetTextColor(OldClr) ;
	pDC->SelectObject(pOldFont) ;
}


void CParamIcon::DrawTitle(CDC *pDC)
{
	if(mTitle.GetLength() > 0)
		DrawMultiLineStr(pDC, GetTitlePos(), mTitle, mTitleFontClr, mTitleFontSize, mTitleFont.GetLength() > 0 ? mTitleFont : NULL) ;
}

void CParamIcon::DrawParam(CDC *pDC)
{
	CString ValStr ;
	CDataVsString mTool ;
	switch(mParamType)
	{
	case INT_DATA :
		ValStr = mTool.IntToString(mValue.IntData) ;
		break ;
	case FLOAT_DATA :
		ValStr = mTool.FloatToString(mValue.FltData, FLOAT_PRECISION) ;
		break ;
	case ID_DEF :
		ValStr.Format(_T("%X"), mValue.id) ;
		break ;
	case STR_PTR :
		ValStr = mValue.pStr ;
		break ;
	case ENUM_GATE_IDX :
		ValStr = GateIdxToString(mValue.GateIdx)  ;
		break ;
	}
	DrawSingleLineStr(pDC, GetParamRect(), ValStr, mDataFontClr, mDataFontSize, mDataFont.GetLength() > 0 ? mDataFont : NULL) ;
}

RECT CParamIcon::GetTitlePos(void)
{
	CRect Pos ;
	GetClientRect(&Pos) ;
	if(mTitle.GetLength() > 0)
		Pos.right -= (int)(Pos.Width() * (1.0f - PARAM_ICON_TITLE_WIDTH)) ;
	return Pos ;
}


RECT CParamIcon::GetParamRect(void)
{
	CRect Pos ;
	GetClientRect(&Pos) ;
	if(mTitle.GetLength() > 0)
		Pos.left += (int)(Pos.Width() * PARAM_ICON_TITLE_WIDTH) ;
	return Pos ;
}
