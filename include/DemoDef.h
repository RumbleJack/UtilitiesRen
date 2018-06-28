/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

// Demo(无实际意义)
//typedef struct
//{
//	long	Style;
//	unsigned short MinIdxEle;
//	unsigned short MaxIdxEle;
//	float	SizeEle;
//} STRUCT_PROBE_SETTING;
// 试块类型
#define TESTBLOCK_STYLE_UNDEFINED	0
#define TESTBLOCK_STYLE_CUBIC	1
#define TESTBLOCK_STYLE_CYLINDER	2
typedef struct
{
	long	Shape;
	float Thickness;
} STRUCT_TESTBLOCK_SETTING;


