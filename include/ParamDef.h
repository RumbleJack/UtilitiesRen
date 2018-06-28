/*---------------------------------------------------------------------------*/
/*-----文件StrucParamDef：定义超声探伤仪器中使用结构化参数-------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
// 配置参数
#include "ProbeDef.h"
#include "WeldDef.h"
#include "WorkPieceDef.h"
#include "WedgeDef.h"
#include "FoucusLawDef.h"
#include "GroupHeaderDef.h"

// 扫查参数
#include "UTDef.h"
#include "MeasureDef.h"
#include "DisplayDef.h"
#include "GateAlarmDef.h"
#include "ScanDef.h"

// 其他参数
#include "FFTDef.h"
#include "DemoDef.h"
#include "CalibrationDef.h"
#include "ScanDataDef.h"

#include "RationDef.h"
#include "PADef.h"
/*---------------------------------------------------------------------------*/
/* ------------------------------定义组--------------------------------------*/
/*---------------------------------------------------------------------------*/
class USGroup
{
public:
	USGroup()
	{
		// 组头
		GroupHeader.InitGroupHeader();
		// 工件及焊缝
		WorkPiece.Init();
		// 探头(与组头中PA对应)
		Probe.Init();
		// 楔块
		Wedge.Init();
		// 探头位置
		Probeposition.Init();
		// 聚焦法则（仅PA组）
		FoucusLaw.Init();

		//当前组超声设置
		UT.Init();
		//当前组测量设置
		Measure.Cursor.Init();

		//当前组显示设置
		//当前组闸门设置
		Gate.Init();
		//当前组报警设置
		Alarm.Init();
		//当前组扫查设置
		// 探头FFT特性
	}
	~USGroup()
	{
	}
public:
	// 组头，保存了当前组的基本配置
	STRUCT_GROUPHEADER_SETTING GroupHeader;
	// 工件及焊缝（焊缝作为工件结构体的一个成员）
	STRUCT_WORKPIECE_SETTING WorkPiece;
	// 探头
	STRUCT_PROBE_SETTING Probe;
	// 楔块
	STRUCT_WEDGE_SETTING Wedge;
	// 探头位置
	STRUCT_PROBEPOSITION_SETTING Probeposition;
	// 聚焦法则（仅PA组）
	STRUCT_FOUCUSLAW_SETTING FoucusLaw;

	//当前组超声设置
	STRUCT_UT_SETTING UT;
	//当前组测量设置
	STRUCT_MEASURE_SETTING Measure;
	//当前组显示设置
	STRUCT_DISPLAY_SETTING Display;
	//当前组闸门设置
	STRUCT_GATE_SETTING Gate;
	//当前组报警设置
	STRUCT_ALARM_SETTING Alarm;
	//当前组扫查设置
	STRUCT_SCAN_SETTING Scan;

	//探头FFT特性
	STRUCT_FFT_PROPERTY FFTProperty;

	// 当前组校准结果
	STRUCT_CALIBRATION_SETTING Calibration;
};



