// ImgWndTools.h : ImgWndTools DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CImgWndToolsApp
// �йش���ʵ�ֵ���Ϣ������� ImgWndTools.cpp
//

class CImgWndToolsApp : public CWinApp
{
public:
	CImgWndToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
