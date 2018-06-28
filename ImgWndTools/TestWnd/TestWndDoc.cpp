
// TestWndDoc.cpp : CTestWndDoc 类的实现
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


// CTestWndDoc 构造/析构

CTestWndDoc::CTestWndDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTestWndDoc::~CTestWndDoc()
{
}

BOOL CTestWndDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTestWndDoc 序列化

void CTestWndDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CTestWndDoc 诊断

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


// CTestWndDoc 命令
