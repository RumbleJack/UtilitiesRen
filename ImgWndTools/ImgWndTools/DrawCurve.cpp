#include "StdAfx.h"
#include "DrawCurve.h"
#define MACRO_FREE_OBJ(x) {if(x!=NULL) delete x ;}

CDrawCurve::CDrawCurve(RECT Client, ENUM_ORGINAL_POS OrgPos)
: mpHorzAxis(NULL)
, mpVertAxis(NULL)
{
	mClient = Client ;
	mOrgPos = OrgPos ;

	SetupAxis(HORZ_AXIS, WIDTH_AXIS, CLR_AXIS, _T("X"), FONT_AXIS, CLR_AXIS, FONT_COORD) ;
	SetupAxis(VERT_AXIS, WIDTH_AXIS, CLR_AXIS, _T("Y"), FONT_AXIS, CLR_AXIS, FONT_COORD) ;
	SetupCoord(HORZ_AXIS, 0, 0.0f, 0, 0.0f, 0) ;
	SetupCoord(VERT_AXIS, 0, 0.0f, 0, 0.0f, 0) ;
}

CDrawCurve::~CDrawCurve(void)
{
	MACRO_FREE_OBJ(mpHorzAxis) ;
	MACRO_FREE_OBJ(mpVertAxis) ;
}

int CDrawCurve::SetupAxis(int IdxAxis, int WidthAxis, COLORREF ClrAxis, WCHAR * pNameAxis, WCHAR * pFontAxis, COLORREF ClrCoord, WCHAR * pFontCoord)
{
	STRUCT_AXIS *pAxis = NULL ;
	switch(IdxAxis)
	{
	case HORZ_AXIS :
		if(mpHorzAxis == NULL)
			mpHorzAxis = new STRUCT_AXIS ;
		pAxis = mpHorzAxis ;
		break ;
	case VERT_AXIS :
		if(mpVertAxis == NULL)
			mpVertAxis = new STRUCT_AXIS ;
		pAxis = mpVertAxis ;
	}

	if(pAxis != NULL)
	{
		pAxis->Width = WidthAxis ;
		pAxis->Color = ClrAxis ;
		wcsncpy_s(pAxis->pName, MAX_CNT_AXIS_NAME, pNameAxis, _TRUNCATE) ;
		memset(&pAxis->FontName, 0, sizeof(pAxis->FontName));
		wcsncpy_s(pAxis->FontName.lfFaceName, LF_FACESIZE,pFontAxis, _TRUNCATE);
		pAxis->FontName.lfHeight = SIZE_FONT_AXIS * 3 / 2 ;
		pAxis->FontName.lfWidth = SIZE_FONT_AXIS ;
		pAxis->FontName.lfWeight = FW_BOLD ;

		pAxis->ClrCoord = ClrCoord ;
		memset(&pAxis->FontCoord, 0, sizeof(pAxis->FontName));
		wcsncpy_s(pAxis->FontCoord.lfFaceName, LF_FACESIZE, pFontCoord, _TRUNCATE);
		pAxis->FontCoord.lfHeight = SIZE_FONT_COORD * 3 / 2 ;
		pAxis->FontCoord.lfWidth = SIZE_FONT_COORD ;
		pAxis->FontCoord.lfWeight = FW_NORMAL ;
		return 0;
	}
	else
		return -1 ;
}

int CDrawCurve::SetupCoord(int IdxAxis, int MinVal, float PosMinVal, int MaxVal, float PosMaxVal, int Interval)
{
	STRUCT_AXIS *pAxis = NULL ;
	switch(IdxAxis)
	{
	case HORZ_AXIS :
		pAxis = mpHorzAxis ;
		break ;
	case VERT_AXIS :
		pAxis = mpVertAxis ;
	}

	if(pAxis != NULL)
	{
		pAxis->DataType = INT_VAL ;
		pAxis->MinVal.Int = MinVal ;
		pAxis->PosMinVal = PosMinVal ;
		pAxis->MaxVal.Int = MaxVal ;
		pAxis->PosMaxVal = PosMaxVal ;
		pAxis->Interval.Int = Interval ;
		return 0;
	}
	else
		return -1 ;
}

int CDrawCurve::SetupCoord(int IdxAxis, float MinVal, float PosMinVal, float MaxVal, float PosMaxVal, float Interval)
{
	STRUCT_AXIS *pAxis = NULL ;
	switch(IdxAxis)
	{
	case HORZ_AXIS :
		pAxis = mpHorzAxis ;
		break ;
	case VERT_AXIS :
		pAxis = mpVertAxis ;
	}

	if(pAxis != NULL)
	{
		pAxis->DataType =FLT_VAL ;
		pAxis->MinVal.Flt = MinVal ;
		pAxis->PosMinVal = PosMinVal ;
		pAxis->MaxVal.Flt = MaxVal ;
		pAxis->PosMaxVal = PosMaxVal ;
		pAxis->Interval.Flt = Interval ;
		return 0;
	}
	else
		return -1 ;
}

