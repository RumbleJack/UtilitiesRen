#pragma once

#include "PubMacroDef.h"
#include "GateAlarmDef.h"
#include "UTDef.h"
#include "CalibrationDef.h"

// 超声校准类
class DllExport USCalibration
{
public:
	//	回波类型，包括半径、深度、厚度。
	enum ECHOSTYLE :long { ECHO_STYLE_RADIUS, ECHO_STYLE_DEEPNESS, ECHO_STYLE_THICKNESS, };
	ECHOSTYLE EchoStyle;
	// 可选择应用于全部法则或2~3个法则。设置枚举类型：声速校准默认应用于全部聚焦法则
	enum RULENUMBER :long { RULENUMBER_ALL, RULENUMBER_2OR3, };
	RULENUMBER RuleNumber;
	//	半径 / 深度 / 厚度1、2，除声速校准，其余只有1有效
	float Baseline[2];
	//指定A扫描设置
	STRUCT_ASCAN_SETTING*  AScan;
	//指定当前闸门参数
	STRUCT_GATE_SETTING*  Gate;
};

class DllExport USCalibrationDACManual : public USCalibration
{
	long CurAngleOrVPA;// 采集数据时的角度或VPA
	bool IsApplyToAllLaw;// 是否应用于全部聚焦法则
	long QuantitativeType;// 定量类型，枚举：可选自定义、JIS、ASME标准。当定量类型选择自定义时，曲线类型和曲线数量可编辑。
	long CurveType;// 	曲线类型，定义宏，直线、对数、多项式
	long CurvesNum;// 曲线数量
	vector<float>CurvesOffset;// 为每条曲线设置偏移
	float RefAmplitude;// 参考波幅，通常设为80%
	struct STRUCT_PONITDAC_DATA
	{
		float depth;//深度
		vector<pair<float, float>> Pair_Gain_Amplitude;//增益波幅对。
	};
	vector<STRUCT_PONITDAC_DATA> AllPointData; //在超声轴上寻找多个位置不同的点，测量其位置及对应波幅，及其当前增益。

	//UT矫正时法则数为1，增益波幅对相应为1，PA时大于1。
	typedef vector<pair<float, float>> DAC_CURVE;// Pair_Dis_Amp距离波幅对
	DAC_CURVE OneDACCurve;// 校准结果;获得一条法则的DAC曲线，曲线横坐标为声程（深度）纵坐标为波幅，并且需要记录校准DAC曲线时所对应的增益。UT矫正时法则数为1，PA时法则数大于1
	float DACGain;// 校准结果DAC曲线所对应的增益

};

class DllExport USCalibrationDACAuto : public USCalibration
{
	long CurAngleOrVPA;// 采集数据时的角度或VPA
	bool IsApplyToAllLaw;// 是否应用于全部聚焦法则
	long QuantitativeType;// 定量类型，枚举：可选自定义、JIS、ASME标准。当定量类型选择自定义时，曲线类型和曲线数量可编辑。
	long CurveType;// 曲线类型，定义宏，直线、对数、多项式
	long CurvesNum;// 曲线数量
	vector<float>CurvesOffset;// 为每条曲线设置偏移
	float RefAmplitude;// 参考波幅，通常设为80%
	float MaterialAttenuation;// 材料衰减，根据材料衰减自动计算DAC

	DAC_CURVE OneDACCurve;// 校准结果;获得一条法则的DAC曲线，曲线横坐标为声程（深度）纵坐标为波幅，并且需要记录校准DAC曲线时所对应的增益。UT矫正时法则数为1，PA时法则数大于1 UT矫正时法则数为1，PA时法则数大于1
	float DACGain;// 记录校准DAC曲线所对应的增益
};

class DllExport USCalibrationTCGManual : public USCalibration
{
	long CurAngleOrVPA;// 采集数据时的角度或VPA
	bool IsApplyToAllLaw;// 是否应用于全部聚焦法则
	float RefAmplitude;// 	参考波幅，通常设为80%
	struct STRUCT_PONITTCG_DATA {
		float depth;//深度
		vector<pair<float, float>> Pair_Gain_Amplitude;//增益波幅对。
	};// 
	vector<STRUCT_PONITTCG_DATA> AllPointData;//在超声轴上寻找多个位置不同的点，测量其位置及对应波幅，及其当前增益。

	vector< TCG_CURVE > AllTCGCurve;// 校准结果,对每个聚焦法则进行TCG校准，曲线横坐标为声程（深度）纵坐标为补偿增益

	float TCGGain; //	记录校准TCG曲线所对应的基础增益
};