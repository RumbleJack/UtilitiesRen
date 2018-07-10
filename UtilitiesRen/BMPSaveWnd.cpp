#include "stdafx.h"
#include "BMPSaveWnd.h"

#include <tchar.h>
#include <iostream>
#include <iomanip>
using namespace std;

void errhandler(const char * info, HWND hwnd)
{
	cout << "error occurs:" << info << endl;
	return;
}

PBITMAPINFO CreateBitmapInfoStruct( HBITMAP HBitmap, HWND hwnd)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// 获取bitmap颜色格式以及尺寸
	int objectSize = 0;
	if (!(objectSize = GetObject(HBitmap, sizeof(BITMAP), &bmp)))
		errhandler("GetObject");

	// bmPlanes始终为1，而bmBitsPixel表示每个像素所需的位数
	// 二者相乘，实际上还是表示每个像素所需的位数，即最多共有2^cClrBits颜色
	// 将颜色格式转化为表示颜色所需的位数
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

	// 为BITMAPINFO分配内存，该结构体包含一个BITMAPINFOHEADER以及一个RGBQUAD数组
	if (cClrBits < 24)
	{
		pbmi = (PBITMAPINFO)new char[
			sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * (1 << cClrBits)];
	}
	else
	{
		// 对于两种图像格式，无需RGBQUAD数组: 每像素24位、每像素32位
		pbmi = (PBITMAPINFO)new char[
			sizeof(BITMAPINFOHEADER)];
	}

	// 初始化BITMAPINFO结构体
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;// 始终为1
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
	{
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
	}
	else
	{
		pbmi->bmiHeader.biClrUsed = 0;
	}
	// 如果未压缩，设置 BI_RGB 标志.  
	pbmi->bmiHeader.biCompression = BI_RGB;
	// 计算图像颜色索引所需的字节数，并存储（24/32位图像，索引本身就是RGB颜色）
	// bitmap宽度必须为双字对齐，除非使用RLE压缩
	// 不压缩情况下可以填0
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// biClrImportant设为0，意为所有颜色都重要 
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(LPTSTR fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd )
{
	// 将BitmapInfo强制转化为BitmapInfoHeader
	PBITMAPINFOHEADER pbmiHeader;
	pbmiHeader = (PBITMAPINFOHEADER)pbmi;

	// 为像素指针分配内存
	void* lpBitsData;
	lpBitsData = new char[pbmiHeader->biSizeImage];
	if (!lpBitsData)
		errhandler("GlobalAlloc");

	// 从DIB中获取颜色表(RGBQUAD array) 以及图像像素数据（颜色索引）
	if (!GetDIBits(compatibleHDC, HBitmap, 0, (WORD)pbmiHeader->biHeight, lpBitsData, pbmi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits");
	}

	BITMAPFILEHEADER bmfHeader;
	//bmfHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	bmfHeader.bfType = MAKEWORD('B', 'M');
	// 计算整个文件的大小，该尺寸包括：文件头大小+BMP头大小+RGBQUAD数组大小+像素数据大小
	bmfHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD)
		+ pbmiHeader->biSizeImage);
	bmfHeader.bfReserved1 = 0;
	bmfHeader.bfReserved2 = 0;
	// 计算像素数据（索引）偏移
	bmfHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD));

	// 创建文件准备写入
	HANDLE HFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	// 复制文件头、bmp头（BITMAPINFOHEADER以及RGBQUAD数组）以及bmp数据到文件
	DWORD  numOfByteWriten;
	if (!WriteFile(HFile, (LPVOID)&bmfHeader, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&numOfByteWriten, NULL))
		errhandler("WriteFile");
	if (!WriteFile(HFile, (LPVOID)pbmiHeader, sizeof(BITMAPINFOHEADER)
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&numOfByteWriten, (NULL)))
		errhandler("WriteFile");
	if (!WriteFile(HFile, (LPSTR)lpBitsData, (int)(pbmiHeader->biSizeImage),
		(LPDWORD)&numOfByteWriten, NULL))
		errhandler("WriteFile");

	// 关闭文件
	if (!CloseHandle(HFile))
		errhandler("CloseHandle");

	delete lpBitsData;
}

