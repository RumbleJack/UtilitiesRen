#pragma once
#include <vector>
#include <utility>
using std::vector;
using std::pair;

#include "GroupHeaderDef.h"

typedef vector<pair<float, float>> DAC_CURVE;//距离波幅对曲线
typedef vector<pair<float, float>> TCG_CURVE;//声程补偿增益对曲线

// 超声矫正一般设置
struct STRUCT_USCALIBRATION_GENERAL_SETTING
{
	
	void Init()
	{
		AScan->Init();
	}
	//	回波类型，包括半径、深度、厚度。
	enum ECHOSTYLE :long { ECHO_STYLE_RADIUS, ECHO_STYLE_DEEPNESS, ECHO_STYLE_THICKNESS, };
	ECHOSTYLE EchoStyle;
	// 可选择应用于全部法则或2~3个法则。设置枚举类型：声速校准默认应用于全部聚焦法则
	enum RULENUMBER :long { RULENUMBER_ALL, RULENUMBER_2OR3, };
	RULENUMBER RuleNumber;
	//	半径 / 深度 / 厚度1、2，除声速校准，其余只有1有效
	float Baseline[2];
	//指定A扫描设置
	STRUCT_ASCAN_SETTING* AScan;
	
	//指定当前闸门参数
	STRUCT_GATE_SETTING*  Gate;
};

// 超声声速矫正设置
struct STRUCT_USCALIBRATION_SPEED_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long AngleOrVPAToCalibrate;//	指定角度(扇形扫描) / VPA（线性扫描）用于声速校准
	float CalibratedSpeed;//校准后的声速
};

//灵敏度校准设置
struct STRUCT_USCALIBRATION_SENSITIVITY_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	float CalibAmplitudeV;
	float SetCompensateGain;
	float SetGainGain;
	float SetGateStart;
	float SetGateThreshold;
	float SetGateWidth;
	float SetIntervalFirstAngle;
	float SetIntervalLastAngle;
	float SetRefAmplitudeError;
	float SetRefAmplitudeRefAmplitude;
};

// 超声楔块延迟矫正设置
struct STRUCT_USCALIBRATION_WEDGE_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	float TolerateErrorA;//设置半径A允许误差
	float TolerateErrorSection;//设置区间允许误差
	vector<pair<long, float>> Envelope;//	包络数据, 横坐标为角度 / VPA，纵坐标为深度 / 厚度 / 半径。UT时size为1
	vector<pair<long, float>> CalibratedWedgeDelay;//校准结果, 横坐标为角度 / VPA，纵坐标为校准延时。UT时size为1
};
struct STRUCT_USCALIBRATION_WEDGEUT_SETTING :public STRUCT_USCALIBRATION_WEDGE_SETTING
{

};
struct STRUCT_USCALIBRATION_WEDGEPA_SETTING :public STRUCT_USCALIBRATION_WEDGE_SETTING
{
	long BeiginAngleOrVPA;//	开始角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	long FinalAngleOrVPA;//	最后角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	pair<bool, long> SpecifiedRule[3];//	使用标准库类型pair定义指定法则。由于不确定指定了2或3个法则，使用bool类型变量标明每个法则是否有效。
};

// 超声ACG矫正设置
struct STRUCT_USCALIBRATION_ACGPA_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long BeiginAngleOrVPA;//	开始角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	long FinalAngleOrVPA;//最后角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	pair<bool, long> SpecifiedRule[3];//	使用标准库类型pair定义指定法则。由于不确定指定了2或3个法则，使用bool类型变量标明每个法则是否有效。
	float RefAmplitude;//参考波幅，通常设为80%
	float TolerateError;//允许误差
	vector<pair<long, float>>  EnvelopeLine;//包络线数据, 横坐标为角度 / VPA，纵坐标为波幅
	vector<pair<long, float>> CalibratedSensitivity;//校准结果, 横坐标为角度 / VPA，纵坐标为补偿增益
};

