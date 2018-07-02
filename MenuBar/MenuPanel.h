#pragma once
#include "BlankWnd.h"
#include "MenuIcon.h"
#include "IconList.h"
#include "PubMacroDef.h"
#include "SysDef.h"

// CMenuPanel

class DllExport CMenuPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CMenuPanel)

public:
	CMenuPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CMenuPanel();
protected :
	// �ϼ���������
	CBaseIcon mParentIcon ;
	// �˵��������б�
	CIconList mMenuBar ;
	// ���������ο��ߴ�
	CSize	  mIconRefSize ;
	// �˵����λ��
	CRect	  mBarPos ;
	// һ���˵�������Ŀ�������б�
	int	  mCntRootMenuIcon ;
	const STRUCT_ICON *mpRootMenu ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL LoadRootMenu(int CntIcon, const STRUCT_ICON * pRootMenu, int DefaultIconWidth, int DefaultIconHeight);
	// �ú���δʹ��
	void SetIconRefSize(int Width, int Height);
	// ������ʵİ����ߴ�
	SIZE FindIconSize(int CntIcon, int DefaultWidth, int DefaultHeight);
	// �ж��Ƿ�����һ���˵������ڷ����ϼ��˵���
	BOOL CheckBackMenuLevel(STRUCT_ICON *pIcon)
	{
		return mParentIcon.id == pIcon->id ;
	}
	// ��Ӧ�˵������������͵���ϢWM_MENU_ITEM_CLICKED������wParamΪ����id������lParamΪ�˵�����ָ��
	afx_msg LRESULT OnMenuItemClicked(WPARAM wParam, LPARAM lParam);
};


