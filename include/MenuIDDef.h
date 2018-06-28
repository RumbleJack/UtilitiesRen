#ifndef MENU_ITEM_ID_DEFINITION
#define MENU_ITEM_ID_DEFINITION

// 所有按键ID定义为ID_ICON_xxx
// 按键ID取值范围：
// ID: 0X0000 保留，表示“空”
// 菜单ID : [0X0001 - 0X00FF] （菜单按键）(255个)
// 快捷键ID ：[0x0100 - 0x011F] (单个快捷按键）（32个）
// 参数键ID：[0x0120 - 0x013F] (动态参数显示及更改按键）（32个）
// 其它ID: [0X0200-], 用于定义其它的项，例如各种枚举的值

// 无效按键
#define ID_ICON_EMPTY		0

// 文件相关设置按键
#define ID_ICON_FILE_SETTING	0X11		// 文件->设置
#define ID_ICON_FILE_REPORT		0X12		// 文件->报告
#define ID_ICON_FILE_DATA		0X13		// 文件->数据
#define ID_ICON_FILE_IMAGE		0X14		// 文件->图像
#define ID_ICON_FILE_DATA_SETTING	0X15	// 文件->数据设置

// 向导相关设置
#define ID_ICON_WIZARD_WORKPIECE	0X21	// 向导->工件与焊缝
#define ID_ICON_WIZARD_SETTING		0X22	// 向导->设置
#define ID_ICON_WIZARD_CORRECT		0X23	// 向导->校准

// UT设置相关设置
#define ID_ICON_UT_BASIC		0X31	// UT设置->一般
#define ID_ICON_UT_PULSE		0X32	// UT设置->脉冲发生器
#define ID_ICON_UT_RECEIVER		0X33	// UT设置->接收器
#define	ID_ICON_UT_BEAM			0X34	// UT设置->声束
#define	ID_ICON_UT_ADVANCE		0X35	// UT设置->高级

// 测量相关设置
#define ID_ICON_MEASURE_CURSOR	0X41	// 测量->光标
#define ID_ICON_MEASURE_DATA	0X42	// 测量->读数
#define	ID_ICON_MEASURE_REPORT	0X43	// 测量->缺陷报表

// 显示相关
#define ID_ICON_DISPLAY_SELECTION	0X51	// 显示->选择
#define ID_ICON_DISPLAY_VIEW		0X52	// 显示->视图设置
#define	ID_ICON_DISPLAY_LAYER		0X53	// 显示->覆盖
#define ID_ICON_DISPLAY_ZOOM		0X54	// 显示->放大
#define	ID_ICON_DISPLAY_ATTR		0X55 	// 显示->属性

// 定量
#define ID_ICON_ACCURACY_TYPE		0X61	// 定量->类型
#define ID_ICON_ACCURACY_OPERATOR	0X62	// 定量->操作员模式
#define ID_ICON_ACCURACY_MODEL		0X63	// 定量->类型设置
#define	ID_ICON_ACCURACY_CURVE		0X64	// 定量->曲线设置

// 闸门与报警
#define ID_ICON_GATE_ALARM_GATE		0X71	// 闸门与报警->闸门
#define ID_ICON_GATE_ALARM_ALARM	0X72	// 闸门与报警->报警
#define ID_ICON_GATE_ALARM_EXPORT	0X73	// 闸门与报警->输出
#define ID_ICON_GATE_ALARM_SIMULATE	0X74	// 闸门与报警->模拟
#define	ID_ICON_GATE_ALARM_DEPTH	0X75	// 闸门与报警->厚度

// 组/探头和工件
#define ID_ICON_PROBE_WORKPIECE_MANAGER		0X81	// 组/探头和工件->组管理
#define ID_ICON_PROBE_WORKPIECE_PROBE_WEDGE	0X82	// 组/探头和工件->探头和楔块
#define ID_ICON_PROBE_WORKPIECE_POSITION	0X83	// 组/探头和工件->位置
#define ID_ICON_PROBE_WORKPIECE_CHARACTER	0X84	// 组/探头和工件->指定特性
#define ID_ICON_PROBE_WORKPIECE_WORKPIECE	0X85	// 组/探头和工件->工件
// 聚焦法则
#define ID_ICON_FOCUS_SETTING_SETTING	0X91	// 聚焦法则->配置
#define ID_ICON_FOCUS_SETTING_APERTURE	0X92	// 聚焦法则->孔径
#define ID_ICON_FOCUS_SETTING_BEAM		0X93	// 聚焦法则->声束
#define ID_ICON_FOCUS_SETTING_RULE		0X94	// 聚焦法则->法则

// 扫描
#define ID_ICON_SCAN_IMAGE			0XA1	// 扫描->视图模式
#define ID_ICON_SCAN_DETECT			0XA2	// 扫描->检测
#define	ID_ICON_SCAN_CODER			0XA3	// 扫描->编码器
#define ID_ICON_SCAN_REGION			0XA4	// 扫描->区域
#define ID_ICON_SCAN_DATA			0XA5	// 扫描->数据
#define ID_ICON_SCAN_RUNNING		0XA6	// 扫描->开始

// 偏好
#define ID_ICON_CUSTOM_SETTING		0XB1	// 偏好->设置
#define ID_ICON_CUSTOM_DEVICE		0XB2	// 偏好->仪器
#define ID_ICON_CUSTOM_TOOLS		0XB3	// 偏好->工具

// 根菜单
#define ID_ICON_FILE_SERVER	0X01
#define ID_ICON_WIZARD		0X02
#define	ID_ICON_UT_SETTING	0X03
#define ID_ICON_MEASURE		0X04
#define ID_ICON_DISPLAY		0X05
#define ID_ICON_ACCURACY	0X06
#define	ID_ICON_GATE_ALARM	0X07
#define	ID_ICON_PROBE_WORKPIECE	0X08
#define	ID_ICON_FOCUS_SETTING	0X09
#define	ID_ICON_SCAN			0X0A
#define	ID_ICON_CUSTOM			0X0B

// 参数栏键
#define ID_PARAM_UNDEFINED 0X0120
#define ID_PARAM_GAIN	0x0121
#define ID_PARAM_FILE	0x0122
#define ID_PARAM_GATE_IDX	0X0123
#define ID_PARAM_ECHO_AMP	0X0124
#define ID_PARAM_ECHO_DEPTH	0X0125
#define ID_PARAM_ECHO_POS	0X0126
#define ID_PARAM_BEAM_DISTANCE 0X0127

// 快捷菜单
#define ID_ACCEL_LAYOUT 0X101
#define ID_ACCEL_PROBE	0X102
#define ID_ACCEL_CURSOR	0X103
#define ID_ACCEL_ANGLE	0X104
#define ID_ACCEL_SETTING	0X105

// 闸门枚举
#define ID_PARAM_GATE_I		0X201
#define ID_PARAM_GATE_A		0X202
#define ID_PARAM_GATE_B		0X203
#define ID_PARAM_GATE_C		0X204

// 布局枚举
#define ID_ACCEL_LAYOUT_FULL_SCREEN	0X211
#define ID_ACCEL_LAYOUT_NORMAL		0X212

// 组
#endif