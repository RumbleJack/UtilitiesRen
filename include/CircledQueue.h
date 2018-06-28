#pragma once
#include "SafeArray.h"

template <class T_DATA>
class CCircledQueue : public CSafeArray <T_DATA>
{
public :
	CRITICAL_SECTION cs ;
public:
static const int FORWARD_QUEUE = 1 ;
static const int BACKWARD_QUEUE = -1 ;

	CCircledQueue()
		: CSafeArray <T_DATA> ()
		, mFirstCircle(TRUE)
		, mSizeWritePosToReadPos(1)
	{
		mPos.Read = mPos.Write = 0 ;
		mPos.Dir = FORWARD_QUEUE ;
		InitializeCriticalSection(&cs) ;
	}

	CCircledQueue(int Size, int SizeWritePosToReadPos = 1)
		: CSafeArray <T_DATA> (Size)
		, mFirstCircle(TRUE)
		, mSizeWritePosToReadPos(SizeWritePosToReadPos)
	{
		mPos.Read = mPos.Write = 0 ;
		mPos.Dir = FORWARD_QUEUE ;
		InitializeCriticalSection(&cs) ;

	}

	void SetSizeWritePosToReadPos(int size)
	{
		mSizeWritePosToReadPos = size ;
	}

	virtual ~CCircledQueue(void)
	{
		DeleteCriticalSection(&cs) ;
	}

	inline bool IsEmpty()
	{
		return (mPos.Write == mPos.Read) ;
	}

	inline bool IsFull()
	{
		return (GetCntEmptyElement() == 0) ;
	}

	inline int GetPosRefToReadPos(int Offset = 0)
	{
		return CircledPos(mPos.Read+Offset*mPos.Dir) ;
	}

	inline T_DATA &GetElementOnReadPos(int Offset = 0)
	{
		return *(mpData + GetPosRefToReadPos(Offset)) ;
	}

	T_DATA &ReadElementAndForwardReadPos(int Offset = 1)
	{
		T_DATA &Ele = GetElementOnReadPos() ;
		while(Offset-- > 0)
			IncReadPos() ;
		return Ele ;
	}

	bool WriteElementAndForwardWritePos(T_DATA &Ele)
	{
		if(!IsFull())
		{
			*(mpData + mPos.Write) = Ele ;
			IncWritePos() ;
			return true ;
		}
		else
			return false ;
	}

	inline int GetPosRefToWritePos(int Offset = 0)
	{
		return CircledPos(mPos.Write+Offset*mPos.Dir) ;
	}

	inline T_DATA &GetElementOnWritePos(int Offset = 0)
	{
		return *(mpData + GetPosRefToWritePos(Offset)) ;
	}

	inline T_DATA &GetLastWrittenElement()
	{
		return GetElementOnWritePos(-1) ;
	}

	inline int GetPosOfLastWrittenElement(int Offset = 0)
	{
		return GetPosRefToWritePos(-1+Offset) ;
	}

	T_DATA &GetWriteElementAndForwardWritePos(long *pWrittenPos = NULL, int Offset = 1)
	{
		T_DATA &Ele = GetElementOnWritePos() ;
		if(pWrittenPos != NULL)
			*pWrittenPos = mPos.Write ;
		while(Offset-- > 0)
			IncWritePos() ;
		return Ele ;
	}

	bool NewElement(T_DATA &Ele)
	{
		if(IsFull())
			return false ;
		else
		{
			Ele = GetWriteElementAndForwardWritePos() ;
			return true ;
		}
	}

	 T_DATA &NewElementWithoutOverflow()
	{
		if(IsFull())
			IncReadPos() ;
		return GetWriteElementAndForwardWritePos() ;
	}

	inline int GetCntReadyElement()
	{
		return CircledPos((mPos.Write - mPos.Read) * mPos.Dir) ;
	}

	inline int GetCntEmptyElement()
	{
		return CircledPos((mPos.Read - mPos.Write) * mPos.Dir - mSizeWritePosToReadPos)  ;
	}

	inline int GetCntHistoryElement(int pos)
	{
		if(mFirstCircle)
			return CircledPos(pos*mPos.Dir) ;
		else
			return CircledPos((pos - mPos.Write) * mPos.Dir) ;
	}

	inline int IncReadPos()
	{
		if(mPos.Read != mPos.Write)
			mPos.Read = CircledPos(mPos.Read +  mPos.Dir) ;
		return mPos.Read ;
	}

	inline int IncPos(int pos)
	{
		return CircledPos(pos+mPos.Dir) ;
	}

	inline int DecPos(int pos)
	{
		return CircledPos(pos-mPos.Dir) ;
	}

	inline int DecReadPos()
	{
		if(mPos.Read != mPos.Write && !(mFirstCircle && mPos.Read == 0))
			mPos.Read = CircledPos(mPos.Read +  mPos.Dir) ;
		return mPos.Read ;
	}

	inline int ForwardPos(int pos, int step)
	{
		return CircledPos(pos + step * mPos.Dir) ;
	}

	inline int IncWritePos()
	{
		if(!IsFull())
		{
			mPos.Write = CircledPos(mPos.Write + mPos.Dir) ;
			if(mPos.Write == 0)
				mFirstCircle = FALSE ;
		}
		return mPos.Write ;
	}
	
	inline  int DecWritePos()
	{
		if(!IsEmpty())
			mPos.Write = CircledPos(mPos.Write - mPos.Dir) ;
		return mPos.Write ;
	}

	inline T_DATA &GetElement(int Pos)
	{
		return *(mpData + CircledPos(Pos)) ;
	}

	void SetQueueDirection(int Dir = FORWARD_QUEUE)
	{
		if(Dir != mPos.Dir)
		{
			if( !IsEmpty())
			{
				int TmpPos = mPos.Read ;
				mPos.Read = CircledPos(mPos.Write - mPos.Dir) ;
				mPos.Write = CircledPos(TmpPos - mPos.Dir) ;
			}
			mPos.Dir = Dir ;
		}
	}

	void ReverseQueueDirection()
	{
		if( !IsEmpty())
		{
			int TmpPos = mPos.Read ;
			mPos.Read = CircledPos(mPos.Write - mPos.Dir)  ;
			mPos.Write = CircledPos(TmpPos - mPos.Dir ) ;
		}
		mPos.Dir *= -1 ;
	}

	void ClearBuf()
	{
		mPos.Read = mPos.Write = 0 ;
	} 

	void GetQueuePtr(long &posRead, long &posWritten, long &dir)
	{
		posRead = mPos.Read ;
		posWritten = mPos.Write ;
		dir = mPos.Dir ;
	}
public :
	inline int CircledPos(int Pos)
	{
		return (Pos + mSize) % mSize ;
	}

protected :

	typedef struct
	{
		int Read, Write, Dir ;
	} QUEUE_POS ;
	QUEUE_POS mPos ;
	BOOL	mFirstCircle ;
	int	mSizeWritePosToReadPos ;
};
