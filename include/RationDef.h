//------------------------created on 30th,April,2018-------------------
//-------------------------------Hsu-----------------------------------

//-----------------------定义定量功能---------------------------------
#pragma once

#include "ProbeDef.h"
#include "WedgeDef.h"

//定量功能类型
enum RATION_TYPE :long
{
	DISABLED,
	DAC,
	LINEAR_DAC,
	TCG,
	DGS,
	AWS
};

//DAC的参数
struct STRUCT_DAC_SETTING
{
	
	void Init()
	{
		RATION_ACCORD_WITH = DIY;
		CURVE_TYPE = STRAIGHT_LINE;
		RefGain = 0.0f;
		CurveNum = 0;
		Offset = 0;
		AllLaw = true;
		Axisx = 0.0f;
		Amplitude = 0.0f;
	}
	//符合某种国际标准
	enum  :long{DIY, JIS, ASME}RATION_ACCORD_WITH;
	//参考波幅
	float RefGain;
	//曲线类型
	enum  :long{STRAIGHT_LINE, LOGARITHM, POLYNOMIAL}CURVE_TYPE;
	//曲线数量
	long CurveNum;
	//曲线偏移
	long Offset;
	//应用于(false代表应用于部分法则)
	bool AllLaw;
	//所选点在超声轴的位置
	float Axisx;
	//波幅
	float Amplitude;
};

//线性DAC的参数
struct STRUCT_LINEAR_DAC_SETTING
{
	void Init()
	{
		RefGain = 0.0f;
		CurveNum = 0;
		Offset = 0;
		Offset = 0;
		Attenuation = 0.0f;
		Delay = 0.0f;
	}
	//参考波幅
	float RefGain;

	//曲线数量
	long CurveNum;
	//曲线偏移
	long Offset;
	//材料衰减
	float Attenuation;
	//延迟
	float Delay;
	
};

//TCG曲线的参数
struct STRUCT_TCG_SETTING
{
	void Init()
	{
		RATION_ACCORD_WITH = DIY;
		RefGain = 0.0f;
		CurveNum = 0;
		Offset = 0;
		AllLaw = true;
		Axisx = 0.0f;
		Gain = 0;
	}
	//符合某种国际标准
	enum  :long{DIY, JIS, ASME}RATION_ACCORD_WITH;
	//参考波幅
	float RefGain;

	//曲线数量
	long CurveNum;
	//曲线偏移
	long Offset;
	//应用于(false代表应用于部分法则)
	bool AllLaw;
	//所选点在超声轴的位置
	float Axisx;
	//增益
	long Gain;
};

struct STRUCT_DGS_SETTING
{
	void Init()
	{
		ProbePA.Init();
		REFLECTOR = SDH;
		Diameter = 0.0f;
	}
	STRUCT_PROBEPA_SETTING ProbePA;
	union{
		void Init()
		{
			WedgePA.Init();
			Contact = false;
		}
		STRUCT_WEDGEPA_SETTING WedgePA;
		//不使用探头时Contact为true
		bool Contact;
	}UnionWedge;
	enum :long{SDH, FBH, K1_IIW, K2_DSC}REFLECTOR;
	float Diameter;
};

struct STRUCT_AWS_SETTING
{
	void Init()
	{
		STANDARD = AWS_D11;
		ANGLE = AWS45;
		Thickness = 0.0f;
	}
	enum :long{AWS_D11, AWS_D15} STANDARD;
	union{
		void Init()
		{
			D11 = STATIC;
			D15 = COMPRESS;
		}
		enum :long{STATIC, CYCLE}D11;
		enum :long{COMPRESS, STRETCH}D15;
	}UnionStandard;
	enum :long{AWS45,aws60, aws70} ANGLE;
	float Thickness;

};