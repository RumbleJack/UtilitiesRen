#ifndef MENU_ITEM_ID_DEFINITION
#define MENU_ITEM_ID_DEFINITION

// ���а���ID����ΪID_ICON_xxx
// ����IDȡֵ��Χ��
// ID: 0X0000 ��������ʾ���ա�
// �˵�ID : [0X0001 - 0X00FF] ���˵�������(255��)
// ��ݼ�ID ��[0x0100 - 0x011F] (������ݰ�������32����
// ������ID��[0x0120 - 0x013F] (��̬������ʾ�����İ�������32����
// ����ID: [0X0200-], ���ڶ�����������������ö�ٵ�ֵ

// ��Ч����
#define ID_ICON_EMPTY		0

// �ļ�������ð���
#define ID_ICON_FILE_SETTING	0X11		// �ļ�->����
#define ID_ICON_FILE_REPORT		0X12		// �ļ�->����
#define ID_ICON_FILE_DATA		0X13		// �ļ�->����
#define ID_ICON_FILE_IMAGE		0X14		// �ļ�->ͼ��
#define ID_ICON_FILE_DATA_SETTING	0X15	// �ļ�->��������

// ���������
#define ID_ICON_WIZARD_WORKPIECE	0X21	// ��->�����뺸��
#define ID_ICON_WIZARD_SETTING		0X22	// ��->����
#define ID_ICON_WIZARD_CORRECT		0X23	// ��->У׼

// UT�����������
#define ID_ICON_UT_BASIC		0X31	// UT����->һ��
#define ID_ICON_UT_PULSE		0X32	// UT����->���巢����
#define ID_ICON_UT_RECEIVER		0X33	// UT����->������
#define	ID_ICON_UT_BEAM			0X34	// UT����->����
#define	ID_ICON_UT_ADVANCE		0X35	// UT����->�߼�

// �����������
#define ID_ICON_MEASURE_CURSOR	0X41	// ����->���
#define ID_ICON_MEASURE_DATA	0X42	// ����->����
#define	ID_ICON_MEASURE_REPORT	0X43	// ����->ȱ�ݱ���

// ��ʾ���
#define ID_ICON_DISPLAY_SELECTION	0X51	// ��ʾ->ѡ��
#define ID_ICON_DISPLAY_VIEW		0X52	// ��ʾ->��ͼ����
#define	ID_ICON_DISPLAY_LAYER		0X53	// ��ʾ->����
#define ID_ICON_DISPLAY_ZOOM		0X54	// ��ʾ->�Ŵ�
#define	ID_ICON_DISPLAY_ATTR		0X55 	// ��ʾ->����

// ����
#define ID_ICON_ACCURACY_TYPE		0X61	// ����->����
#define ID_ICON_ACCURACY_OPERATOR	0X62	// ����->����Աģʽ
#define ID_ICON_ACCURACY_MODEL		0X63	// ����->��������
#define	ID_ICON_ACCURACY_CURVE		0X64	// ����->��������

// բ���뱨��
#define ID_ICON_GATE_ALARM_GATE		0X71	// բ���뱨��->բ��
#define ID_ICON_GATE_ALARM_ALARM	0X72	// բ���뱨��->����
#define ID_ICON_GATE_ALARM_EXPORT	0X73	// բ���뱨��->���
#define ID_ICON_GATE_ALARM_SIMULATE	0X74	// բ���뱨��->ģ��
#define	ID_ICON_GATE_ALARM_DEPTH	0X75	// բ���뱨��->���

// ��/̽ͷ�͹���
#define ID_ICON_PROBE_WORKPIECE_MANAGER		0X81	// ��/̽ͷ�͹���->�����
#define ID_ICON_PROBE_WORKPIECE_PROBE_WEDGE	0X82	// ��/̽ͷ�͹���->̽ͷ��Ш��
#define ID_ICON_PROBE_WORKPIECE_POSITION	0X83	// ��/̽ͷ�͹���->λ��
#define ID_ICON_PROBE_WORKPIECE_CHARACTER	0X84	// ��/̽ͷ�͹���->ָ������
#define ID_ICON_PROBE_WORKPIECE_WORKPIECE	0X85	// ��/̽ͷ�͹���->����
// �۽�����
#define ID_ICON_FOCUS_SETTING_SETTING	0X91	// �۽�����->����
#define ID_ICON_FOCUS_SETTING_APERTURE	0X92	// �۽�����->�׾�
#define ID_ICON_FOCUS_SETTING_BEAM		0X93	// �۽�����->����
#define ID_ICON_FOCUS_SETTING_RULE		0X94	// �۽�����->����

// ɨ��
#define ID_ICON_SCAN_IMAGE			0XA1	// ɨ��->��ͼģʽ
#define ID_ICON_SCAN_DETECT			0XA2	// ɨ��->���
#define	ID_ICON_SCAN_CODER			0XA3	// ɨ��->������
#define ID_ICON_SCAN_REGION			0XA4	// ɨ��->����
#define ID_ICON_SCAN_DATA			0XA5	// ɨ��->����
#define ID_ICON_SCAN_RUNNING		0XA6	// ɨ��->��ʼ

// ƫ��
#define ID_ICON_CUSTOM_SETTING		0XB1	// ƫ��->����
#define ID_ICON_CUSTOM_DEVICE		0XB2	// ƫ��->����
#define ID_ICON_CUSTOM_TOOLS		0XB3	// ƫ��->����

// ���˵�
#define ID_ICON_FILE_SERVER	0X01
#define ID_ICON_WIZARD		0X02
#define	ID_ICON_UT_SETTING	0X03
#define ID_ICON_MEASURE		0X04
#define ID_ICON_DISPLAY		0X05
#define ID_ICON_ACCURACY	0X06
#define	ID_ICON_GATE_ALARM	0X07
#define	ID_ICON_PROBE_WORKPIECE	0X08
#define	ID_ICON_FOCUS_SETTING	0X09
#define	ID_ICON_SCAN			0X0A
#define	ID_ICON_CUSTOM			0X0B

// ��������
#define ID_PARAM_UNDEFINED 0X0120
#define ID_PARAM_GAIN	0x0121
#define ID_PARAM_FILE	0x0122
#define ID_PARAM_GATE_IDX	0X0123
#define ID_PARAM_ECHO_AMP	0X0124
#define ID_PARAM_ECHO_DEPTH	0X0125
#define ID_PARAM_ECHO_POS	0X0126
#define ID_PARAM_BEAM_DISTANCE 0X0127

// ��ݲ˵�
#define ID_ACCEL_LAYOUT 0X101
#define ID_ACCEL_PROBE	0X102
#define ID_ACCEL_CURSOR	0X103
#define ID_ACCEL_ANGLE	0X104
#define ID_ACCEL_SETTING	0X105

// բ��ö��
#define ID_PARAM_GATE_I		0X201
#define ID_PARAM_GATE_A		0X202
#define ID_PARAM_GATE_B		0X203
#define ID_PARAM_GATE_C		0X204

// ����ö��
#define ID_ACCEL_LAYOUT_FULL_SCREEN	0X211
#define ID_ACCEL_LAYOUT_NORMAL		0X212

// ��
#endif