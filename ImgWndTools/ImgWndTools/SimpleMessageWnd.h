#pragma once
#include "BlankWnd.h"

// CSingleMessageWnd

class __declspec( dllexport ) CSimpleMessageWnd : public CBlankWnd
{
	DECLARE_DYNAMIC(CSimpleMessageWnd)

public:
	CSimpleMessageWnd(CWnd *pParentWnd) ;
	CSimpleMessageWnd(CWnd *pParentWnd, RECT Pos, COLORREF Clr = RGB(0, 0, 0), BOOL Titled = FALSE, int FontSize = 18);
	CSimpleMessageWnd(CWnd *pParentWnd, RECT Pos, LPCTSTR pMsg, LPCTSTR pTitle, COLORREF Clr = RGB(0, 0, 0), int FontSize = 18);
	BOOL CreateMsgWnd(RECT Pos, COLORREF Clr = RGB(0, 0, 0), BOOL Titled = FALSE, int FontSize = 18);
	BOOL CreateMsgWnd(RECT Pos, LPCTSTR pMsg, LPCTSTR pTitle, COLORREF Clr = RGB(0, 0, 0), int FontSize = 18);
	virtual ~CSimpleMessageWnd();
protected :
	CString mMsg ;
	CString mTitle ;
	COLORREF mClr ;
	int	mSizeFont ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int ShowMessage(LPCTSTR pMsg);
	int ShowTitle(LPCTSTR pTitle);
	afx_msg void OnPaint();
	void SetFontSize(int size);
	void SetFontColor(COLORREF clr);
};


