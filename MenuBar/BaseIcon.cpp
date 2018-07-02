#include "StdAfx.h"
#include "BaseIcon.h"


CBaseIcon::CBaseIcon(void)
{
	id = ID_ICON_EMPTY ;
	pTitle = NULL ;
	CntSubMenu = 0 ;
	pSubMenu = NULL ;
}

CBaseIcon::CBaseIcon(STRUCT_ICON Def)
{
	Load(&Def) ;
}

CBaseIcon::CBaseIcon(WORD id, const WCHAR *pTitle, STRUCT_ICON *pSubMenu)
{
	id = id ;
	pTitle = pTitle ;
	pSubMenu = pSubMenu ;
}

CBaseIcon::~CBaseIcon(void)
{
}
