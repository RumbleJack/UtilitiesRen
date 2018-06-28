#pragma once
#include "SafeArray.h"

template <class T_DATA>
class CSimpleCircledBuffer : public CSafeArray <T_DATA>
{
public :
	CSimpleCircledBuffer()
		: CSafeArray <T_DATA> ()
		, mPosToNewEle(0)
	{
	}

	~CSimpleCircledBuffer()
	{
	}

	CSimpleCircledBuffer(int size)
		: CSafeArray <T_DATA> (size)
		, mPosToNewEle(0)
	{
	}

	int	AppendElement(T_DATA ele)
	{
		*(mpData + mPosToNewEle) = ele ;
		return IncreasePos() ;
	}

	inline int GetLastAppendedElement()
	{
		return *(mpData + GetCircledPos(mPosToNewEle-1)) ;
	}

	inline int GetEarliestAppendedElement()
	{
		return *(mpData + mPosToNewEle) ;
	}

	inline int GetCircledPos(int pos)
	{
		return (pos + mSize) % mSize ;
	}

	inline int IncreasePos()
	{
		return mPosToNewEle = GetCircledPos(mPosToNewEle+1) ;
	}

protected :
	int	mPosToNewEle ;
} ;