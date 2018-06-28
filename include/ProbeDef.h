/*---------------------------------------------------------------------------*/
/*-----文件ProbeDef：定义探头参数--------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#pragma once
/*---------------------------------------------------------------------------*/
/* ------------------------------定义探头------------------------------------*/
/*---------------------------------------------------------------------------*/
// 探头类型
enum ENUM_PROBE_STYLE :long
{
	PROBE_STYLE_UNDEFINED,
	PROBE_STYLE_LINEAR,
	PROBE_STYLE_CIRCLE,
	PROBE_STYLE_RECTANGLE
};

// PA探头
struct STRUCT_PROBEPA_SETTING
{
public:
	void Init()
	{
		strcpy_s(ProbeModel, "Default");
		strcpy_s(SerialNumber, "Default");
		MaxActiveWaferNum = 16;
		MaxWaferNum = 64;
		ProbeStyle = PROBE_STYLE_LINEAR;
		ProbeFrequency = 5;
		ProbeFrontEdge = 40;
		WaferSpacing = 0.6f;
		WaferGap = 0;
		Length = 38.4f;
		ReferebcePoint = -39.2f;
	}
	//探头型号，字符串
	char ProbeModel[32];
	//探头序列号，字符串
	char SerialNumber[32];
	//最大激活晶片数
	long MaxActiveWaferNum;
	//最大晶片数
	long MaxWaferNum;
	//探头类型
	ENUM_PROBE_STYLE ProbeStyle;
	//探头频率，单位：MHz
	float ProbeFrequency;
	//探头前沿，单位：mm
	float ProbeFrontEdge;
	//晶片间距，单位：mm
	float WaferSpacing;
	//晶片间隙，单位：mm
	float WaferGap;
	//晶片总长度，单位：mm
	float Length;
	//参考点，单位：mm
	float ReferebcePoint;
} ;
// UT探头
struct STRUCT_PROBEUT_SETTING
{
public:
	void Init()
	{
		strcpy_s(ProbeModel, "Default");
		strcpy_s(SerialNumber, "Default");
		MaxWaferNum = 64;
		ProbeFrequency = 5;
		ProbeStyle = PROBE_STYLE_LINEAR;
		WaferDiameter = 0;
		Side1 = 0;
		Side2 = 0;
	}
	//探头型号，字符串
	char ProbeModel[32];
	//探头序列号，字符串
	char SerialNumber[32];
	//探头的晶片数量，单晶或双晶
	long MaxWaferNum;	
	//探头频率，单位：MHz
	float ProbeFrequency;
	//探头类型
	ENUM_PROBE_STYLE ProbeStyle;
	//晶片直径，针对环形探头晶片
	float WaferDiameter;
	//晶片侧面1长度，针对矩形探头晶片
	float Side1;
	//晶片侧面2长度，针对矩形探头晶片
	float Side2;
} ;


struct STRUCT_PROBE_SETTING
{
public:
	void Init()
	{
		ProbeType = PROBE_TYPE_PA;
		UnionProbe.Init();
	}
	enum :long { PROBE_TYPE_UT, PROBE_TYPE_PA }ProbeType;
	union{
		void Init()
		{
			ProbePA.Init();
		}
		STRUCT_PROBEUT_SETTING ProbeUT;
		STRUCT_PROBEPA_SETTING ProbePA;
	}UnionProbe;
};




/*---------------------------------------------------------------------------*/
/* ------------------------------定义探头位置--------------------------------*/
/*---------------------------------------------------------------------------*/
struct STRUCT_PROBEPOSITION_SETTING
{
	void Init()
	{
		ScanOffset = 0;
		StepOffset = 0;
		Angle = 0;
	}
	//扫查偏移
	float ScanOffset;
	//步进偏移
	float StepOffset;
	//夹角，定义超声声束相对于扫查轴的方向。90度时表示探头在左侧，270度表示探头在右侧
	float Angle;
};
