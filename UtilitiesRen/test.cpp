#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <tchar.h>
using namespace std;

#include "SafeArray.h"
#include "GetFilePath.h"
#include "test.h"

bool testSafeArray()
{
	CSafeArray<int> safeIntArray;
	cout << "SafeArraySize: " << safeIntArray.Create(100) << endl;
	for (int i = 0; i < 100; i++)
	{
		safeIntArray[i] = i * i;
	}
	cout << "SafeArrayElement: " << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << safeIntArray[i];
		if (i % 10 == 9)
		{
			cout << endl;
		}
	}
	return true;
}

void testGetFilePath()
{
	wchar_t folderpath[] = _T("D:\\Users\\JackRen\\Documents\\GitHub\\MineViewer\\MineViewerFileSys\\probe");
	vector<string> filepath;

	char *mbPath = new char[100];
	wcstombs_s(NULL,mbPath,100, folderpath,100);

	//��ȡ��·���µ������ļ�  
	GetFilesPath(mbPath, filepath);
	int fpsize = filepath.size();
	for (int i = 0; i < fpsize; i++)
		cout << filepath[i].c_str() << endl;

}

void wtestGetFilePath()
{
	wchar_t folderpath[] = _T("D:\\Users\\JackRen\\Documents\\GitHub\\MineViewer\\MineViewerFileSys\\probe");
	vector<wstring> filepath;

	//��ȡ��·���µ������ļ�  
	locale::global(locale(""));// ���ñ��ػ��ַ�����(�����ʾ������ֽ��ַ���ת����Ҫ���)
	//locale::global(locale("C"));// �ָ�Ĭ���ַ�����
	wGetFilesPath(folderpath, filepath);
	int fpsize = filepath.size();
	for (int i = 0; i < fpsize; i++)
		wcout << filepath[i] << endl;
}

void testGetScreenBMP(const char* fileName)
{
	// ��ȡ���ں��豸���
	HWND deskWndHWnd = GetDesktopWindow();
	HDC srcWndHDC = GetWindowDC(deskWndHWnd);

	// ��ȡ���ڳߴ�
	RECT wndRect;
	SIZE wndSize;
	GetWindowRect(deskWndHWnd, &wndRect);
	wndSize.cx = wndRect.right - wndRect.left;
	wndSize.cy = wndRect.bottom - wndRect.top;

	// ����bitmap����������豸���
	// HBITMAP HBitmap = CreateDIBSection(compatibleHDC, &bitmapInfo, DIB_RGB_COLORS, &buf, 0, 0);
	HBITMAP HBitmap = CreateCompatibleBitmap(srcWndHDC, wndSize.cx, wndSize.cy);
	HDC compatibleHDC = CreateCompatibleDC(srcWndHDC);

	// ��Դ�豸��������bitmap���츴�Ƶ������豸��������
	SelectObject(compatibleHDC, HBitmap);
	StretchBlt(compatibleHDC, 0, 0, wndSize.cx, wndSize.cy, 
		srcWndHDC, 0, 0, wndSize.cx, wndSize.cy, SRCCOPY);

	// ��ȡbitmap��ɫ��ʽ�Լ��ߴ�
	BITMAP bmp;
	int objectSize = GetObject(HBitmap, sizeof(BITMAP), &bmp);

	PBITMAPINFO pBitmapInfo = new BITMAPINFO();
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pBitmapInfo->bmiHeader.biWidth = wndSize.cx;
	pBitmapInfo->bmiHeader.biHeight = wndSize.cy;
	pBitmapInfo->bmiHeader.biPlanes = 1;	// ����Ϊ1
	pBitmapInfo->bmiHeader.biBitCount = 32; 
	pBitmapInfo->bmiHeader.biCompression = 0;
	pBitmapInfo->bmiHeader.biSizeImage = 0; // ��ѹ������¿�����0

	// ��ȡ���HBitMap������Ϣ������д��buf�ֽ���
	// ����ͼ�񻺴�
	void* buf = new char[wndSize.cx*wndSize.cy * 4];
	
	GetDIBits(compatibleHDC, HBitmap, 
		0, pBitmapInfo->bmiHeader.biHeight, buf, pBitmapInfo, DIB_RGB_COLORS);
	
	BITMAPFILEHEADER bitmapFileHeader;
	bitmapFileHeader.bfType = MAKEWORD('B', 'M');
	bitmapFileHeader.bfSize = wndSize.cx * wndSize.cy * 4 + 54;
	bitmapFileHeader.bfOffBits = 54;
	//bitmapFileHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
	//	bitmapInfo.bmiHeader.biSize + bitmapInfo.bmiHeader.biClrUsed
	//	* sizeof(RGBQUAD) + bitmapInfo.bmiHeader.biSizeImage);
	//bitmapFileHeader.bfReserved1 = 0;
	//bitmapFileHeader.bfReserved2 = 0;
	//// Compute the offset to the array of color indices.  
	//bitmapFileHeader.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
	//	bitmapInfo.bmiHeader.biSize + bitmapInfo.bmiHeader.biClrUsed
	//	* sizeof(RGBQUAD);
	BITMAPINFOHEADER bitmapInfoHeader;
	bitmapInfoHeader.biSize = 40;
	bitmapInfoHeader.biWidth = wndSize.cx;
	bitmapInfoHeader.biHeight = wndSize.cy;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 32;
	bitmapInfoHeader.biCompression = 0;
	bitmapInfoHeader.biSizeImage = wndSize.cx * wndSize.cy * 4;

	// �����ļ�׼��д��
	wchar_t *fileNameW = new wchar_t[100];
	mbstowcs_s(NULL, fileNameW, 100, fileName, 100);
	void* HFile = CreateFile(fileNameW, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	DWORD numOfByteWriten;
	WriteFile(HFile, &bitmapFileHeader, sizeof(bitmapFileHeader), &numOfByteWriten, NULL);
	WriteFile(HFile, &bitmapInfoHeader, sizeof(bitmapInfoHeader), &numOfByteWriten, NULL);
	WriteFile(HFile, buf, wndSize.cx*wndSize.cy * 4, &numOfByteWriten, NULL);
	CloseHandle(HFile);

	delete buf;
	DeleteDC(srcWndHDC);
	DeleteDC(compatibleHDC);
}
