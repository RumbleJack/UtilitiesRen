/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once

/*---------------------------------------------------------------------------*/
/* ------------------------------定义组头------------------------------------*/
/*---------------------------------------------------------------------------*/
struct STRUCT_GROUPHEADER_SETTING
{
public:
	//STRUCT_GROUPHEADER_SETTING()
	//	:DetectMode(DETECT_MODE_PA), Application(APPLICATION_STYLE_WELD)
	//{}
	enum DETECT_MODE :long { DETECT_MODE_UT, DETECT_MODE_PA };
	enum APPLICATION_STYLE :long { APPLICATION_STYLE_WELD, APPLICATION_STYLE_CORROSION };

	void InitGroupHeader(DETECT_MODE mode = DETECT_MODE_PA,
		APPLICATION_STYLE style = APPLICATION_STYLE_CORROSION)
	{
		DetectMode = mode;
		Application = style;
	}
public:
	// 检测模式（UT、PA）
	DETECT_MODE DetectMode;
	//应用（焊缝、腐蚀等）
	APPLICATION_STYLE Application;

};


