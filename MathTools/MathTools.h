// MathTools.h : MathTools DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMathToolsApp
// �йش���ʵ�ֵ���Ϣ������� MathTools.cpp
//

class CMathToolsApp : public CWinApp
{
public:
	CMathToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
