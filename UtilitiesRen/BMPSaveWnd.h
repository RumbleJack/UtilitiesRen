#pragma once
#include "stdafx.h"

void errhandler(const char* info, HWND hwnd = 0);

// �ú���ʹ�þ��HBITMAP��ȡBitmap�ṹ����Ϣ��������ʼ��PBITMAPINFOָ�롣
PBITMAPINFO CreateBitmapInfoStruct( HBITMAP HBitmap, HWND hwnd = 0);

void CreateBMPFile(const char* fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd = 0);
void CreateBMPFile(LPTSTR fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd = 0);

void SavaWndBMP(const char* fileName,HWND hwnd = 0);