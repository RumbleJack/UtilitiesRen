// MenuBar.h : MenuBar DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMenuBarApp
// �йش���ʵ�ֵ���Ϣ������� MenuBar.cpp
//

class CMenuBarApp : public CWinApp
{
public:
	CMenuBarApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
