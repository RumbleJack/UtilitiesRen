/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

struct STRUCT_ASCAN_SETTING
{
	void Init()
	{
		GainValue = 70;
		IntervalBegin = 0;
		IntervalWidth = 50;
		SizeChanged = false;
	}
	float GainValue;//���棨����ʹ��һ���źŲ����ﵽAɨ��������Լ80%������ֵ��
	long IntervalBegin;//Aɨ����ʼ������������ʼֵ
	long IntervalWidth;//Aɨ�������������
	bool SizeChanged;//ɨ�����Χ�����仯
};

struct STRUCT_UT_GENERAL_SETTING
{
	void Init()
	{
		AScan.Init();
		WedgeDelay = 0.0f;
		Speed = 5900.0f;
	}
	STRUCT_ASCAN_SETTING AScan;// Aɨ������
	float WedgeDelay;	//	Ш���ӳ٣�PA��UT���趨һ������������ΪPA����һ����������ʣ���Ϊÿ���Ƕ�ȷ����ͬ���ӳ٣�
	float Speed;		//	����
};
struct STRUCT_UT_PULSEGEN_SETTING
{
	void Init()
	{
		TxRxMode = 1;
		TransmitFrequency = 0.0f;
		Energy = 30;
		PW = 0.1f;
		PRF = 1000;
	}
	long  TxRxMode;//	���� / ����ģʽ������һ��һ�ա�����ز�����͸
	float TransmitFrequency;//̽ͷƵ��
	float Energy;	//	���������أ�
	float PW;		//������
	float PRF;		//�����ظ�Ƶ��(pulse recurre - nce frequency)ÿ���Ӳ����Ĵ���������Ŀ

};
struct STRUCT_UT_PULSERCV_SETTING
{
	void Init()
	{
		Filter = 0;
		Demodulator = 1;
		VideoFilter = FALSE;
		SmoothLen = 1;
		Supression = 0.0f;
	}
	long Filter;//	�˲�����0M~2M��2M~7M��7M~OO
	long Demodulator;//	�첨�������첨��ȫ����---RF��HW + ��HW��FW---
	BOOL VideoFilter;//	�Ƿ�����Ƶ�˲���
	long SmoothLen;//ƽ�����ȣ�ָ���ز�����ȡƽ��ֵ����������
	float Supression;//���ƣ�ָ�����������ڸò�������Ϊ0��Ĭ��0

};
struct STRUCT_UT_SOUNDBEAM_SETTING
{
	void Init()
	{
		ScanOffset = 0.0f;
		StepOffset = 0.0f;
		Angle = 30.0f;
		RefractionAngle = 30.0f;
		BeamDelay = 0.0f;
		GainCompensate = 0.0f;
	}
	float ScanOffset;//ɨ��ƫ�ƣ��ɶ���Ϊֻ������̽ͷλ���в����ظ���
	float StepOffset;//	��������ƫ��
	float Angle;//�нǣ����峬�����������ɨ����ķ���90��ʱ��ʾ̽ͷ����࣬270�ȱ�ʾ̽ͷ���Ҳࣨ�ɶ���Ϊֻ������̽ͷλ���в����ظ���
	float RefractionAngle;//�����г��������Ƕ�
	float BeamDelay;//�����ӳ�
	float GainCompensate;//���油��
};
struct STRUCT_UT_ADVANCED_SETTING
{
	void Init()
	{
		RefAmplitude = 0.0f;
		SetAsXXX = 0.0f;
		Ref = FALSE;
		AscanSaveDot = -1;
		ScaleFactor = 4;
		Attenuation = FALSE;
	}
	float RefAmplitude;//	�ο�����
	float SetAsXXX;//����
	BOOL Ref;//�Ƿ����ο����湦��
	long AscanSaveDot;//Aɨ�豻����ĵ����� - 1��ʾ�Զ�
	long ScaleFactor;//�������
	BOOL Attenuation;//˥��20dB�Ƿ���

};



// UT����
struct STRUCT_UT_SETTING
{
	void Init()
	{
		UTGeneral.Init();
		UTPulseGen.Init();
		UTPulseRcv.Init();
		UTSoundBeam.Init();
		UTAdvance.Init();
	}
	STRUCT_UT_GENERAL_SETTING UTGeneral;
	STRUCT_UT_PULSEGEN_SETTING UTPulseGen;
	STRUCT_UT_PULSERCV_SETTING UTPulseRcv;
	STRUCT_UT_SOUNDBEAM_SETTING UTSoundBeam;
	STRUCT_UT_ADVANCED_SETTING UTAdvance;
};