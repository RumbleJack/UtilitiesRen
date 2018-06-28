/*---------------------------------------------------------------------------*/
/*-----文件WorkPieceDef：定义工件参数----------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------定义工件------------------------------------*/
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
	//工件纵波声速
	float Material_Speed_LW;
	//工件横波声速
	float Material_Speed_SW;
	// 被测工件几何形状参数，有平板、外径、内径三种
	typedef enum :long 
	{ 
		WORKPIECE_STYLE_FLAT, WORKPIECE_STYLE_OUTSIDEDIAMETER, WORKPIECE_STYLE__INSIDEDIAMETER
	}	WORKPIECE_STYLE;
	WORKPIECE_STYLE CSCMode;
	//当CSCMode选择了平板，该参数指定厚度；否则，指定直径。单位：毫米(mm)
	float Thickness;
	// 被测工件中的焊缝形状有V（偏移），双V（偏移），J, U及无焊缝
	typedef enum :long
	{
		WELD_STYLE_NULL,WELD_STYLE_V, WELD_STYLE_VV, WELD_STYLE_J,WELD_STYLE_U
	}WELD_STYLE;
	WELD_STYLE WeldStyle;
	//	焊缝，关于焊缝结构体的定义见焊缝
	UNION_WELD_SETTING Weld;
};