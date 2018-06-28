/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

struct STRUCT_ASCAN_SETTING
{
	void Init()
	{
		GainValue = 70;
		IntervalBegin = 0;
		IntervalWidth = 50;
		SizeChanged = false;
	}
	float GainValue;//增益（调整使第一个信号波幅达到A扫描满屏高约80%的增益值）
	long IntervalBegin;//A扫描起始横坐标区间起始值
	long IntervalWidth;//A扫描横坐标区间宽度
	bool SizeChanged;//扫描最大范围发生变化
};

struct STRUCT_UT_GENERAL_SETTING
{
	void Init()
	{
		AScan.Init();
		WedgeDelay = 0.0f;
		Speed = 5900.0f;
	}
	STRUCT_ASCAN_SETTING AScan;// A扫描设置
	float WedgeDelay;	//	楔块延迟（PA和UT都设定一个常数，我认为PA设置一个数组更合适，来为每个角度确定不同的延迟）
	float Speed;		//	声速
};
struct STRUCT_UT_PULSEGEN_SETTING
{
	void Init()
	{
		TxRxMode = 1;
		TransmitFrequency = 0.0f;
		Energy = 30;
		PW = 0.1f;
		PRF = 1000;
	}
	long  TxRxMode;//	发送 / 接收模式，包括一发一收、脉冲回波、穿透
	float TransmitFrequency;//探头频率
	float Energy;	//	能量（伏特）
	float PW;		//脉冲宽度
	float PRF;		//脉冲重复频率(pulse recurre - nce frequency)每秒钟产生的触发脉冲数目

};
struct STRUCT_UT_PULSERCV_SETTING
{
	void Init()
	{
		Filter = 0;
		Demodulator = 1;
		VideoFilter = FALSE;
		SmoothLen = 1;
		Supression = 0.0f;
	}
	long Filter;//	滤波器：0M~2M，2M~7M，7M~OO
	long Demodulator;//	检波器：不检波、全波；---RF、HW + 、HW、FW---
	BOOL VideoFilter;//	是否开启视频滤波器
	long SmoothLen;//平均长度，指定回波数量取平均值抑制噪声。
	float Supression;//抑制，指定波幅，低于该波幅抑制为0，默认0

};
struct STRUCT_UT_SOUNDBEAM_SETTING
{
	void Init()
	{
		ScanOffset = 0.0f;
		StepOffset = 0.0f;
		Angle = 30.0f;
		RefractionAngle = 30.0f;
		BeamDelay = 0.0f;
		GainCompensate = 0.0f;
	}
	float ScanOffset;//扫查偏移（可定义为只读，与探头位置中参数重复）
	float StepOffset;//	声束步进偏移
	float Angle;//夹角，定义超声声束相对于扫查轴的方向。90度时表示探头在左侧，270度表示探头在右侧（可定义为只读，与探头位置中参数重复）
	float RefractionAngle;//材料中超声声束角度
	float BeamDelay;//声束延迟
	float GainCompensate;//增益补偿
};
struct STRUCT_UT_ADVANCED_SETTING
{
	void Init()
	{
		RefAmplitude = 0.0f;
		SetAsXXX = 0.0f;
		Ref = FALSE;
		AscanSaveDot = -1;
		ScaleFactor = 4;
		Attenuation = FALSE;
	}
	float RefAmplitude;//	参考波幅
	float SetAsXXX;//不懂
	BOOL Ref;//是否开启参考增益功能
	long AscanSaveDot;//A扫描被保存的点数， - 1表示自动
	long ScaleFactor;//标度因子
	BOOL Attenuation;//衰减20dB是否开启

};



// UT设置
struct STRUCT_UT_SETTING
{
	void Init()
	{
		UTGeneral.Init();
		UTPulseGen.Init();
		UTPulseRcv.Init();
		UTSoundBeam.Init();
		UTAdvance.Init();
	}
	STRUCT_UT_GENERAL_SETTING UTGeneral;
	STRUCT_UT_PULSEGEN_SETTING UTPulseGen;
	STRUCT_UT_PULSERCV_SETTING UTPulseRcv;
	STRUCT_UT_SOUNDBEAM_SETTING UTSoundBeam;
	STRUCT_UT_ADVANCED_SETTING UTAdvance;
};