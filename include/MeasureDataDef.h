#pragma once
#include "PubMacroDef.h"
#include "MeasureDef.h"

#define NUM_OF_TOP_BAR_MEASURE_DATES	8

struct STRUCT_SINGLE_MEASURE_DATA
{
	STRUCT_SINGLE_MEASURE_DATA()
	{	
		MeasureID = GATE_A_PEAK;
		MeasureData = 0.0f;
	}

	ENUM_READING	MeasureID;
	float			MeasureData;
};

struct STRUCT_TOPBAR_MEASURE_DATAS
{
	STRUCT_TOPBAR_MEASURE_DATAS()
	{
		NumOfDatas = NUM_OF_TOP_BAR_MEASURE_DATES;
		pMeasureDatas = new STRUCT_SINGLE_MEASURE_DATA[NumOfDatas];
	}
	~STRUCT_TOPBAR_MEASURE_DATAS()
	{
		if (pMeasureDatas)
			delete[]pMeasureDatas;
		pMeasureDatas = NULL;
	}
	
	STRUCT_SINGLE_MEASURE_DATA *pMeasureDatas;
	long NumOfDatas;
};

// 与闸门相关的测量数据
struct STRUCT_SINGLE_GATE_MEASURE_DATA
{	
	// %	闸门内信号峰值波幅
	STRUCT_SINGLE_MEASURE_DATA MaxAmplitude;
	// dB	峰值波幅相对于闸门阈值的增益
	STRUCT_SINGLE_MEASURE_DATA DbAccordGateLimit;
	// dB	峰值波幅相对于参考波幅的增益
	STRUCT_SINGLE_MEASURE_DATA DbAccordReferLimit;
	// ^	闸门内信号的峰值位置
	STRUCT_SINGLE_MEASURE_DATA MaxAmplitudePos;
	// /	闸门内信号的穿出位置
	STRUCT_SINGLE_MEASURE_DATA OutGatePos;
	// RX^	步进轴上，声束入射点到闸门中测得信号指示间的水平距离

	// PX^	步进轴上，楔块前沿到闸门中测得信号指示间的水平距离

	// DX^	闸门中测得信号反射体的深度

	// SX^	声束入射点到闸门中测得信号指示间的声程

	// VsX^	闸门中测得信号指示相对于扫查轴的距离

	// ViX^	闸门中测得信号指示相对于步进轴的距离

	// LX^	声束入射点到闸门测得信号指示间声波跳转次数
};

struct STRUCT_MULTI_GATES_MEASURE_DATA
{
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateAData;
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateBData;
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateIData;
};

// 光标的测量数据
struct STRUCT_SINGLE_CURSOR_DATA
{
	// %	光标处信号波幅
	STRUCT_SINGLE_MEASURE_DATA AmplitudeData;
	// U	光标处超声轴上的位置
	STRUCT_SINGLE_MEASURE_DATA UltrAxisPos;
	// P	光标处与探头前沿的距离
	STRUCT_SINGLE_MEASURE_DATA ProbeFrontLength;
	// S	光标处在扫查轴上的位置
	STRUCT_SINGLE_MEASURE_DATA ScanAxisPos;
	// I	光标处在步进轴上的位置
	STRUCT_SINGLE_MEASURE_DATA StepAxisPos;
	// %(U(X))	光标处在超声轴上的信号波幅
	STRUCT_SINGLE_MEASURE_DATA AmplitudeInUltrAxisPos;
};

// 光标的测量数据
struct STRUCT_MULTI_CURSORS_DATA
{
	STRUCT_SINGLE_CURSOR_DATA	ReferCursorData;
	STRUCT_SINGLE_CURSOR_DATA	MeasureCursorData;
	STRUCT_SINGLE_CURSOR_DATA	Measure_ReferCursorData;
	
	// IU(mr)	由测量光标与参考光标交叉形成的长方形框的对角线的距离
	STRUCT_SINGLE_MEASURE_DATA	Measure_ReferDiagLength;
};