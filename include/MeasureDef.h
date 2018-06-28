/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "PubMacroDef.h"

#include <vector>
using std::vector;
enum ENUM_READING : long
{
	GATE_A_PEAK = 0,// 闸门内信号峰值波幅
	GATE_B_PEAK,// 
	GATE_I_PEAK,// 
	GATE_AdBA,// 
	GATE_BdBB,// 闸门B内峰值波幅相对于闸门B阈值的增益，单位为dB
	GATE_AdBr,// 闸门A内峰值波幅相对于参考波幅的增益，单位为dB
	GATE_BdBr,// 闸门B内峰值波幅相对于参考波幅的增益，单位为dB
	GATE_A_PEAK_POS,// 	^和 / 分别表示各闸门内信号的峰值位置和穿出位置
	GATE_B_PEAK_POS,// 
	GATE_I_PEAK_POS,// 
	GATE_A_PIERCE_POS,// 
	GATE_B_PIERCE_POS,// 
	GATE_I_PIERCE_POS,// 
	POS_RA,// 在步进轴上，声束入射点到闸门A、B中测得信号指示间的水平距离
	POS_RB,// 
	POS_PA,// 在步进轴上，楔块前沿到闸门A、B中测得信号指示间的水平距离
	POS_PB,// 
	POS_DA,// 闸门A、B中测得信号反射体的深度
	POS_DB,// 
	POS_SA,// 声束入射点到闸门A、B中测得信号指示间的声程
	POS_SB,// 
	POS_VsA,// 闸门A、B中测得信号指示相对于扫查轴的距离
	POS_VsB,// 
	POS_ViA,// 闸门A、B中测得信号指示相对于步进轴的距离
	POS_ViB,// 
	POS_LA,// 声束入射点到闸门A、B中测得信号指示间声波跳转次数
	POS_LB,// 

	CURSOR_REF_AMPLITUDE, //参考光标位置的波幅值
	CURSOR_MES_AMPLITUDE, //测量光标位置的波幅值
	CURSOR_MES_MINUS_REF_AMPLITUDE, //测量光标的波幅值减去参考光标的波幅值
	CURSOR_REF_POS_USAXIS, //参考光标在超声轴上的位置
	CURSOR_MES_POS_USAXIS, //测量光标在超声轴上的位置
	CURSOR_MES_MINUS_REF_POS_USAXIS, //测量光标位置减去参考光标位置
	CURSOR_REF_PROBE_DISTANCE, //参考光标与探头前沿的距离
	CURSOR_MES_PROBE_DISTANCE, //测量光标与探头前沿的距离
	CURSOR_MES_MINUS_REF_PROBE_DISTANCE, //测量光标位置减去参考光标的距离
	CURSOR_REF_POS_SCANAXIS, //扫查轴上参考光标的位置
	CURSOR_MES_POS_SCANAXIS, //扫查轴上测量光标的位置
	CURSOR_MES_MINUS_REF_POS_SCANAXIS, //测量光标位置减去参考光标的距离
	CURSOR_REF_POS_STEPAXIS, //步进轴上参考光标的位置
	CURSOR_MES_POS_STEPAXIS, //步进轴上测量光标的位置
	CURSOR_MES_MINUS_REF_POS_STEPAXIS, //测量光标位置减去参考光标的距离
	CURSOR_REF_MES_DIOGONAL, //测量光标与参考光标组成长方形框对角线距离
	CURSOR_REF_AMPLITUDE_USAXIS, //超声轴上参考光标位置信号波幅
	CURSOR_MES_AMPLITUDE_USAXIS, //超声轴上测量光标位置信号波幅

