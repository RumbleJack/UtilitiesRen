#ifndef X_RAY_IMAGING_DEFINITION
#define X_RAY_IMAGING_DEFINITION

// ϵͳģʽ
#define MONO_ENERGY 1  // ����ϵͳ
#define DUAL_ENERGY 2   // ˫��ϵͳ

// ����Դѡ��
#define HE_CHNL			0		//	����������
#define LE_CHNL			1		//	����������
#define DUAL_CHNL	2		//	�ߵ��������ں�

// �ɼ�����״̬ ISmplLnBufFor**::AddPkg(LONG Status, ...)
#define BK_DATA						0	//	�������ݣ�����Դ�رգ�
#define ATTEN_DATA				1	//	�����������ݣ�����Դ����
#define FULL_SCALE_DATA	2	//	�������ݣ�������˥����
#define UNSTABLE_DATA		3 //	����Դ���ȶ����������߽����ڣ�


// ͼ����ģʽ
#define WITHOUT_ENH			0		//	����ǿ����
#define NORMAL_ENH				1		//	������ǿ����
#define SUPER_ENH					2		//	������ǿ����

// ��ʾģʽ
#define GRAY_OUT					0		//	�Ҷ�ͼ���
#define COLOR_OUT					1		//  ��ɫͼ���
#define ORG_STRIP					2		//	�л����޳�
#define ORG_ONLY					3		//	�޻����޳������л��
#define NEG_OUT						4		//	��ɫ���
#define HIGH_PENET				5		//	�ߴ�͸ģʽ
#define ABSORPT_RANGE		6		//	��ָ��˥����Χ�������������˥��ɨ�裩
#define Z_RANGE						7		//	ָ����Чԭ��������Χ�����������Zɨ�裩

// ���ش����붨��
#define ERR_CODE						0x200
#define ERR_UNDEFINED			0x01		// δ����
#define ERR_FAIL_CREATE			0x02		// ����ʧ��
#define ERR_UNINITIALIZED		0x03		// δ��ʼ��
#define ERR_FAIL_LOAD				0x04		// ��ȡʧ��
#define ERR_FAIL_SAVE				0x05		// ����ʧ��
#define ERR_FULL						0x11		// ������
#define ERR_EMPTY						0x12		// ������
#define ERR_OCCUPIED				0x13  // ��ռ��
#define ERR_MISC						0x30    // δ��������

#define MAKE_OWN_FAIL_RESULT(x) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, ERR_CODE+x)
#define GET_OWN_FAIL_CODE(x) (HRESULT_CODE(x)-ERR_CODE)

#define DATA_SMPL unsigned short		// data type of normalized samples
#endif