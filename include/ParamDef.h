/*---------------------------------------------------------------------------*/
/*-----�ļ�StrucParamDef�����峬��̽��������ʹ�ýṹ������-------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
// ���ò���
#include "ProbeDef.h"
#include "WeldDef.h"
#include "WorkPieceDef.h"
#include "WedgeDef.h"
#include "FoucusLawDef.h"
#include "GroupHeaderDef.h"

// ɨ�����
#include "UTDef.h"
#include "MeasureDef.h"
#include "DisplayDef.h"
#include "GateAlarmDef.h"
#include "ScanDef.h"

// ��������
#include "FFTDef.h"
#include "DemoDef.h"
#include "CalibrationDef.h"
#include "ScanDataDef.h"

#include "RationDef.h"
#include "PADef.h"
/*---------------------------------------------------------------------------*/
/* ------------------------------������--------------------------------------*/
/*---------------------------------------------------------------------------*/
class USGroup
{
public:
	USGroup()
	{
		// ��ͷ
		GroupHeader.InitGroupHeader();
		// ����������
		WorkPiece.Init();
		// ̽ͷ(����ͷ��PA��Ӧ)
		Probe.Init();
		// Ш��
		Wedge.Init();
		// ̽ͷλ��
		Probeposition.Init();
		// �۽����򣨽�PA�飩
		FoucusLaw.Init();

		//��ǰ�鳬������
		UT.Init();
		//��ǰ���������
		Measure.Cursor.Init();

		//��ǰ����ʾ����
		//��ǰ��բ������
		Gate.Init();
		//��ǰ�鱨������
		Alarm.Init();
		//��ǰ��ɨ������
		// ̽ͷFFT����
	}
	~USGroup()
	{
	}
public:
	// ��ͷ�������˵�ǰ��Ļ�������
	STRUCT_GROUPHEADER_SETTING GroupHeader;
	// ���������죨������Ϊ�����ṹ���һ����Ա��
	STRUCT_WORKPIECE_SETTING WorkPiece;
	// ̽ͷ
	STRUCT_PROBE_SETTING Probe;
	// Ш��
	STRUCT_WEDGE_SETTING Wedge;
	// ̽ͷλ��
	STRUCT_PROBEPOSITION_SETTING Probeposition;
	// �۽����򣨽�PA�飩
	STRUCT_FOUCUSLAW_SETTING FoucusLaw;

	//��ǰ�鳬������
	STRUCT_UT_SETTING UT;
	//��ǰ���������
	STRUCT_MEASURE_SETTING Measure;
	//��ǰ����ʾ����
	STRUCT_DISPLAY_SETTING Display;
	//��ǰ��բ������
	STRUCT_GATE_SETTING Gate;
	//��ǰ�鱨������
	STRUCT_ALARM_SETTING Alarm;
	//��ǰ��ɨ������
	STRUCT_SCAN_SETTING Scan;

	//̽ͷFFT����
	STRUCT_FFT_PROPERTY FFTProperty;

	// ��ǰ��У׼���
	STRUCT_CALIBRATION_SETTING Calibration;
};



