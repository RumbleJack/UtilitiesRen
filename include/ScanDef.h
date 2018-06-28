/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once


struct STRUCT_SCAN_DETECT_SETTING
{
	long ScanStyle;// 扫查类型：单线扫查、光栅扫查
	long ScanAxis;// 扫查轴数据源：时间、编码器1，编码器2
	long StepAxis;// 步进轴数据源：编码器1，编码器2
	long ScanSpeed;// 扫查速度（mm / s），时间扫查有效
	long MaxScanSpeed;// 	最大扫查速度（mm / s）, 使用编码器扫查有效

};

struct STRUCT_SCAN_CODING_SETTING
{
	long CoderNum;// 编码器编号
	bool Polarity;// 极性，探头只能在逆方向上扫查时，该参数可使编码器反向计数
	bool CoderStyle;// 选择当前编码器类型：时钟 / 方向、正交、向上、向下、时钟 / 方向向上、时钟 / 方向向下、点击器、点击器 + 预设。不理解这里什么意思
	long Resolution;// 分辨率
	long Origin;// 原点
	long Default;// 预设

};

struct STRUCT_SCAN_AREA_SETTING
{
	long ScanStart;// 扫查起始位置（mm）
	long ScanEnd;// 扫查终止位置（mm）
	long ScanResolution;// 	扫查分辨率（采集点步距）
	long StepStart;// 	步进起始位置（mm）
	long StepEnd;// 	步进终止位置（mm）
	long StepResolution;// 	步进分辨率（采集点步距）
	float CoderError;// 编码器误差（只存在于线性扫查）

};

struct STRUCT_SCAN_DATA_SETTING
{
	long Storage;// 当扫查经过同一位置时，保存的数据由该项确定：最后、A%、最大厚度、最小厚度
};

struct STRUCT_SCAN_START_SETTING
{
	long StartMode;// 	开始模式，指定在开始采集时的操作：复位全部、复位编码器。复位数据
	bool Start;// 	当start变为true时，执行StartMode中操作，然后将Start复位到False。（程序中该参数可以省略）
	bool Pause;// 暂停和开始采集

};

struct STRUCT_SCAN_SETTING
{
	STRUCT_SCAN_DETECT_SETTING ScanDetect;	//检测子菜单
	STRUCT_SCAN_CODING_SETTING ScanCoding;	//编码器子菜单
	STRUCT_SCAN_AREA_SETTING   ScanArea;	//区域子菜单
	STRUCT_SCAN_DATA_SETTING   ScanData;	//数据子菜单
	STRUCT_SCAN_START_SETTING  ScanStart;	//	开始子菜单
};
