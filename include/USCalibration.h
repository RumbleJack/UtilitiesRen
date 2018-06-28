#pragma once

#include "PubMacroDef.h"
#include "GateAlarmDef.h"
#include "UTDef.h"
#include "CalibrationDef.h"

// ����У׼��
class DllExport USCalibration
{
public:
	//	�ز����ͣ������뾶����ȡ���ȡ�
	enum ECHOSTYLE :long { ECHO_STYLE_RADIUS, ECHO_STYLE_DEEPNESS, ECHO_STYLE_THICKNESS, };
	ECHOSTYLE EchoStyle;
	// ��ѡ��Ӧ����ȫ�������2~3����������ö�����ͣ�����У׼Ĭ��Ӧ����ȫ���۽�����
	enum RULENUMBER :long { RULENUMBER_ALL, RULENUMBER_2OR3, };
	RULENUMBER RuleNumber;
	//	�뾶 / ��� / ���1��2��������У׼������ֻ��1��Ч
	float Baseline[2];
	//ָ��Aɨ������
	STRUCT_ASCAN_SETTING*  AScan;
	//ָ����ǰբ�Ų���
	STRUCT_GATE_SETTING*  Gate;
};

class DllExport USCalibrationDACManual : public USCalibration
{
	long CurAngleOrVPA;// �ɼ�����ʱ�ĽǶȻ�VPA
	bool IsApplyToAllLaw;// �Ƿ�Ӧ����ȫ���۽�����
	long QuantitativeType;// �������ͣ�ö�٣���ѡ�Զ��塢JIS��ASME��׼������������ѡ���Զ���ʱ���������ͺ����������ɱ༭��
	long CurveType;// 	�������ͣ�����ֱ꣬�ߡ�����������ʽ
	long CurvesNum;// ��������
	vector<float>CurvesOffset;// Ϊÿ����������ƫ��
	float RefAmplitude;// �ο�������ͨ����Ϊ80%
	struct STRUCT_PONITDAC_DATA
	{
		float depth;//���
		vector<pair<float, float>> Pair_Gain_Amplitude;//���沨���ԡ�
	};
	vector<STRUCT_PONITDAC_DATA> AllPointData; //�ڳ�������Ѱ�Ҷ��λ�ò�ͬ�ĵ㣬������λ�ü���Ӧ���������䵱ǰ���档

	//UT����ʱ������Ϊ1�����沨������ӦΪ1��PAʱ����1��
	typedef vector<pair<float, float>> DAC_CURVE;// Pair_Dis_Amp���벨����
	DAC_CURVE OneDACCurve;// У׼���;���һ�������DAC���ߣ����ߺ�����Ϊ���̣���ȣ�������Ϊ������������Ҫ��¼У׼DAC����ʱ����Ӧ�����档UT����ʱ������Ϊ1��PAʱ����������1
	float DACGain;// У׼���DAC��������Ӧ������

};

class DllExport USCalibrationDACAuto : public USCalibration
{
	long CurAngleOrVPA;// �ɼ�����ʱ�ĽǶȻ�VPA
	bool IsApplyToAllLaw;// �Ƿ�Ӧ����ȫ���۽�����
	long QuantitativeType;// �������ͣ�ö�٣���ѡ�Զ��塢JIS��ASME��׼������������ѡ���Զ���ʱ���������ͺ����������ɱ༭��
	long CurveType;// �������ͣ�����ֱ꣬�ߡ�����������ʽ
	long CurvesNum;// ��������
	vector<float>CurvesOffset;// Ϊÿ����������ƫ��
	float RefAmplitude;// �ο�������ͨ����Ϊ80%
	float MaterialAttenuation;// ����˥�������ݲ���˥���Զ�����DAC

	DAC_CURVE OneDACCurve;// У׼���;���һ�������DAC���ߣ����ߺ�����Ϊ���̣���ȣ�������Ϊ������������Ҫ��¼У׼DAC����ʱ����Ӧ�����档UT����ʱ������Ϊ1��PAʱ����������1 UT����ʱ������Ϊ1��PAʱ����������1
	float DACGain;// ��¼У׼DAC��������Ӧ������
};

class DllExport USCalibrationTCGManual : public USCalibration
{
	long CurAngleOrVPA;// �ɼ�����ʱ�ĽǶȻ�VPA
	bool IsApplyToAllLaw;// �Ƿ�Ӧ����ȫ���۽�����
	float RefAmplitude;// 	�ο�������ͨ����Ϊ80%
	struct STRUCT_PONITTCG_DATA {
		float depth;//���
		vector<pair<float, float>> Pair_Gain_Amplitude;//���沨���ԡ�
	};// 
	vector<STRUCT_PONITTCG_DATA> AllPointData;//�ڳ�������Ѱ�Ҷ��λ�ò�ͬ�ĵ㣬������λ�ü���Ӧ���������䵱ǰ���档

	vector< TCG_CURVE > AllTCGCurve;// У׼���,��ÿ���۽��������TCGУ׼�����ߺ�����Ϊ���̣���ȣ�������Ϊ��������

	float TCGGain; //	��¼У׼TCG��������Ӧ�Ļ�������
};