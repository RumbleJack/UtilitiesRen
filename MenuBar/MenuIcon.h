#pragma once
#include "MenuDef.h"
#include "GlobalMsgDef.h"
#include "SafeArray.h"
#include "BlankWnd.h"
#include "BaseIcon.h"
#include "SysDef.h"
// CMenuIcon

// 菜单按键定义：CBaseIcon包含基础按键定义，CBlankWnd包含GUI定义
class DllExport CMenuIcon : public CBaseIcon, public CBlankWnd
{
	DECLARE_DYNAMIC(CMenuIcon)

public:
	/*-----------------------------------构建按键------------------------------------*/
	CMenuIcon(CWnd *pParentWnd);
	BOOL CreateIcon(const STRUCT_ICON * pIconDef, RECT Pos, COLORREF BkClr = UNSELECTED_ICON_BK_CLR, BOOL Visible = TRUE);
	/*-------------------------------------------------------------------------------*/
	virtual ~CMenuIcon();
protected :
	COLORREF	mBkClr ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	/*-----------------------------------按键响应------------------------------------*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/*-------------------------------------------------------------------------------*/

	/*-----------------------------------绘制按键------------------------------------*/
	afx_msg void OnPaint();
	void ShowIcon(CDC * pDC);
	/*-------------------------------------------------------------------------------*/

	/*-----------------------------------修改背景色----------------------------------*/
	void ModifyBkColor(COLORREF BkClr);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	/*-------------------------------------------------------------------------------*/
};


