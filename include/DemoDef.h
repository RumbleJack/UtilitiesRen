/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

// Demo(��ʵ������)
//typedef struct
//{
//	long	Style;
//	unsigned short MinIdxEle;
//	unsigned short MaxIdxEle;
//	float	SizeEle;
//} STRUCT_PROBE_SETTING;
// �Կ�����
#define TESTBLOCK_STYLE_UNDEFINED	0
#define TESTBLOCK_STYLE_CUBIC	1
#define TESTBLOCK_STYLE_CYLINDER	2
typedef struct
{
	long	Shape;
	float Thickness;
} STRUCT_TESTBLOCK_SETTING;


