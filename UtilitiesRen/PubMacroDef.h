#ifndef PUBLIC_MACRO_TOOLS
#define PUBLIC_MACRO_TOOLS

// ʹ��__declspec(dllexport)�Ͳ���Ҫʹ��Def�ļ���ʾ���嶯̬�⵼����
// ����ʹ��__declspec(dllexport),��ʹ��__declspec(dllimport)���ܻᵼ��ȫ�ֱ�������̬�����ȳ�����
#ifdef PROJECT_EXPORTING
#define DllExport   __declspec( dllexport )
#else
#define DllExport   __declspec( dllimport )
#endif

/*----------------------------------------------------------*/
/*--------------------------��ʱ��--------------------------*/
/*Time_us: ��΢��Ϊ��λ�������ʱ��ֵ-----------------------*/
/*----------------------------------------------------------*/
#define PREPARE_TIME_COST() \
		LARGE_INTEGER CPUFreq ; \
		LARGE_INTEGER BeginTick, EndTick; \
		/* ��ȡCPUƵ��(ÿ��) */ \
		QueryPerformanceFrequency(&CPUFreq) ; 
#define BEGIN_TIME_COST() \
		QueryPerformanceCounter(&BeginTick) ; 
#define END_TIME_COST(Time_us) \
		QueryPerformanceCounter(&EndTick) ; \
		Time_us =(double) (EndTick.QuadPart - BeginTick.QuadPart) / (double)CPUFreq.QuadPart * 1000000.0 ;

/*----------------------------------------------------------*/
/*------------------------�ͷ��ڴ�--------------------------*/
/*DESTROY_MEMORY: �ͷ�����----------------------------------*/
/*DESTROY_OBJECT: �ͷŶ���ָ��------------------------------*/
/*RELEASE_RESOURCE: �ͷ���Դ--------------------------------*/
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
/*------------------------�Ƕ��뻡�ȵ�ת��------------------*/
/*----------------------------------------------------------*/
#ifndef CONV_ARC_DEGREE
#define CONV_ARC_DEGREE
#define PI 3.141592654f
#define ARC_TO_DEGREE(x) ((x)*180/PI)
#define DEGREE_TO_ARC(x) ((x)*PI/180)
#endif

/*----------------------------------------------------------*/
/*------------------------����/��������---------------------*/
/*���������޷���32λ����------------------------------------*/
/*----------------------------------------------------------*/
// �������ڣ�������(yy,mm,dd)�е������շֱ�����ڵ�24λ
#define MAKE_DATE(yy,mm,dd) (((((yy)<<8)+(mm))<<8)+(dd))	
// ���ѱ��������У�����ָ����
#define SET_YEAR(x, yy) ((((yy)<<16)&0xffff0000)+((x)&0x0000ffff))
#define SET_MONTH(x,mm) ((((mm)<<8)&0xff00)+((x)&0xffff00ff))
#define SET_DAY(x,dd) (((dd)&0xff)+((x)&0xffffff00))
// ���ѱ��������У�����ָ����
#define FIND_DATE(pk, yy, mm, dd) {dd=(pk)&0xff; mm=((pk)>>8)&0xff; yy=((pk)>>16)&0xffff;} 
#define GET_YEAR(x) ((x)>>16)
#define GET_MONTH(x) (((x)>>8)&0xff)
#define GET_DAY(x) ((x)&0xff)

/*----------------------------------------------------------*/
/*------------------------����/����ʱ��---------------------*/
/*���������޷���32λ����------------------------------------*/
/*----------------------------------------------------------*/
// ����ʱ�䣬������(hh, mm, ss, cs)�е�ʱ���֡��롢����ֱ�����ڵ�24λ������8λ
#define MAKE_TIME(hh, mm, ss, cs) ((((((hh)<<8)+(mm))<<8)+(ss))+((cs)<<24))
// ���ѱ���ʱ���У�����ָ����
#define FIND_TIME(pk, hh, mm, ss, cs) {ss=(pk)&0xff; mm=((pk)>>8)&0xff; hh=((pk)>>16)&0xff;cs=((pk)>>24)&0xff;}
#define GET_HOUR(x) (((x)>>16)&0xff)
#define GET_MINUTE(x) (((x)>>8)&0xff)
#define GET_SECOND(x) ((x)&0xff)
#define GET_CENTISECOND(x) (((x)>>24)&0xff)

/*----------------------------------------------------------*/
/*------------------------����������------------------------*/
/*ROUNDING���������뵽����----------------------------------*/
/*TRUNCATING���ضϵ�����------------------------------------*/
/*CLOSE_TO_ZERO������ӽ�0�ĸ�����(��Ϊ�б��׼)------------*/
/*CHK_TO_ZERO����鸡�����Ƿ����Ϊ��0----------------------*/
/*----------------------------------------------------------*/
#define ROUNDING(x) ((int)(x+0.5))
#define TRUNCATING(x) ((int)x)
#define CLOSE_TO_ZERO 0.000001
#define CHK_TO_ZERO(x) (abs(x)<=CLOSE_TO_ZERO)

#endif