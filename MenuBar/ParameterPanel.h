#pragma once
#include "BlankWnd.h"
#include "PubMacroDef.h"
#include "MenuDef.h"
#include "ParamIcon.h"
#include "SysDef.h"
#include <list>

// CParameterPanel
using namespace std ;

class DllExport CParameterPanel : public CBlankWnd
{
	DECLARE_DYNAMIC(CParameterPanel)

public:
	CParameterPanel(CWnd *pParentWnd, RECT Rect);
	virtual ~CParameterPanel();
protected :
	list <CParamIcon *> mIcons ;
	CRect	mRect ;
	CSize	mIconSize ;
	int		mIdxAppendBlock ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Reset(void);
	int RemoveIcon(WORD IconID);
	BOOL CreateLine(int CntIcon);
	BOOL CreateLine(int CntIcon, const STRUCT_ACCEL_ICON * pIconList) ;
	BOOL CreateLine(int CntIcon, const STRUCT_PARAM_ICON * pIconList) ;
	/* 当可编辑参数栏被修改，将消息向父类传递 */
	afx_msg LRESULT OnParamModified(WPARAM ItemID, LPARAM pItem);
	virtual void ParamModifiedCallback(WORD ItemID,  CParamIconAttr *pItemAttr);
	BOOL Append(int CntIcon, const STRUCT_PARAM_ICON * pIcon);
	BOOL SetIconTitle(WORD IconID, const WCHAR * pTitle);
	BOOL UpdateParameter(WORD id, UNION_DATA_TRANSFER val);
	BOOL SetIconTitleFont(WORD id, int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL) ;
	BOOL SetIconParamFont(WORD id, int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL) ;
private :
	POINT FindNewIconPos() ;
	BOOL AppendIcon(RECT IconPos, const STRUCT_PARAM_ICON * pIconDef);
	BOOL UpdateParameter(CParamIconAttr * pIcon, UNION_DATA_TRANSFER val);
	BOOL AppendSplitIcons(int CntIcon, const STRUCT_PARAM_ICON * pIconDef, BOOL VertAlign) ;
	BOOL SetIconTitle(CParamIconAttr * pIcon, const WCHAR * pTitle);
	BOOL SetIconTitleFont(CParamIcon * pIcon, int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL) ;
	BOOL SetIconParamFont(CParamIcon * pIcon, int FontSize, COLORREF FontClr, const WCHAR *pFont = NULL ) ;
	BOOL AppendIcon(const STRUCT_PARAM_ICON * pIconDef);
	CParamIcon *FindIcon(WORD id) ;
};