int CDrawCurve::ResizeFrame(int Width, int Height)
{
	mClient.right = mClient.left + Width ;
	mClient.bottom = mClient.top + Height ;
	return 0 ;
}

int CDrawCurve::MoveOriginal(int x0, int y0)
{
	mClient.right = mClient.left + x0 ;
	mClient.bottom = mClient.top + y0 ;
	mClient.left = x0 ;
	mClient.top = y0 ;

	return 0;
}

int CDrawCurve::ResizeFrame(int Left, int Top,  int Right, int Bottom)
{
	mClient.left = Left ;
	mClient.right = Right ;
	mClient.top = Top ;
	mClient.bottom = Bottom ;

	return 0 ;
}

void CDrawCurve::DrawAxis(CDC *pDC)
{
	if(mpHorzAxis != NULL)
		DrawAxis(HORZ_AXIS, pDC, mpHorzAxis) ;
	if(mpVertAxis != NULL)
		DrawAxis(VERT_AXIS, pDC, mpVertAxis) ;
}

void CDrawCurve::DrawAxis(int IdxAxis, CDC *pDC, STRUCT_AXIS *pAxis)
{
	CPen PenAxis(PS_SOLID, pAxis->Width, pAxis->Color) ;
	CFont FontAxisName ;
	FontAxisName.CreateFontIndirectW(&(pAxis->FontName)) ;
	CFont FontCoord ;
	FontCoord.CreateFontIndirectW(&(pAxis->FontCoord)) ;
	
	CPen *pOldPen = pDC->SelectObject(&PenAxis) ;
	int OldROP = pDC->SetROP2(R2_COPYPEN) ;
	CPoint OrgPos ;
	int	SizeAxis ;
	CPoint NamePos ;

	switch(IdxAxis)
	{
	case HORZ_AXIS :
		switch(mOrgPos)
		{
		case ORG_LEFT_TOP :
			OrgPos = mClient.TopLeft() ;
			SizeAxis = mClient.Width() ;
			break ;
		case ORG_LEFT_BOTTOM :
			OrgPos = CPoint(mClient.left, mClient.bottom) ;
			SizeAxis = mClient.Width() ;
			break ;
		case ORG_RIGHT_TOP :
			OrgPos = CPoint(mClient.right, mClient.top) ;
			SizeAxis = -mClient.Width() ;
			break ;
		case ORG_RIGHT_BOTTOM :
			OrgPos = mClient.BottomRight() ;
			SizeAxis = -mClient.Width() ;
			break ;
		}
		pDC->MoveTo(OrgPos) ;
		pDC->LineTo(OrgPos.x+SizeAxis, OrgPos.y) ;
		break ;
	case VERT_AXIS :
		switch(mOrgPos)
		{
		case ORG_LEFT_TOP :
			OrgPos = mClient.TopLeft() ;
			SizeAxis = mClient.Height() ;
			break ;
		case ORG_LEFT_BOTTOM :
			OrgPos = CPoint(mClient.left, mClient.bottom) ;
			SizeAxis = -mClient.Height() ;
			break ;
		case ORG_RIGHT_TOP :
			OrgPos = CPoint(mClient.right, mClient.top) ;
			SizeAxis = mClient.Height() ;
			break ;
		case ORG_RIGHT_BOTTOM :
			OrgPos = mClient.BottomRight() ;
			SizeAxis = -mClient.Height() ;
			break ;
		}
		pDC->MoveTo(OrgPos) ;
		pDC->LineTo(OrgPos.x, OrgPos.y + SizeAxis) ;
		break ;
	}

	pDC->SetROP2(OldROP) ;
	pDC->SelectObject(pOldPen) ;
	
}

//void CDrawCurve::DrawCurve(CDC * pDC, int CntDot, int * pVal, COLORREF Color, ENUM_CURVE_STYLE Style)
//{
//	
//}
//
//void CDrawCurve::DrawCurve(CDC * pDC, int CntDot , float * pVal, COLORREF Color, ENUM_CURVE_STYLE Style)
//{
//}
//
//void CDrawCurve::DrawCurve(CDC * pDC, int CntDot, POINT * pPos, COLORREF Color, ENUM_CURVE_STYLE Style)
//{
//}
//
//void CDrawCurve::DrawCurve(CDC * pDC, int CntDot, STRUCT_FLT_POINT * pPos, COLORREF Color, ENUM_CURVE_STYLE Style)
//{
//}
//
//int CDrawCurve::DrawGrid(BOOL Enable, int LineStyle, int Width, COLORREF Color)
//{
//	if(Enable)
//	{
//		if(mpGrid == NULL)
//			mpGrid = new LOGPEN ;
//		mpGrid->lopnStyle = LineStyle ;
//		mpGrid->lopnWidth = CPoint(Width, 0) ;
//		mpGrid->lopnColor = Color ;
//	}
//	else
//	{
//		if(mpGrid != NULL)
//		{
//			delete mpGrid ;
//			mpGrid = NULL ;
//		}
//	}
//
//
//	return 0;
//}

int CDrawCurve::AddCurve(int CntDot, int * pData)
{
	return 0;
}
