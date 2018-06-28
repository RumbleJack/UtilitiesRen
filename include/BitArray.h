#ifndef BIT_ARRAY_DEFINITION
#define BIT_ARRAY_DEFINITION

#define FIND_BIT_ARRAY_SIZE_IN_BYTE(CntBit) (((CntBit)+7)/8)
#define SET_BIT(pBuf, IdxBit) *(pBuf + (IdxBit/8))|=(1<<((IdxBit)%8)) ;
#define RESET_BIT(pBuf, IdxBit) *(pBuf + (IdxBit/8))&=(0xff-(1<<((IdxBit)%8))) ;
#define CHECK_BIT(pBuf, IdxBit) (*(pBuf + (IdxBit/8))&(1<<((IdxBit)%8)))!=0

#include "SafeArray.h"

class CBitArray
{
public :
	CBitArray()
		: mCntBit(0)
	{
	}
	CBitArray(int CntBit)
		: mCntBit(0)
	{
		CreateBuf(CntBit) ;
	}

	int CreateBuf(int CntBit)
	{
		mBuf.Create(FIND_BIT_ARRAY_SIZE_IN_BYTE(mCntBit = CntBit)) ;
		ResetAllBits() ;
		return mBuf.GetArraySize() ;
	}

	BOOL CheckValidBit(int IdxBit)
	{
		return IdxBit >= 0 && IdxBit < mCntBit ;
	}

	BOOL CheckBit(int IdxBit)
	{
		if(CheckValidBit(IdxBit))
			return CHECK_BIT(mBuf.GetPtrToArray(), IdxBit) ;
		else
			return FALSE ;
	}

	void SetAllBits()
	{
		mBuf.SetVal(0XFF) ;
	}

	void ResetAllBits()
	{
		mBuf.SetVal(0) ;
	}

	static void SetAllBits(int SizeBuf, BYTE *pBuf)
	{
		for(int i = 0 ; i < SizeBuf ; ++i)
			*(pBuf+i) = 0xff ;
	}

	static void ResetAllBits(int SizeBuf, BYTE *pBuf)
	{
		for(int i = 0 ; i < SizeBuf ; ++i)
			*(pBuf+i) = 0 ;
	}


	BOOL SetBit(int IdxBit)
	{
		if(CheckValidBit(IdxBit))
		{
			SET_BIT(mBuf.GetPtrToArray(), IdxBit) 
			return TRUE ;
		}
		else
			return FALSE ;
	}

	void SetBitPiece(int IdxBeginBit, int IdxEndBit)
	{
		for(int i = max(0, IdxBeginBit) ; i <= min(IdxEndBit, mCntBit-1) ; ++i)
			SetBit(i) ;
	}

	void ResetBitPiece(int IdxBeginBit, int IdxEndBit)
	{
		for(int i = max(0, IdxBeginBit) ; i <= min(IdxEndBit, mCntBit-1) ; ++i)
			ResetBit(i) ;
	}

	BOOL ResetBit(int IdxBit)
	{
		if(CheckValidBit(IdxBit))
		{
			RESET_BIT(mBuf.GetPtrToArray(), IdxBit) 
			return TRUE ;
		}
		else
			return FALSE ;
	}

	int GetCntBit()
	{
		return mCntBit ;
	}

	int GetArraySizeInByte()
	{
		return mBuf.GetArraySize() ;
	}

	void ImportArrayBuffer(int CntBit, const BYTE *pBuf, int SizeBufInByte = 0) // SizeBufInByte == 0 indicates size of buffer fit CntBit
	{
		CreateBuf(CntBit) ;
		int BufSize = GetArraySizeInByte() ;
		if(SizeBufInByte > 0 && BufSize > SizeBufInByte)
			BufSize = SizeBufInByte ;
			
		for(int i = 0 ; i < BufSize ; ++i)
			mBuf[i] = *(pBuf+i) ;
	}