void CreateBMPFile(const char* fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd)
{
	// 将BitmapInfo强制转化为BitmapInfoHeader
	PBITMAPINFOHEADER pbmiHeader;
	pbmiHeader = (PBITMAPINFOHEADER)pbmi;

	// 为像素指针分配内存
	void* lpBitsData;
	lpBitsData = new char[pbmiHeader->biSizeImage];
	if (!lpBitsData)
		errhandler("GlobalAlloc");

	// 从DIB中获取颜色表(RGBQUAD array) 以及图像像素数据（颜色索引）
	if (!GetDIBits(compatibleHDC, HBitmap, 0, (WORD)pbmiHeader->biHeight, lpBitsData, pbmi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits");
	}

	BITMAPFILEHEADER bmfHeader;
	//bmfHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	bmfHeader.bfType = MAKEWORD('B', 'M');
	// 计算整个文件的大小，该尺寸包括：文件头大小+BMP头大小+RGBQUAD数组大小+像素数据大小
	bmfHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD)
		+ pbmiHeader->biSizeImage);
	bmfHeader.bfReserved1 = 0;
	bmfHeader.bfReserved2 = 0;
	// 计算像素数据（索引）偏移
	bmfHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD));

	// 创建文件准备写入
	wchar_t *fileNameW = new wchar_t[100];
	mbstowcs_s(NULL, fileNameW, 100, fileName, 100);
	HANDLE HFile = CreateFile(fileNameW, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	// 复制文件头、bmp头（BITMAPINFOHEADER以及RGBQUAD数组）以及bmp数据到文件
	DWORD  numOfByteWriten;
	if (!WriteFile(HFile, (LPVOID)&bmfHeader, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&numOfByteWriten, NULL))
		errhandler("WriteFile");
	if (!WriteFile(HFile, (LPVOID)pbmiHeader, sizeof(BITMAPINFOHEADER)
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&numOfByteWriten, (NULL)))
		errhandler("WriteFile");
	if (!WriteFile(HFile, (LPSTR)lpBitsData, (int)(pbmiHeader->biSizeImage),
		(LPDWORD)&numOfByteWriten, NULL))
		errhandler("WriteFile");

	// 关闭文件
	if (!CloseHandle(HFile))
		errhandler("CloseHandle");

	delete lpBitsData;
}

void SavaWndBMP(const char* fileName,  HWND hwnd )
{
	// 获取窗口和设备句柄
	HWND SrcHWnd = hwnd;
	if (SrcHWnd == 0)
	{
		SrcHWnd = GetDesktopWindow();
	}
	HDC srcHDC = GetWindowDC(SrcHWnd);

	// 获取窗口尺寸
	RECT wndRect;
	SIZE wndSize;
	GetWindowRect(SrcHWnd, &wndRect);
	wndSize.cx = wndRect.right - wndRect.left;
	wndSize.cy = wndRect.bottom - wndRect.top;

	// 创建bitmap句柄、兼容设备句柄
	// HBITMAP HBitmap = CreateDIBSection(compatibleHDC, &bitmapInfo, DIB_RGB_COLORS, &buf, 0, 0);
	HBITMAP HBitmap = CreateCompatibleBitmap(srcHDC, wndSize.cx, wndSize.cy);
	HDC compatibleHDC = CreateCompatibleDC(srcHDC);

	// 将源设备上下文中bitmap拉伸复制到兼容设备上下文中
	SelectObject(compatibleHDC, HBitmap);
	StretchBlt(compatibleHDC, 0, 0, wndSize.cx, wndSize.cy,
		srcHDC, 0, 0, wndSize.cx, wndSize.cy, SRCCOPY);
	
	PBITMAPINFO pbmi;
	pbmi = CreateBitmapInfoStruct(HBitmap);
	CreateBMPFile(fileName, pbmi, HBitmap, compatibleHDC);
	
	delete pbmi;

	DeleteDC(srcHDC);
	DeleteDC(compatibleHDC);
}