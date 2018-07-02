#pragma once
#include "MenuDef.h"
#include "PubMacroDef.h"

// 基础按键定义
class DllExport CBaseIcon : public STRUCT_ICON 
{
public:
	CBaseIcon(void);
	CBaseIcon(STRUCT_ICON Def) ;
	CBaseIcon(WORD id, const WCHAR *pTitle, STRUCT_ICON *pSubMenu) ;
	~CBaseIcon(void);
public :
	BOOL CheckDefined()
	{
		return id != ID_ICON_EMPTY ;
	}
	void Reset()
	{
		id = ID_ICON_EMPTY ;
		pTitle = NULL ;
		CntSubMenu = 0 ;
		pSubMenu = NULL ;
	}
	void Load(STRUCT_ICON Def)
	{
		Load(&Def) ;
	}
	void Load(const STRUCT_ICON *pDef)
	{
		id = pDef->id ;
		pTitle = pDef->pTitle ;
		CntSubMenu = pDef->CntSubMenu ;
		pSubMenu = pDef->pSubMenu ;
	}
};

