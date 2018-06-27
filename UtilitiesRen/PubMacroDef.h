#ifndef PUBLIC_MACRO_TOOLS
#define PUBLIC_MACRO_TOOLS

// 使用__declspec(dllexport)就不需要使用Def文件显示定义动态库导出。
// 但仅使用__declspec(dllexport),不使用__declspec(dllimport)可能会导致全局变量、静态函数等出问题
#ifdef PROJECT_EXPORTING
#define DllExport   __declspec( dllexport )
#else
#define DllExport   __declspec( dllimport )
#endif

/*----------------------------------------------------------*/
/*--------------------------计时宏--------------------------*/
/*Time_us: 以微秒为单位，输出计时数值-----------------------*/
/*----------------------------------------------------------*/
#define PREPARE_TIME_COST() \
		LARGE_INTEGER CPUFreq ; \
		LARGE_INTEGER BeginTick, EndTick; \
		/* 获取CPU频率(每秒) */ \
		QueryPerformanceFrequency(&CPUFreq) ; 
#define BEGIN_TIME_COST() \
		QueryPerformanceCounter(&BeginTick) ; 
#define END_TIME_COST(Time_us) \
		QueryPerformanceCounter(&EndTick) ; \
		Time_us =(double) (EndTick.QuadPart - BeginTick.QuadPart) / (double)CPUFreq.QuadPart * 1000000.0 ;

/*----------------------------------------------------------*/
/*------------------------释放内存--------------------------*/
/*DESTROY_MEMORY: 释放数组----------------------------------*/
/*DESTROY_OBJECT: 释放对象指针------------------------------*/
/*RELEASE_RESOURCE: 释放资源--------------------------------*/
/*----------------------------------------------------------*/
#define DESTROY_MEMORY(pArray) \
	if(pArray != NULL)		\
	{	delete [] pArray ; \
		pArray = NULL ; \
	}
#define DESTROY_OBJECT(pObj) \
	if(pObj != NULL)	\
	{	delete pObj ; \
		pObj = NULL ; \
	}
#define RELEASE_RESOURCE(p) \
	if(p != NULL) \
	{	\
		p->Release(); \
		p=NULL;	\
	}

/*----------------------------------------------------------*/
/*------------------------角度与弧度的转化------------------*/
/*----------------------------------------------------------*/
#ifndef CONV_ARC_DEGREE
#define CONV_ARC_DEGREE
#define PI 3.141592654f
#define ARC_TO_DEGREE(x) ((x)*180/PI)
#define DEGREE_TO_ARC(x) ((x)*PI/180)
#endif

/*----------------------------------------------------------*/
/*------------------------编码/解码日期---------------------*/
/*建议输入无符号32位整数------------------------------------*/
/*----------------------------------------------------------*/
// 编码日期，将输入(yy,mm,dd)中的年月日分别放置在低24位
#define MAKE_DATE(yy,mm,dd) (((((yy)<<8)+(mm))<<8)+(dd))	
// 在已编码日期中，设置指定项
#define SET_YEAR(x, yy) ((((yy)<<16)&0xffff0000)+((x)&0x0000ffff))
#define SET_MONTH(x,mm) ((((mm)<<8)&0xff00)+((x)&0xffff00ff))
#define SET_DAY(x,dd) (((dd)&0xff)+((x)&0xffffff00))
// 从已编码日期中，解码指定项
#define FIND_DATE(pk, yy, mm, dd) {dd=(pk)&0xff; mm=((pk)>>8)&0xff; yy=((pk)>>16)&0xffff;} 
#define GET_YEAR(x) ((x)>>16)
#define GET_MONTH(x) (((x)>>8)&0xff)
#define GET_DAY(x) ((x)&0xff)

/*----------------------------------------------------------*/
/*------------------------编码/解码时间---------------------*/
/*建议输入无符号32位整数------------------------------------*/
/*----------------------------------------------------------*/
// 编码时间，将输入(hh, mm, ss, cs)中的时、分、秒、厘秒分别放置在低24位，及高8位
#define MAKE_TIME(hh, mm, ss, cs) ((((((hh)<<8)+(mm))<<8)+(ss))+((cs)<<24))
// 从已编码时间中，解码指定项
#define FIND_TIME(pk, hh, mm, ss, cs) {ss=(pk)&0xff; mm=((pk)>>8)&0xff; hh=((pk)>>16)&0xff;cs=((pk)>>24)&0xff;}
#define GET_HOUR(x) (((x)>>16)&0xff)
#define GET_MINUTE(x) (((x)>>8)&0xff)
#define GET_SECOND(x) ((x)&0xff)
#define GET_CENTISECOND(x) (((x)>>24)&0xff)

/*----------------------------------------------------------*/
/*------------------------浮点数操作------------------------*/
/*ROUNDING：四舍五入到整数----------------------------------*/
/*TRUNCATING：截断到整数------------------------------------*/
/*CLOSE_TO_ZERO：定义接近0的浮点数(作为判别标准)------------*/
/*CHK_TO_ZERO：检查浮点数是否可认为是0----------------------*/
/*----------------------------------------------------------*/
#define ROUNDING(x) ((int)(x+0.5))
#define TRUNCATING(x) ((int)x)
#define CLOSE_TO_ZERO 0.000001
#define CHK_TO_ZERO(x) (abs(x)<=CLOSE_TO_ZERO)

#endif