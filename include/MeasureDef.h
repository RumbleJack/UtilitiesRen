/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "PubMacroDef.h"

#include <vector>
using std::vector;
enum ENUM_READING : long
{
	GATE_A_PEAK = 0,// բ�����źŷ�ֵ����
	GATE_B_PEAK,// 
	GATE_I_PEAK,// 
	GATE_AdBA,// 
	GATE_BdBB,// բ��B�ڷ�ֵ���������բ��B��ֵ�����棬��λΪdB
	GATE_AdBr,// բ��A�ڷ�ֵ��������ڲο����������棬��λΪdB
	GATE_BdBr,// բ��B�ڷ�ֵ��������ڲο����������棬��λΪdB
	GATE_A_PEAK_POS,// 	^�� / �ֱ��ʾ��բ�����źŵķ�ֵλ�úʹ���λ��
	GATE_B_PEAK_POS,// 
	GATE_I_PEAK_POS,// 
	GATE_A_PIERCE_POS,// 
	GATE_B_PIERCE_POS,// 
	GATE_I_PIERCE_POS,// 
	POS_RA,// �ڲ������ϣ���������㵽բ��A��B�в���ź�ָʾ���ˮƽ����
	POS_RB,// 
	POS_PA,// �ڲ������ϣ�Ш��ǰ�ص�բ��A��B�в���ź�ָʾ���ˮƽ����
	POS_PB,// 
	POS_DA,// բ��A��B�в���źŷ���������
	POS_DB,// 
	POS_SA,// ��������㵽բ��A��B�в���ź�ָʾ�������
	POS_SB,// 
	POS_VsA,// բ��A��B�в���ź�ָʾ�����ɨ����ľ���
	POS_VsB,// 
	POS_ViA,// բ��A��B�в���ź�ָʾ����ڲ�����ľ���
	POS_ViB,// 
	POS_LA,// ��������㵽բ��A��B�в���ź�ָʾ��������ת����
	POS_LB,// 

	CURSOR_REF_AMPLITUDE, //�ο����λ�õĲ���ֵ
	CURSOR_MES_AMPLITUDE, //�������λ�õĲ���ֵ
	CURSOR_MES_MINUS_REF_AMPLITUDE, //�������Ĳ���ֵ��ȥ�ο����Ĳ���ֵ
	CURSOR_REF_POS_USAXIS, //�ο�����ڳ������ϵ�λ��
	CURSOR_MES_POS_USAXIS, //��������ڳ������ϵ�λ��
	CURSOR_MES_MINUS_REF_POS_USAXIS, //�������λ�ü�ȥ�ο����λ��
	CURSOR_REF_PROBE_DISTANCE, //�ο������̽ͷǰ�صľ���
	CURSOR_MES_PROBE_DISTANCE, //���������̽ͷǰ�صľ���
	CURSOR_MES_MINUS_REF_PROBE_DISTANCE, //�������λ�ü�ȥ�ο����ľ���
	CURSOR_REF_POS_SCANAXIS, //ɨ�����ϲο�����λ��
	CURSOR_MES_POS_SCANAXIS, //ɨ�����ϲ�������λ��
	CURSOR_MES_MINUS_REF_POS_SCANAXIS, //�������λ�ü�ȥ�ο����ľ���
	CURSOR_REF_POS_STEPAXIS, //�������ϲο�����λ��
	CURSOR_MES_POS_STEPAXIS, //�������ϲ�������λ��
	CURSOR_MES_MINUS_REF_POS_STEPAXIS, //�������λ�ü�ȥ�ο����ľ���
	CURSOR_REF_MES_DIOGONAL, //���������ο������ɳ����ο�Խ��߾���
	CURSOR_REF_AMPLITUDE_USAXIS, //�������ϲο����λ���źŲ���
	CURSOR_MES_AMPLITUDE_USAXIS, //�������ϲ������λ���źŲ���

