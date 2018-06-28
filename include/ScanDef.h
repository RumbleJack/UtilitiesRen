/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once


struct STRUCT_SCAN_DETECT_SETTING
{
	long ScanStyle;// ɨ�����ͣ�����ɨ�顢��դɨ��
	long ScanAxis;// ɨ��������Դ��ʱ�䡢������1��������2
	long StepAxis;// ����������Դ��������1��������2
	long ScanSpeed;// ɨ���ٶȣ�mm / s����ʱ��ɨ����Ч
	long MaxScanSpeed;// 	���ɨ���ٶȣ�mm / s��, ʹ�ñ�����ɨ����Ч

};

struct STRUCT_SCAN_CODING_SETTING
{
	long CoderNum;// ���������
	bool Polarity;// ���ԣ�̽ͷֻ�����淽����ɨ��ʱ���ò�����ʹ�������������
	bool CoderStyle;// ѡ��ǰ���������ͣ�ʱ�� / �������������ϡ����¡�ʱ�� / �������ϡ�ʱ�� / �������¡������������� + Ԥ�衣���������ʲô��˼
	long Resolution;// �ֱ���
	long Origin;// ԭ��
	long Default;// Ԥ��

};

struct STRUCT_SCAN_AREA_SETTING
{
	long ScanStart;// ɨ����ʼλ�ã�mm��
	long ScanEnd;// ɨ����ֹλ�ã�mm��
	long ScanResolution;// 	ɨ��ֱ��ʣ��ɼ��㲽�ࣩ
	long StepStart;// 	������ʼλ�ã�mm��
	long StepEnd;// 	������ֹλ�ã�mm��
	long StepResolution;// 	�����ֱ��ʣ��ɼ��㲽�ࣩ
	float CoderError;// ��������ֻ����������ɨ�飩

};

struct STRUCT_SCAN_DATA_SETTING
{
	long Storage;// ��ɨ�龭��ͬһλ��ʱ������������ɸ���ȷ�������A%������ȡ���С���
};

struct STRUCT_SCAN_START_SETTING
{
	long StartMode;// 	��ʼģʽ��ָ���ڿ�ʼ�ɼ�ʱ�Ĳ�������λȫ������λ����������λ����
	bool Start;// 	��start��Ϊtrueʱ��ִ��StartMode�в�����Ȼ��Start��λ��False���������иò�������ʡ�ԣ�
	bool Pause;// ��ͣ�Ϳ�ʼ�ɼ�

};

struct STRUCT_SCAN_SETTING
{
	STRUCT_SCAN_DETECT_SETTING ScanDetect;	//����Ӳ˵�
	STRUCT_SCAN_CODING_SETTING ScanCoding;	//�������Ӳ˵�
	STRUCT_SCAN_AREA_SETTING   ScanArea;	//�����Ӳ˵�
	STRUCT_SCAN_DATA_SETTING   ScanData;	//�����Ӳ˵�
	STRUCT_SCAN_START_SETTING  ScanStart;	//	��ʼ�Ӳ˵�
};
