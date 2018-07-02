#pragma once
#include "PubMacroDef.h"

class DllExport CMiscFunc
{
public:
	CMiscFunc(void);
	~CMiscFunc(void);

public :
	template <class T_DATA>
	static void XchgVar(T_DATA &x, T_DATA &y)
	{
		T_DATA Tmp = x ;
		x = y ;
		y = x ;
	}

};

