// MiscTools.h : MiscTools DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMiscToolsApp
// �йش���ʵ�ֵ���Ϣ������� MiscTools.cpp
//

class CMiscToolsApp : public CWinApp
{
public:
	CMiscToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
