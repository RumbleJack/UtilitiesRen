// SmplImgWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "SmplImgWnd.h"


// CSmplImgWnd

IMPLEMENT_DYNAMIC(CSmplImgWnd, CBlankWnd)

CSmplImgWnd::CSmplImgWnd(CWnd *pParentWnd, RECT Pos, BOOL FitImgSize, BOOL Titled, BOOL Sizing, BOOL Visiable)
: CBlankWnd(pParentWnd, Pos, Titled, Sizing, Visiable)
, mpImg(NULL)
{
	mFitImgSize = FitImgSize ;
}

CSmplImgWnd::~CSmplImgWnd()
{
	if(mpImg != NULL)
	{
		if(!mpImg->IsNull())
			mpImg->Destroy() ;
		delete mpImg ;
	}
}


BEGIN_MESSAGE_MAP(CSmplImgWnd, CBlankWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CSmplImgWnd 消息处理程序



void CSmplImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(mpImg != NULL)
	{
		if(!mpImg->IsNull())
			mpImg->Draw(dc.GetSafeHdc(), -mHorzPos, -mVertPos) ;
	}
	ExDraw(&dc) ;
}

int CSmplImgWnd::AttachGrayImage(int cx, int cy, BYTE * pPixels)
{
	if(mpImg == NULL)
		mpImg = new CImage ;
	else
	{
		if(!mpImg->IsNull())
			mpImg->Destroy() ;
	}
	mpImg->Create(cx, -cy, BPP_GRAY_IMG) ; // top-down
	int Pitch = mpImg->GetPitch() ;
	BYTE *pBits = (BYTE *)mpImg->GetBits() ;
	int DataSize = abs(Pitch) ;
	for(int i = 0 ; i < cy ; i++)
	{
		memcpy(pBits, pPixels, DataSize) ;
		pPixels += cx ;
		pBits += Pitch ;
	}
	RGBQUAD *pLUT = new RGBQUAD [256] ;
	for(int i = 0 ; i < 256 ; i++)
	{
		(pLUT + i)->rgbBlue = (pLUT + i)->rgbGreen = (pLUT+i)->rgbRed = i ;
		(pLUT + i)->rgbReserved = 0 ;
	}
	mpImg->SetColorTable(0,256, pLUT) ;
	delete [] pLUT ;

	if(mFitImgSize)
	{
		FitWndSizeToImg(cx, cy) ;
		ShowScrollBar(SB_BOTH, FALSE) ;
	}
	else
		SetupScrollBar() ;
	RedrawWindow() ;
	return 0;
}

int CSmplImgWnd::AttachColorImage(int cx, int cy, BYTE * pPixels)
{
	if(mpImg == NULL)
		mpImg = new CImage ;
	else
	{
		if(!mpImg->IsNull())
			mpImg->Destroy() ;
	}
	mpImg->Create(cx, -cy, BPP_COLOR_IMG) ; // top-down
	int Pitch = mpImg->GetPitch() ;
	BYTE *pBits = (BYTE *)mpImg->GetBits() ;
	int DataSize = abs(Pitch) ;
	for(int i = 0 ; i < cy ; i++)
	{
		memcpy(pBits, pPixels, DataSize) ;
		pPixels += cx * BYTE_COLOR_IMG ;
		pBits += Pitch ;
	}
	if(mFitImgSize)
	{
		FitWndSizeToImg(cx, cy) ;
		ShowScrollBar(SB_BOTH, FALSE) ;
	}
	else
		SetupScrollBar() ;
	RedrawWindow() ;
	return 0;
}

void CSmplImgWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	SetupScrollBar() ;
}

int CSmplImgWnd::SetupScrollBar()
{
	if(mpImg != NULL)
	{
		if(!mpImg->IsNull())
		{
			CRect WndRect ;
			GetClientRect(WndRect) ;
			if(WndRect.Width() < mpImg->GetWidth())
			{
				SetScrollRange(SB_HORZ, 0, mpImg->GetWidth() - WndRect.Width()) ;
				mHorzPos = 0 ;
				SetScrollPos(SB_HORZ, mHorzPos) ;
				ShowScrollBar(SB_HORZ, TRUE) ;
			}
			else
				ShowScrollBar(SB_HORZ, FALSE) ;
			if(WndRect.Height() < mpImg->GetHeight())
			{
				SetScrollRange(SB_VERT, 0, mpImg->GetHeight() - WndRect.Height()) ;
				mVertPos = 0 ;
				SetScrollPos(SB_VERT, mVertPos) ;
				ShowScrollBar(SB_VERT, TRUE) ;
			}
			else
				ShowScrollBar(SB_VERT, FALSE) ;
		}
	}
	return 0;
}

int CSmplImgWnd::FitWndSizeToImg(int cx, int cy)
{
	CRect WndClient ;
	CRect WndFrame ;
	GetClientRect(WndClient) ;
	GetWindowRect(WndFrame) ;
	mpParentWnd->ScreenToClient(WndFrame) ;
	WndFrame.right += cx-WndClient.Width() ;
	WndFrame.bottom += cy-WndClient.Height() ;
	MoveWindow(WndFrame) ;
	return 0;
}

void CSmplImgWnd::ExDraw(CDC * pDC)
{
}

