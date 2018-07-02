#pragma once
#include "PubMacroDef.h"
#include "Safe2DArray.h"

class DllExport CBasicDIPFunc
{
public:
	CBasicDIPFunc(void);
	~CBasicDIPFunc(void);
	template <class T_DATA>
	static void ZoomWithLinearInterpolation1D(int SizeSrc, T_DATA *pSrcData, int SrcCenter, int SizeOut, T_DATA *pOutData, int OutCenter, double ZoomRate, T_DATA valBkgrnd)
	{
		double SrcPos ;
		double InterpRate ;
		int	IdxSrc ;
		for(int i = 0 ; i < SizeOut ; ++i, ++pOutData)
		{
			SrcPos = (double)(i - OutCenter) / ZoomRate + SrcCenter ;
			IdxSrc = (int)SrcPos ;
			if(IdxSrc < 0 || IdxSrc >= SizeOut-1)
				*pOutData = valBkgrnd ;
			else
			{
				InterRate =SrcPos - IdxSrc ;
				*pOutData = (T_DATA)(*(pSrcData + IdxSrc) * (1.0f - InterRate) + *(pSrcData + IdxSrc + 1) * InterRate) ;
			}
		}
	}

	template <class T_DATA>
	static void ZoomWithLinearInterpolation2D(int WidthSrc, int HeightSrc, T_DATA *pSrcData, int XSrcCenter, int YSrcCenter, int WidthOut, int HeightOut, T_DATA *pOutData, int XOutCenter, int YOutCenter, double WidthZoomRate, double HeightZoomRate, T_DATA valBkgrnd)
	{
		double XPosSrc, YPosSrc ;
		double InterpRateX, InterpRateY ;
		int	IdxSrcX, IdxSrcY ;
		for(int i = 0 ; i < HeightOut ; ++i, pOutData += WidthOut)
		{
			YPosSrc = (double)(i - YOutCenter) / HeightZoomRate + YSrcCenter ;
			IdxSrcY = (int)YPosSrc ;
			if(IdxSrcY < 0 || IdxSrcY >= HeightSrc-1)
			{
				for(int j = 0 ; j < WidthOut ; ++j)
					*(pOutData+j) = valBkgrnd ;
			}
			else
			{
				InterRateY = YPosSrc - IdxSrcY ;
				for(int j = 0 ; j < WidthOut ; ++j)
				{
					XPosSrc = (double)(j - XOutCenter) / WidthZoomRate + XSrcCenter ;
					IdxSrcX = (int)XPosSrc ; 
					InterRateX = XPosSrc - IdxSrcX ;
					if(IdxSrcX < 0 || IdxSrcX >= WidthSrc-1)
						*(pOutData + j) = valBkgrnd ;
					else
					{
						*(pOutData+j) = (T_DATA)((*(pSrcData + IdxSrcY * WidthSrc + IdxSrcX) * (1.0 - InterRateX) + *(pSrcData + IdxSrcY * WidthSrc + IdxSrc + 1) * InterRateX) * (1.0 - InterRateY)
							+  (*(pSrcData + (IdxSrcY + 1) * WidthSrc + IdxSrcX) * (1.0 - InterRateX) + *(pSrcData + (IdxSrcY + 1) * WidthSrc + IdxSrc + 1) * InterRateX) * InterRateY);
					}
				}
			}
		}
	}

	template <class T_DATA>
	static void ZoomWithClosestNeighborInterpolation1D(int SizeSrc, T_DATA *pSrcData, int SrcCenter, int SizeOut, T_DATA *pOutData, int OutCenter, double ZoomRate, T_DATA valBkgrnd)
	{
		double InterpRate ;
		int	IdxSrc ;
		for(int i = 0 ; i < SizeOut ; ++i, ++pOutData)
		{
			IdxSrc = (int)((double)(i - OutCenter) / ZoomRate + SrcCenter + 0.5) ;
			if(IdxSrc < 0 || IdxSrc >= SizeOut)
				*pOutData = valBkgrnd ;
			else
				*pOutData = *(pSrcData + IdxSrc)  ;
		}
	}

	template <class T_DATA>
	static void ZoomWithClosestNeighborInterpolation2D(int WidthSrc, int HeightSrc, T_DATA *pSrcData, int XSrcCenter, int YSrcCenter, int WidthOut, int HeightOut, T_DATA *pOutData, int XOutCenter, int YOutCenter, double WidthZoomRate, double HeightZoomRate, T_DATA valBkgrnd)
	{
		int	IdxSrcX, IdxSrcY ;
		for(int i = 0 ; i < HeightOut ; ++i, pOutData += WidthOut)
		{
			IdxSrcY = (int)((double)(i - YOutCenter)/ HeightZoomRate + YSrcCenter + 0.5) ;
			if(IdxSrcY < 0 || IdxSrcY >= HeightSrc)
			{
				for(int j = 0 ; j < WidthOut ; ++j)
					*(pOutData+j) = valBkgrnd ;
			}
			else
			{
				for(int j = 0 ; j < WidthOut ; ++j)
				{
					IdxSrcX = (int)((double)(j - XOutCenter) / WidthZoomRate + XSrcCenter + 0.5) ;
					if(IdxSrcX < 0 || IdxSrcX >= WidthSrc-1)
						*(pOutData + j) = valBkgrnd ;
					else
						*(pOutData+j) = *(pSrcData + IdxSrcY * WidthSrc + IdxSrcX) ;
				}
			}
		}
	}