// 超声DAC矫正设置
struct STRUCT_USCALIBRATION_DAC_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long QuantitativeType;//	定量类型，枚举：可选自定义、JIS、ASME标准。当定量类型选择自定义时，曲线类型和曲线数量可编辑。
	long CurveType;//曲线类型，定义宏，直线、对数、多项式
	long CurvesNum;//	曲线数量
	vector<float>CurvesOffset;//	为每条曲线设置偏移
	float RefAmplitude;//参考波幅，通常设为80%
	float TolerateError;//允许误差（通常有默认值）

	struct STRUCT_PONITDAC_DATA {
		float depth;//深度
		vector<pair<float, float>> Pair_Gain_Amplitude;//增益波幅对。UT矫正时法则数为1，增益波幅对相应为1，PA时大于1。
	};
	vector<STRUCT_PONITDAC_DATA> AllPointData;//在超声轴上寻找多个位置不同的点，测量其位置及对应波幅，及其当前增益。

											  //校准结果; 获得每条法则的DAC曲线，曲线横坐标为声程（深度）纵坐标为波幅，并且需要记录校准DAC曲线时所对应的增益。
	vector<DAC_CURVE> AllDACCurve;
};
struct STRUCT_USCALIBRATION_DACUT_SETTING :public STRUCT_USCALIBRATION_DAC_SETTING
{

};
struct STRUCT_USCALIBRATION_DACPA_SETTING :public STRUCT_USCALIBRATION_DAC_SETTING
{
	long BeiginAngleOrVPA;// 	开始角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	long FinalAngleOrVPA;// 	最后角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	pair<bool, long> SpecifiedRule[3];// 	由于不确定指定了2或3个法则，使用bool类型变量标明每个法则是否有效。
};

// 超声TCG矫正设置
struct STRUCT_USCALIBRATION_TCGPA_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long BeiginAngleOrVPA; //开始角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	long FinalAngleOrVPA; //最后角度(扇形扫描) / VPA（线性扫描），当指定了应用于全部聚焦法则后，该参数有效
	pair<bool, long> SpecifiedRule[3]; //使用标准库类型pair定义指定法则。由于不确定指定了2或3个法则，使用bool类型变量标明每个法则是否有效。声速校准无效
	float RefAmplitude; //参考波幅，通常设为80%
	float RefAmplitudeStart;//参考波幅起始位置
	float TolerateError; //允许误差
	enum ACCORDWITH :long {ASME, JIS, DIY};
	ACCORDWITH Accordwith;
	struct STRUCT_PONITTCG_DATA {
		float depth;//深度
		vector<pair<float, float>> Pair_Gain_Amplitude;//增益波幅对。
	};// 
	pair<float, float> p1;
	pair<float, float> p2;
	STRUCT_PONITTCG_DATA PointTCGData;
	int CurveNum;
	vector<STRUCT_PONITTCG_DATA> AllPointData;//在超声轴上寻找多个位置不同的点，测量其位置及对应波幅，及其当前增益。

	vector< TCG_CURVE > AllTCGCurve;// 校准结果,对每个聚焦法则进行TCG校准，曲线横坐标为声程（深度）纵坐标为补偿增益
};
struct STRUCT_ENCODER_CALIBRATION_SETTING
{
	float BeginPosition; //起始位置
	float EndPosition; //终止位置
	long Resolution; //编码器分辨率
};
struct STRUCT_WAFERCONSISTANCY_CALIBRATION_SETTING
{
	float BeginPosition; //起始位置
	float EndPosition; //终止位置
	long Resolution; //编码器分辨率
};


//校准配置
struct STRUCT_CALIBRATION_SETTING
{
	const STRUCT_GROUPHEADER_SETTING* pGroupHeader;

	// 当前校准方式
	enum ENUM_CALI_MODE { CALI_MODE_US, CALI_MODE_RATION, CALI_MODE_ENCODER };
	ENUM_CALI_MODE CaliMode;
	enum ENUM_APPLY_TO { TWO_THREE_VPA, TWO_THREE_ANGLE, ALL_VPA, ALL_ANGLE };
	ENUM_APPLY_TO ApplytoMode;

	void Init()
	{
		CaliMode = CALI_MODE_US;
		ApplytoMode = TWO_THREE_VPA;
	}
	STRUCT_USCALIBRATION_SPEED_SETTING SpeedCali;

	STRUCT_USCALIBRATION_SENSITIVITY_SETTING SensiCali;

	STRUCT_USCALIBRATION_WEDGEUT_SETTING WedgeUTCali;
	STRUCT_USCALIBRATION_WEDGEPA_SETTING WedgePACali;

	STRUCT_USCALIBRATION_ACGPA_SETTING ACGCali;

	STRUCT_USCALIBRATION_DACUT_SETTING DACUTCali;
	STRUCT_USCALIBRATION_DACPA_SETTING DACPACali;

	STRUCT_USCALIBRATION_TCGPA_SETTING TCGCali;

	STRUCT_ENCODER_CALIBRATION_SETTING EncoderCali;
	STRUCT_WAFERCONSISTANCY_CALIBRATION_SETTING WaferConsCali;
};