	QUANTIFY_A_PEAK_MINUS_CURVE_PERCENT, // 闸门A中测得的信号峰值同所选定曲线上响应波幅差值，以百分数表示
	QUANTIFY_B_PEAK_MINUS_CURVE_PERCENT,
	QUANTIFY_A_PEAK_MINUS_CURVE_DB,//闸门A中测得的信号峰值同所选定曲线上响应波幅差值，以dB表示
	QUANTIFY_B_PEAK_MINUS_CURVE_DB,
	QUANTIFY_A_PEAK_MINUS_CURVE_PERCENT_MAX,//最后一次选择曲线或最后一次复位数据，闸门A中测得的信号峰值同所选定曲线上响应波幅差值，以百分数表示
	QUANTIFY_B_PEAK_MINUS_CURVE_PERCENT_MAX,
	QUANTIFY_A_PEAK_MINUS_CURVE_DB_MAX,//最后一次选择曲线或最后一次复位数据，闸门A中测得的信号峰值同所选定曲线上响应波幅差值，以dB表示
	QUANTIFY_B_PEAK_MINUS_CURVE_DB_MAX,

	SPECIFICATION_AWS_A, SPECIFICATION_AWS_B, SPECIFICATION_AWS_C, SPECIFICATION_AWS_D, SPECIFICATION_AWS_CL,

	ENV_E_AMPLITUDE, ENV_E_PEAK, ENV_E_EDGE , ENV_E_3dB, ENV_E_6dB, ENV_E_12dB, ENV_E_20dB,

	CORROSION_T,
	CORROSION_ML,
	CORROSION_Tmin,
	CORROSION_S_TMin_,
	CORROSION_I_TMin_,
	CORROSION_Angle_TMin,
	CORROSION_TminZ,
	CORROSION_S_TMinZ,
	CORROSION_I_TMinZ,
	CORROSION_Angle_TMinZ,


	WATERLOGGING_I_PIERCE,//信号穿出闸门I的位置
	WATERLOGGING_I_W_PIERCE,//信号穿出闸门I的位置, 使用水中声速

	UT_SCALE, //标度(与数字化频率相关的信号压缩因子)
};

// 光标选择与定位参数
struct STRUCT_CURSOR_SETTING
{
	void Init()
	{
		VPAOrAngle = 0;
	}
	enum ENUM_CATEGORY :long 
	{
		CATEGORY_A,
		CATEGORY_B,
		CATEGORY_C,
		CATEGORY_S,
	};
	ENUM_CATEGORY Category;	//可选：A、B、C、S、数据等，取决于当前布局
	long  MoveMode;	//移动模式：单独、同时
	float Delta;	//	参考和测量光标间的距离：仅在 Cursor 为RandM时可用
	long  Axis;	    //可选A（波幅轴）、U超声轴、S扫查轴、I步进轴，角度，VPA
	long  Cursor;	//可选R（参考光标）m（测量光标）RandM（参考光标和测量光标）
	float ScanPosition;	//	光标在扫查轴位置（仅类别 = 数据有效）
	float StepPosition;	//光标在扫查轴位置（仅类别 = 数据且未光栅扫查有效）
	long  VPAOrAngle;	//	设置光标当前角度（仅类别 = 数据有效）
};

// 记录当前读数栏配置
struct STRUCT_READINGCOL_SETTING
{
	static const int ReadingColNum = 8;	// 读数栏中读数个数
	long MeasureMode;	//选择测量模式, 值为 - 1时，表示自定义读数栏配置
	long MeasureSetting[ReadingColNum];	//存储自定义读数栏配置
};

//缺陷报表
struct STRUCT_DEFECTREPORT_SETTING
{
	vector<long> ColSetting;	//除必选项外，缺陷报表要包含的列名（使用表示不同的读数宏）
	vector<vector<float>> data;	//缺陷报表所有条目
};

struct STRUCT_MEASURE_SETTING
{
	STRUCT_CURSOR_SETTING			Cursor;	//光标
	STRUCT_READINGCOL_SETTING		ReadingCol;	    //读数栏
	STRUCT_DEFECTREPORT_SETTING		DefectReport;	//缺陷报表
	// 定义二维常量数组，存储预定义测量模式。每组预定义测量模式包含8个读数宏。
	static const ENUM_READING		PreDefinedMeasureMode [][8];
};

