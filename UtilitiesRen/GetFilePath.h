#pragma once
//getFilepath.h

/*-------------------------------------------------*/
/* ---------------------调用示例-------------------
//main.cpp
#include "getFilepath.h"
#include <iostream>
using namespace std;
int main()
{
	char folderpath[] = "D:\\Users\\jackren\\documents\\visual studio 2013\\Projects\\recFilePath\\recFilePath";
	vector<string> filepath;

	//获取该路径下的所有文件  
	GetFilesPath(folderpath, filepath);
	int fpsize = filepath.size();
	for (int i = 0; i < fpsize; i++)
		cout << filepath[i].c_str() << endl;
	system("pause");
}
---------------------------------------------------*/
void GetFilesPath(string folderpath, vector<string>& filespath);
void wGetFilesPath(wstring folderpath, vector<wstring>& filespath);
/*-------------------------------------------------*/