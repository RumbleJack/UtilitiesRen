#pragma once
#include "MenuDef.h"
#include "GlobalMsgDef.h"
#include "SafeArray.h"
#include "BlankWnd.h"
#include "BaseIcon.h"
#include "SysDef.h"
// CMenuIcon

// �˵��������壺CBaseIcon���������������壬CBlankWnd����GUI����
class DllExport CMenuIcon : public CBaseIcon, public CBlankWnd
{
	DECLARE_DYNAMIC(CMenuIcon)

public:
	/*-----------------------------------��������------------------------------------*/
	CMenuIcon(CWnd *pParentWnd);
	BOOL CreateIcon(const STRUCT_ICON * pIconDef, RECT Pos, COLORREF BkClr = UNSELECTED_ICON_BK_CLR, BOOL Visible = TRUE);
	/*-------------------------------------------------------------------------------*/
	virtual ~CMenuIcon();
protected :
	COLORREF	mBkClr ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	/*-----------------------------------������Ӧ------------------------------------*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/*-------------------------------------------------------------------------------*/

	/*-----------------------------------���ư���------------------------------------*/
	afx_msg void OnPaint();
	void ShowIcon(CDC * pDC);
	/*-------------------------------------------------------------------------------*/

	/*-----------------------------------�޸ı���ɫ----------------------------------*/
	void ModifyBkColor(COLORREF BkClr);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	/*-------------------------------------------------------------------------------*/
};


