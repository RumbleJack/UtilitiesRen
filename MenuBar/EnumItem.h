#pragma once
#include "BlankPopupWnd.h"
#define WM_CLICKED_MSG_TO_PARENT_WND	WM_USER+0X315
// CEnumItem

class CEnumItem : public CBlankPopupWnd
{
	DECLARE_DYNAMIC(CEnumItem)

public:
	CEnumItem(CWnd *pParentWnd, RECT WndPos, WORD id, const WCHAR *pTitle, BOOL Selected = FALSE, COLORREF UnselectedBrush = RGB(255, 255, 255), COLORREF SelectedBrush = RGB(128,128,128));
	virtual ~CEnumItem();
protected :
	WORD mID ;
	BOOL mSelected ;
	COLORREF mUnselectedBrush ;
	COLORREF mSelectedBrush ;
	CString mTitle ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	WORD	GetID()
	{
		return mID ;
	}
	BOOL IsSelected()
	{
		return mSelected ;
	}
};