	static void SetupCublicSplineConvKernel(int ZoomInRate, CSafe2DArray <double> *pKernel)
	{
		pKernel->Create(ZoomInRate, 4) ;
		for(int i = 0 ; i < ZoomInRate ; ++i)
		{
			double s = (double)i / (double)ZoomInRate ;
			pKernel->FindAt(i)[0] = (-s * s * s + 2 * s * s - s)/ 2 ;
			pKernel->FindAt(i)[1] =  (3 * s * s * s - 5 * s * s + 2) / 2 ;
			pKernel->FindAt(i)[2] = (-3 * s * s * s + 4 * s * s + s) / 2 ;
			pKernel->FindAt(i)[3] =  (s * s * s - s * s) / 2 ;
		}
	}

	template <class T_DATA>
	static void ZoomWithCubicSplineInterpolation1D(int SizeSrc, T_DATA *pSrcData, int SrcCenter, int SrcPitch, int SizeOut, T_DATA *pOutData, int OutCenter, int OutPitch, int ZoomInRate, T_DATA valBkgrnd, CSafe2DArray <double> *pConvKernel = NULL)
	{
		if(pConvKernel == NULL)
		{
			CSafe2DArray <double> mCoeff ;
			SetupCublicSplineConvKernel(ZoomInRate, &mCoeff) ;
			pConvKernel = &mCoeff ;
		}
		int minOutIdx = OutCenter % ZoomInRate ;
		int maxOutIdx = (SizeOut - OutCenter) / ZoomInRate * ZoomInRate + OutCenter ;
		int minSrcIdx = SrcCenter - OutCenter / ZoomInRate ;
		int maxSrcIdx = SrcCenter + (SizeOut - OutCenter) / ZoomInRate ;
		for(int i = 0 ; i < minOutIdx ; ++i)
			*(pOutData + i * OutPitch) = valBkgrnd ;
		for(int i = maxOutIdx - ZoomInRate ; i < SizeOut ; ++i)
			*(pOutData + i * OutPitch) = valBkgrnd ;

		for(int i = minOutIdx, idxSrc = minSrcIdx ; i < maxOutIdx - ZoomInRate ; i += ZoomInRate, ++idxSrc)
		{
			if(idxSrc < 1 || idxSrc >= SizeSrc-2)
			{
				for(int j = 0 ; j < ZoomInRate ; ++j)
					*(pOutData + (i + j) * OutPitch) = valBkgrnd ;
			}
			else
			{
				for(int j = 0 ; j < ZoomInRate ; ++j)
				{
					*(pOutData + (i + j) * OutPitch) = (T_DATA)(*(pSrcData + (idxSrc - 1) * SrcPitch) * pConvKernel->FindAt(j)[0]
																			+ *(pSrcData + idxSrc * SrcPitch) * pConvKernel->FindAt(j)[1]
																			+ *(pSrcData + (idxSrc+1) * SrcPitch) * pConvKernel->FindAt(j)[2]
																			+ *(pSrcData + (idxSrc+2) * SrcPitch) * pConvKernel->FindAt(j)[3]) ;
				}
			}
		}
	}

	template <class T_DATA>
	static void ZoomInWithCubicSplineInterpolation2D(int WidthSrc, int HeightSrc, T_DATA *pSrcData, int XSrcCenter, int YSrcCenter, int WidthOut, int HeightOut, T_DATA *pOutData, int XOutCenter, int YOutCenter, int XZoomInRate, int YZoomInRate, T_DATA valBkgrnd)
	{
		CSafeArray <T_DATA> mBufHorzZoom(WidthOut * HeightSrc) ;
		T_DATA	*pPtrBuf = mBufHorzZoom.GetPtrToArray() ;
		CSafe2DArray <double> ConvKernel ;
		SetupCublicSplineConvKernel(XZoomInRate, &ConvKernel) ;
		for(int i = 0 ; i < HeightSrc ; ++i, pSrcData += WidthSrc, pPtrBuf += WidthOut)
		{
			ZoomWithCubicSplineInterpolation1D(WidthSrc, pSrcData, XSrcCenter, 1, WidthOut, pPtrBuf, XOutCenter, 1, XZoomInRate, valBkgrnd, &ConvKernel) ;
		}
		SetupCublicSplineConvKernel(YZoomInRate, &ConvKernel) ;
		pPtrBuf = mBufHorzZoom.GetPtrToArray() ;
		for(int i = 0 ; i < WidthOut ; ++i, ++pPtrBuf, ++pOutData)
		{
			ZoomWithCubicSplineInterpolation1D(HeightSrc, pPtrBuf, YSrcCenter, WidthOut, HeightOut, pOutData, YOutCenter, WidthOut, YZoomInRate, valBkgrnd, &ConvKernel) ;
		}
	}


	static int SnapImgWnd(CWnd * pWnd, LPCTSTR pImgFileName);
};
