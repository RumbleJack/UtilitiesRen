
// TestWndDoc.cpp : CTestWndDoc ���ʵ��
//

#include "stdafx.h"
#include "TestWnd.h"

#include "TestWndDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestWndDoc

IMPLEMENT_DYNCREATE(CTestWndDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestWndDoc, CDocument)
END_MESSAGE_MAP()


// CTestWndDoc ����/����

CTestWndDoc::CTestWndDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTestWndDoc::~CTestWndDoc()
{
}

BOOL CTestWndDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTestWndDoc ���л�

void CTestWndDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CTestWndDoc ���

#ifdef _DEBUG
void CTestWndDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestWndDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestWndDoc ����
