#pragma once
#include "SafeArray.h"

template <class T_DATA>
class  __declspec( dllexport ) CDynamicVector : public CSafeArray < T_DATA >
{
public :
	CDynamicVector(int Size)
		: CSafeArray <T_DATA> (Size)
		, mVectorTail(0)
		, mStkExpSize(Size)
	{
	}

	~CDynamicVector()
	{
	}

	int Add(const T_DATA &Ele)
	{
		if(mVectorTail < mSize)
		{
			*(mpData + mVectorTail++) = Ele ;
		}
		else
		{
			T_DATA *pBuf = new T_DATA [mSize + mStkExpSize] ;
			memcpy(pBuf, mpData, mSize * sizeof(T_DATA)) ;
			delete [] mpData ;
			mpData = pBuf ;
			mSize += mStkExpSize ;
			*(mpData + mVectorTail++) = Ele ;
		}
		return mVectorTail ;
	}

	inline void ClearElement()
	{
		mVectorTail = 0 ;
	}

	inline int GetCntElement()
	{
		return mVectorTail ;
	}

	inline T_DATA &GetAt(int Pos)
	{
		return *(mpData + Pos) ;
	}

	inline void SetAt(int Pos, T_DATA &Val)
	{
		*(mpData + Pos) = Val ;
	}

	void SaveToFile(LPCTSTR pFileName)
	{
		FILE *pFile = NULL ;
		if(_wfopen_s(&pFile, pFileName, _T("wb")) == 0)
		{
			long CntSmpl = mVectorTail ;
			fwrite(&CntSmpl, sizeof(long), 1, pFile) ;
			if(CntSmpl > 0)
				fwrite(mpData, sizeof(T_DATA), CntSmpl, pFile) ;

			fclose(pFile) ;
		}
	}
protected :
	int	mStkExpSize ;
	int mVectorTail ;
} ;
