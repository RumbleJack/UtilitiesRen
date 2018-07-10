#pragma once
#include "stdafx.h"

void errhandler(const char* info,HWND hwnd)
{
	cout << "error occurs:" << info << endl;
	return;
}

// 该函数使用句柄HBITMAP获取Bitmap结构体信息，进而初始化PBITMAPINFO指针。
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		errhandler("GetObject", hwnd);

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{
	PBITMAPINFOHEADER pbmInfoHeader;     // bitmap info-header  
	BITMAPFILEHEADER bmFileHeader;       // bitmap file-header  
	HANDLE hFile;                 // file handle 
	
	LPBYTE lpBits;              // 指向BMP图像像素数据的指针
	DWORD dwTmp;

	// 为像素指针分配内存
	pbmInfoHeader = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbmInfoHeader->biSizeImage);
	if (!lpBits)
		errhandler("GlobalAlloc", hwnd);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbmInfoHeader->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits", hwnd);
	}

	// 创建bmp文件
	hFile = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		errhandler("CreateFile", hwnd);
	bmFileHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
								// Compute the size of the entire file.  
	bmFileHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbmInfoHeader->biSize + pbmInfoHeader->biClrUsed
		* sizeof(RGBQUAD) + pbmInfoHeader->biSizeImage);
	bmFileHeader.bfReserved1 = 0;
	bmFileHeader.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	bmFileHeader.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbmInfoHeader->biSize + pbmInfoHeader->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hFile, (LPVOID)&bmFileHeader, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		errhandler("WriteFile", hwnd);
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hFile, (LPVOID)pbmInfoHeader, sizeof(BITMAPINFOHEADER)
		+ pbmInfoHeader->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		errhandler("WriteFile", hwnd);

	// Copy the array of color indices into the .BMP file.  
	if (!WriteFile(hFile, (LPSTR)lpBits, (int)(pbmInfoHeader->biSizeImage), (LPDWORD)&dwTmp, NULL))
		errhandler("WriteFile", hwnd);

	// Close the .BMP file.  
	if (!CloseHandle(hFile))
		errhandler("CloseHandle", hwnd);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}