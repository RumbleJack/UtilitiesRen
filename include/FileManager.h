#pragma once
#include "PubMacroDef.h"
#include "ParamDef.h"

/*---------------------------------------------------------------------------*/
/* ------------------------------�����ļ�������-------------------------------*/
/*---------------------------------------------------------------------------*/
#define SIZE_FILE_ID    4
#define SIZE_KEY_NOTE	4
class DllExport FileDef
{
public:
	// �ļ�״̬
	enum :long
	{
		RET_FILE_CHECKED = 0, // ����
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
	// �ļ���ʶ
	static const char  FILE_ID[SIZE_FILE_ID];
	static const char  FILE_PROB_ID[SIZE_FILE_ID];
	static const char  FILE_WEDG_ID[SIZE_FILE_ID];
	static const char  FILE_PFFT_ID[SIZE_FILE_ID];
	static const char  FILE_CONF_ID[SIZE_FILE_ID];
	static const char  FILE_DATA_ID[SIZE_FILE_ID];
	static const char  FILE_REPT_ID[SIZE_FILE_ID];

	// ���ݶ�ID
	enum :long
	{
		ID_SECTION_SOFTWARE = 0x0001, //������
		ID_SECTION_SEPARATE = 0x0002, //���ݷָ�
		ID_SECTION_FILEGEN = 0x0003, //�ļ�����
		ID_SECTION_ASSCFILE = 0x0010, //�����ļ�
		ID_SECTION_FILEEND = 0xFFFF, //�ļ�������

		ID_SECTION_GROUPHEAD_SETTING = 0X0020,
		ID_SECTION_PROBE_SETTING = 0X0021,
		ID_SECTION_WEDGE_SETTING = 0X0022,
		ID_SECTION_WORKPIECE_SETTING = 0X0023,
		ID_SECTION_PROBEPOS_SETTING = 0X0024,
		ID_SECTION_FOUCUSLAW_SETTING = 0X0025,
		ID_SECTION_FFT_SETTING = 0X0026,

		// Demo ������
		ID_SECTION_TESTBLOCK_SETTING = 0X0052,
	};
	// ���Ǽ�
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

	// Demo ������
	static const char NOTE_SECTION_TESTBLOCK_SETTING[SIZE_KEY_NOTE];

public:
	// ���ݶε������ֶ�
	struct STRUCT_SECTION_HEADER
	{
		WORD Id;
		WORD Status;
		BYTE KeyNote[SIZE_KEY_NOTE];
		DWORD Length;
		DWORD Reserved;
	};

	// �����Ƕ�
#define SIZE_SOFTWARE_NAME	16
#define SIZE_SOFTWARE_VERSION 8
#define SIZE_SOFTWARE_COMMENT 8
	struct STRUCT_SOFTWARE
	{
		WCHAR Name[SIZE_SOFTWARE_NAME];
		WCHAR Version[SIZE_SOFTWARE_VERSION];
		WCHAR Comment[SIZE_SOFTWARE_COMMENT];
	};

	// ��������ݶ����ݳ���
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

	// Demo ������
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
	// �����ȡ̽ͷ��Ш�顢FFT�����ݡ�ȱ���ļ�API
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

	// ʾ��	
	int SaveProbeSetting(STRUCT_PROBE_SETTING *pProbe);
	int SaveTestBlockSetting(STRUCT_TESTBLOCK_SETTING *pTestBlock);

private:
	// �������ļ�
	int CreateFileForSavingData();
	int CreateFileForSavingData(LPCTSTR pFileName, LPCTSTR pSoftware = NULL, LPCTSTR pVersion = NULL, LPCTSTR pNote = NULL);
	// �ڴ����ļ�ʱ���Զ�д���ļ�ͷ�������Ϣ��
	int SaveFileHeader();
	int SaveSoftwareSection();

	int CloseFile();
private:
	// ��Ҫ������ļ���
	CString mFileName;
	
	// �����Ϣ(�����Ƕ�)
	CString mSoftware;
	CString mVersion;
	CString mFileNote;

	// �ļ����
	FILE *mpFile;

	// ����������ݶ���Ϣ
	USGroup mUSGroup;
};

