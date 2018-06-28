/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include <vector>
using std::vector;
using namespace std;

// 闸门位置
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
	float BeiginPosition;	//闸门起始位置
	float Width;			//闸门宽度
	float Threshould;		//闸门阈值
	float RefAmplitude;		//设定为XX.X%，不太理解这个
};

// 闸门模式
struct STRUCT_GATE_MODE_SETTING
{
	void Init()
	{
		Sync = 0;
		AScanSync = 0;
		Peak = 0;
		Measure = 0;
	}
	long Sync;			//同步：Pulse、I / 、A^、A /
	long AScanSync;		//A扫描同步：Pulse、I /
	long Peak;			//峰值选择：MaxPeak、FirstPeak
	long Measure;		//测量：Peak、Edge
};

// 闸门
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
	STRUCT_GATE_POSITION_SETTING Position[GATE_NUM];	//闸门位置(A、B、I)
	STRUCT_GATE_MODE_SETTING Mode[GATE_NUM];	//闸门模式(A、B、I)
	enum ENUM_GATE_SELECTED :int {A, B, I};
	ENUM_GATE_SELECTED GateSelected;
};

// 报警条件
struct STRUCT_ALARM_CONDITION
{
	long Condition1;//条件1，定义一组宏：闸门A、B、I、未穿出闸门A、B、I、LessMinT、GreaterMaxT
		long LogicOperator;//逻辑运算：无（0），与(1)、或(2)；设为0时，仅考虑条件1.
		long Condition2;//条件2，定义一组宏：闸门A、B、I、未穿出闸门A、B、I、LessMinT、GreaterMaxT
		bool IsOutPut;//输出是否开启，true(开启)

};

// 报警输出
struct STRUCT_ALARM_OUTPUT
{
	vector<long> CurCnt;//当前报警条件触发次数
		vector<long> MaxCnt;//报警条件最大触发次数，若CurCnt >= MaxCnt, 开始报警
		bool IsSounding;//声音是否开启，true(开启)
		long duration;//报警持续时间，单位秒

};

// 报警及输出
struct STRUCT_ALARM_SETTING
{
	vector<STRUCT_ALARM_CONDITION> AlarmCondition;//定义多个报警条件
	vector<STRUCT_ALARM_OUTPUT>AlarmOutPut;//定义多个报警输出，每个报警条件对应一个报警输出
	enum ENUM_ALARM_SELECTED: int {A, B, I};
	ENUM_ALARM_SELECTED ChooseAlarm;
	void Init()
	{
		STRUCT_ALARM_CONDITION c1;
		AlarmCondition.push_back(c1);
	}
};