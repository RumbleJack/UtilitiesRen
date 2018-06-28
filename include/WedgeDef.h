/*---------------------------------------------------------------------------*/
/*-----�ļ�WedgeDef������Ш�����--------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
/*---------------------------------------------------------------------------*/
/* ------------------------------����Ш��------------------------------------*/
/*---------------------------------------------------------------------------*/

enum WEDGE_PROBEDRC
{
	WEDGE_PROBEDRC_FOWARD,
	WEDGE_PROBEDRC_BACKWARD,
};
// PAШ��
struct STRUCT_WEDGEPA_SETTING
{
	void Init()
	{
		strcpy_s(WedgeModel, "Default");
		ProbeDrc = WEDGE_PROBEDRC_FOWARD;
		Angle = 0.0f;
		Height = 30.0f;
		Width = 0;
		FirstOffset = 71.7f;
		SecondOffset = 0;
		Speed = 2337.0f;
		IsUsed = false;
	}
	//Ш���ͺţ��ַ���
	char WedgeModel[32];
	// ̽ͷ���򣬿�ȡ����(0)������(1)
	WEDGE_PROBEDRC ProbeDrc;
	//Ш��Ƕ�
	float Angle;
	//Ш��߶ȣ���һ��Ƭ�߶ȣ�ͨ����Ш���������ṩ��
	float Height;
	//Ш����
	float Width;
	//����ƫ�ƣ�Ш��ǰ����̽ͷ��һ��Ƭ���ļ�ľ��룩��Ĭ������£������0�ο������ڵ�һ��Ƭλ���ϡ�Ҫ��0�ο���������Ш��ǰ��λ�ã���Ҫ������ƫ��������Ш��ǰ�غ͵�һ��Ƭλ��֮��ľ��롣��ֵ����Ϊ��ֵ��
	float FirstOffset;
	//����ƫ�ơ�0��ʾ̽ͷ�ڴ��᷽����λ��Ш�����ġ����̽ͷû�д���Ш�����ģ������ʵ�ֵ������������Ϊɨ�鷽��
	float SecondOffset;
	//Ш������;
	float Speed;
	
	// �Ƿ�ʹ��
	bool IsUsed;
} ;

// UTШ��
typedef struct
{
	void Init()
	{
		strcpy_s(WedgeModel, "Default");
		ProbeDrc = WEDGE_PROBEDRC_FOWARD;
		Angle = 39.0f;
		WaveType = 0;
		RefPoint = 0;
		IsUsed = true;
	}
	//Ш���ͺţ��ַ���
	char WedgeModel[32];
	// ̽ͷ���򣬿�ȡ����(0)������(1)
	WEDGE_PROBEDRC ProbeDrc;
	// ����Ƕȣ�����Ш��Ƕ�Page89
	float Angle;
	//����,�������ͣ���ѡ�Შ��0�����ݲ�(1).����PA�������ھ۽������ж���
	long WaveType;
	//�ο���
	float RefPoint;

	// �Ƿ�ʹ��
	bool IsUsed;
} STRUCT_WEDGEUT_SETTING;


struct STRUCT_WEDGE_SETTING
{
public:
	void Init()
	{
		WedgeType = WEDGE_TYPE_PA;
		UnionWedge.Init();
	}
	enum :long { WEDGE_TYPE_UT, WEDGE_TYPE_PA }WedgeType;
	union {
		void Init()
		{
			WedgePA.Init();
		}
		STRUCT_WEDGEUT_SETTING WedgeUT;
		STRUCT_WEDGEPA_SETTING WedgePA;
	}UnionWedge;
};
