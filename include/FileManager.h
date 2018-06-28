#pragma once
#include "PubMacroDef.h"
#include "ParamDef.h"

/*---------------------------------------------------------------------------*/
/* ------------------------------定义文件管理类-------------------------------*/
/*---------------------------------------------------------------------------*/
#define SIZE_FILE_ID    4
#define SIZE_KEY_NOTE	4
class DllExport FileDef
{
public:
	// 文件状态
	enum :long
	{
		RET_FILE_CHECKED = 0, // 受阻
		RET_FILE_CREATED = 1,
		RET_FILE_CLOSED = 2,
		RET_FILE_EXIST = 3,
		RET_FILE_FAIL_TO_CREATE = -1,
		RET_FILE_FAIL_TO_WRITE = -2,
		RET_FILE_FAIL_TO_READ = -3,
		RET_FILE_UNRECOGNIZED = -4,
		RET_FILE_UNDEFINED_SECTION = -5,
		RET_FILE_ERR_PARAMETER = -6,
	};
	// 文件标识
	static const char  FILE_ID[SIZE_FILE_ID];
	static const char  FILE_PROB_ID[SIZE_FILE_ID];
	static const char  FILE_WEDG_ID[SIZE_FILE_ID];
	static const char  FILE_PFFT_ID[SIZE_FILE_ID];
	static const char  FILE_CONF_ID[SIZE_FILE_ID];
	static const char  FILE_DATA_ID[SIZE_FILE_ID];
	static const char  FILE_REPT_ID[SIZE_FILE_ID];

	// 数据段ID
	enum :long
	{
		ID_SECTION_SOFTWARE = 0x0001, //软件标记
		ID_SECTION_SEPARATE = 0x0002, //数据分隔
		ID_SECTION_FILEGEN = 0x0003, //文件生成
		ID_SECTION_ASSCFILE = 0x0010, //关联文件
		ID_SECTION_FILEEND = 0xFFFF, //文件结束段

		ID_SECTION_GROUPHEAD_SETTING = 0X0020,
		ID_SECTION_PROBE_SETTING = 0X0021,
		ID_SECTION_WEDGE_SETTING = 0X0022,
		ID_SECTION_WORKPIECE_SETTING = 0X0023,
		ID_SECTION_PROBEPOS_SETTING = 0X0024,
		ID_SECTION_FOUCUSLAW_SETTING = 0X0025,
		ID_SECTION_FFT_SETTING = 0X0026,

