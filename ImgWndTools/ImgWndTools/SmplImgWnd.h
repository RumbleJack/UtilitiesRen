#pragma once

#include <atlimage.h>
#define BPP_GRAY_IMG 8
#define BYTE_COLOR_IMG 3
#define BPP_COLOR_IMG BYTE_COLOR_IMG*8 

#include "BlankWnd.h"

// CSmplImgWnd

class __declspec( dllexport ) CSmplImgWnd : public CBlankWnd
{
	DECLARE_DYNAMIC(CSmplImgWnd)

public:
	CSmplImgWnd(CWnd *pParentWnd, RECT Pos, BOOL FitImgSize = FALSE, BOOL Titled = TRUE, BOOL Sizing = TRUE, BOOL Visiable = TRUE);
	virtual ~CSmplImgWnd();
protected :
	//CWnd *mpParentWnd ;
	BOOL mFitImgSize ;
	CImage *mpImg;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int AttachGrayImage(int cx, int cy, BYTE * pPixels);
	int AttachColorImage(int cx, int cy, BYTE * pPixels);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	int SetupScrollBar();
	int FitWndSizeToImg(int cx, int cy);
public:
	virtual void ExDraw(CDC * pDC);
};


