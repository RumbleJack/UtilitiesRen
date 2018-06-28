#pragma once
#include <vector>
#include <utility>
using std::vector;
using std::pair;

#include "GroupHeaderDef.h"

typedef vector<pair<float, float>> DAC_CURVE;//���벨��������
typedef vector<pair<float, float>> TCG_CURVE;//���̲������������

// ��������һ������
struct STRUCT_USCALIBRATION_GENERAL_SETTING
{
	
	void Init()
	{
		AScan->Init();
	}
	//	�ز����ͣ������뾶����ȡ���ȡ�
	enum ECHOSTYLE :long { ECHO_STYLE_RADIUS, ECHO_STYLE_DEEPNESS, ECHO_STYLE_THICKNESS, };
	ECHOSTYLE EchoStyle;
	// ��ѡ��Ӧ����ȫ�������2~3����������ö�����ͣ�����У׼Ĭ��Ӧ����ȫ���۽�����
	enum RULENUMBER :long { RULENUMBER_ALL, RULENUMBER_2OR3, };
	RULENUMBER RuleNumber;
	//	�뾶 / ��� / ���1��2��������У׼������ֻ��1��Ч
	float Baseline[2];
	//ָ��Aɨ������
	STRUCT_ASCAN_SETTING* AScan;
	
	//ָ����ǰբ�Ų���
	STRUCT_GATE_SETTING*  Gate;
};

// �������ٽ�������
struct STRUCT_USCALIBRATION_SPEED_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long AngleOrVPAToCalibrate;//	ָ���Ƕ�(����ɨ��) / VPA������ɨ�裩��������У׼
	float CalibratedSpeed;//У׼�������
};

//������У׼����
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

// ����Ш���ӳٽ�������
struct STRUCT_USCALIBRATION_WEDGE_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	float TolerateErrorA;//���ð뾶A�������
	float TolerateErrorSection;//���������������
	vector<pair<long, float>> Envelope;//	��������, ������Ϊ�Ƕ� / VPA��������Ϊ��� / ��� / �뾶��UTʱsizeΪ1
	vector<pair<long, float>> CalibratedWedgeDelay;//У׼���, ������Ϊ�Ƕ� / VPA��������ΪУ׼��ʱ��UTʱsizeΪ1
};
struct STRUCT_USCALIBRATION_WEDGEUT_SETTING :public STRUCT_USCALIBRATION_WEDGE_SETTING
{

};
struct STRUCT_USCALIBRATION_WEDGEPA_SETTING :public STRUCT_USCALIBRATION_WEDGE_SETTING
{
	long BeiginAngleOrVPA;//	��ʼ�Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	long FinalAngleOrVPA;//	���Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	pair<bool, long> SpecifiedRule[3];//	ʹ�ñ�׼������pair����ָ���������ڲ�ȷ��ָ����2��3������ʹ��bool���ͱ�������ÿ�������Ƿ���Ч��
};

// ����ACG��������
struct STRUCT_USCALIBRATION_ACGPA_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long BeiginAngleOrVPA;//	��ʼ�Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	long FinalAngleOrVPA;//���Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	pair<bool, long> SpecifiedRule[3];//	ʹ�ñ�׼������pair����ָ���������ڲ�ȷ��ָ����2��3������ʹ��bool���ͱ�������ÿ�������Ƿ���Ч��
	float RefAmplitude;//�ο�������ͨ����Ϊ80%
	float TolerateError;//�������
	vector<pair<long, float>>  EnvelopeLine;//����������, ������Ϊ�Ƕ� / VPA��������Ϊ����
	vector<pair<long, float>> CalibratedSensitivity;//У׼���, ������Ϊ�Ƕ� / VPA��������Ϊ��������
};

