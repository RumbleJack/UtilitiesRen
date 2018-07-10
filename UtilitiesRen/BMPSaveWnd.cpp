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

	// ��ȡbitmap��ɫ��ʽ�Լ��ߴ�
	int objectSize = 0;
	if (!(objectSize = GetObject(HBitmap, sizeof(BITMAP), &bmp)))
		errhandler("GetObject");

	// bmPlanesʼ��Ϊ1����bmBitsPixel��ʾÿ�����������λ��
	// ������ˣ�ʵ���ϻ��Ǳ�ʾÿ�����������λ��������๲��2^cClrBits��ɫ
	// ����ɫ��ʽת��Ϊ��ʾ��ɫ�����λ��
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

	// ΪBITMAPINFO�����ڴ棬�ýṹ�����һ��BITMAPINFOHEADER�Լ�һ��RGBQUAD����
	if (cClrBits < 24)
	{
		pbmi = (PBITMAPINFO)new char[
			sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * (1 << cClrBits)];
	}
	else
	{
		// ��������ͼ���ʽ������RGBQUAD����: ÿ����24λ��ÿ����32λ
		pbmi = (PBITMAPINFO)new char[
			sizeof(BITMAPINFOHEADER)];
	}

	// ��ʼ��BITMAPINFO�ṹ��
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;// ʼ��Ϊ1
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
	{
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
	}
	else
	{
		pbmi->bmiHeader.biClrUsed = 0;
	}
	// ���δѹ�������� BI_RGB ��־.  
	pbmi->bmiHeader.biCompression = BI_RGB;
	// ����ͼ����ɫ����������ֽ��������洢��24/32λͼ�������������RGB��ɫ��
	// bitmap��ȱ���Ϊ˫�ֶ��룬����ʹ��RLEѹ��
	// ��ѹ������¿�����0
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// biClrImportant��Ϊ0����Ϊ������ɫ����Ҫ 
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(LPTSTR fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd )
{
	// ��BitmapInfoǿ��ת��ΪBitmapInfoHeader
	PBITMAPINFOHEADER pbmiHeader;
	pbmiHeader = (PBITMAPINFOHEADER)pbmi;

	// Ϊ����ָ������ڴ�
	void* lpBitsData;
	lpBitsData = new char[pbmiHeader->biSizeImage];
	if (!lpBitsData)
		errhandler("GlobalAlloc");

	// ��DIB�л�ȡ��ɫ��(RGBQUAD array) �Լ�ͼ���������ݣ���ɫ������
	if (!GetDIBits(compatibleHDC, HBitmap, 0, (WORD)pbmiHeader->biHeight, lpBitsData, pbmi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits");
	}

	BITMAPFILEHEADER bmfHeader;
	//bmfHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	bmfHeader.bfType = MAKEWORD('B', 'M');
	// ���������ļ��Ĵ�С���óߴ�������ļ�ͷ��С+BMPͷ��С+RGBQUAD�����С+�������ݴ�С
	bmfHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD)
		+ pbmiHeader->biSizeImage);
	bmfHeader.bfReserved1 = 0;
	bmfHeader.bfReserved2 = 0;
	// �����������ݣ�������ƫ��
	bmfHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD));

	// �����ļ�׼��д��
	HANDLE HFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	// �����ļ�ͷ��bmpͷ��BITMAPINFOHEADER�Լ�RGBQUAD���飩�Լ�bmp���ݵ��ļ�
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

	// �ر��ļ�
	if (!CloseHandle(HFile))
		errhandler("CloseHandle");

	delete lpBitsData;
}

void CreateBMPFile(const char* fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd)
{
	// ��BitmapInfoǿ��ת��ΪBitmapInfoHeader
	PBITMAPINFOHEADER pbmiHeader;
	pbmiHeader = (PBITMAPINFOHEADER)pbmi;

	// Ϊ����ָ������ڴ�
	void* lpBitsData;
	lpBitsData = new char[pbmiHeader->biSizeImage];
	if (!lpBitsData)
		errhandler("GlobalAlloc");

	// ��DIB�л�ȡ��ɫ��(RGBQUAD array) �Լ�ͼ���������ݣ���ɫ������
	if (!GetDIBits(compatibleHDC, HBitmap, 0, (WORD)pbmiHeader->biHeight, lpBitsData, pbmi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits");
	}

	BITMAPFILEHEADER bmfHeader;
	//bmfHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	bmfHeader.bfType = MAKEWORD('B', 'M');
	// ���������ļ��Ĵ�С���óߴ�������ļ�ͷ��С+BMPͷ��С+RGBQUAD�����С+�������ݴ�С
	bmfHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD)
		+ pbmiHeader->biSizeImage);
	bmfHeader.bfReserved1 = 0;
	bmfHeader.bfReserved2 = 0;
	// �����������ݣ�������ƫ��
	bmfHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER)
		+ pbmiHeader->biSize
		+ pbmiHeader->biClrUsed * sizeof(RGBQUAD));

	// �����ļ�׼��д��
	wchar_t *fileNameW = new wchar_t[100];
	mbstowcs_s(NULL, fileNameW, 100, fileName, 100);
	HANDLE HFile = CreateFile(fileNameW, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	// �����ļ�ͷ��bmpͷ��BITMAPINFOHEADER�Լ�RGBQUAD���飩�Լ�bmp���ݵ��ļ�
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

	// �ر��ļ�
	if (!CloseHandle(HFile))
		errhandler("CloseHandle");

	delete lpBitsData;
}

void SavaWndBMP(const char* fileName,  HWND hwnd )
{
	// ��ȡ���ں��豸���
	HWND SrcHWnd = hwnd;
	if (SrcHWnd == 0)
	{
		SrcHWnd = GetDesktopWindow();
	}
	HDC srcHDC = GetWindowDC(SrcHWnd);

	// ��ȡ���ڳߴ�
	RECT wndRect;
	SIZE wndSize;
	GetWindowRect(SrcHWnd, &wndRect);
	wndSize.cx = wndRect.right - wndRect.left;
	wndSize.cy = wndRect.bottom - wndRect.top;

	// ����bitmap����������豸���
	// HBITMAP HBitmap = CreateDIBSection(compatibleHDC, &bitmapInfo, DIB_RGB_COLORS, &buf, 0, 0);
	HBITMAP HBitmap = CreateCompatibleBitmap(srcHDC, wndSize.cx, wndSize.cy);
	HDC compatibleHDC = CreateCompatibleDC(srcHDC);

	// ��Դ�豸��������bitmap���츴�Ƶ������豸��������
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