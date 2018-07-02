#pragma once
#include "MenuIcon.h"
#include "BaseObjectList.h"
using namespace std ;

// �����б�
class DllExport CIconList
{
public:
	CIconList(CWnd *pParentWnd = NULL);
	~CIconList(void);
public :
	// �����б�
	CBaseObjectList <CMenuIcon *> mIconList ;
	// ������
	CWnd *mpParentWnd ;
public :
	void SetParentWnd(CWnd *pWnd)
	{
		mpParentWnd = pWnd ;
	}
	void DestroyAllIcons(void);
	// ���¹��������б�
	BOOL Reload(POINT PosMenu, SIZE IconSize, STRUCT_ICON *pParentIcon, int CntIcon, const STRUCT_ICON * pMenu, BOOL VertAlign = TRUE) ;
	// Ϊѡ��һ���������˵���ָ������ɫ
	void ModifyIconBkClr(WORD ParentIcon, WORD HotIcon, COLORREF HotIconClr, COLORREF UnselectedIconClr);
};

