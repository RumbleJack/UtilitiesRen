//------------------------created on 30th,April,2018-------------------
//-------------------------------Hsu-----------------------------------

//-----------------------���嶨������---------------------------------
#pragma once

#include "ProbeDef.h"
#include "WedgeDef.h"

//������������
enum RATION_TYPE :long
{
	DISABLED,
	DAC,
	LINEAR_DAC,
	TCG,
	DGS,
	AWS
};

//DAC�Ĳ���
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
	//����ĳ�ֹ��ʱ�׼
	enum  :long{DIY, JIS, ASME}RATION_ACCORD_WITH;
	//�ο�����
	float RefGain;
	//��������
	enum  :long{STRAIGHT_LINE, LOGARITHM, POLYNOMIAL}CURVE_TYPE;
	//��������
	long CurveNum;
	//����ƫ��
	long Offset;
	//Ӧ����(false����Ӧ���ڲ��ַ���)
	bool AllLaw;
	//��ѡ���ڳ������λ��
	float Axisx;
	//����
	float Amplitude;
};

//����DAC�Ĳ���
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
	//�ο�����
	float RefGain;

	//��������
	long CurveNum;
	//����ƫ��
	long Offset;
	//����˥��
	float Attenuation;
	//�ӳ�
	float Delay;
	
};

//TCG���ߵĲ���
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
	//����ĳ�ֹ��ʱ�׼
	enum  :long{DIY, JIS, ASME}RATION_ACCORD_WITH;
	//�ο�����
	float RefGain;

	//��������
	long CurveNum;
	//����ƫ��
	long Offset;
	//Ӧ����(false����Ӧ���ڲ��ַ���)
	bool AllLaw;
	//��ѡ���ڳ������λ��
	float Axisx;
	//����
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
		//��ʹ��̽ͷʱContactΪtrue
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