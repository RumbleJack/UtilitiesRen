#pragma once
#include "BlankPopupWnd.h"

// CFloatingMsgWnd

class __declspec( dllexport ) CFloatingMsgWnd : public CBlankPopupWnd
{
	DECLARE_DYNAMIC(CFloatingMsgWnd)

public:
	CFloatingMsgWnd(CWnd *pParentWnd, POINT Center, const WCHAR *pText, int TextSize, COLORREF TextClr, COLORREF BkClr, const WCHAR *pFont = NULL, int HorzFrameSize = 2, int VertFrameSize = 2);
	virtual ~CFloatingMsgWnd();

protected :
	int	mTextSize ;
	COLORREF	mTextColor ;
	COLORREF	mBkColor ;
	int	mHorzFrameSize ;
	int	mVertFrameSize ;
	CString	mShownTitle ;
	CFont	mFont ;
	CPoint	mWndCenter ;
	CSize	mWndSize ;
	CBrush	mBkBrush ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void MoveCenterTo(int x, int y);
	void MoveCenterTo(POINT pt);
	void MoveCenterToClientPos(int x, int y) ;	// 坐标定义在父窗口的client坐标系中
	void MoveCenterToClientPos(POINT pt) ;	// 坐标定义在父窗口的client坐标系中
	void ShowData(int val, int MinCntChr = 1);
	void ShowData(float val , int Precision = 2, BOOL Round = TRUE, int MinCntChar = 1);
	void ShowData(WCHAR * pStr);
	void CreateTextFont(int TextSize, const WCHAR *pFont) ;
	void SetWndSize();
	void SetFont(COLORREF TextClr, COLORREF BkClr, int TextSize, const WCHAR * pFont = NULL) ;
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


