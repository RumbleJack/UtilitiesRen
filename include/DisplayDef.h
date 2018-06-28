/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "GateAlarmDef.h"
#include "ScanDataDef.h"

// 超声数据的矫正水平
struct STRUCT_DISPLAY_UT_SETTING
{
	STRUCT_DISPLAY_UT_SETTING()
	{
		UTMode = UT_MODE_SOUNDPATH;
		TrueDepthMode = ALL_LAWS;
		UnitStyle = UT_UNIT_STYLE_DISTANCE;
	}
	enum ENUM_UT_MODE:long{
		UT_MODE_REALDEPTH = 0, UT_MODE_SOUNDPATH, UT_MODE_UNCORRECTED
	};
	ENUM_UT_MODE UTMode;// 选择视图中所显示的超声数据的矫正水平。可选真实深度、声程、未矫正（仅PA）
	enum ENUM_TRUE_DEPTH_MODE :long{
		CURRENT_LAW = 0, ALL_LAWS
	};
	ENUM_TRUE_DEPTH_MODE TrueDepthMode;// 当UTMode选择真实深度，且为PA模式，该参数有效，可选全部聚焦法则、当前聚焦法则。
	enum ENUM_UNIT_STYLE :long {
		UT_UNIT_STYLE_TIME = 0, UT_UNIT_STYLE_DISTANCE
	};
	ENUM_UNIT_STYLE UnitStyle;// 仅UTMode选择声程、未矫正（仅PA）时有效。真实深度可选时间或距离
};

// A扫描配置
struct STRUCT_DISPLAY_ASCAN_SETTING
{
	long AScanDataSrc;// 选择显示在A扫描视图中的一个A扫描或多个A扫描的组合。可选正常、最高、最薄、全部法则等。
	long Color;// A扫描颜色
	long Exterior;// 外观。可选中空、填充、中空两种颜色、填充两种颜色

};
// C扫描配置
struct STRUCT_DISPLAY_CSCAN_SETTING
{
	long CScanDataSrc;// 选择C扫描的源，可选A%, B%I / 厚度，比例1:1
};
// 声线跟踪配置
struct STRUCT_DISPLAY_SOUNDTRACE_SETTING
{
	long StepNum;// 设置声线跟踪当中跨的数目
	float Magnification;// 放大比例。（以步进轴为中心放大）

};
struct STRUCT_DCOVER_CURSOR_SETTING
{
	BOOL Cursor[2];// 设置需要显示的光标：参考光标、测量光标
	BOOL Value;// 是否在光标位置显示数值
	BOOL AScan;// 在A扫描视图右上角显示光标位置处A扫描数值

};
struct STRUCT_DCOVER_ASCAN_SETTING
{
	BOOL Envelope;// 包络
	long QuanCurve;// 	定量曲线 : DAC、TCG、DGS
	BOOL TCGGainCurve;// 	TCG增益曲线(不懂)友联的人也不懂
	BOOL RefAmp;// 	参考波幅
	BOOL Raster;// 栅格

};
struct STRUCT_DCOVER_INDICATOR_SETTING
{
	BOOL Weld;// 	焊缝
	BOOL Step;// 	跨
};
//覆盖配置
struct STRUCT_DISPLAY_COVER_SETTING
{
	STRUCT_DISPLAY_COVER_SETTING()
	{
		for (int i = 0; i < STRUCT_GATE_SETTING::GATE_NUM; i++)
		{
			Gate[i] = TRUE;
		}
	}
	BOOL Gate[STRUCT_GATE_SETTING::GATE_NUM];// 设置需要显示的闸门（A、B、I）
	STRUCT_DCOVER_CURSOR_SETTING DCoverCursor;// 	光标
	STRUCT_DCOVER_ASCAN_SETTING DCoverAScan;// A扫描
	STRUCT_DCOVER_INDICATOR_SETTING DCoverIndicator;// 指示器
};

// 伪彩色
struct STRUCT_DISPLAY_COLOR
{
	STRUCT_DISPLAY_COLOR()
	{
		ColorRGBA.SetRGBA(255, 255, 255, 1);
		StartAmplitude = 0;
		EndAmplitude = 10;
	}
	bool operator == (STRUCT_DISPLAY_COLOR& other)
	{
		if (ColorRGBA == other.ColorRGBA
			&& StartAmplitude == other.StartAmplitude
			&& EndAmplitude == other.EndAmplitude)
			return true;
		else
			return false;
	}
	STRUCT_RGBA_DATA ColorRGBA;
	LONG StartAmplitude;
	LONG EndAmplitude;
};

