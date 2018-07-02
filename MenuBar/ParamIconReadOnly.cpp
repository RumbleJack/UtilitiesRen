// ParamIconReadOnly.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuBar.h"
#include "ParamIconReadOnly.h"


// CParamIconReadOnly

IMPLEMENT_DYNAMIC(CParamIconReadOnly, CParamIcon)

CParamIconReadOnly::CParamIconReadOnly(CWnd *pParentWnd, RECT Pos, const STRUCT_PARAM_ICON *pIcon)
: CParamIcon(pParentWnd, Pos, pIcon)
{

}

CParamIconReadOnly::~CParamIconReadOnly()
{
}


BEGIN_MESSAGE_MAP(CParamIconReadOnly, CParamIcon)
END_MESSAGE_MAP()

void CParamIconReadOnly::DrawIcon(CDC *pDC)
{
	DrawTitle(pDC) ;
	DrawParam(pDC) ;
}

// CParamIconReadOnly 消息处理程序


