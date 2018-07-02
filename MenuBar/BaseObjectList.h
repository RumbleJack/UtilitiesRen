#pragma once
#include <list>
#include "PubMacroDef.h"

using namespace std ;
template <class T_OBJ>
class CBaseObjectList :
	public list <T_OBJ>
{
public:
	CBaseObjectList(void)
	{
	}
	~CBaseObjectList(void)
	{
		DestroyAll() ;
	}
	void DestroyAll()
	{
		list <T_OBJ>::iterator Idx ;
		for(Idx = begin() ; Idx != end() ; Idx++)
		{
			if(*Idx != NULL)
				DESTROY_OBJECT(*Idx) ;
		}
		clear() ;
	}
};