	int GetDataBuffer(BYTE **ppBuf)
	{
		*ppBuf = mBuf.GetPtrToArray() ;
		return mBuf.GetArraySize() ;
	}

	void ShiftLeft(int CntBit)
	{
		int CntByte = mBuf.GetArraySize() ;
		if(CntByte < 1)
			return ;
		int ShiftByte = CntBit / 8 ;
		if(ShiftByte >= CntByte)
		{
			ResetAllBits() ;
			return ;
		}
		if(ShiftByte > 0)
		{
			for(int i = CntByte - 1 ; i >= ShiftByte ; --i)
			{
				mBuf[i] = mBuf[i-ShiftByte] ;
			}
			for(int i = ShiftByte-1 ; i >= 0 ; --i)
				mBuf[i] = 0 ;
		}
		int ShiftBit = CntBit % 8 ;
		if(ShiftBit > 0)
		{
			typedef union
			{
				WORD word ;
				BYTE byte[2] ;
			} UNION_DATA ;
			BYTE Overflow = 0 ;
			UNION_DATA Data ;
			for(int i = ShiftByte ; i < CntByte ; ++i)
			{
				Data.word = mBuf[i] ;
				Data.word <<= ShiftBit ;
				mBuf[i] = Data.byte[0] | Overflow ;
				Overflow = Data.byte[1] ;
			}
		}
	}

	void ShiftRight(int CntBit)
	{
		int CntByte = mBuf.GetArraySize() ;
		if(CntByte < 1)
			return ;
		int ShiftByte = CntBit / 8 ;
		if(ShiftByte >= CntByte)
		{
			ResetAllBits() ;
			return ;
		}
		if(ShiftByte > 0)
		{
			for(int i = 0 ; i < CntByte - ShiftByte ; ++i)
			{
				mBuf[i] = mBuf[i+ShiftByte] ;
			}
			for(int i = CntByte - ShiftByte ; i < CntByte ; ++i)
				mBuf[i] = 0 ;
		}
		int ShiftBit = CntBit % 8 ;
		if(ShiftBit > 0)
		{
			BYTE Overflow = 0 ;
			typedef union
			{
				WORD word ;
				BYTE byte[2] ;
			} UNION_DATA ;
			UNION_DATA Data ;
			for(int i = CntByte-ShiftByte-1 ; i >= 0 ; --i)
			{
				Data.word = mBuf[i] << (8-ShiftBit) ;
				mBuf[i] = Data.byte[1] | Overflow ;
				Overflow = Data.byte[0] ;
			}
		}
	}

	void RotateLeft1Byte()
	{
		int CntByte = mBuf.GetArraySize() ;
		if(CntByte <= 1)
			return ;
		int TailBit = mCntBit - (CntByte - 1) * 8 ;
		WORD MostByte = mBuf[CntByte-1] ;
		if(TailBit != 0)
			MostByte = (((MostByte << 8) + mBuf[CntByte-2]) >> TailBit) & 0xff ;
		for(int i = CntByte-1 ; i > 0 ; --i)
			mBuf[i] = mBuf[i-1] ;
		mBuf[0] = (BYTE)MostByte ;
	}

