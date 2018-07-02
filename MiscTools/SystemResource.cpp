#include "StdAfx.h"
#include "SystemResource.h"


CSystemResource::CSystemResource(void)
{
}


CSystemResource::~CSystemResource(void)
{
}


int CSystemResource::GetValidCommPort(CString * pNameList, CString * pPortList, int MaxCnt)
{
	CRegKey RegKey;   
    int nCount = 0;   
       
    if(RegKey.Open(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), KEY_READ) == ERROR_SUCCESS)   
    {   
        while(nCount < MaxCnt)   
        {   
            WCHAR ValueName[_MAX_PATH];   
            WCHAR ValueData[_MAX_PATH];   
            DWORD nValueSize = _MAX_PATH;   
            DWORD nDataSize = _MAX_PATH;   
            DWORD nType;   
            if(::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, (unsigned char *)ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)   
                break;   
              
            if(pNameList)   
                pNameList[nCount] = ValueName;   
               
            if(pPortList)   
                pPortList[nCount] = ValueData;   
               
            nCount++;   
        }   
    }   
       
    return nCount;   
}  

int CSystemResource::PipeSystemCommand(const WCHAR *pCmdStr, BYTE *pBuf, int MaxBufSize)
{
//      1. ����һ�������ܵ���
	SECURITY_ATTRIBUTES sa; 
    HANDLE hReadPipe,hWritePipe;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE; 
 
 //�����ܵ�
	if(!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
		return 0 ;

 //���������д�����Ϣ
	STARTUPINFO si; 
 //���ؽ�����Ϣ
    PROCESS_INFORMATION pi;

    si.cb = sizeof(STARTUPINFO); 
    GetStartupInfo(&si); 
    si.hStdError = hWritePipe; 
    si.hStdOutput = hWritePipe; 
    si.wShowWindow = SW_HIDE; //���������д���
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

 //������ȡ�����н���
	DWORD ReadSize = 0 ;
	wchar_t *pNewCmd = _tcsdup(pCmdStr) ;
	if(pNewCmd != NULL)
	{
		if(CreateProcess (NULL, pNewCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi ))
		{
			  WaitForSingleObject (pi.hProcess, INFINITE); 
			  ReadFile(hReadPipe,  pBuf,  MaxBufSize-1,  &ReadSize,  0);
		}
	   CloseHandle(pi.hProcess); 
		CloseHandle(pi.hThread); 
		free(pNewCmd) ;
	}
	CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
	return ReadSize ;
 }
