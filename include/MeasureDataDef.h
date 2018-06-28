#pragma once
#include "PubMacroDef.h"
#include "MeasureDef.h"

#define NUM_OF_TOP_BAR_MEASURE_DATES	8

struct STRUCT_SINGLE_MEASURE_DATA
{
	STRUCT_SINGLE_MEASURE_DATA()
	{	
		MeasureID = GATE_A_PEAK;
		MeasureData = 0.0f;
	}

	ENUM_READING	MeasureID;
	float			MeasureData;
};

struct STRUCT_TOPBAR_MEASURE_DATAS
{
	STRUCT_TOPBAR_MEASURE_DATAS()
	{
		NumOfDatas = NUM_OF_TOP_BAR_MEASURE_DATES;
		pMeasureDatas = new STRUCT_SINGLE_MEASURE_DATA[NumOfDatas];
	}
	~STRUCT_TOPBAR_MEASURE_DATAS()
	{
		if (pMeasureDatas)
			delete[]pMeasureDatas;
		pMeasureDatas = NULL;
	}
	
	STRUCT_SINGLE_MEASURE_DATA *pMeasureDatas;
	long NumOfDatas;
};

// ��բ����صĲ�������
struct STRUCT_SINGLE_GATE_MEASURE_DATA
{	
	// %	բ�����źŷ�ֵ����
	STRUCT_SINGLE_MEASURE_DATA MaxAmplitude;
	// dB	��ֵ���������բ����ֵ������
	STRUCT_SINGLE_MEASURE_DATA DbAccordGateLimit;
	// dB	��ֵ��������ڲο�����������
	STRUCT_SINGLE_MEASURE_DATA DbAccordReferLimit;
	// ^	բ�����źŵķ�ֵλ��
	STRUCT_SINGLE_MEASURE_DATA MaxAmplitudePos;
	// /	բ�����źŵĴ���λ��
	STRUCT_SINGLE_MEASURE_DATA OutGatePos;
	// RX^	�������ϣ���������㵽բ���в���ź�ָʾ���ˮƽ����

	// PX^	�������ϣ�Ш��ǰ�ص�բ���в���ź�ָʾ���ˮƽ����

	// DX^	բ���в���źŷ���������

	// SX^	��������㵽բ���в���ź�ָʾ�������

	// VsX^	բ���в���ź�ָʾ�����ɨ����ľ���

	// ViX^	բ���в���ź�ָʾ����ڲ�����ľ���

	// LX^	��������㵽բ�Ų���ź�ָʾ��������ת����
};

struct STRUCT_MULTI_GATES_MEASURE_DATA
{
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateAData;
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateBData;
	STRUCT_SINGLE_GATE_MEASURE_DATA	GateIData;
};

// ���Ĳ�������
struct STRUCT_SINGLE_CURSOR_DATA
{
	// %	��괦�źŲ���
	STRUCT_SINGLE_MEASURE_DATA AmplitudeData;
	// U	��괦�������ϵ�λ��
	STRUCT_SINGLE_MEASURE_DATA UltrAxisPos;
	// P	��괦��̽ͷǰ�صľ���
	STRUCT_SINGLE_MEASURE_DATA ProbeFrontLength;
	// S	��괦��ɨ�����ϵ�λ��
	STRUCT_SINGLE_MEASURE_DATA ScanAxisPos;
	// I	��괦�ڲ������ϵ�λ��
	STRUCT_SINGLE_MEASURE_DATA StepAxisPos;
	// %(U(X))	��괦�ڳ������ϵ��źŲ���
	STRUCT_SINGLE_MEASURE_DATA AmplitudeInUltrAxisPos;
};

// ���Ĳ�������
struct STRUCT_MULTI_CURSORS_DATA
{
	STRUCT_SINGLE_CURSOR_DATA	ReferCursorData;
	STRUCT_SINGLE_CURSOR_DATA	MeasureCursorData;
	STRUCT_SINGLE_CURSOR_DATA	Measure_ReferCursorData;
	
	// IU(mr)	�ɲ��������ο���꽻���γɵĳ����ο�ĶԽ��ߵľ���
	STRUCT_SINGLE_MEASURE_DATA	Measure_ReferDiagLength;
};