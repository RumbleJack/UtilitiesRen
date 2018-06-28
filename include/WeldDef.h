/*---------------------------------------------------------------------------*/
/*-----�ļ�WeldDef.h�����庸�����-------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------���庸��------------------------------------*/
/*---------------------------------------------------------------------------*/
enum WELD_SYMMETRIC :long
{
	WELD_SYMMETRIC_AXIS, WELD_SYMMETRIC_VL, WELD_SYMMETRIC_VR
};

// V�κ���
struct STRUCT_WELDV_SETTING
{
	// ����Գƹ�ϵ���ֱ��ʾ�Գ������ᡢ��ֱ�󡢴�ֱ��
	WELD_SYMMETRIC SymmetricalType;
	//��������ƫ��ֵ
	float offset;
	//�۱߸߶�
	float land;
	//�Ⱥ����Ƕ�
	float HPAngle;
	//�Ⱥ����߶�
	float HPHeight;
	//�ϲ��������Ƕ�
	float TopFilledAreaAngle;
	//�ϲ��������߶�
	float TopFilledAreaHeight;
};
// VV�κ���
struct STRUCT_WELDVV_SETTING
{
	// ����Գƹ�ϵ
	long SymmetricalType;
	//��������ƫ��ֵ
	float offset;
	//�۱߸߶�
	float land;
	//�Ⱥ����Ƕ�
	float HPAngle;
	//�Ⱥ����߶�
	float HPHeight;
	//�ϲ��������Ƕ�
	float TopFilledAreaAngle;
	//�ϲ��������߶�
	float TopFilledAreaHeight;
	//�²��������Ƕ�
	float BottomFilledAreaAngle;
	//�²��������߶�
	float BottomFilledAreaHeight;

};
// J�κ���
 struct STRUCT_WELDJ_SETTING
{
	// ����Գƹ�ϵ
	long SymmetricalType;
	//��������ƫ��ֵ
	float offset;
	//�����Ⱥ����뾶
	float Radius;
	//�ϲ��������Ƕ�
	float TopFilledAreaAngle;
	//�ϲ��������߶�
	float TopFilledAreaHeight;
	//�²��������Ƕ�
	float BottomFilledAreaAngle;
	//�²��������߶�
	float BottomFilledAreaHeight;

};
// U�κ���
 struct STRUCT_WELDU_SETTING
{
	// ����Գƹ�ϵ
	long SymmetricalType;
	//��������ƫ��ֵ
	float offset;
	//�����Ⱥ����뾶
	float Radius;
	//�ϲ��������Ƕ�
	float TopFilledAreaAngle;
	//�ϲ��������߶�
	float TopFilledAreaHeight;
};

// Ϊ��ͬ����ṹ��������,���ļ��洢ʱ���幤��Union����
union UNION_WELD_SETTING
{
	STRUCT_WELDV_SETTING WeldV;
	STRUCT_WELDVV_SETTING WeldVV;
	STRUCT_WELDJ_SETTING WeldJ;
	STRUCT_WELDU_SETTING WeldU;
};
