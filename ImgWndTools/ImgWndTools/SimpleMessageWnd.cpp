// SingleMessageWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "SimpleMessageWnd.h"


// CSingleMessageWnd

IMPLEMENT_DYNAMIC(CSimpleMessageWnd, CBlankWnd)
CSimpleMessageWnd::CSimpleMessageWnd(CWnd *pParentWnd)
: CBlankWnd(pParentWnd)
{
}

CSimpleMessageWnd::CSimpleMessageWnd(CWnd *pParentWnd, RECT Pos, COLORREF Clr, BOOL Titled, int FontSize)
: CBlankWnd(pParentWnd, Pos, Titled, FALSE, TRUE, WHITE_BRUSH)
, mClr(Clr)
, mSizeFont(FontSize)
{
}

BOOL CSimpleMessageWnd::CreateMsgWnd(RECT Pos, COLORREF Clr, BOOL Titled, int FontSize)
{
	mClr = Clr ;
	mSizeFont = FontSize ;
	return CreateWnd(Pos, Titled, FALSE, TRUE, WHITE_BRUSH) ;
}

CSimpleMessageWnd::CSimpleMessageWnd(CWnd *pParentWnd, RECT Pos, LPCTSTR pMsg, LPCTSTR pTitle, COLORREF Clr, int FontSize)
	: CBlankWnd(pParentWnd, Pos, (pTitle == NULL ? FALSE : TRUE), FALSE, TRUE, WHITE_BRUSH)
	, mClr(Clr)
	, mSizeFont(FontSize)
{
	if(pMsg != NULL)
		mMsg = pMsg ;
	else
		mMsg = _T("") ;
	if(pTitle != NULL)
		mTitle = pTitle ;
	else
		mTitle = _T("") ;
}

BOOL CSimpleMessageWnd::CreateMsgWnd(RECT Pos, LPCTSTR pMsg, LPCTSTR pTitle, COLORREF Clr, int FontSize)
{
	mClr = Clr ;
	mSizeFont = FontSize ;
	if(pMsg != NULL)
		mMsg = pMsg ;
	else
		mMsg = _T("") ;
	if(pTitle != NULL)
		mTitle = pTitle ;
	else
		mTitle = _T("") ;
	return 	CreateWnd(Pos, (pTitle == NULL ? FALSE : TRUE), FALSE, TRUE, WHITE_BRUSH) ;
}

CSimpleMessageWnd::~CSimpleMessageWnd()
{
}


BEGIN_MESSAGE_MAP(CSimpleMessageWnd, CBlankWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSingleMessageWnd 消息处理程序




int CSimpleMessageWnd::ShowMessage(LPCTSTR pMsg)
{
	if(pMsg != NULL)
		mMsg = pMsg ;
	else
		mMsg = _T('\0') ;
	return 0;
}


int CSimpleMessageWnd::ShowTitle(LPCTSTR pTitle)
{
	if(pTitle != NULL)
		mTitle = pTitle ;
	else
		mTitle = _T('\0') ;
	return 0;
}


void CSimpleMessageWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	int BkMode = dc.SetBkMode(TRANSPARENT) ;
	CFont mFont ;
	mFont.CreatePointFont(mSizeFont*10, _T("宋体"), &dc) ;
	CFont *pOldFont = dc.SelectObject(&mFont) ;

	CSize SizeStr = dc.GetTextExtent(mMsg) ;
	CRect ClientRect ;
	GetClientRect(ClientRect) ;
	ClientRect.DeflateRect((ClientRect.Width()-SizeStr.cx) / 2, (ClientRect.Height() - SizeStr.cy) / 2) ;
	COLORREF OldClr = dc.SetTextColor(mClr) ;
	
	dc.TextOutW(ClientRect.left, ClientRect.top, mMsg) ;
	dc.SetBkMode(BkMode) ;
	dc.SetTextColor(mClr) ;
	dc.SelectObject(pOldFont) ;
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CBlankWnd::OnPaint()
}


void CSimpleMessageWnd::SetFontSize(int size)
{
	mSizeFont = size ;
}


void CSimpleMessageWnd::SetFontColor(COLORREF clr)
{
	mClr = clr ;
}
