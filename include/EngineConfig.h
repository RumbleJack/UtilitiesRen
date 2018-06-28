#pragma once
/*-------------------------------------------------------------------------*/
/*----------------------------ȫ�ֺ궨��ͷ�ļ�-----------------------------*/
/*-------------------------------------------------------------------------*/
#include "PubMacroDef.h"
//#pragma warning( disable: 4251 )

/*-------------------------------------------------------------------------*/
/*--------------------------------D3Dͷ�ļ�--------------------------------*/
/*-------------------------------------------------------------------------*/
#define DIRECTX_2010
#ifdef DIRECTX_2010
	// ��ֹ��16�ֽڶ���
	#define _XM_NO_INTRINSICS_
	#define XM_NO_ALIGNMENT
	#include <xnamath.h>
	struct DllExport _XMFLOAT4;
	struct DllExport _XMMATRIX;
	#include <d3dx11Async.h>
	#include <DxErr.h>
	//// ����
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
	//��Win8������ƽ̨����
	#define _XM_NO_INTRINSICS_
	#define XM_NO_ALIGNMENT
	#include <directxmath.h>
	#include <d3dcompiler.h>
	using namespace DirectX;
	struct DllExport DirectX::XMMATRIX;
	struct DllExport DirectX::XMFLOAT4;
	//// ����
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
/*------------------------------��׼C++ͷ�ļ�------------------------------*/
/*-------------------------------------------------------------------------*/
#include <stdio.h>
#include <fstream>
#include <map>
using std::ofstream;
using std::ifstream;
using std::map;

/*-------------------------------------------------------------------------*/
/*------------------------------ȫ�ֱ���-----------------------------------*/
/*-------------------------------------------------------------------------*/
const bool	FULL_SCREEN = false;
const bool	VSYNC_ENABLED = true;	//��ֱͬ��
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 10.0f;
const bool  MSAA4X_ENABLED = false;


