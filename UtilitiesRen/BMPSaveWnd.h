#pragma once
#include "stdafx.h"

void errhandler(const char* info, HWND hwnd = 0);

// 该函数使用句柄HBITMAP获取Bitmap结构体信息，进而初始化PBITMAPINFO指针。
PBITMAPINFO CreateBitmapInfoStruct( HBITMAP HBitmap, HWND hwnd = 0);

void CreateBMPFile(const char* fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd = 0);
void CreateBMPFile(LPTSTR fileName, PBITMAPINFO pbmi, HBITMAP HBitmap, HDC compatibleHDC, HWND hwnd = 0);

void SavaWndBMP(const char* fileName,HWND hwnd = 0);