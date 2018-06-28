#pragma once
#include "SafeArray.h"

template <class T_DATA>
class  __declspec( dllexport ) CSafe2DArray : public CSafeArray < CSafeArray <T_DATA> >
{
public :
	CSafe2DArray(int CntLine, int DotsPerLine)
		: CSafeArray < CSafeArray<T_DATA> > (CntLine)
	{
		for(int i = 0 ; i < mSize ; i++)
			(mpData+i)->Create(DotsPerLine) ;
	}

	CSafe2DArray()
		: CSafeArray<CSafeArray<T_DATA> > ()
	{
	}

	~CSafe2DArray()
	{
	}

	void Create(int CntLine, int DotsPerLine)
	{
		CSafeArray::Create(CntLine) ;
		for(int i = 0 ; i < mSize ; i++)
			(mpData+i)->Create(DotsPerLine) ;

	}
	inline int GetCntLine()
	{
		return mSize ;
	}

	inline int GetDotsPerLine()
	{
		return (mpData+i)->GetArraySize() ;
	}
} ;