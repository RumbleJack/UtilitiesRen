#ifndef GLOBAL_MESSAGE_DEFINITION
#define GLOBAL_MESSAGE_DEFINITION

#define WM_BASE WM_USER+0X200
#define WM_MENU_EXIT			WM_BASE+0X10	// �����˳�
#define WM_MENU_ITEM_CLICKED	WM_BASE+0X11	// �˵��ѡ��
#define WM_MENU_ACCEL_KEY_CLICKED	WM_BASE+0X12  // ��ݼ���ѡ��
#define WM_MENU_PARAM_MODIFIED	WM_BASE+0X13  // �������������޸�

#define WM_SCAN_ITEM_CLICKED    WM_BASE+0X20  // ɨ����ͼ��ѡ��
#define WM_GET_A_SCAN_DATA		WM_USER + 0X21 // ��ȡAɨ������
#define WM_GET_S_SCAN_DATA		WM_USER + 0X22 // ��ȡSɨ������
#define WM_GET_SCAN_DATA		WM_USER + 0X23 // ��ȡɨ������
#endif