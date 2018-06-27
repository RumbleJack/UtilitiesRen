#pragma once
#include "PubMacroDef.h"

template <class T_DATA>
class  /*DllExport*/ CSafeArray
{
public :
	CSafeArray()
		: mpData(NULL)
		, mSize(0)
	{
	}

	CSafeArray(int SizeArray)
		: mpData(new T_DATA [SizeArray])
		, mSize(SizeArray)
	{
	}

	CSafeArray(CSafeArray <T_DATA> &SrcArray)
		: mpData(new T_DATA [SrcArray.GetArraySize()])
		, mSize(SrcArray.GetArraySize())
	{
		memcpy(mpData, SrcArray.GetPtrToArray(), mSize * sizeof(T_DATA)) ;
	}

	~CSafeArray()
	{
		DESTROY_MEMORY(mpData) ;
	}

	void FreeAll()
	{
		DESTROY_MEMORY(mpData) ;
		mSize = 0 ;
	}

	inline T_DATA *GetPtrToArray()
	{
		return mpData ;
	}

	inline int	GetArraySize()
	{
		return mSize ;
	}

	void operator = (CSafeArray <T_DATA> &Src)
	{
		if(mpData != NULL)
			memcpy(mpData, Src.GetPtrToArray(), min(mSize, Src.GetArraySize()) * sizeof(T_DATA)) ;
	}

	void operator = (T_DATA Val)
	{
		SetVal(Val) ;
	}

	void Copy(const T_DATA *pData)
	{
		if(mpData != NULL)
			memcpy(mpData, pData, mSize * sizeof(T_DATA)) ;
	}

	void Copy(int SizeData, const T_DATA *pData)
	{
		if(mpData != NULL)
			memcpy(mpData, pData, min(mSize, SizeData) * sizeof(T_DATA)) ;
	}

	template <class T_SRC>
	void CopyWithScaling(T_SRC *pSrc, T_SRC Rate)
	{
		if(mpData != NULL)
		{
			for(int i = 0 ; i < mSize ; ++i)
				*(mpData + i) = (T_DATA)(*(pSrc + i) * Rate) ;
		}
	}

	int ExportData(int Size, T_DATA *pData)
	{
		int ActSize = min(Size, mSize) ;
		memcpy(pData, mpData, ActSize * sizeof(T_DATA)) ;
		return ActSize ;
	}

	int ExportData(void *pData)
	{
		memcpy(pData, mpData, mSize * sizeof(T_DATA)) ;
		return mSize ;
	}

	void ExportScaledData(T_DATA *pOutData, double Scale)
	{
		for (int i = 0; i < mSize; ++i)
			*(pOutData + i) = (T_DATA)(*(mpData + i) * Scale);
	}

	inline T_DATA & operator [] (int Idx)
	{
		return *(mpData + Idx) ;
	}

	inline T_DATA & FindAt(int Idx)
	{
		return *(mpData + Idx) ;
	}

	int Create(int SizeArray)
	{
		DESTROY_MEMORY(mpData) ;
		mpData = new T_DATA [SizeArray] ;
		return (mSize = SizeArray) ;
	}

	void SetVal(T_DATA Val)
	{
		for(int i = 0 ; i < mSize ; ++i)
			*(mpData + i) = Val ;
	}

	inline bool CheckValid()
	{
		return mSize > 0 && mpData != NULL ;
	}

	inline bool IsEmpty()
	{
		return mpData == NULL || mSize == 0 ;
	}

	void InsertEle(int Idx, T_DATA Val)
	{
		if(Idx < mSize - 1)
			memcpy(mpData + Idx + 1, mpData + Idx, (mSize - Idx - 1) * sizeof(T_DATA)) ;
		*(mpData + Idx) = Val ;
	}

	void AddArray(T_DATA *pArray)
	{
		for(int i = 0 ; i < mSize ; ++i)
			*(mpData + i) += *(pArray + i) ;
	}

protected :
	int mSize ;
	T_DATA *mpData ;
} ;