
// TestWndView.h : CTestWndView ��Ľӿ�
//


#pragma once
class CTestWndView : public CView
{
protected: // �������л�����
	CTestWndView();
	DECLARE_DYNCREATE(CTestWndView)

// ����
public:
	CTestWndDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTestWndView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCurveWnd();
	afx_msg void OnTestNewCurveWnd();
	afx_msg void OnShowMsgWnd();
};

#ifndef _DEBUG  // TestWndView.cpp �еĵ��԰汾
inline CTestWndDoc* CTestWndView::GetDocument() const
   { return reinterpret_cast<CTestWndDoc*>(m_pDocument); }
#endif

