
// TestWndDoc.h : CTestWndDoc ��Ľӿ�
//


#pragma once


class CTestWndDoc : public CDocument
{
protected: // �������л�����
	CTestWndDoc();
	DECLARE_DYNCREATE(CTestWndDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTestWndDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


