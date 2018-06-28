/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include <vector>
using std::vector;
using namespace std;

// բ��λ��
struct STRUCT_GATE_POSITION_SETTING
{
	void Init()
	{
		BeiginPosition = 0;
		RefAmplitude = 0;
		Threshould = 0;
		Width = 0;
	}
	bool operator==(STRUCT_GATE_POSITION_SETTING& other)
	{
		if (other.BeiginPosition == BeiginPosition
			&& other.Width == Width
			&& other.Threshould == Threshould
			&& other.RefAmplitude == RefAmplitude)
		{
			return true;
		}
		return false;
	}
	float BeiginPosition;	//բ����ʼλ��
	float Width;			//բ�ſ��
	float Threshould;		//բ����ֵ
	float RefAmplitude;		//�趨ΪXX.X%����̫������
};

// բ��ģʽ
struct STRUCT_GATE_MODE_SETTING
{
	void Init()
	{
		Sync = 0;
		AScanSync = 0;
		Peak = 0;
		Measure = 0;
	}
	long Sync;			//ͬ����Pulse��I / ��A^��A /
	long AScanSync;		//Aɨ��ͬ����Pulse��I /
	long Peak;			//��ֵѡ��MaxPeak��FirstPeak
	long Measure;		//������Peak��Edge
};

// բ��
struct STRUCT_GATE_SETTING
{
	void Init()
	{
		for (int i=0;i<GATE_NUM;i++)
		{
			Position[i].Init();
			Mode[i].Init();
		}
		GateSelected = A;
	}
	STRUCT_GATE_SETTING& operator=(STRUCT_GATE_SETTING& other)
	{
		for (int i = 0; i<GATE_NUM; i++)
		{
			Position[i] = other.Position[i];
			Mode[i] = other.Mode[i];
		}
		GateSelected = other.GateSelected;
		return *this;
	}

	static const int GATE_NUM = 3;
	STRUCT_GATE_POSITION_SETTING Position[GATE_NUM];	//բ��λ��(A��B��I)
	STRUCT_GATE_MODE_SETTING Mode[GATE_NUM];	//բ��ģʽ(A��B��I)
	enum ENUM_GATE_SELECTED :int {A, B, I};
	ENUM_GATE_SELECTED GateSelected;
};

// ��������
struct STRUCT_ALARM_CONDITION
{
	long Condition1;//����1������һ��꣺բ��A��B��I��δ����բ��A��B��I��LessMinT��GreaterMaxT
		long LogicOperator;//�߼����㣺�ޣ�0������(1)����(2)����Ϊ0ʱ������������1.
		long Condition2;//����2������һ��꣺բ��A��B��I��δ����բ��A��B��I��LessMinT��GreaterMaxT
		bool IsOutPut;//����Ƿ�����true(����)

};

// �������
struct STRUCT_ALARM_OUTPUT
{
	vector<long> CurCnt;//��ǰ����������������
		vector<long> MaxCnt;//����������󴥷���������CurCnt >= MaxCnt, ��ʼ����
		bool IsSounding;//�����Ƿ�����true(����)
		long duration;//��������ʱ�䣬��λ��

};

// ���������
struct STRUCT_ALARM_SETTING
{
	vector<STRUCT_ALARM_CONDITION> AlarmCondition;//��������������
	vector<STRUCT_ALARM_OUTPUT>AlarmOutPut;//���������������ÿ������������Ӧһ���������
	enum ENUM_ALARM_SELECTED: int {A, B, I};
	ENUM_ALARM_SELECTED ChooseAlarm;
	void Init()
	{
		STRUCT_ALARM_CONDITION c1;
		AlarmCondition.push_back(c1);
	}
};