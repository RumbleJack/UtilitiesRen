#pragma once
#include "SafeArray.h"
template <class T_DATA>
class   __declspec(dllexport) CSimpleCircledQueue : public CSafeArray <T_DATA>
{
public:
	CSimpleCircledQueue()
		: CSafeArray <T_DATA> ()
		, mPosHdr(0)
		, mPosTlr(0)
	{
	}

	CSimpleCircledQueue(int Size)
		: CSafeArray <T_DATA> (Size)
		, mPosHdr(0)
		, mPosTlr(0)
	{
	}

	~CSimpleCircledQueue(void)
	{
	}

protected :
	int	mPosHdr ;
	int	mPosTlr ;
public:
	int GetCntEmptyEle(void)
	{
		return (mPosHdr - mPosTlr - 1 + mSize) % mSize ;
	}

	int GetCntBufferedEle(void)
	{
		return (mPosTlr - mPosHdr + mSize) % mSize ;
	}

	T_DATA * PopBufferedEle(void)
	{
		if(mPosHdr != mPosTlr)
		{
			T_DATA *pEle = mpData + mPosHdr ;
			mPosHdr = CircledInc(mPosHdr) ;
			return pEle ;
		}
		else
			return NULL;
	}

	BOOL PopBufferedEle(T_DATA &ele)
	{
		if(mPosHdr != mPosTlr)
		{
			ele = *(mpData + mPosHdr) ;
			mPosHdr = CircledInc(mPosHdr) ;
			return TRUE ;
		}
		else
			return FALSE ;
	}


	T_DATA * GetPtrToPushEle(void)
	{
		if(GetCntEmptyEle() > 0)
		{
			T_DATA *pEle = mpData + mPosTlr ;
			mPosTlr = CircledInc(mPosTlr) ;
			return pEle ;
		}
		else
			return NULL;
	}

	BOOL UndoPushEle(void)
	{
		if(mPosTlr != mPosHdr) // not empty
		{
			mPosTlr = (mPosTlr + mSize - 1) % mSize ;
			return TRUE ;
		}
		else
			return FALSE ;
	}

	BOOL UndoPopEle(void)
	{
		if((mPosTlr + 1) % mSize != mPosHdr)  // not full
		{
			mPosHdr = (mPosHdr + mSize - 1) % mSize ;
			return TRUE ;
		}
		else
			return FALSE ;
	}

	int PushEleArray(int CntEle, T_DATA * pEle) 
	{
		int CopiedCnt = 0 ;
		int ReadyCnt = min(CntEle, GetCntEmptyEle()) ;
		CopiedCnt = min(ReadyCnt, mSize - mPosTlr) ;	// size from mPosTlr to array end
		if(CopiedCnt < 100)
		{
			for(int i = 0 ; i < CopiedCnt ; ++i)
				*(mpData + mPosTlr + i) = *(pEle + i) ;
		}
		else
			memcpy(mpData + mPosTlr, pEle, CopiedCnt * sizeof(T_DATA)) ;
		mPosTlr = RoundAdd(mPosTlr, CopiedCnt) ;
		if(ReadyCnt > CopiedCnt)
		{
			if(ReadyCnt - CopiedCnt < 100)
			{
				for(int i = 0 ; i < ReadyCnt - CopiedCnt ; ++i)
					*(mpData + mPosTlr + i) = *(pEle + CopiedCnt + i) ;
			}
			else
				memcpy(mpData + mPosTlr, pEle+CopiedCnt, (ReadyCnt - CopiedCnt) * sizeof(T_DATA)) ;
			mPosTlr = RoundAdd(mPosTlr, ReadyCnt - CopiedCnt) ;
		}
		return ReadyCnt ;
	}

	int PopAndIgnoreEle(int Cnt)
	{
		int CntPop = 0 ;
		while(Cnt-- > 0 && CircledInc(mPosHdr) != mPosTlr)
		{
			mPosHdr = CircledInc(mPosHdr) ;
			++CntPop ;
		}
		return CntPop ;
	}

	int PopEleArray(int Cnt, T_DATA * pEle)
	{
		int CntPop = 0 ;
		while(Cnt-- > 0 && CircledInc(mPosHdr) != mPosTlr)
		{
			*(pEle + CntPop++) = *(mpData + mPosHdr) ;
			mPosHdr = CircledInc(mPosHdr) ;
		}
		return CntPop ;
	}

	int PopAndSaveToArray(int CntToPop, int MaxSizeArray, T_DATA * pEle)
	{
		int SizeCopied = 0 ;
		while(CntToPop-- > 0 && CircledInc(mPosHdr) != mPosTlr)
		{
			if(SizeCopied < MaxSizeArray)
				*(pEle + SizeCopied++) = *(mpData + mPosHdr) ;
			mPosHdr = CircledInc(mPosHdr) ;
		}
		return SizeCopied ;
	}

	void EmptyBuf(void)
	{
		mPosHdr = mPosTlr ;
	}

	BOOL PushElement(T_DATA & ele)
	{
		if(GetCntEmptyEle() > 0)
		{
			*(mpData + mPosTlr) = ele ;
			mPosTlr = RoundAdd(mPosTlr, 1) ;
			return TRUE ;
		}
		else
			return FALSE ;
	}

protected :
	int Size(int TrgtPos, int SrcPos)
	{
		return (TrgtPos - SrcPos + mSize) % mSize ;
	}

	int CircledInc(int Pos)
	{
		return (Pos+1)%mSize ;
	}

	int RoundAdd(int Pos, int Offset)
	{
		return (Pos + Offset + mSize) % mSize ;
	}

	int RoundPos(int Pos)
	{
		return (Pos + mSize) % mSize ;
	}
};
