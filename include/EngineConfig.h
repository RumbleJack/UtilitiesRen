#pragma once
/*-------------------------------------------------------------------------*/
/*----------------------------全局宏定义头文件-----------------------------*/
/*-------------------------------------------------------------------------*/
#include "PubMacroDef.h"
//#pragma warning( disable: 4251 )

/*-------------------------------------------------------------------------*/
/*--------------------------------D3D头文件--------------------------------*/
/*-------------------------------------------------------------------------*/
#define DIRECTX_2010
#ifdef DIRECTX_2010
	// 禁止按16字节对齐
	#define _XM_NO_INTRINSICS_
	#define XM_NO_ALIGNMENT
	#include <xnamath.h>
	struct DllExport _XMFLOAT4;
	struct DllExport _XMMATRIX;
	#include <d3dx11Async.h>
	#include <DxErr.h>
	//// 链接
	#pragma comment(lib, "d3d11.lib")   
	#pragma comment(lib, "dxgi.lib")	 
	#pragma comment(lib, "d3dx11.lib")   
	#pragma comment(lib, "dxerr.lib")
	//---------------------------------------------------------------------------------------
	// Simple d3d error checker 
	//---------------------------------------------------------------------------------------
	#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
		{                                                          \
			HRESULT hr = (x);                                      \
			if(FAILED(hr))                                         \
			{                                                      \
				DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
			}                                                      \
		}
	#endif
	#else
	#ifndef HR
	#define HR(x) (x)
	#endif
	#endif 
#else
	//在Win8及以上平台可用
	#define _XM_NO_INTRINSICS_
	#define XM_NO_ALIGNMENT
	#include <directxmath.h>
	#include <d3dcompiler.h>
	using namespace DirectX;
	struct DllExport DirectX::XMMATRIX;
	struct DllExport DirectX::XMFLOAT4;
	//// 链接
	#pragma comment(lib, "d3d11.lib")		// contains all the Direct3D functionality
	#pragma comment(lib, "dxgi.lib")	 //contains tools to interface with the hardware
	#pragma comment(lib, "d3dcompiler.lib")  //contains functionality for compiling shaders
	//---------------------------------------------------------------------------------------
	// Simple d3d error checker 
	//---------------------------------------------------------------------------------------
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif
#include <d3d11.h>
#include <dxgi.h>
//#include <d3dcommon.h>

/*-------------------------------------------------------------------------*/
/*------------------------------标准C++头文件------------------------------*/
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <fstream>
#include <map>
using std::ofstream;
using std::ifstream;
using std::map;

/*-------------------------------------------------------------------------*/
/*------------------------------全局变量-----------------------------------*/
/*-------------------------------------------------------------------------*/
const bool	FULL_SCREEN = false;
const bool	VSYNC_ENABLED = true;	//垂直同步
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 10.0f;
const bool  MSAA4X_ENABLED = false;


