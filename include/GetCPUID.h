#pragma once
#include "SystemResource.h"
#include <WinIoCtl.h>
class CMachineID
{
public :
	CMachineID()
	{
	}
	~CMachineID()
	{
	}

	static void GetCPUID(unsigned long &HiID, unsigned long &LoID, char *pVendor = NULL)
	{
		DWORD mHiID = 0 ;
		DWORD mLoID = 0 ;
		char mpVendor[16] = {0} ;

		_asm
		{
			xor eax, eax
			cpuid
			mov dword ptr mpVendor[0], ebx
			mov dword ptr mpVendor[4], edx
			mov dword ptr mpVendor[8], ecx
			mov eax, 1
			xor edx, edx
			cpuid
			mov mHiID, edx
			mov mLoID, eax
		}
		HiID = mHiID ;
		LoID = mLoID ;
		if(pVendor != NULL)
			strcpy_s(pVendor, 16, mpVendor) ;
	}

	// HiCode: netMAC(lower 4 bytes) + DiskSerialNumber 
	// LoCode: CPUID + DiskID
	static BOOL GetMachineID(DWORD &HiCode, DWORD &LoCode)
	{
		DWORD HiCPUID, LoCPUID ;
		GetCPUID(HiCPUID, LoCPUID) ;

		DWORD HiNetID, LoNetID ;
		if(GetNetMAC(HiNetID, LoNetID))
			HiCode = LoNetID ;
		else
			HiCode = HiCPUID ;
		LoCode = LoCPUID + GetDiskID() ;
		HiCode += GetDiskSerialNumber() ;	
		return TRUE ;
	}