		// Demo 无意义
		ID_SECTION_TESTBLOCK_SETTING = 0X0052,
	};
	// 助记键
	static const char NOTE_SECTION_SOFTWARE[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_SEPARATE[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_FILEGEN[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_ASSCFILE[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_FILEEND[SIZE_KEY_NOTE];

	static const char NOTE_SECTION_GROUPHEAD_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_PROBE_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_WEDGE_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_WORKPIECE_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_PROBEPOS_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_FOUCUSLAW_SETTING[SIZE_KEY_NOTE];
	static const char NOTE_SECTION_FFT_SETTING[SIZE_KEY_NOTE];

	// Demo 无意义
	static const char NOTE_SECTION_TESTBLOCK_SETTING[SIZE_KEY_NOTE];

public:
	// 数据段的引导字段
	struct STRUCT_SECTION_HEADER
	{
		WORD Id;
		WORD Status;
		BYTE KeyNote[SIZE_KEY_NOTE];
		DWORD Length;
		DWORD Reserved;
	};

	// 软件标记段
#define SIZE_SOFTWARE_NAME	16
#define SIZE_SOFTWARE_VERSION 8
#define SIZE_SOFTWARE_COMMENT 8
	struct STRUCT_SOFTWARE
	{
		WCHAR Name[SIZE_SOFTWARE_NAME];
		WCHAR Version[SIZE_SOFTWARE_VERSION];
		WCHAR Comment[SIZE_SOFTWARE_COMMENT];
	};

	// 定义各数据段数据长度
#define SIZE_GROUPHEADER_SETTING	1024
#define SIZE_WORKPIECE_SETTING	1024
#define SIZE_PROBE_SETTING	1024
#define SIZE_WEDGE_SETTING	1024
#define SIZE_PROBEPOSITION_SETTING	1024
#define SIZE_FOUCUSLAW_SETTING	1024
	union UNION_GROUPHEADER_SETTING
	{
		STRUCT_GROUPHEADER_SETTING Setting;
		BYTE Buf[SIZE_GROUPHEADER_SETTING];
	};
	union UNION_WORKPIECE_SETTING
	{
		STRUCT_WORKPIECE_SETTING Setting;
		BYTE Buf[SIZE_WORKPIECE_SETTING];
	};
	union UNION_PROBE_SETTING
	{
		STRUCT_PROBE_SETTING Setting;
		BYTE Buf[SIZE_PROBE_SETTING];
	};
	union UNION_WEDGE_SETTING
	{
		STRUCT_WEDGE_SETTING Setting;
		BYTE Buf[SIZE_WEDGE_SETTING];
	};
	union UNION_PROBEPOSITION_SETTING
	{
		STRUCT_PROBEPOSITION_SETTING Setting;
		BYTE Buf[SIZE_PROBEPOSITION_SETTING];
	};
	union UNION_FOUCUSLAW_SETTING
	{
		STRUCT_FOUCUSLAW_SETTING Setting;
		BYTE Buf[SIZE_FOUCUSLAW_SETTING];
	};

	// Demo 无意义
#define SIZE_TESTBLOCK_SETTING	1024
	union UNION_TESTBLOCK_SETTING
	{
		STRUCT_TESTBLOCK_SETTING Setting;
		BYTE Buf[SIZE_TESTBLOCK_SETTING];
	};
};

class DllExport FileManager:public FileDef
{
public:
	FileManager(void);
	FileManager(LPCTSTR pFileName, LPCTSTR pSoftware = NULL, LPCTSTR pVersion = NULL, LPCTSTR pNote = NULL);
	~FileManager(void);

public:
	// 保存读取探头、楔块、FFT、数据、缺陷文件API
	int SaveProbeUTFile(STRUCT_PROBE_SETTING *pProbe,CString FileName);
	int SaveProbePAFile(STRUCT_PROBE_SETTING *pProbe, CString FileName);
	int SaveWedgeUTFile(STRUCT_WEDGE_SETTING *pWedge, CString FileName);
	int SaveProbeFFTFile(STRUCT_WEDGE_SETTING *pWedge, CString FileName);
	int SaveDataFile(USGroup *pUSGroup, CString FileName);
	int SaveDefectRepFile(USGroup *pUSGroup, CString FileName);
	int ReadProbeUTFile(STRUCT_PROBE_SETTING *pProbe, CString FileName);
	int ReadProbePAFile(STRUCT_PROBE_SETTING *pProbe, CString FileName);
	int ReadWedgeUTFile(STRUCT_WEDGE_SETTING *pWedge, CString FileName);
	int ReadProbeFFTFile(STRUCT_WEDGE_SETTING *pWedge, CString FileName);
	int ReadDataFile(USGroup *pUSGroup, CString FileName);
	int ReadDefectRepFile(USGroup *pUSGroup, CString FileName);

	// 示例	
	int SaveProbeSetting(STRUCT_PROBE_SETTING *pProbe);
	int SaveTestBlockSetting(STRUCT_TESTBLOCK_SETTING *pTestBlock);

private:
	// 创建新文件
	int CreateFileForSavingData();
	int CreateFileForSavingData(LPCTSTR pFileName, LPCTSTR pSoftware = NULL, LPCTSTR pVersion = NULL, LPCTSTR pNote = NULL);
	// 在创建文件时，自动写入文件头及软件信息段
	int SaveFileHeader();
	int SaveSoftwareSection();

	int CloseFile();
private:
	// 将要保存的文件名
	CString mFileName;
	
	// 软件信息(软件标记段)
	CString mSoftware;
	CString mVersion;
	CString mFileNote;

	// 文件句柄
	FILE *mpFile;

	// 配置相关数据段信息
	USGroup mUSGroup;
};

