// DataWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImgWndTools.h"
#include "DataWnd.h"

// CDataWnd

IMPLEMENT_DYNAMIC(CDataWnd, CSmplImgWnd)

CDataWnd::CDataWnd(CWnd *pParentWnd, RECT Pos, BOOL FitImgSize, BOOL Titled, BOOL Sizing, BOOL Visiable)
: CSmplImgWnd(pParentWnd, Pos, FitImgSize, Titled, Sizing, Visiable)
, mpData(NULL)
{

}

CDataWnd::~CDataWnd()
{
	if(mpData != NULL)
		delete [] mpData ;
}


BEGIN_MESSAGE_MAP(CDataWnd, CSmplImgWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CDataWnd 消息处理程序



int CDataWnd::AttachImage(int cx, int cy, BYTE *pData, BYTE MinValShown, BYTE MaxValShown, BOOL Transpose)
{
	mDataType = DATA_BYTE ;
	mTransposed = Transpose ;
	if(mpData != NULL)
		delete [] mpData ;
	CopyData(cx, cy, pData, Transpose) ;
	BYTE *pBuf = new BYTE [mcx * mcy] ;
	StretchValue(mcx, mcy, (BYTE*)mpData, pBuf, MinValShown, MaxValShown) ;
	CSmplImgWnd::AttachGrayImage(mcx, mcy, pBuf) ;
	delete [] pBuf ;

	return 0;
}

int CDataWnd::AttachImage(int cx, int cy, WORD *pData, WORD MinValShown, WORD MaxValShown, BOOL Transpose)
{
	mDataType = DATA_WORD ;
	mTransposed = Transpose ;
	if(mpData != NULL)
		delete [] mpData ;
	CopyData(cx, cy, pData, Transpose) ;

	BYTE *pBuf = new BYTE [mcx * mcy] ;
	StretchValue(mcx, mcy, (WORD *)mpData, pBuf, MinValShown, MaxValShown) ;
	CSmplImgWnd::AttachGrayImage(mcx, mcy, pBuf) ;
	delete [] pBuf ;

	return 0;
}

int CDataWnd::AttachImage(int cx, int cy, short *pData, short MinValShown, short MaxValShown, BOOL Transpose)
{
	mDataType = DATA_SHORT ;
	mTransposed = Transpose ;
	if(mpData != NULL)
		delete [] mpData ;
	CopyData(cx, cy, pData, Transpose) ;

	BYTE *pBuf = new BYTE [mcx * mcy] ;
	StretchValue(mcx, mcy, (short *)mpData, pBuf, MinValShown, MaxValShown) ;
	CSmplImgWnd::AttachGrayImage(mcx, mcy, pBuf) ;
	delete [] pBuf ;

	return 0;
}

int CDataWnd::AttachImage(int cx, int cy, float *pData, float MinValShown, float MaxValShown, BOOL Transpose)
{
	mDataType = DATA_FLOAT ;
	mTransposed = Transpose ;
	if(mpData != NULL)
		delete [] mpData ;
	CopyData(cx, cy, pData, Transpose) ;

	BYTE *pBuf = new BYTE [mcx * mcy] ;
	StretchValue(mcx, mcy, (float *)mpData, pBuf, MinValShown, MaxValShown) ;
	CSmplImgWnd::AttachGrayImage(mcx, mcy, pBuf) ;
	delete [] pBuf ;

	return 0;
}

int CDataWnd::AttachColorImage(int cx, int cy, BYTE *pData, BOOL Transpose)
{
	mDataType = DATA_RGB ;
	mTransposed = Transpose ;
	if(mpData != NULL)
		delete [] mpData ;
	CopyData(cx, cy, (STRUCT_RGB *)pData, Transpose) ;
	CSmplImgWnd::AttachColorImage(mcx, mcy, (BYTE *)mpData) ;
	return 0;
}

void CDataWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(mpData != NULL)
	{
		int x = point.x + mHorzPos ;
		int y = point.y + mVertPos ;
		if(x >= 0 && x < mcx && y >= 0 && y < mcy)
		{
			CString mNote ;
			switch(mDataType)
			{
			case DATA_BYTE :
				mNote.Format(_T("(%d,%d) - %XH"), x, y, *((BYTE *)mpData + x + y * mcx)) ;
				break ;
			case DATA_SHORT :
				mNote.Format(_T("(%d,%d) - %d"), x,y,*((short*)mpData + x + y * mcx)) ;
				break ;
			case DATA_WORD :
				mNote.Format(_T("(%d,%d) - %d"), x, y, *((WORD*)mpData + x + y*mcx)) ;
				break ;
			case DATA_FLOAT :
				mNote.Format(_T("(%d,%d) - %.3f"), x,y,*((float*)mpData + x + y * mcx)) ;
				break ;
			case DATA_RGB :
				{
					STRUCT_RGB *pClr = ((STRUCT_RGB*)mpData+x+y*mcx) ;
					mNote.Format(_T("(%d,%d) - (R%XH,G%XH,B%XH)"), pClr->Red, pClr->Green, pClr->Blue) ;
				}
				break ;
			default :
				break ;
			}
			MessageBox(mNote, _T("pick-up pixel"), MB_OK) ;
		}
	}
	CSmplImgWnd::OnLButtonDown(nFlags, point);
}

void CDataWnd::ExDraw(CDC * pDC)
{
}

void CDataWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CSmplImgWnd::OnLButtonDblClk(nFlags, point);
}