	QUANTIFY_A_PEAK_MINUS_CURVE_PERCENT, // բ��A�в�õ��źŷ�ֵͬ��ѡ����������Ӧ������ֵ���԰ٷ�����ʾ
	QUANTIFY_B_PEAK_MINUS_CURVE_PERCENT,
	QUANTIFY_A_PEAK_MINUS_CURVE_DB,//բ��A�в�õ��źŷ�ֵͬ��ѡ����������Ӧ������ֵ����dB��ʾ
	QUANTIFY_B_PEAK_MINUS_CURVE_DB,
	QUANTIFY_A_PEAK_MINUS_CURVE_PERCENT_MAX,//���һ��ѡ�����߻����һ�θ�λ���ݣ�բ��A�в�õ��źŷ�ֵͬ��ѡ����������Ӧ������ֵ���԰ٷ�����ʾ
	QUANTIFY_B_PEAK_MINUS_CURVE_PERCENT_MAX,
	QUANTIFY_A_PEAK_MINUS_CURVE_DB_MAX,//���һ��ѡ�����߻����һ�θ�λ���ݣ�բ��A�в�õ��źŷ�ֵͬ��ѡ����������Ӧ������ֵ����dB��ʾ
	QUANTIFY_B_PEAK_MINUS_CURVE_DB_MAX,

	SPECIFICATION_AWS_A, SPECIFICATION_AWS_B, SPECIFICATION_AWS_C, SPECIFICATION_AWS_D, SPECIFICATION_AWS_CL,

	ENV_E_AMPLITUDE, ENV_E_PEAK, ENV_E_EDGE , ENV_E_3dB, ENV_E_6dB, ENV_E_12dB, ENV_E_20dB,

	CORROSION_T,
	CORROSION_ML,
	CORROSION_Tmin,
	CORROSION_S_TMin_,
	CORROSION_I_TMin_,
	CORROSION_Angle_TMin,
	CORROSION_TminZ,
	CORROSION_S_TMinZ,
	CORROSION_I_TMinZ,
	CORROSION_Angle_TMinZ,


	WATERLOGGING_I_PIERCE,//�źŴ���բ��I��λ��
	WATERLOGGING_I_W_PIERCE,//�źŴ���բ��I��λ��, ʹ��ˮ������

	UT_SCALE, //���(�����ֻ�Ƶ����ص��ź�ѹ������)
};

// ���ѡ���붨λ����
struct STRUCT_CURSOR_SETTING
{
	void Init()
	{
		VPAOrAngle = 0;
	}
	enum ENUM_CATEGORY :long 
	{
		CATEGORY_A,
		CATEGORY_B,
		CATEGORY_C,
		CATEGORY_S,
	};
	ENUM_CATEGORY Category;	//��ѡ��A��B��C��S�����ݵȣ�ȡ���ڵ�ǰ����
	long  MoveMode;	//�ƶ�ģʽ��������ͬʱ
	float Delta;	//	�ο��Ͳ�������ľ��룺���� Cursor ΪRandMʱ����
	long  Axis;	    //��ѡA�������ᣩ��U�����ᡢSɨ���ᡢI�����ᣬ�Ƕȣ�VPA
	long  Cursor;	//��ѡR���ο���꣩m��������꣩RandM���ο����Ͳ�����꣩
	float ScanPosition;	//	�����ɨ����λ�ã������ = ������Ч��
	float StepPosition;	//�����ɨ����λ�ã������ = ������δ��դɨ����Ч��
	long  VPAOrAngle;	//	���ù�굱ǰ�Ƕȣ������ = ������Ч��
};

// ��¼��ǰ����������
struct STRUCT_READINGCOL_SETTING
{
	static const int ReadingColNum = 8;	// �������ж�������
	long MeasureMode;	//ѡ�����ģʽ, ֵΪ - 1ʱ����ʾ�Զ������������
	long MeasureSetting[ReadingColNum];	//�洢�Զ������������
};

//ȱ�ݱ���
struct STRUCT_DEFECTREPORT_SETTING
{
	vector<long> ColSetting;	//����ѡ���⣬ȱ�ݱ���Ҫ������������ʹ�ñ�ʾ��ͬ�Ķ����꣩
	vector<vector<float>> data;	//ȱ�ݱ���������Ŀ
};

struct STRUCT_MEASURE_SETTING
{
	STRUCT_CURSOR_SETTING			Cursor;	//���
	STRUCT_READINGCOL_SETTING		ReadingCol;	    //������
	STRUCT_DEFECTREPORT_SETTING		DefectReport;	//ȱ�ݱ���
	// �����ά�������飬�洢Ԥ�������ģʽ��ÿ��Ԥ�������ģʽ����8�������ꡣ
	static const ENUM_READING		PreDefinedMeasureMode [][8];
};

