// Geometry.h : Geometry DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGeometryApp
// �йش���ʵ�ֵ���Ϣ������� Geometry.cpp
//

class CGeometryApp : public CWinApp
{
public:
	CGeometryApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
