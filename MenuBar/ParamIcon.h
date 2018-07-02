#pragma once
#include "MenuDef.h"
#include "BlankWnd.h"
#include "EnumBar.h"
#include "ParamIconAttr.h"
// CParamIcon

class CParamIcon : public CBlankWnd, public CParamIconAttr
{
	DECLARE_DYNAMIC(CParamIcon)

public:
	CParamIcon(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon);
	virtual ~CParamIcon();
protected :
	CString mTitleFont ;
	int		mTitleFontSize ;
	COLORREF mTitleFontClr ;
	CString mDataFont ;
	int	mDataFontSize ;
	COLORREF mDataFontClr ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL SetupIcon(const STRUCT_PARAM_ICON * pDef);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void DrawIcon(CDC *pDC) ;
	virtual void ProcLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnClicked(WPARAM wParam, LPARAM lParam);
	virtual void CallbackOnClicked(WPARAM wParam, LPARAM lParam);
	void SetParamFont(int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL);
	void SetTitleFont(int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL);
protected:
	void DrawMultiLineStr(CDC * pDC, RECT Pos, const WCHAR * pStr, COLORREF Clr, int FontSize, const WCHAR * pFont);
	void DrawSingleLineStr(CDC *pDC, RECT Pos, const WCHAR * pStr, COLORREF Clr, int FontSize, const WCHAR * pFont);
	virtual void DrawTitle(CDC *pDC);
	virtual void DrawParam(CDC *pDC);
public:
	RECT GetTitlePos(void);
	RECT GetParamRect(void);
};