// ����DAC��������
struct STRUCT_USCALIBRATION_DAC_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long QuantitativeType;//	�������ͣ�ö�٣���ѡ�Զ��塢JIS��ASME��׼������������ѡ���Զ���ʱ���������ͺ����������ɱ༭��
	long CurveType;//�������ͣ�����ֱ꣬�ߡ�����������ʽ
	long CurvesNum;//	��������
	vector<float>CurvesOffset;//	Ϊÿ����������ƫ��
	float RefAmplitude;//�ο�������ͨ����Ϊ80%
	float TolerateError;//������ͨ����Ĭ��ֵ��

	struct STRUCT_PONITDAC_DATA {
		float depth;//���
		vector<pair<float, float>> Pair_Gain_Amplitude;//���沨���ԡ�UT����ʱ������Ϊ1�����沨������ӦΪ1��PAʱ����1��
	};
	vector<STRUCT_PONITDAC_DATA> AllPointData;//�ڳ�������Ѱ�Ҷ��λ�ò�ͬ�ĵ㣬������λ�ü���Ӧ���������䵱ǰ���档

											  //У׼���; ���ÿ�������DAC���ߣ����ߺ�����Ϊ���̣���ȣ�������Ϊ������������Ҫ��¼У׼DAC����ʱ����Ӧ�����档
	vector<DAC_CURVE> AllDACCurve;
};
struct STRUCT_USCALIBRATION_DACUT_SETTING :public STRUCT_USCALIBRATION_DAC_SETTING
{

};
struct STRUCT_USCALIBRATION_DACPA_SETTING :public STRUCT_USCALIBRATION_DAC_SETTING
{
	long BeiginAngleOrVPA;// 	��ʼ�Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	long FinalAngleOrVPA;// 	���Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	pair<bool, long> SpecifiedRule[3];// 	���ڲ�ȷ��ָ����2��3������ʹ��bool���ͱ�������ÿ�������Ƿ���Ч��
};

// ����TCG��������
struct STRUCT_USCALIBRATION_TCGPA_SETTING :public STRUCT_USCALIBRATION_GENERAL_SETTING
{
	long BeiginAngleOrVPA; //��ʼ�Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	long FinalAngleOrVPA; //���Ƕ�(����ɨ��) / VPA������ɨ�裩����ָ����Ӧ����ȫ���۽�����󣬸ò�����Ч
	pair<bool, long> SpecifiedRule[3]; //ʹ�ñ�׼������pair����ָ���������ڲ�ȷ��ָ����2��3������ʹ��bool���ͱ�������ÿ�������Ƿ���Ч������У׼��Ч
	float RefAmplitude; //�ο�������ͨ����Ϊ80%
	float RefAmplitudeStart;//�ο�������ʼλ��
	float TolerateError; //�������
	enum ACCORDWITH :long {ASME, JIS, DIY};
	ACCORDWITH Accordwith;
	struct STRUCT_PONITTCG_DATA {
		float depth;//���
		vector<pair<float, float>> Pair_Gain_Amplitude;//���沨���ԡ�
	};// 
	pair<float, float> p1;
	pair<float, float> p2;
	STRUCT_PONITTCG_DATA PointTCGData;
	int CurveNum;
	vector<STRUCT_PONITTCG_DATA> AllPointData;//�ڳ�������Ѱ�Ҷ��λ�ò�ͬ�ĵ㣬������λ�ü���Ӧ���������䵱ǰ���档

	vector< TCG_CURVE > AllTCGCurve;// У׼���,��ÿ���۽��������TCGУ׼�����ߺ�����Ϊ���̣���ȣ�������Ϊ��������
};
struct STRUCT_ENCODER_CALIBRATION_SETTING
{
	float BeginPosition; //��ʼλ��
	float EndPosition; //��ֹλ��
	long Resolution; //�������ֱ���
};
struct STRUCT_WAFERCONSISTANCY_CALIBRATION_SETTING
{
	float BeginPosition; //��ʼλ��
	float EndPosition; //��ֹλ��
	long Resolution; //�������ֱ���
};


//У׼����
struct STRUCT_CALIBRATION_SETTING
{
	const STRUCT_GROUPHEADER_SETTING* pGroupHeader;

	// ��ǰУ׼��ʽ
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