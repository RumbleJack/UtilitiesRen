#pragma once

#define SAMPLING_FREQUENCY 100000000
#define M_CONVERT_TO_MM(x) x * 1000 
#define MM_CONVERT_TO_M(x) x / 1000

#define CHECK_FAILED(x) if(!SUCCEEDED(x)) return false
#define CHECK_SUCCESS(x) if(SUCCEEDED(x)) return true
#define CHECK_INIT if (!mpGroupManager || !mpUPATools || mHardWareFailed) return false

#define MAX_TIME_WAIT_FOR_SETTING_READY 3
#define NUM_OF_ECHO_ARRAY	100

#define WAIT_FOR_SETTING_READY			::Sleep(200)
#define WAIT_FOR_SETTING_PUT			::Sleep(0)
#define WAIT_FOR_SETTING_FLUSH			::Sleep(0)
#define WAIT_FOR_NEXT_A_SCAN_DATA		::Sleep(33)

#define SET_TO_ZERO_IF_LESS(x, y)	x = x < y ? 0 : x;
#define SET_TO_ONE_IF_LESS(x, y)	x = x < y ? (x == 0 ? 0 : 1) : x;

#define COM_GATE_TO_GATE(x, y)			switch (x)\
	{\
	case COM_GATE_I:\
		y = STRUCT_GATE_SETTING::I;\
		break;\
	case COM_GATE_A:\
		y = STRUCT_GATE_SETTING::A;\
		break;\
	case COM_GATE_B:\
		y = STRUCT_GATE_SETTING::B;\
		break;\
	default:\
		y = STRUCT_GATE_SETTING::A;\
		break;\
	}

#define GATE_TO_COM_GATE(y, x)			switch (y)\
	{\
	case STRUCT_GATE_SETTING::I:\
		x = COM_GATE_I;\
		break;\
	case STRUCT_GATE_SETTING::A:\
		x = COM_GATE_A;\
		break;\
	case STRUCT_GATE_SETTING::B:\
		x = COM_GATE_B;\
		break;\
	default:\
		x = COM_GATE_A;\
		break;\
	}

class DllExport CHardwareInterface
{
public:
	CHardwareInterface(void);
	~CHardwareInterface(void);

private:
	bool mHardWareFailed;
	bool mWindowChanged;
	bool mDotChanged;
	bool mSScanRefeshed;
	bool mColorsReferBuilt;
	byte *mpImgBuf;
	long mImgWidth;
	long mImgHeight;
	float mLeftMargin;
	float mRightMargin;
	IUPAToolsPtr		mpUPATools;
	USGroupManager	*mpGroupManager;
public:
	void SetGroupManager(USGroupManager *);
	bool GetHardWareFailed() { return mHardWareFailed;  }
	void SetWindowChanged() { mWindowChanged = true; }
	void SetDotChanged() { mDotChanged = true; }
	void SetColorChanged() { mColorsReferBuilt = false; }
	bool HardWareInit(USGroupManager *);

	//////////////////////////////////////////////////////////////////////////
	// Ӳ����������
	//////////////////////////////////////////////////////////////////////////	
	bool PutWorkpieceSoundSpeed();				// ������������
	bool PutProbeSetting();						// ̽ͷ����
	bool PutWedgeSetting();						// Ш������
	bool PutFocusLawSetting();					// �۽���������
	bool PutUTSetting();							// UT����
	bool PutEncoderSetting();					// ����������
	bool PutAllGateSetting();					// բ������
private:
	bool PutGateSetting(COM_ENUM_IDX_GATE);	// բ��X����

	//////////////////////////////////////////////////////////////////////////
	// Ӳ�����ݻ�ȡ groupIndex == -1ʱ��Ĭ�Ϸ��ص�ǰ������
	//////////////////////////////////////////////////////////////////////////
public:
	bool GetAScanData(STRUCT_ASCAN_DATA *&, long groupIndex = -1);	
	bool GetBScanData(STRUCT_BSCAN_DATA *&, long groupIndex = -1);
	bool GetCScanData(STRUCT_CSCAN_DATA *&, long groupIndex = -1);
	bool GetSScanData(STRUCT_SSCAN_DATA *&, long groupIndex = -1);
	bool GetCSScanData(STRUCT_SSCAN_DATA *&, STRUCT_CSCAN_DATA *&, long groupIndex = -1);

	bool GetBScanData(STRUCT_BSCAN_DATA *&, RECT, long groupIndex = -1);	
	bool GetCScanData(STRUCT_CSCAN_DATA *&, RECT, RECT, long groupIndex = -1);
	bool GetSScanData(STRUCT_SSCAN_DATA *&, RECT, long groupIndex = -1);
	bool GetCSScanData(STRUCT_SSCAN_DATA *&, RECT, STRUCT_CSCAN_DATA *&, RECT, long groupIndex = -1);

	bool GetGateInfo();
private:
	bool SetSScanImgSize(long, long, long);						// Sɨͼ����Ϣ����
	bool SetUpSScanImg(long, float &, float &, long &, long&);	// Sɨͼ����Ϣ����
	bool SetUpSScanROI(long, float, float, float, float);			// Sɨͼ����Ϣ����
	//////////////////////////////////////////////////////////////////////////
	// ���ػ�
	//////////////////////////////////////////////////////////////////////////
public:
	bool FlushSetting();
	bool FlushAllSetting();
	bool StartSequencer();
	bool StopSequencer();

private:
	float GetTrueSoundPath(float);
	float GetTrueDepthInSScan();
	float GetTrueStartInSScan();
	bool GetAScanPosInSScan(STRUCT_ASCAN_POS_IN_SSCAN_IMG&);
	bool BuildColorsReferTable();
	bool BuildHSVColorsReferTable();
	bool SetRGBAByAmplitude(STRUCT_RGBA_DATA &, byte);
};

