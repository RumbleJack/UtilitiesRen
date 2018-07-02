#include "StdAfx.h"
#include "FileFuncs.h"


CFileFuncs::CFileFuncs(void)
{
}


CFileFuncs::~CFileFuncs(void)
{
}


BOOL CFileFuncs::BrowseAndGetPathName(CString & PathName)
{
	BOOL RetVal = FALSE ;
	IFileDialog *pfd = NULL; 
	if(SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, 
										NULL, 
										CLSCTX_INPROC_SERVER, 
										IID_PPV_ARGS(&pfd))))
	{
		FILEOPENDIALOGOPTIONS  dwFlags = FOS_PICKFOLDERS ;
		pfd->SetOptions(dwFlags); 
		if(SUCCEEDED(pfd->Show(NULL)))
		{
			IShellItem *pShellItem = NULL ;
			if(SUCCEEDED(pfd->GetResult(&pShellItem)))
			{
				LPWSTR pPath ;
				pShellItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &pPath) ;
				PathName = pPath ;
				RetVal = TRUE ;
				CoTaskMemFree(pPath) ;
				pShellItem->Release() ;
			}
		}
		pfd->Release() ;
	}
	return RetVal  ;
}
