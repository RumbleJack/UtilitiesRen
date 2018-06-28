/*---------------------------------------------------------------------------*/
/*-----���ߣ��ν���----------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#pragma once
#include "GateAlarmDef.h"
#include "ScanDataDef.h"

// �������ݵĽ���ˮƽ
struct STRUCT_DISPLAY_UT_SETTING
{
	STRUCT_DISPLAY_UT_SETTING()
	{
		UTMode = UT_MODE_SOUNDPATH;
		TrueDepthMode = ALL_LAWS;
		UnitStyle = UT_UNIT_STYLE_DISTANCE;
	}
	enum ENUM_UT_MODE:long{
		UT_MODE_REALDEPTH = 0, UT_MODE_SOUNDPATH, UT_MODE_UNCORRECTED
	};
	ENUM_UT_MODE UTMode;// ѡ����ͼ������ʾ�ĳ������ݵĽ���ˮƽ����ѡ��ʵ��ȡ����̡�δ��������PA��
	enum ENUM_TRUE_DEPTH_MODE :long{
		CURRENT_LAW = 0, ALL_LAWS
	};
	ENUM_TRUE_DEPTH_MODE TrueDepthMode;// ��UTModeѡ����ʵ��ȣ���ΪPAģʽ���ò�����Ч����ѡȫ���۽����򡢵�ǰ�۽�����
	enum ENUM_UNIT_STYLE :long {
		UT_UNIT_STYLE_TIME = 0, UT_UNIT_STYLE_DISTANCE
	};
	ENUM_UNIT_STYLE UnitStyle;// ��UTModeѡ�����̡�δ��������PA��ʱ��Ч����ʵ��ȿ�ѡʱ������
};

// Aɨ������
struct STRUCT_DISPLAY_ASCAN_SETTING
{
	long AScanDataSrc;// ѡ����ʾ��Aɨ����ͼ�е�һ��Aɨ�����Aɨ�����ϡ���ѡ��������ߡ����ȫ������ȡ�
	long Color;// Aɨ����ɫ
	long Exterior;// ��ۡ���ѡ�пա���䡢�п�������ɫ�����������ɫ

};
// Cɨ������
struct STRUCT_DISPLAY_CSCAN_SETTING
{
	long CScanDataSrc;// ѡ��Cɨ���Դ����ѡA%, B%I / ��ȣ�����1:1
};
// ���߸�������
struct STRUCT_DISPLAY_SOUNDTRACE_SETTING
{
	long StepNum;// �������߸��ٵ��п����Ŀ
	float Magnification;// �Ŵ���������Բ�����Ϊ���ķŴ�

};
struct STRUCT_DCOVER_CURSOR_SETTING
{
	BOOL Cursor[2];// ������Ҫ��ʾ�Ĺ�꣺�ο���ꡢ�������
	BOOL Value;// �Ƿ��ڹ��λ����ʾ��ֵ
	BOOL AScan;// ��Aɨ����ͼ���Ͻ���ʾ���λ�ô�Aɨ����ֵ

};
struct STRUCT_DCOVER_ASCAN_SETTING
{
	BOOL Envelope;// ����
	long QuanCurve;// 	�������� : DAC��TCG��DGS
	BOOL TCGGainCurve;// 	TCG��������(����)��������Ҳ����
	BOOL RefAmp;// 	�ο�����
	BOOL Raster;// դ��

};
struct STRUCT_DCOVER_INDICATOR_SETTING
{
	BOOL Weld;// 	����
	BOOL Step;// 	��
};
//��������
struct STRUCT_DISPLAY_COVER_SETTING
{
	STRUCT_DISPLAY_COVER_SETTING()
	{
		for (int i = 0; i < STRUCT_GATE_SETTING::GATE_NUM; i++)
		{
			Gate[i] = TRUE;
		}
	}
	BOOL Gate[STRUCT_GATE_SETTING::GATE_NUM];// ������Ҫ��ʾ��բ�ţ�A��B��I��
	STRUCT_DCOVER_CURSOR_SETTING DCoverCursor;// 	���
	STRUCT_DCOVER_ASCAN_SETTING DCoverAScan;// Aɨ��
	STRUCT_DCOVER_INDICATOR_SETTING DCoverIndicator;// ָʾ��
};

// α��ɫ
struct STRUCT_DISPLAY_COLOR
{
	STRUCT_DISPLAY_COLOR()
	{
		ColorRGBA.SetRGBA(255, 255, 255, 1);
		StartAmplitude = 0;
		EndAmplitude = 10;
	}
	bool operator == (STRUCT_DISPLAY_COLOR& other)
	{
		if (ColorRGBA == other.ColorRGBA
			&& StartAmplitude == other.StartAmplitude
			&& EndAmplitude == other.EndAmplitude)
			return true;
		else
			return false;
	}
	STRUCT_RGBA_DATA ColorRGBA;
	LONG StartAmplitude;
	LONG EndAmplitude;
};

// ��������
struct STRUCT_DISPLAY_ATTRIBUTE_SETTING
{
	STRUCT_DISPLAY_ATTRIBUTE_SETTING()
	{
		ColorNum = 4;
		pColors = new STRUCT_DISPLAY_COLOR[ColorNum];

		pColors[0].ColorRGBA.SetRGBA(255, 255, 255, 1);
		pColors[0].StartAmplitude = 0;
		pColors[0].EndAmplitude = 50;

		pColors[1].ColorRGBA.SetRGBA(0, 0, 255, 1);
		pColors[1].StartAmplitude = 50;
		pColors[1].EndAmplitude = 80;

		pColors[2].ColorRGBA.SetRGBA(0, 255, 0, 1);
		pColors[2].StartAmplitude = 80;
		pColors[2].EndAmplitude = 100;

		pColors[3].ColorRGBA.SetRGBA(255, 0, 0, 1);
		pColors[3].StartAmplitude = 100;
		pColors[3].EndAmplitude = 100;

		mpColorsRefer = new STRUCT_RGBA_DATA[NUM_OF_COLORS];
	}
	~STRUCT_DISPLAY_ATTRIBUTE_SETTING()
	{
		if (pColors)
			delete []pColors;
		pColors = NULL;
		if (mpColorsRefer)
			delete []mpColorsRefer;
		mpColorsRefer = NULL;
		ColorNum = 0;
	}
	bool operator==(STRUCT_DISPLAY_ATTRIBUTE_SETTING& other)
	{
		for (int i = 0; i < NUM_OF_COLORS; i++)
		{
			if (!(mpColorsRefer[i] == other.mpColorsRefer[i]))
				return false;
		}
		return true;
	}
	STRUCT_DISPLAY_ATTRIBUTE_SETTING(const STRUCT_DISPLAY_ATTRIBUTE_SETTING& other)
	{
		ColorNum = other.ColorNum;
		pColors = new STRUCT_DISPLAY_COLOR[other.ColorNum];
		memcpy(pColors, other.pColors, sizeof(STRUCT_DISPLAY_COLOR)*other.ColorNum);

		mpColorsRefer = new STRUCT_RGBA_DATA[NUM_OF_COLORS];
		memcpy(mpColorsRefer, other.mpColorsRefer, sizeof(STRUCT_RGBA_DATA)*NUM_OF_COLORS);
	}
	STRUCT_DISPLAY_COLOR *pColors;
	LONG ColorNum;
	STRUCT_RGBA_DATA *mpColorsRefer;
};

enum ENUM_LAYOUT_STYLE :long
{
	LAYOUT_STYLE_A,
	LAYOUT_STYLE_B,
	LAYOUT_STYLE_C,
	LAYOUT_STYLE_S,
	LAYOUT_STYLE_R,
	LAYOUT_STYLE_A_S,
	LAYOUT_STYLE_A_C,
	LAYOUT_STYLE_A_C_S,
	LAYOUT_STYLE_A_C_R_S,
};

struct STRUCT_DISPLAY_SETTING
{
	STRUCT_DISPLAY_SETTING()
	{
		GroupNum = 0;
		IsFullScrenn = false;
		IsAllGroup = false;
		Layout = LAYOUT_STYLE_A_C_S;
	}
	long GroupNum;// ָ����ǰ��ʾ����
	BOOL IsFullScrenn;//  �Ƿ�ȫ��
	BOOL IsAllGroup;	//�Ƿ���ʾ����
	
	ENUM_LAYOUT_STYLE Layout;// ָ����ǰ������ͼ�����з�ʽ����ѡ��ʾ��A��B��C��S��R�����������ֻ�����ɨ������
	STRUCT_DISPLAY_UT_SETTING DisplayUT;// �������ݵĽ���ˮƽ
	STRUCT_DISPLAY_ASCAN_SETTING DisplayAScan;// Aɨ������
	STRUCT_DISPLAY_CSCAN_SETTING DisplayCScan;// Cɨ������
	STRUCT_DISPLAY_SOUNDTRACE_SETTING DisplaySoundBeam;// ���߸�������
	STRUCT_DISPLAY_COVER_SETTING DisplayCover;// ��������
	STRUCT_DISPLAY_ATTRIBUTE_SETTING DisplayAttribute;	// ��������
};