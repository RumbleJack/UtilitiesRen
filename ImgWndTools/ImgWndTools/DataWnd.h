#pragma once
#include "SmplImgWnd.h"

// CDataWnd

class __declspec( dllexport ) CDataWnd : public CSmplImgWnd
{
	DECLARE_DYNAMIC(CDataWnd)
public :

public:
	CDataWnd(CWnd *pParentWnd, RECT Pos, BOOL FitImgSize = FALSE, BOOL Titled = TRUE, BOOL Sizing = TRUE, BOOL Visiable = TRUE);
	virtual ~CDataWnd();
protected :
	typedef enum
	{
		DATA_BYTE,
		DATA_WORD,
		DATA_SHORT,
		DATA_FLOAT,
		DATA_RGB
	} ENUM_DATA_TYPE ;

	typedef struct
	{
		BYTE Blue, Green, Red ;
	} STRUCT_RGB ;

	int	mcx ;
	int	mcy ;
	ENUM_DATA_TYPE	mDataType ;
	BYTE mTransposed ;
	void *mpData ;
private :
	template <class T>
	int CopyData(int cx, int cy, T *pData, BOOL Transpose)
	{
		if(Transpose)
		{
			mcx = cy & (~3) ;
			mcy = cx ;
			mpData = new T [mcx * mcy] ;
			T *pLine = (T *)mpData ;
			for(int i = 0 ; i < mcy ; i++)
			{
				for(int j = 0 ; j < mcx ; j++)
				{
					*pLine++ = *pData ;
					pData += cx ;
				}
				pData -= mcx * cx - 1 ;
			}
		}
		else
		{
			mcx = cx & (~3) ;
			mcy = cy ;
			mpData = new T [mcx * mcy] ;
			T *pLine = (T *)mpData ;
			for(int i = 0 ; i < mcy ; i++)
			{
				memcpy(pLine, pData, mcx * sizeof(T)) ;
				pLine += mcx ;
				pData += mcx ;
			}
		}
		return 0 ;
	}

#define MAX_GRAY 255
	template <class T>
	int StretchValue(int cx, int cy, T *pData, BYTE *pGray, T MinShown, T MaxShown)
	{
		if(MaxShown - MinShown <= (T)0.0001)
		{
			MinShown = MaxShown = *pData ;
			for(int i = 1 ; i < cx * cy ; i++)
			{
				if(*(pData + i) < MinShown)
					MinShown = *(pData + i) ;
				if(*(pData + i) > MaxShown)
					MaxShown = *(pData + i) ;
			}
		}
		if(MaxShown - MinShown <= (T)0.0001)
			return -1 ;
		for(int i = 0 ; i < cx * cy ; i++)
		{
			if(*(pData + i) <= MinShown)
				*(pGray + i) = 0 ;
			else if(*(pData + i) >= MaxShown)
				*(pGray + i) = MAX_GRAY ;
			else
				*(pGray + i) = (BYTE)((*(pData + i) - MinShown) * MAX_GRAY / (MaxShown - MinShown)) ;
		}

		return 0 ;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	int AttachImage(int cx, int cy, BYTE *pData, BYTE MinValShown = 0, BYTE MaxValShown = 255, BOOL Transpose = FALSE);
	int AttachImage(int cx, int cy, WORD *pData, WORD MinValShown = 0, WORD MaxValShown = 0, BOOL Transpose = FALSE) ;
	int AttachImage(int cx, int cy, short *pData, short MinValShown = 0 , short MaxValShown = 0 , BOOL Transpose = FALSE) ;
	int AttachImage(int cx, int cy, float *pData, float MinValShown = 0.0f, float MaxValShown = 0.0f, BOOL Transpose = FALSE) ;
	int AttachColorImage(int cx, int cy, BYTE *pData, BOOL Transpose = FALSE) ;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void ExDraw(CDC * pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


