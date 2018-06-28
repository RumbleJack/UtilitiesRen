/*---------------------------------------------------------------------------*/
/*-----�ļ�WorkPieceDef�����幤������----------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------���幤��------------------------------------*/
/*---------------------------------------------------------------------------*/
struct STRUCT_WORKPIECE_SETTING
{
public:
	//STRUCT_WORKPIECE_SETTING()
	//	:Material_Speed_LW(5900), Material_Speed_SW(3200),
	//	CSCMode(WORKPIECE_STYLE_FLAT), Thickness(40), WeldStyle(WELD_STYLE_NULL)
	//{}
	//~STRUCT_WORKPIECE_SETTING()
	//{
	//	if (Weld != NULL)
	//		delete Weld;
	//}
	void Init()
	{
		CSCMode = STRUCT_WORKPIECE_SETTING::WORKPIECE_STYLE_FLAT;
		Material_Speed_LW = 5900;
		Material_Speed_SW = 3200;
		Thickness = 40;
		WeldStyle = STRUCT_WORKPIECE_SETTING::WELD_STYLE_NULL;
		Weld;
	}
public:
	//�����ݲ�����
	float Material_Speed_LW;
	//�����Შ����
	float Material_Speed_SW;
	// ���⹤��������״��������ƽ�塢�⾶���ھ�����
	typedef enum :long 
	{ 
		WORKPIECE_STYLE_FLAT, WORKPIECE_STYLE_OUTSIDEDIAMETER, WORKPIECE_STYLE__INSIDEDIAMETER
	}	WORKPIECE_STYLE;
	WORKPIECE_STYLE CSCMode;
	//��CSCModeѡ����ƽ�壬�ò���ָ����ȣ�����ָ��ֱ������λ������(mm)
	float Thickness;
	// ���⹤���еĺ�����״��V��ƫ�ƣ���˫V��ƫ�ƣ���J, U���޺���
	typedef enum :long
	{
		WELD_STYLE_NULL,WELD_STYLE_V, WELD_STYLE_VV, WELD_STYLE_J,WELD_STYLE_U
	}WELD_STYLE;
	WELD_STYLE WeldStyle;
	//	���죬���ں���ṹ��Ķ��������
	UNION_WELD_SETTING Weld;
};