	void RotateLeft(int CntBit)
	{
		int ArrayByte = mBuf.GetArraySize() ;
		if(ArrayByte == 0 || mCntBit == 1)
			return ;
		typedef union
		{
			WORD word ;
			BYTE byte[2] ;
		} UNION_DATA ;

		if(ArrayByte == 1)
		{
			if(CntBit == 0)
				return ;
			BYTE MaskMSB = 1 << (mCntBit-1) ;
			BYTE MaskVal = (1 << mCntBit) - 1 ;
			BYTE Val = mBuf[0] ;
			for(int i = 0 ; i < CntBit ; ++i)
			{
				if(Val & MaskMSB)	// MSB = 1
					Val = ((Val << 1) | 1) & MaskVal ;
				else
					Val = (Val << 1) & MaskVal ;
			}
			mBuf[0] = Val ;
		}
		else
		{
			int RotateByte = CntBit / 8 ;
			for(int i = 0 ; i < RotateByte ; ++i)
				RotateLeft1Byte() ;
			CntBit %= 8 ;
			if(CntBit > 0)
			{
				UNION_DATA Data ;
				BYTE Overflow = 0 ;
				for(int i = 0 ; i < ArrayByte-1 ; ++i)
				{
					Data.word = mBuf[i] ;
					Data.word <<= CntBit ;
					mBuf[i] = Data.byte[0] | Overflow ;
					Overflow = Data.byte[1] ;
				}
				int CntTailBit = mCntBit - (ArrayByte-1)*8 ;
				WORD TailMask = (1 << CntTailBit) - 1 ;
				Data.word = mBuf[ArrayByte-1] & TailMask ;
				Data.word <<= CntBit ;
				Data.word |= Overflow ;
				mBuf[ArrayByte-1] = (BYTE)(Data.word & TailMask) ;
				Data.word >>= CntTailBit ;
				mBuf[0] |= Data.byte[0] ;
			}
		}
	}

	void RotateRight1Byte()
	{
		int CntByte = mBuf.GetArraySize() ;
		if(CntByte <= 1)
			return ;
		int TailBit = mCntBit - (CntByte - 1) * 8 ;
		BYTE MaskTailBit = (1 << TailBit) - 1 ;
		WORD FuseData = mBuf[0] ;
		FuseData = (FuseData << TailBit) | (mBuf[CntByte-1] & MaskTailBit) ;

		for(int i = 0 ; i < CntByte-2 ; ++i)
			mBuf[i] = mBuf[i+1] ;
		mBuf[CntByte-2] = (BYTE)(FuseData & 0xff) ;
		mBuf[CntByte-1] = (BYTE)(FuseData >> 8) ;
	}

	void RotateRight(int CntBit)
	{
		int ArrayByte = mBuf.GetArraySize() ;
		if(ArrayByte == 0 || mCntBit == 1)
			return ;
		typedef union
		{
			WORD word ;
			BYTE byte[2] ;
		} UNION_DATA ;

		if(ArrayByte == 1)
		{
			if(CntBit == 0)
				return ;
			BYTE MSB = 1 << (mCntBit-1) ;
			BYTE MaskVal = (1 << mCntBit) - 1 ;
			BYTE Val = mBuf[0] & MaskVal ;
			for(int i = 0 ; i < CntBit ; ++i)
			{
				if(Val & 1)	
					Val = (Val >> 1) | MSB ;
				else
					Val = Val >> 1 ;
			}
			mBuf[0] = Val ;
		}
		else
		{
			int RotateByte = CntBit / 8 ;
			for(int i = 0 ; i < RotateByte ; ++i)
				RotateRight1Byte() ;

			CntBit %= 8 ;

			if(CntBit > 0)
			{
				int CntTailBit = mCntBit - (ArrayByte-1)*8 ;
				BYTE TailMask = (1 << CntTailBit) - 1 ;
				BYTE ShiftMask = (1 << CntBit) - 1 ;
				UNION_DATA Data = {0} ;
				Data.word = (mBuf[0] << CntTailBit) | (mBuf[ArrayByte-1] & TailMask) ;
				BYTE Overflow = (BYTE)(Data.word & ShiftMask) ;
				mBuf[ArrayByte-1] = (BYTE)((Data.word >> CntBit) & TailMask) ;
				for(int i = ArrayByte-2 ; i >= 0  ; --i)
				{
					Data.byte[1] = Overflow ;
					Data.byte[0] = mBuf[i] ;
					Overflow = (BYTE)(Data.word & ShiftMask) ;
					Data.word >>= CntBit ;
					mBuf[i] = Data.byte[0] ;
				}
			}
		}
	}
public :
	int	mCntBit ;
	CSafeArray <BYTE> mBuf ;
} ;

#endif