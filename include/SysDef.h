#ifndef SYSTEM_PARAMETERS_DEFINITION
#define SYSTEM_PARAMETERS_DEFINITION

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768

typedef struct
{
	unsigned MenuBar : 1 ;	// 1 : 显示菜单条
	unsigned UpperParamBar : 1 ; // 1: 显示上层参数条
	unsigned LowerParamBar : 1 ;	// 1: 显示下层参数条
	unsigned AccelBar : 1 ;			// 1: 显示快捷条
	unsigned StatusBlk : 2 ;		// 00: 不显示，01：显示小块状态栏, 10：显示大块状态栏
	unsigned LogoBlk : 1 ;			// 1: 显示LOGO
	unsigned ImgViewWnd : 1 ;
	// ... 此处定义视窗模式
} STRUCT_LAYOUT ;	// 定义界面布局，ArrangeCtrlPanelPos()取决于此

const STRUCT_LAYOUT DEFAULT_LAYOUT = {1, 1, 1, 1, 2, 1, 0} ; // 初始布局

#define WIDTH_LEFT_FUNC_PANEL	0.1f
#define WIDTH_MAIN_PANEL	1.0f-WIDTH_LEFT_FUNC_PANEL

#define WIDTH_STATUS_PANEL		WIDTH_LEFT_FUNC_PANEL
#define HEIGHT_STATUS_PANEL		0.20f

#define WIDTH_SMALL_STATUS_PANEL	0.05f  // 小状态栏，适用于无菜单栏，仅快捷栏
#define HEIGHT_SMALL_STATUS_PANEL	0.04f  

#define WIDTH_LOGO_PANEL	WIDTH_LEFT_FUNC_PANEL
#define HEIGHT_LOGO_PANEL	0.1f

#define DEFAULT_ICON_WIDTH	WIDTH_LEFT_FUNC_PANEL
#define DEFAULT_ICON_HEIGHT	0.05f

#define WIDTH_PARAM_PANEL	1.0f-WIDTH_LEFT_FUNC_PANEL
#define HEIGHT_PARAM_PANEL	0.06f

#define WIDTH_ACCEL_PANEL	1.0f-WIDTH_LEFT_FUNC_PANEL 
#define HEIGHT_ACCEL_PANEL	0.04f

#define FLOAT_PRECISION 2

// 按键前景，背景（选中，未选中）颜色
#define ICON_TEXT_COLOR RGB(128, 128, 128) 
#define HOT_ICON_BK_CLR	RGB(0, 255, 255) 
#define UNSELECTED_ICON_BK_CLR	RGB(255, 255, 255)
#define SCANVIEW_ICON_BK_CLR RGB(0, 0, 0) // 扫查视图背景色

#define PARAM_ICON_FONT _T("宋体")
#define PARAM_ICON_TITLE_COLOR	RGB(128, 128, 128)
#define PARAM_ICON_DATA_COLOR	RGB(0, 0, 255)
#define PARAM_ICON_EDIT_BK_COLOR RGB(0, 0, 0)
#define PARAM_ICON_EDIT_DATA_COLOR RGB(255, 255, 255)
#define PARAM_ICON_TITLE_CHAR_SIZE	16
#define PARAM_ICON_PARAM_CHAR_SIZE	24
#define PARAM_ICON_TITLE_WIDTH	0.5f 

#define WIDTH_POPUP_ENUM_ITEM 100
#define HEIGHT_POPUP_ENUM_ITEM	30

/*-------------------------------------------------------------------------------*/
/*-----------------------------------以下还未读----------------------------------*/
/*-------------------------------------------------------------------------------*/
typedef enum
{
	WITHOUT_DATA,
	ID_DEF,
	INT_DATA,
	FLOAT_DATA,
	STR_PTR,
	ENUM_GATE_IDX
} ENUM_PARAM_TYPE ;

typedef struct
{
	unsigned GATE_I : 1 ;
	unsigned GATE_A : 1 ;
	unsigned GATE_B : 1 ;
	unsigned GATE_C	: 1 ;
} STRUCT_GATE_DEF ;

#define CNT_DIVIDED_ICON 2	// 单个参数栏尺寸被分割成两个子参数栏
typedef union
{
	WORD	id ;
	STRUCT_GATE_DEF	GateIdx ;
	float	FltData ;
	long		IntData ;
	WCHAR *	pStr ;
} UNION_DATA_TRANSFER ;

#endif