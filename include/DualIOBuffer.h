#pragma once
#include <Windows.h>

#define	CNT_BUF	2

template <class T_DATA>
class CDualIOBuffer
{
public :
	CDualIOBuffer() 
		: mIdxInBuf(0)
		, mExchangeBufFlag(FALSE)
	{
	}

	~CDualIOBuffer()
	{
	}

	void ExchangeIOBuffer()
	{
		mIdxInBuf = (mIdxInBuf+1) % CNT_BUF ;
	}

	T_DATA	&GetInBuf(BOOL *pExchangeIO = NULL)
	{
		if(pExchangeIO != NULL)
			*pExchangeIO = mExchangeBufFlag ;
		if(mExchangeBufFlag)
		{
			ExchangeIOBuffer() ;
			mExchangeBufFlag = FALSE ;
		}
		return mBuffer[mIdxInBuf] ;
	}

	T_DATA &GetOutBuf()
	{
		return mBuffer[(mIdxInBuf+1)%CNT_BUF] ;
	}
	void SetExchangeFlag()
	{
		mExchangeBufFlag = TRUE ;
	}
protected :
	BOOL mExchangeBufFlag ;
	T_DATA	mBuffer[CNT_BUF] ;
	int	mIdxInBuf ;
} ;