// 属性配置
struct STRUCT_DISPLAY_ATTRIBUTE_SETTING
{
	STRUCT_DISPLAY_ATTRIBUTE_SETTING()
	{
		ColorNum = 4;
		pColors = new STRUCT_DISPLAY_COLOR[ColorNum];

		pColors[0].ColorRGBA.SetRGBA(255, 255, 255, 1);
		pColors[0].StartAmplitude = 0;
		pColors[0].EndAmplitude = 50;

		pColors[1].ColorRGBA.SetRGBA(0, 0, 255, 1);
		pColors[1].StartAmplitude = 50;
		pColors[1].EndAmplitude = 80;

		pColors[2].ColorRGBA.SetRGBA(0, 255, 0, 1);
		pColors[2].StartAmplitude = 80;
		pColors[2].EndAmplitude = 100;

		pColors[3].ColorRGBA.SetRGBA(255, 0, 0, 1);
		pColors[3].StartAmplitude = 100;
		pColors[3].EndAmplitude = 100;

		mpColorsRefer = new STRUCT_RGBA_DATA[NUM_OF_COLORS];
	}
	~STRUCT_DISPLAY_ATTRIBUTE_SETTING()
	{
		if (pColors)
			delete []pColors;
		pColors = NULL;
		if (mpColorsRefer)
			delete []mpColorsRefer;
		mpColorsRefer = NULL;
		ColorNum = 0;
	}
	bool operator==(STRUCT_DISPLAY_ATTRIBUTE_SETTING& other)
	{
		for (int i = 0; i < NUM_OF_COLORS; i++)
		{
			if (!(mpColorsRefer[i] == other.mpColorsRefer[i]))
				return false;
		}
		return true;
	}
	STRUCT_DISPLAY_ATTRIBUTE_SETTING(const STRUCT_DISPLAY_ATTRIBUTE_SETTING& other)
	{
		ColorNum = other.ColorNum;
		pColors = new STRUCT_DISPLAY_COLOR[other.ColorNum];
		memcpy(pColors, other.pColors, sizeof(STRUCT_DISPLAY_COLOR)*other.ColorNum);

		mpColorsRefer = new STRUCT_RGBA_DATA[NUM_OF_COLORS];
		memcpy(mpColorsRefer, other.mpColorsRefer, sizeof(STRUCT_RGBA_DATA)*NUM_OF_COLORS);
	}
	STRUCT_DISPLAY_COLOR *pColors;
	LONG ColorNum;
	STRUCT_RGBA_DATA *mpColorsRefer;
};

enum ENUM_LAYOUT_STYLE :long
{
	LAYOUT_STYLE_A,
	LAYOUT_STYLE_B,
	LAYOUT_STYLE_C,
	LAYOUT_STYLE_S,
	LAYOUT_STYLE_R,
	LAYOUT_STYLE_A_S,
	LAYOUT_STYLE_A_C,
	LAYOUT_STYLE_A_C_S,
	LAYOUT_STYLE_A_C_R_S,
};

struct STRUCT_DISPLAY_SETTING
{
	STRUCT_DISPLAY_SETTING()
	{
		GroupNum = 0;
		IsFullScrenn = false;
		IsAllGroup = false;
		Layout = LAYOUT_STYLE_A_C_S;
	}
	long GroupNum;// 指定当前显示组编号
	BOOL IsFullScrenn;//  是否全屏
	BOOL IsAllGroup;	//是否显示多组
	
	ENUM_LAYOUT_STYLE Layout;// 指定当前数据视图的排列方式。可选显示有A、B、C、S、R、及以上两种或三种扫描的组合
	STRUCT_DISPLAY_UT_SETTING DisplayUT;// 超声数据的矫正水平
	STRUCT_DISPLAY_ASCAN_SETTING DisplayAScan;// A扫描配置
	STRUCT_DISPLAY_CSCAN_SETTING DisplayCScan;// C扫描配置
	STRUCT_DISPLAY_SOUNDTRACE_SETTING DisplaySoundBeam;// 声线跟踪配置
	STRUCT_DISPLAY_COVER_SETTING DisplayCover;// 覆盖配置
	STRUCT_DISPLAY_ATTRIBUTE_SETTING DisplayAttribute;	// 属性配置
};