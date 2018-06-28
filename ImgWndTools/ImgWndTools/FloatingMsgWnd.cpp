// FloatingMsgWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "FloatingMsgWnd.h"
#include "DataVsString.h"

// CFloatingMsgWnd
#define DEFAULT_WND_WIDTH 50
IMPLEMENT_DYNAMIC(CFloatingMsgWnd, CBlankPopupWnd)

CFloatingMsgWnd::CFloatingMsgWnd(CWnd *pParentWnd, POINT Center, const WCHAR *pText, int TextSize, COLORREF TextClr, COLORREF BkClr, const WCHAR *pFont, int HorzFrameSize, int VertFrameSize)
:CBlankPopupWnd(pParentWnd)
, mShownTitle(pText)
, mTextSize(TextSize)
, mTextColor(TextClr)
, mBkColor(BkClr)
, mWndCenter(Center)
, mHorzFrameSize(HorzFrameSize)
, mVertFrameSize(VertFrameSize)
{
	CreateTextFont(TextSize, pFont) ;
	mBkBrush.CreateSolidBrush(mBkColor);
	SetWndSize() ;
	CRect WndRect(mWndCenter.x - mWndSize.cx/2, 
					mWndCenter.y-mWndSize.cy/2, 
					mWndCenter.x + mWndSize.cx/2,
					mWndCenter.y + mWndSize.cy/2) ;
	CreateWnd(WndRect, FALSE, TRUE, BkClr) ;
}

CFloatingMsgWnd::~CFloatingMsgWnd()
{
}

void CFloatingMsgWnd::CreateTextFont(int TextSize, const WCHAR *pFont)
{
	if(mFont.GetSafeHandle())
		mFont.DeleteObject();
	LOGFONT LogFont={0};
	if(pFont != NULL && wcslen(pFont) > 1)
		_tcsncpy_s(LogFont.lfFaceName, LF_FACESIZE, pFont , wcslen(pFont)) ;
	LogFont.lfHeight = TextSize;                      
	mFont.CreateFontIndirectW(&LogFont);
}

void CFloatingMsgWnd::SetFont(COLORREF TextClr, COLORREF BkClr, int TextSize, const WCHAR * pFont)
{
	mTextColor =TextClr ;
	mBkColor = BkClr ;
	
	if (mBkBrush.GetSafeHandle())
		mBkBrush.DeleteObject();
	mBkBrush.CreateSolidBrush(mBkColor);

	CreateTextFont(TextSize, pFont) ;
}

BEGIN_MESSAGE_MAP(CFloatingMsgWnd, CBlankPopupWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CFloatingMsgWnd 消息处理程序




void CFloatingMsgWnd::MoveCenterTo(int x, int y)
{
	mWndCenter.x = x ;
	mWndCenter.y = y ;
	MoveWindow(x-mWndSize.cx/2, y-mWndSize.cy/2, mWndSize.cx, mWndSize.cy) ;
}


void CFloatingMsgWnd::MoveCenterTo(POINT pt)
{
	MoveCenterTo(pt.x, pt.y) ;
}

void CFloatingMsgWnd::MoveCenterToClientPos(int x, int y)
{
	MoveCenterToClientPos(CPoint(x,y)) ;
}

void CFloatingMsgWnd::MoveCenterToClientPos(POINT pt)
{
	if(mpParentWnd != NULL)
	{
		mpParentWnd->ClientToScreen(&pt) ;
		MoveCenterTo(pt) ;
	}
}

void CFloatingMsgWnd::ShowData(int val, int MinCntChr)
{
	CDataVsString Tools ;
	mShownTitle = Tools.IntToString(val, MinCntChr) ;
	SetWndSize() ;
	RedrawWindow() ;
}


void CFloatingMsgWnd::ShowData(float val , int Precision, BOOL Round, int MinCntChar)
{
	CDataVsString Tools ;
	mShownTitle = Tools.FloatToString(val, Precision, TRUE, MinCntChar) ;
	SetWndSize() ;
	RedrawWindow() ;
}


void CFloatingMsgWnd::ShowData(WCHAR * pStr)
{
	mShownTitle = pStr ;
	SetWndSize() ;
	RedrawWindow() ;
}



void CFloatingMsgWnd::SetWndSize()
{
	int CntChr = wcslen(mShownTitle) ;
	mWndSize.cx = CntChr * mTextSize + mHorzFrameSize * 2 ;
	mWndSize.cy = mTextSize + mVertFrameSize * 2 ;
}


void CFloatingMsgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetBkMode(TRANSPARENT) ;
	CWnd::SetFont(&mFont) ;
	dc.SetTextColor(mTextColor);
	//dc.SetBkColor(mBkColor);
	CRect ClientRect ;
	GetClientRect(&ClientRect) ;
	dc.DrawText(mShownTitle, &ClientRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE) ;
}


BOOL CFloatingMsgWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pDC->SelectObject(&mBkBrush) ;

	return CBlankPopupWnd::OnEraseBkgnd(pDC);
}
