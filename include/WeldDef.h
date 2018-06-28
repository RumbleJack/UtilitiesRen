/*---------------------------------------------------------------------------*/
/*-----文件WeldDef.h：定义焊缝参数-------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------定义焊缝------------------------------------*/
/*---------------------------------------------------------------------------*/
enum WELD_SYMMETRIC :long
{
	WELD_SYMMETRIC_AXIS, WELD_SYMMETRIC_VL, WELD_SYMMETRIC_VR
};

// V形焊缝
struct STRUCT_WELDV_SETTING
{
	// 焊缝对称关系，分别表示对称于中轴、垂直左、垂直右
	WELD_SYMMETRIC SymmetricalType;
	//焊缝中心偏移值
	float offset;
	//钝边高度
	float land;
	//热焊道角度
	float HPAngle;
	//热焊道高度
	float HPHeight;
	//上部填充区域角度
	float TopFilledAreaAngle;
	//上部填充区域高度
	float TopFilledAreaHeight;
};
// VV形焊缝
struct STRUCT_WELDVV_SETTING
{
	// 焊缝对称关系
	long SymmetricalType;
	//焊缝中心偏移值
	float offset;
	//钝边高度
	float land;
	//热焊道角度
	float HPAngle;
	//热焊道高度
	float HPHeight;
	//上部填充区域角度
	float TopFilledAreaAngle;
	//上部填充区域高度
	float TopFilledAreaHeight;
	//下部填充区域角度
	float BottomFilledAreaAngle;
	//下部填充区域高度
	float BottomFilledAreaHeight;

};
// J形焊缝
 struct STRUCT_WELDJ_SETTING
{
	// 焊缝对称关系
	long SymmetricalType;
	//焊缝中心偏移值
	float offset;
	//焊缝热焊道半径
	float Radius;
	//上部填充区域角度
	float TopFilledAreaAngle;
	//上部填充区域高度
	float TopFilledAreaHeight;
	//下部填充区域角度
	float BottomFilledAreaAngle;
	//下部填充区域高度
	float BottomFilledAreaHeight;

};
// U形焊缝
 struct STRUCT_WELDU_SETTING
{
	// 焊缝对称关系
	long SymmetricalType;
	//焊缝中心偏移值
	float offset;
	//焊缝热焊道半径
	float Radius;
	//上部填充区域角度
	float TopFilledAreaAngle;
	//上部填充区域高度
	float TopFilledAreaHeight;
};

// 为不同焊缝结构定义联合,在文件存储时定义工件Union长度
union UNION_WELD_SETTING
{
	STRUCT_WELDV_SETTING WeldV;
	STRUCT_WELDVV_SETTING WeldVV;
	STRUCT_WELDJ_SETTING WeldJ;
	STRUCT_WELDU_SETTING WeldU;
};
