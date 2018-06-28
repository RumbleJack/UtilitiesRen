
// TestWndView.cpp : CTestWndView ���ʵ��
//

#include "stdafx.h"
#include "TestWnd.h"

#include "TestWndDoc.h"
#include "TestWndView.h"
#include "SimpleMessageWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DrawMultiPropagatingCurves.h"
#include "PubMacroDef.h"
// CTestWndView

IMPLEMENT_DYNCREATE(CTestWndView, CView)

BEGIN_MESSAGE_MAP(CTestWndView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestWndView::OnFilePrintPreview)
	ON_COMMAND(ID_CURVE_WND, &CTestWndView::OnCurveWnd)
	ON_COMMAND(ID_TEST_NEW_CURVE_WND, &CTestWndView::OnTestNewCurveWnd)
	ON_COMMAND(ID_SHOW_MSG_WND, &CTestWndView::OnShowMsgWnd)
END_MESSAGE_MAP()

// CTestWndView ����/����

CTestWndView::CTestWndView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestWndView::~CTestWndView()
{
}

BOOL CTestWndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestWndView ����

void CTestWndView::OnDraw(CDC* /*pDC*/)
{
	CTestWndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTestWndView ��ӡ


void CTestWndView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTestWndView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestWndView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestWndView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CTestWndView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestWndView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTestWndView ���

#ifdef _DEBUG
void CTestWndView::AssertValid() const
{
	CView::AssertValid();
}

void CTestWndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestWndDoc* CTestWndView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestWndDoc)));
	return (CTestWndDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestWndView ��Ϣ�������

void CTestWndView::OnCurveWnd()
{
}


void CTestWndView::OnTestNewCurveWnd()
{
	CDrawMulti1DArray <int> Axis ;
	//CDraw1DArray <int> Axis ;
	Axis.SetStyle(CCoordinateAxis<int, int>::ORG_LB, CCoordinateAxis<int, int>::GRID) ;
	CRect RectWnd ;
	GetClientRect(RectWnd) ;
	RectWnd.InflateRect(-100, -100) ;
	Axis.SetDrawRange(RectWnd) ;
	Axis.SetDrawCurveRange(0, 640, -1080, 13070) ;
	Axis.SetCoordinateDefinition(32, 64, 1000, 2000) ;
	Axis.SetPaintAxisStyle(RGB(0, 0, 255), 2) ;
	Axis.SetPaintGridStyle(RGB(0, 128, 128), 1, PS_SOLID) ;
	Axis.SetAxisMarkStyle(RGB(255, 0, 0), 1, 10) ;
	Axis.SetAxisLabelStyle(RGB(0, 0, 255), 0, 0) ;
	Axis.SetAxisLabelPosition(10, 10) ;

	Axis.SetCurveStyle(CDrawPropagatingCurve <int> ::CURVE) ; //, RGB(255, 0, 255), 1, PS_SOLID) ;
	int *pY = new int [640] ;
	for(int i = 0 ; i < 640 ; ++i)
		*(pY + i) = -4000 + i * 50 ;
	int *pX = new int [640] ;
	for(int i = 0 ; i < 640 ; ++i)
		*(pX + i) = -3000 + i * 35 ;

	int idxStyle[2] ;
	idxStyle[0] = Axis.InsertCurveLineStyle(RGB(255, 0, 255), 1, PS_SOLID) ;
	idxStyle[1] = Axis.InsertCurveLineStyle(RGB(255, 128, 0), 1, PS_SOLID) ;
//	double Time_us ;
//PREPARE_TIME_COST() 
//BEGIN_TIME_COST()
	

	CDC *pDC = GetDC() ;
	RedrawWindow(RectWnd) ;
	Axis.DrawAxis(pDC) ;
	Axis.DrawArray(pDC, idxStyle[0], 640, pX) ;
	Axis.DrawArray(pDC, idxStyle[1], 640, pY) ;
	//Axis.EnableRestartWhenMeetRightMargin(TRUE) ;
	//int value[2] ;
	//BOOL MeetRightMargin ;
	//for(int i = 0 ; i < 640 ; ++i)
	//{
	//	value[0] = *(pX + i) ;
	//	value[1] = *(pY + i) ;
	//	Axis.DrawNewDot(pDC, 2, idxStyle, value, &MeetRightMargin) ;
	//	if(MeetRightMargin)
	//	{
	//		RedrawWindow(RectWnd) ;
	//		Axis.DrawAxis(pDC) ;
	//	}
	//	Sleep(10) ;
	//}
	//Axis.DrawArray(pDC, idxStyle[0], 640, pY) ;
	//Axis.DrawArray(pDC, idxStyle[1], 640, pX) ;
	ReleaseDC(pDC) ;
//END_TIME_COST(Time_us)

	//CString Note ;
	//Note.Format(_T("cost time (us): %.6f"), Time_us) ;
	//MessageBox(Note) ;

	delete [] pY ;
	delete [] pX ;
}


void CTestWndView::OnShowMsgWnd()
{
	RECT rect = {200, 200, 700, 400} ;
	CSimpleMessageWnd MsgWnd(this, rect, _T("this is a message wnd\n\rnext line"), NULL, RGB(0, 0, 255), 18) ;

	MessageBox(_T("press any key to continue")) ;
}
