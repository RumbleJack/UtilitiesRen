/*---------------------------------------------------------------------------*/
/*-----文件WedgeDef：定义楔块参数--------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
/*---------------------------------------------------------------------------*/
/* ------------------------------定义楔块------------------------------------*/
/*---------------------------------------------------------------------------*/

enum WEDGE_PROBEDRC
{
	WEDGE_PROBEDRC_FOWARD,
	WEDGE_PROBEDRC_BACKWARD,
};
// PA楔块
struct STRUCT_WEDGEPA_SETTING
{
	void Init()
	{
		strcpy_s(WedgeModel, "Default");
		ProbeDrc = WEDGE_PROBEDRC_FOWARD;
		Angle = 0.0f;
		Height = 30.0f;
		Width = 0;
		FirstOffset = 71.7f;
		SecondOffset = 0;
		Speed = 2337.0f;
		IsUsed = false;
	}
	//楔块型号，字符串
	char WedgeModel[32];
	// 探头方向，可取正向(0)、负向(1)
	WEDGE_PROBEDRC ProbeDrc;
	//楔块角度
	float Angle;
	//楔块高度（第一晶片高度，通常由楔块制造商提供）
	float Height;
	//楔块宽度
	float Width;
	//主轴偏移（楔块前沿与探头第一晶片中心间的距离），默认情况下，软件将0参考点设在第一晶片位置上。要将0参考点设置在楔块前沿位置，需要在主轴偏移中输入楔块前沿和第一晶片位置之间的距离。数值必须为负值。
	float FirstOffset;
	//次轴偏移。0表示探头在次轴方向上位于楔块中心。如果探头没有处于楔块中心，输入适当值（定义正方向为扫查方向）
	float SecondOffset;
	//楔块声速;
	float Speed;
	
	// 是否使用
	bool IsUsed;
} ;

// UT楔块
typedef struct
{
	void Init()
	{
		strcpy_s(WedgeModel, "Default");
		ProbeDrc = WEDGE_PROBEDRC_FOWARD;
		Angle = 39.0f;
		WaveType = 0;
		RefPoint = 0;
		IsUsed = true;
	}
	//楔块型号，字符串
	char WedgeModel[32];
	// 探头方向，可取正向(0)、负向(1)
	WEDGE_PROBEDRC ProbeDrc;
	// 折射角度，输入楔块角度Page89
	float Angle;
	//波形,声波类型，可选横波（0）、纵波(1).对于PA，波形在聚焦法则中定义
	long WaveType;
	//参考点
	float RefPoint;

	// 是否使用
	bool IsUsed;
} STRUCT_WEDGEUT_SETTING;


struct STRUCT_WEDGE_SETTING
{
public:
	void Init()
	{
		WedgeType = WEDGE_TYPE_PA;
		UnionWedge.Init();
	}
	enum :long { WEDGE_TYPE_UT, WEDGE_TYPE_PA }WedgeType;
	union {
		void Init()
		{
			WedgePA.Init();
		}
		STRUCT_WEDGEUT_SETTING WedgeUT;
		STRUCT_WEDGEPA_SETTING WedgePA;
	}UnionWedge;
};
