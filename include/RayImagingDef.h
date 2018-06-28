#ifndef X_RAY_IMAGING_DEFINITION
#define X_RAY_IMAGING_DEFINITION

// 系统模式
#define MONO_ENERGY 1  // 单能系统
#define DUAL_ENERGY 2   // 双能系统

// 数据源选择
#define HE_CHNL			0		//	仅高能数据
#define LE_CHNL			1		//	仅低能数据
#define DUAL_CHNL	2		//	高低能数据融合

// 采集数据状态 ISmplLnBufFor**::AddPkg(LONG Status, ...)
#define BK_DATA						0	//	本底数据（射线源关闭）
#define ATTEN_DATA				1	//	正常过包数据（射线源开）
#define FULL_SCALE_DATA	2	//	满度数据（射线无衰减）
#define UNSTABLE_DATA		3 //	射线源不稳定（处于射线建立期）


// 图像处理模式
#define WITHOUT_ENH			0		//	无增强处理
#define NORMAL_ENH				1		//	常规增强处理
#define SUPER_ENH					2		//	超级增强处理

// 显示模式
#define GRAY_OUT					0		//	灰度图输出
#define COLOR_OUT					1		//  彩色图输出
#define ORG_STRIP					2		//	有机物剔除
#define ORG_ONLY					3		//	无机物剔除（仅有机物）
#define NEG_OUT						4		//	反色输出
#define HIGH_PENET				5		//	高穿透模式
#define ABSORPT_RANGE		6		//	仅指定衰减范围内输出（可用于衰减扫描）
#define Z_RANGE						7		//	指定等效原子序数范围输出（可用于Z扫描）

// 返回错误码定义
#define ERR_CODE						0x200
#define ERR_UNDEFINED			0x01		// 未定义
#define ERR_FAIL_CREATE			0x02		// 创建失败
#define ERR_UNINITIALIZED		0x03		// 未初始化
#define ERR_FAIL_LOAD				0x04		// 读取失败
#define ERR_FAIL_SAVE				0x05		// 保存失败
#define ERR_FULL						0x11		// 存贮满
#define ERR_EMPTY						0x12		// 存贮空
#define ERR_OCCUPIED				0x13  // 被占用
#define ERR_MISC						0x30    // 未命名错误

#define MAKE_OWN_FAIL_RESULT(x) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, ERR_CODE+x)
#define GET_OWN_FAIL_CODE(x) (HRESULT_CODE(x)-ERR_CODE)

#define DATA_SMPL unsigned short		// data type of normalized samples
#endif