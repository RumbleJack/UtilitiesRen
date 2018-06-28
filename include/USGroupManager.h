/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "PubMacroDef.h"

// �������壬����������ṹ�壨STRUCT_GROUP_SETTING������
#include  "ParamDef.h"		
#include "USCalibration.h"

// �����Ǵ� ConfigManager.dll ������
class DllExport USGroupManager {
public:
	USGroupManager(void);
	USGroupManager(USGroupManager&);
	~USGroupManager(void);

public:
	// ��ȡ/���õ�ǰ����
	long GetCurGroupNum();
	bool SetCurGroupNum(long);
	USGroup *GetCurGroup();
	USGroup *GetGroupAt(long);
	// ��ȡ��ǰ������
	long GetGroupCnt();
	// �ж����Ƿ���Ч
	bool IsGroupValid(long);
	//�����
	bool AddGroup();
	//ɾ����
	bool DeleteGroup(long);

public:
	// ��ͷ
	STRUCT_GROUPHEADER_SETTING GetGroupHeader();
	bool SetGroupHeader(STRUCT_GROUPHEADER_SETTING&);
	// ���������죨������Ϊ�����ṹ���һ����Ա��
	STRUCT_WORKPIECE_SETTING GetWorkPiece();
	bool SetWorkPiece(STRUCT_WORKPIECE_SETTING&);
	// Ҳ���Ե������ú���
	UNION_WELD_SETTING GetWeld();
	bool SetWeld(UNION_WELD_SETTING&);
	// ̽ͷ
	STRUCT_PROBE_SETTING GetProbe();
	bool SetProbe(STRUCT_PROBE_SETTING&);
	// Ш��
	STRUCT_WEDGE_SETTING GetWedge();
	bool SetWedge(STRUCT_WEDGE_SETTING&);
	// ̽ͷλ��
	STRUCT_PROBEPOSITION_SETTING GetProbePosition();
	bool SetProbePosition(STRUCT_PROBEPOSITION_SETTING&);
	// �۽����򣨽�PA�飩
	STRUCT_FOUCUSLAW_SETTING GetFoucusLaw();
	bool SetFoucusLaw(STRUCT_FOUCUSLAW_SETTING&);

	
private:
	// ���������
	static const long mGroupCnt = 8;

	// ��ǰ���ţ�Ĭ��0
	long mCurGroupNum;
	// ָ�����飬�洢����������Ϣ
	USGroup* mGroup[mGroupCnt];
	// ��ʾ��Ӧ������Ƿ���Ч
	bool mIsValid[mGroupCnt];
public:
	//У׼һ���˵�����
	STRUCT_CALIBRATION_SETTING GetCalibMode(void);
	bool SetCalibMode(STRUCT_CALIBRATION_SETTING &);
};

extern DllExport int nConfigManager;

DllExport int fnConfigManager(void);
