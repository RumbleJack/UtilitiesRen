#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------定义聚焦法则--------------------------------*/
/*---------------------------------------------------------------------------*/
struct STRUCT_APERTURE_SETTING
{
public:
	//STRUCT_APERTURE_SETTING()
	//	:FirstWafer(0), LastWafer(TotalWafer), WaferStep(1), WaferNumPerAperture(4)
	//{}
	void InitAperture(long firstWafer= 0, long lastWafer = 15,
		long waferStep = 1, long waferNumPerAperture = 8)
	{
		FirstWafer = firstWafer;
		LastWafer = lastWafer;
		WaferStep = waferStep;
		WaferNumPerAperture = waferNumPerAperture;
	}
public:
	// 第一晶片，扇形法则中，表示所使用的第一晶片；线性法则中，用于设置孔径的第一晶片
	long FirstWafer;
	// 最后晶片；扇形法则中，表明所使用的最后晶片（由第一晶片和晶片数量决定）；在线性法则中，这个参数用于设置所使用的最后晶片，以确定法则的数量
	long LastWafer;
	// 晶片步距；扇形法则中无效；线性法则中，设置孔径中的晶片步距
	long WaferStep;
	// 晶片数量，扇形法则中，表示产生声束所需的晶片数量；线性法则中，用于设置孔径中的晶片数量
	long WaferNumPerAperture;

	// 晶片总量（该项与探头相关，此处应该删除，尽快删除相关操作）
	static const long TotalWafer = 64;
};

struct STRUCT_SOUNDBEAM_SETTING
{
public:
	//STRUCT_SOUNDBEAM_SETTING()
	//	:MinAngle(-30), MaxAngle(30), AngleStep(1), 
	//	FocusDepth(20),FoucusAngle(0)
	//{}
	void InitSoundBeam(float minAngle = -20, float maxAngle = 33,
		float angleStep = 0.3, float focusDepth = 30,
		float foucusAngle = 0)
	{
		MinAngle = minAngle;
		MaxAngle = maxAngle;
		AngleStep = angleStep;
		FocusDepth = focusDepth;
		FoucusAngle = foucusAngle;
	}
public:
	// 最小角度，用于设置声速的最小角度（线性法则无效）
	float MinAngle;
	// 最大角度，用于设置声速的最大角度（线性法则无效）
	float MaxAngle;
	// 角度步距，每个角度间的步距值。单位为角度。（线性法则无效）
	float AngleStep;
	// 聚焦深度，设置被测工件中的聚焦深度
	float FocusDepth;
	// 法则角度，用于指定超声线性扫查时超声的偏转角度。（扇形法则无效）
	float FoucusAngle;
};

struct STRUCT_FOUCUSLAW_SETTING
{
public:
	//STRUCT_FOUCUSLAW_SETTING():FoucusLawStyle(APPLICATION_STYLE_SECTOR), WaveType(WAVE_STYLE_SHEER)
	//{}
	void Init()
	{
		FoucusLawStyle = STRUCT_FOUCUSLAW_SETTING::FOUCUSLAW_STYLE_SECTOR;
		WaveType = STRUCT_FOUCUSLAW_SETTING::WAVE_STYLE_SHEER;
		Aperture.InitAperture();
		SoundBeam.InitSoundBeam();
	}
public:
	// 聚焦法则类型, 仅PA检测模式，包括扇形法则、线性法则
	enum FOUCUSLAW_STYLE:long { FOUCUSLAW_STYLE_SECTOR, FOUCUSLAW_STYLE_LINER, FOUCUSLAW_STYLE_ZERO_LINEAR } ;
	FOUCUSLAW_STYLE FoucusLawStyle;
	//声波类型，可选横波、纵波
	typedef enum :long { WAVE_STYLE_SHEER, WAVE_STYLE_LONGI } WAVE_STYLE;
	WAVE_STYLE WaveType;
	bool AutoSequence;
	//孔径设置
	STRUCT_APERTURE_SETTING Aperture;
	//声束设置
	STRUCT_SOUNDBEAM_SETTING SoundBeam;
};


