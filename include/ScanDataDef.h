#pragma once
#define ASCANDATA_MAX_VALUE 512

#define NUM_OF_COLORS			256
#define NUM_OF_H_IN_HSV		360
#define H_OF_BLUE_HSV			240
#define H_OF_GREEN_HSV		120
#define H_OF_RED_HSV			0
#define H_OF_PINK_HSV			300

struct STRUCT_HSV_DATA
{
	void SetHSV(float h, float s, float v)
	{
		H = h;
		S = s;
		V = v;
	}

	STRUCT_HSV_DATA& operator=(STRUCT_HSV_DATA& other)
	{
		SetHSV(other.H, other.S, other.V);
		return *this;
	}

	float H;
	float S;
	float V;
};

struct STRUCT_RGBA_DATA
{
	void SetRGBA(byte r, byte g, byte b, byte a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	void SetFromHSV(STRUCT_HSV_DATA& hsv)
	{
		float h = hsv.H;
		float s = hsv.S;
		float v = hsv.V;
		float f, p, q, t;
		int i, intV, intT, intP, intQ;
		byte r, g, b;

		h /= 60;
		i = (int)floor(h);
		f = h - i;
		p = v * (1 - s);
		q = v * (1 - s * f);
		t = v * (1 - s * (1 - f));

		v *= (NUM_OF_COLORS - 1);
		t *= (NUM_OF_COLORS - 1);
		p *= (NUM_OF_COLORS - 1);
		q *= (NUM_OF_COLORS - 1);
		intV = (int)v;
		intT = (int)t;
		intP = (int)p;
		intQ = (int)q;

		switch (i) {
		case 0:
			r = (byte)intV;
			g = (byte)intT;
			b = (byte)intP;
			break;
		case 1:
			r = (byte)intQ;
			g = (byte)intV;
			b = (byte)intP;
			break;
		case 2:
			r = (byte)intP;
			g = (byte)intV;
			b = (byte)intT;
			break;
		case 3:
			r = (byte)intP;
			g = (byte)intQ;
			b = (byte)intV;
			break;
		case 4:
			r = (byte)intT;
			g = (byte)intP;
			b = (byte)intV;
			break;
		default:
			r = (byte)intV;
			g = (byte)intP;
			b = (byte)intQ;
			break;
		}
		
		SetRGBA(r, g, b, 1);
	}

	STRUCT_RGBA_DATA& operator=(STRUCT_RGBA_DATA& other)
	{
		SetRGBA(other.R, other.G, other.B, other.A);
		return *this;
	}
	
	bool operator ==(STRUCT_RGBA_DATA& other)
	{
		if (R == other.R
			&&G == other.G
			&&B == other.B
			&&A == other.A)
			return true;
		else
			return false;
	}
	
	byte R;
	byte G;
	byte B;
	byte A;
};

struct STRUCT_ASCAN_DATA
{
	STRUCT_ASCAN_DATA()
	{
		Data = NULL;
		DataSize = 0;
		SquintAngle = 0.0f;
		IncidentPoint = 0.0f;
	}
	~STRUCT_ASCAN_DATA()
	{
		if (Data != NULL)
		{
			delete Data;
			Data = NULL;
		}
	}

	void Init()
	{
		Data = NULL;
		DataSize = 0;
	}
	// һά���飬����ֵΪ����
	short*	Data;
	// �����С
	long	DataSize;
	// �����봹ֱ�ڹ������淽��ļн�
	float	SquintAngle;
	// �������䵽�Լ���λ��
	float	IncidentPoint;
};

struct STRUCT_BSCAN_DATA
{
	STRUCT_BSCAN_DATA()
	{
		pImgBuf = NULL;
		ImgWidth = 0;
		ImgHeight = 0;
	}
	~STRUCT_BSCAN_DATA()
	{
		if (pImgBuf)
		{
			delete pImgBuf;
			pImgBuf = NULL;
		}
	}

	void Init()
	{
		//������ά����
		pImgBuf = NULL;
		ImgWidth = 0;
		ImgHeight = 0;
		LeftMargin = 0.0f;
		RightMargin = 0.0f;
	}
	void Recycle()
	{
		if (pImgBuf != NULL)
			delete[]pImgBuf;
		pImgBuf = NULL;
	}

	//���ݸ���
	long BufSize;
	byte * pImgBuf;
	long ImgWidth;
	long ImgHeight;
	// ɨ���������߽�λ��
	float LeftMargin;
	// ɨ��������ұ߽�λ��
	float RightMargin;
};

struct STRUCT_CSCAN_DATA
{
	STRUCT_CSCAN_DATA()
	{
		pImgBuf = NULL;
		LeftMargin = 0.0f;
		RightMargin = 0.0f;
	}
	~STRUCT_CSCAN_DATA()
	{
		if (pImgBuf)
		{
			delete pImgBuf;
			pImgBuf = NULL;
		}
	}

	void Init()
	{
		//������ά����
		pImgBuf = NULL;
		LeftMargin = 0.0f;
		RightMargin = 0.0f;
	}
	void Recycle()
	{
		if (pImgBuf != NULL)
			delete []pImgBuf;
		pImgBuf = NULL;
	}

	//���ݸ���
	long BufSize;
	byte * pImgBuf;
	// ɨ���������߽�λ��
	float LeftMargin;
	// ɨ��������ұ߽�λ��
	float RightMargin;
};

struct STRUCT_ASCAN_POS_IN_SSCAN_IMG
{
	STRUCT_ASCAN_POS_IN_SSCAN_IMG()
	{
		SquintAngle = 0.0f;
		StartHorzPosInSScan = 0.0f;
		EndDepthInSScan = 0.0f;
		EndHorzPosInSScan = 0.0f;
	}
	void Init()
	{
		SquintAngle = 0.0f;
		StartHorzPosInSScan = 0.0f;
		EndDepthInSScan = 0.0f;
		EndHorzPosInSScan = 0.0f;
	}
	
	// �����봹ֱ�ڹ������淽��ļн�
	float	SquintAngle;
	// Aɨ������Sɨͼ���λ��
	float	StartHorzPosInSScan;		// ��ʼˮƽλ��
	float	EndDepthInSScan;			// �յ㴹ֱλ��
	float	EndHorzPosInSScan;		// �յ�ˮƽλ��
};

struct STRUCT_SSCAN_DATA
{
	STRUCT_SSCAN_DATA()
	{
		pImgBuf = NULL;
		ImgWidth = 0;
		ImgHeight = 0;
		LeftMargin = 0.0f;
		RightMargin = 0.0f;
	}
	~STRUCT_SSCAN_DATA()
	{
		if (pImgBuf)
		{
			delete pImgBuf;
			pImgBuf = NULL;
		}
	}
	void Init()
	{
		//������ά����
		pImgBuf = NULL;
		ImgWidth = 0;
		ImgHeight = 0;
		LeftMargin = 0.0f;
		RightMargin = 0.0f;
	}
	void Recycle()
	{
		if (pImgBuf != NULL)
			delete []pImgBuf;
		pImgBuf = NULL;
	}
	
	//���ݸ���
	long BufSize;
	byte * pImgBuf;
	long ImgWidth;
	long ImgHeight;
	// ɨ��������ϱ߽�λ��
	float TopMargin;
	// ɨ��������±߽�λ��
	float BottomMargin;
	// ɨ���������߽�λ��
	float LeftMargin;
	// ɨ��������ұ߽�λ��
	float RightMargin;
	// Aɨ��������Sɨͼ��λ��
	STRUCT_ASCAN_POS_IN_SSCAN_IMG AScanPos;
};