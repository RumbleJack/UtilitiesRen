/*---------------------------------------------------------------------------*/
/*-----作者：任杰文----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "PubMacroDef.h"

// 参数定义，包含超声组结构体（STRUCT_GROUP_SETTING）定义
#include  "ParamDef.h"		
#include "USCalibration.h"

// 此类是从 ConfigManager.dll 导出的
class DllExport USGroupManager {
public:
	USGroupManager(void);
	USGroupManager(USGroupManager&);
	~USGroupManager(void);

public:
	// 获取/设置当前组编号
	long GetCurGroupNum();
	bool SetCurGroupNum(long);
	USGroup *GetCurGroup();
	USGroup *GetGroupAt(long);
	// 获取当前组数量
	long GetGroupCnt();
	// 判断组是否有效
	bool IsGroupValid(long);
	//添加组
	bool AddGroup();
	//删除组
	bool DeleteGroup(long);

public:
	// 组头
	STRUCT_GROUPHEADER_SETTING GetGroupHeader();
	bool SetGroupHeader(STRUCT_GROUPHEADER_SETTING&);
	// 工件及焊缝（焊缝作为工件结构体的一个成员）
	STRUCT_WORKPIECE_SETTING GetWorkPiece();
	bool SetWorkPiece(STRUCT_WORKPIECE_SETTING&);
	// 也可以单独设置焊缝
	UNION_WELD_SETTING GetWeld();
	bool SetWeld(UNION_WELD_SETTING&);
	// 探头
	STRUCT_PROBE_SETTING GetProbe();
	bool SetProbe(STRUCT_PROBE_SETTING&);
	// 楔块
	STRUCT_WEDGE_SETTING GetWedge();
	bool SetWedge(STRUCT_WEDGE_SETTING&);
	// 探头位置
	STRUCT_PROBEPOSITION_SETTING GetProbePosition();
	bool SetProbePosition(STRUCT_PROBEPOSITION_SETTING&);
	// 聚焦法则（仅PA组）
	STRUCT_FOUCUSLAW_SETTING GetFoucusLaw();
	bool SetFoucusLaw(STRUCT_FOUCUSLAW_SETTING&);

	
private:
	// 最大组数量
	static const long mGroupCnt = 8;

	// 当前组编号，默认0
	long mCurGroupNum;
	// 指针数组，存储了所有组信息
	USGroup* mGroup[mGroupCnt];
	// 表示对应编号组是否有效
	bool mIsValid[mGroupCnt];
public:
	//校准一级菜单设置
	STRUCT_CALIBRATION_SETTING GetCalibMode(void);
	bool SetCalibMode(STRUCT_CALIBRATION_SETTING &);
};

extern DllExport int nConfigManager;

DllExport int fnConfigManager(void);
