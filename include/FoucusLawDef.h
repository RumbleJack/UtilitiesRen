#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------����۽�����--------------------------------*/
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
	// ��һ��Ƭ�����η����У���ʾ��ʹ�õĵ�һ��Ƭ�����Է����У��������ÿ׾��ĵ�һ��Ƭ
	long FirstWafer;
	// ���Ƭ�����η����У�������ʹ�õ����Ƭ���ɵ�һ��Ƭ�;�Ƭ�����������������Է����У������������������ʹ�õ����Ƭ����ȷ�����������
	long LastWafer;
	// ��Ƭ���ࣻ���η�������Ч�����Է����У����ÿ׾��еľ�Ƭ����
	long WaferStep;
	// ��Ƭ���������η����У���ʾ������������ľ�Ƭ���������Է����У��������ÿ׾��еľ�Ƭ����
	long WaferNumPerAperture;

	// ��Ƭ������������̽ͷ��أ��˴�Ӧ��ɾ��������ɾ����ز�����
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
	// ��С�Ƕȣ������������ٵ���С�Ƕȣ����Է�����Ч��
	float MinAngle;
	// ���Ƕȣ������������ٵ����Ƕȣ����Է�����Ч��
	float MaxAngle;
	// �ǶȲ��࣬ÿ���Ƕȼ�Ĳ���ֵ����λΪ�Ƕȡ������Է�����Ч��
	float AngleStep;
	// �۽���ȣ����ñ��⹤���еľ۽����
	float FocusDepth;
	// ����Ƕȣ�����ָ����������ɨ��ʱ������ƫת�Ƕȡ������η�����Ч��
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
	// �۽���������, ��PA���ģʽ���������η������Է���
	enum FOUCUSLAW_STYLE:long { FOUCUSLAW_STYLE_SECTOR, FOUCUSLAW_STYLE_LINER, FOUCUSLAW_STYLE_ZERO_LINEAR } ;
	FOUCUSLAW_STYLE FoucusLawStyle;
	//�������ͣ���ѡ�Შ���ݲ�
	typedef enum :long { WAVE_STYLE_SHEER, WAVE_STYLE_LONGI } WAVE_STYLE;
	WAVE_STYLE WaveType;
	bool AutoSequence;
	//�׾�����
	STRUCT_APERTURE_SETTING Aperture;
	//��������
	STRUCT_SOUNDBEAM_SETTING SoundBeam;
};


