/*---------------------------------------------------------------------------*/
/*-----�ļ�ProbeDef������̽ͷ����--------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#pragma once
/*---------------------------------------------------------------------------*/
/* ------------------------------����̽ͷ------------------------------------*/
/*---------------------------------------------------------------------------*/
// ̽ͷ����
enum ENUM_PROBE_STYLE :long
{
	PROBE_STYLE_UNDEFINED,
	PROBE_STYLE_LINEAR,
	PROBE_STYLE_CIRCLE,
	PROBE_STYLE_RECTANGLE
};

// PA̽ͷ
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
	//̽ͷ�ͺţ��ַ���
	char ProbeModel[32];
	//̽ͷ���кţ��ַ���
	char SerialNumber[32];
	//��󼤻Ƭ��
	long MaxActiveWaferNum;
	//���Ƭ��
	long MaxWaferNum;
	//̽ͷ����
	ENUM_PROBE_STYLE ProbeStyle;
	//̽ͷƵ�ʣ���λ��MHz
	float ProbeFrequency;
	//̽ͷǰ�أ���λ��mm
	float ProbeFrontEdge;
	//��Ƭ��࣬��λ��mm
	float WaferSpacing;
	//��Ƭ��϶����λ��mm
	float WaferGap;
	//��Ƭ�ܳ��ȣ���λ��mm
	float Length;
	//�ο��㣬��λ��mm
	float ReferebcePoint;
} ;
// UT̽ͷ
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
	//̽ͷ�ͺţ��ַ���
	char ProbeModel[32];
	//̽ͷ���кţ��ַ���
	char SerialNumber[32];
	//̽ͷ�ľ�Ƭ������������˫��
	long MaxWaferNum;	
	//̽ͷƵ�ʣ���λ��MHz
	float ProbeFrequency;
	//̽ͷ����
	ENUM_PROBE_STYLE ProbeStyle;
	//��Ƭֱ������Ի���̽ͷ��Ƭ
	float WaferDiameter;
	//��Ƭ����1���ȣ���Ծ���̽ͷ��Ƭ
	float Side1;
	//��Ƭ����2���ȣ���Ծ���̽ͷ��Ƭ
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
/* ------------------------------����̽ͷλ��--------------------------------*/
/*---------------------------------------------------------------------------*/
struct STRUCT_PROBEPOSITION_SETTING
{
	void Init()
	{
		ScanOffset = 0;
		StepOffset = 0;
		Angle = 0;
	}
	//ɨ��ƫ��
	float ScanOffset;
	//����ƫ��
	float StepOffset;
	//�нǣ����峬�����������ɨ����ķ���90��ʱ��ʾ̽ͷ����࣬270�ȱ�ʾ̽ͷ���Ҳ�
	float Angle;
};
