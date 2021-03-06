#include "stdafx.h"
#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>
#include <atltrace.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//////////////////////////////////////////////////
class ScreenCatcher
{
public:
	// 将源窗口截图显示在目标窗口中
	ScreenCatcher(HWND src_hwnd, HWND dst_hwnd)
		:m_srcHWnd(src_hwnd), m_dstHWnd(dst_hwnd)
	{
		m_srcWndSize = { 0,0 };
	}

	//根据句柄获得窗口DC
	HDC  GetWindowsDC(HWND hwnd)
	{
		return ::GetDC(hwnd);
	}

	void GetWindowsSize(HWND hwnd)
	{
		::RECT rect;
		::GetWindowRect(m_srcHWnd, &rect);
		LONG wndWidth = rect.right - rect.left;
		LONG wndHeight = rect.bottom - rect.top;
		m_srcWndSize = { wndWidth,wndHeight };
	}

	//将源窗口画到目标窗口
	void BitBltPicture()
	{
		if (m_srcHWnd == m_dstHWnd)
		{
			m_srcHDC = GetWindowsDC(m_srcHWnd);
			m_dstHDC = m_srcHDC;
		}
		else
		{
			m_srcHDC = GetWindowsDC(m_srcHWnd);
			m_dstHDC = GetWindowsDC(m_dstHWnd);
		}
		GetWindowsSize(m_srcHWnd);

		m_hdcCompatible = ::CreateCompatibleDC(m_srcHDC);
		m_hBitmap = ::CreateCompatibleBitmap(m_srcHDC, m_srcWndSize.cx, m_srcWndSize.cy);
		::SelectObject(m_hdcCompatible, m_hBitmap);
		::BitBlt(m_hdcCompatible, 0, 0, m_srcWndSize.cx, m_srcWndSize.cy, m_srcHDC, 0, 0, SRCCOPY);
		::BitBlt(m_dstHDC, 0,0, m_srcWndSize.cx, m_srcWndSize.cy, m_hdcCompatible, 0, 0, SRCCOPY);
	}

	~ScreenCatcher()
	{
		::DeleteDC(m_hdcCompatible);
		::DeleteDC(m_srcHDC);
		::DeleteDC(m_dstHDC);
		::DeleteObject(m_hBitmap);
	}

private:
	// 源目的窗口、及其设备上下文句柄
	HWND        m_srcHWnd;
	HWND        m_dstHWnd;
	HDC         m_srcHDC;
	HDC         m_dstHDC;
	
	// 兼容设备上下文
	HDC         m_hdcCompatible;
	HBITMAP     m_hBitmap;
	// 源窗口尺寸
	SIZE		m_srcWndSize;
};

/////////////////////////////////////////////////


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Bricks1");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("LoadBitmap Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC            hdc;
	static HINSTANCE      hInstance;

	// 将源窗口截图显示在目标窗口中
	static HWND hwndsrc = ::GetDesktopWindow();
	static ScreenCatcher screenCatcher(hwndsrc, hwnd);

	switch (message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		return 0;

	case WM_SIZE:
		screenCatcher.BitBltPicture();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