	static DWORD GetDiskSerialNumber()
	{
		BYTE IdentifyResult[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
		DWORD dwBytesReturned;
		GETVERSIONINPARAMS get_version;
		SENDCMDINPARAMS send_cmd = { 0 };
		const int SizeName = 30 ;
		WCHAR pDrvName[SizeName] = {0} ;

		DWORD SerialNo = 0 ;

		HANDLE hFile = 0 ;
		for(int IdxDrv = 0 ; IdxDrv < 4; ++IdxDrv)
		{
			if(hFile != 0 && hFile != INVALID_HANDLE_VALUE)
			{
				CloseHandle(hFile) ;
				hFile = 0 ;
			}
			wsprintf(pDrvName, _T("\\\\.\\PHYSICALDRIVE%d"), IdxDrv) ;
			hFile = CreateFile(pDrvName, GENERIC_READ | GENERIC_WRITE,    
					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if(hFile == INVALID_HANDLE_VALUE)
				continue ;
			//get version
			if(!DeviceIoControl(hFile, SMART_GET_VERSION, NULL, 0, &get_version, sizeof(get_version), &dwBytesReturned, NULL))
				continue ;
			send_cmd.irDriveRegs.bCommandReg = (get_version.bIDEDeviceMap & (16>>IdxDrv))? ATAPI_ID_CMD : ID_CMD;
			send_cmd.bDriveNumber = IdxDrv ;
			send_cmd.irDriveRegs.bSectorCountReg = 1 ;
			send_cmd.irDriveRegs.bSectorNumberReg = 1 ;
			send_cmd.cBufferSize = 512 ;
			if(!DeviceIoControl(hFile, SMART_RCV_DRIVE_DATA, &send_cmd, sizeof(SENDCMDINPARAMS) - 1,
						IdentifyResult, sizeof(IdentifyResult), &dwBytesReturned, NULL))
				continue ;

			// ----->
			typedef struct   
			{   
				USHORT wGenConfig;   
				USHORT wNumCyls;   
				USHORT wReserved;   
				USHORT wNumHeads;   
				USHORT wBytesPerTrack;   
				USHORT wBytesPerSector;   
				USHORT wSectorsPerTrack;   
				USHORT wVendorUnique[3];   
				CHAR sSerialNumber[20];   
				USHORT wBufferType;   
				USHORT wBufferSize;   
				USHORT wECCSize;   
				CHAR sFirmwareRev[8];   
				CHAR sModelNumber[40];   
				USHORT wMoreVendorUnique;   
				USHORT wDoubleWordIO;   
				USHORT wCapabilities;   
				USHORT wReserved1;   
				USHORT wPIOTiming;   
				USHORT wDMATiming;   
				USHORT wBS;   
				USHORT wNumCurrentCyls;   
				USHORT wNumCurrentHeads;   
				USHORT wNumCurrentSectorsPerTrack;   
				ULONG ulCurrentSectorCapacity;   
				USHORT wMultSectorStuff;   
				ULONG ulTotalAddressableSectors;   
				USHORT wSingleWordDMA;   
				USHORT wMultiWordDMA;   
				BYTE bReserved[128];   
			} IDSECTOR ;   
			// ----- >
			//adjust the byte order
			//PUSHORT pWords = (USHORT*)(((SENDCMDOUTPARAMS*)IdentifyResult)->bBuffer);
			IDSECTOR *pStructedOut = (IDSECTOR *)(((SENDCMDOUTPARAMS*)IdentifyResult)->bBuffer) ;
			const int SizeOutStr = 100 ;
			char OutStr[SizeOutStr] = {0} ;
			//ToLittleEndian(pWords, 27, 46, OutStr);	// model
			//ToLittleEndian(pWords, 10, 19, OutStr);	// serial number
			ToLittleEndian(pStructedOut->sSerialNumber, 20, OutStr) ;
			int i = 0 ;
			while(OutStr[i] > 0 && i < 20)
			{
				if(OutStr[i] >= '0' && OutStr[i] <= '9')
					SerialNo = SerialNo * 10 + (OutStr[i] - '0') ;
				++i ;
			}
			break ;
		}
		if(hFile != 0 && hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile) ;
		return SerialNo ;
	}

	static void ToLittleEndian(char *pSrcStr, int CntChr, char * pOut)
	{
 		for(int i = 0 ; i < CntChr / 2 ; ++i)
		{
			*(pOut + i*2) = *(pSrcStr + i*2 + 1) ;
			*(pOut + i*2 + 1) = *(pSrcStr + i*2) ;
		}
  
	}

	// diskID : diskpart -> select disk 0 -> detail disk -> ID: XXXXXXXX
	static DWORD GetDiskID()
	{
		const char Script[] = "select disk 0\r\ndetail disk\r\nexit\r\n" ;
		const WCHAR ScriptFile[] = _T("ScriptFile.txt") ;
		CString CmdStr = _T("diskpart /s ") ;
		CmdStr += ScriptFile ;


		FILE *pf = 0 ;
		if(_wfopen_s(&pf, ScriptFile,  _T("wb")) == 0 && pf != NULL)
		{
			fwrite(Script, 1, sizeof(Script), pf) ;
			fclose(pf) ;
		}
		else
			return 0 ;
		const int SizeDiskBuf = 3000 ;
		BYTE *pDiskBuf = new BYTE [SizeDiskBuf] ;
		memset(pDiskBuf, 0, SizeDiskBuf) ;
		CSystemResource Tool ;
		int ReadSize = Tool.PipeSystemCommand(CmdStr, pDiskBuf, SizeDiskBuf) ;
		DWORD DiskID = GetDiskIDFromStr(pDiskBuf, ReadSize) ;

		delete [] pDiskBuf ;
		DeleteFile(ScriptFile) ;
		return DiskID ;
	}

	static DWORD GetDiskIDFromStr(BYTE *pDiskBuf, int ReadSize)
	{
		DWORD idVal = 0 ;
		const BYTE idItem[] = {'I', 'D', ':'} ;
		int Pos = FindSubStr(pDiskBuf, ReadSize, idItem, sizeof(idItem)) ;
		if(Pos > 0 && Pos < ReadSize-15)
		{
			Pos += 3 ;
			int MaxCnt = 10 ;
			while(!CheckHexDigit(*(pDiskBuf + Pos)) && MaxCnt-- > 0)
				++Pos ;

			if(MaxCnt > 0)
			{
				for(int i = 0 ; i < 8 && (Pos+i)<ReadSize ; ++i)
				{
					idVal = (idVal << 4) + (GetHexDigitVal(*(pDiskBuf+Pos+i)) & 0x0f) ;
				}
			}
		}
		return idVal ;
	}

	// HiCode : Higher 2 bytes, LoCode: lower 4 bytes
	static BOOL GetNetMAC(DWORD &HiCode, DWORD &LoCode)
	{
		const int SizeNetInfo = 1000 ;
		BYTE *pNetInfo = new BYTE [SizeNetInfo] ;
		memset(pNetInfo, 0, SizeNetInfo) ;
		CSystemResource Tool ;
		int SizeReadNetInfo = Tool.PipeSystemCommand(_T("ipconfig /all"), pNetInfo, SizeNetInfo) ;
		BOOL State = FindNetPhysicalAddr(pNetInfo, SizeReadNetInfo, HiCode, LoCode) ;
		delete [] pNetInfo ;
		return State ;
	}

	static BOOL FindNetPhysicalAddr(BYTE *pInfoStr, int SizeInfoStr, DWORD &HiCode, DWORD &LoCode)
	{
		const BYTE ITEM_NAME[] = {0XCE, 0XEF, 0XC0, 0XED, 0XB5, 0XD8, 0XD6, 0XB7} ;
		CString ITEM_NAME_IN_CHS = _T("ÎïÀíµØÖ·") ;
		int CntLength = ITEM_NAME_IN_CHS.GetLength() ;
		const char ITEM_NAME_IN_ENG[] = "Physical Address" ;
		int IdxCodePos = 0 ;
		if((IdxCodePos = FindSubStr(pInfoStr, SizeInfoStr, ITEM_NAME, sizeof(ITEM_NAME))) < 0)
		{
			if((IdxCodePos = FindSubStr(pInfoStr, SizeInfoStr, (BYTE *)ITEM_NAME_IN_CHS.GetBuffer(), ITEM_NAME_IN_CHS.GetLength() * sizeof(WCHAR))) < 0)
			{
				if((IdxCodePos = FindSubStr(pInfoStr, SizeInfoStr, (BYTE *)ITEM_NAME_IN_ENG, sizeof(ITEM_NAME_IN_ENG))) < 0)
					IdxCodePos = 0 ;
				else
					IdxCodePos += sizeof(ITEM_NAME_IN_ENG) ;
			}
			else
				IdxCodePos += ITEM_NAME_IN_CHS.GetLength() * sizeof(WCHAR) ;
		}
		else
			IdxCodePos += sizeof(ITEM_NAME) ;
		return CheckAndLoadNetCode(pInfoStr, SizeInfoStr, IdxCodePos, HiCode, LoCode) ;
	}

	static int FindSubStr(const BYTE *pStr, int SizeStr, const BYTE *pTargStr, int SizeTargStr)
	{
		for(int i = 0 ; i < SizeStr - SizeTargStr ; ++i)
		{
			if(*(pStr + i) == *pTargStr)
			{
				BOOL Found = TRUE ;
				for(int j = 1 ; j < SizeTargStr ; ++j)
				{
					if(*(pStr + i + j) != *(pTargStr + j))
					{
						Found = FALSE ;
						break ;
					}
				}
				if(Found)
					return i ;
			}
		}
		return -1 ;
	}

	static BOOL CheckAndLoadNetCode(BYTE *pInfoStr, int SizeInfoStr, int IdxCodePos, DWORD &HiCode, DWORD &LoCode) 
	{
		const int CodeSize = 17 ;	// 2x6 digit, 5 x '-'
		const int IdxDigit[] = {0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16} ;
		int CntDigit = sizeof(IdxDigit) / sizeof(int) ;
		const int IdxLink[] = {2, 5, 8, 11, 14} ;
		int CntLink = sizeof(IdxLink) / sizeof(int) ;
		BOOL Found = FALSE ;
		for(int i = IdxCodePos ; i < SizeInfoStr - IdxCodePos - CodeSize ; ++i)
		{
			Found = TRUE ;
			for(int j = 0 ; j < CntDigit ; ++j)
			{
				if(!CheckHexDigit(*(pInfoStr + i + IdxDigit[j])))
				{
					Found = FALSE ;
					break ;
				}
			}
			if(!Found)
				continue ;
			for(int j = 0 ; j < CntLink ; ++j)
			{
				if(*(pInfoStr + i + IdxLink[j]) != '-')
				{
					Found = FALSE ;
					break ;
				}
			}
			if(!Found)
				continue ;
			if(*(pInfoStr + i + CodeSize) == '-')
			{
				Found = FALSE ;
				i += CodeSize ;
			}
			if(Found)
			{
				IdxCodePos = i ;
				break ;
			}
		}
		if(Found)
		{
			LONGLONG Code = 0 ;
			for(int j = 0 ; j < CntDigit ; ++j)
			{
				Code = (Code << 4) + (GetHexDigitVal((char)*(pInfoStr + IdxCodePos + IdxDigit[j])) & 0X0F) ;
			}
			LoCode = Code & 0XFFFFFFFF;
			HiCode = (Code >> 32) & 0XFFFFFFFF ;
			return TRUE ;
		}
		LoCode = HiCode = 0 ;
		return FALSE ;
	}

	static BOOL CheckHexDigit(BYTE val)
	{
		return (val >= '0' && val <= '9') || (val >= 'A' && val <= 'F') || (val >= 'a' && val <= 'f') ;
	}

	static BYTE GetHexDigitVal(char hexChr)
	{
		if(hexChr>= '0' && hexChr <= '9')
			return hexChr - '0' ;
		else if(hexChr >= 'A' && hexChr <= 'F')
			return hexChr - 'A' + 10 ;
		else if(hexChr >= 'a' && hexChr <= 'f')
			return hexChr - 'a' + 10 ;
		else
			return 0xff ;
	}
} ;