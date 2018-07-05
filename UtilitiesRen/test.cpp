#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <tchar.h>
using namespace std;

#include "SafeArray.h"
#include "GetFilePath.h"
#include "test.h"

bool testSafeArray()
{
	CSafeArray<int> safeIntArray;
	cout << "SafeArraySize: " << safeIntArray.Create(100) << endl;
	for (int i = 0; i < 100; i++)
	{
		safeIntArray[i] = i * i;
	}
	cout << "SafeArrayElement: " << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << setw(8) << safeIntArray[i];
		if (i % 10 == 9)
		{
			cout << endl;
		}
	}
	return true;
}

void testGetFilePath()
{
	wchar_t folderpath[] = _T("D:\\Users\\JackRen\\Documents\\GitHub\\MineViewer\\MineViewerFileSys\\probe");
	vector<string> filepath;

	char *mbPath = new char[100];
	wcstombs_s(NULL,mbPath,100, folderpath,100);

	//获取该路径下的所有文件  
	GetFilesPath(mbPath, filepath);
	int fpsize = filepath.size();
	for (int i = 0; i < fpsize; i++)
		cout << filepath[i].c_str() << endl;

}

void wtestGetFilePath()
{
	wchar_t folderpath[] = _T("D:\\Users\\JackRen\\Documents\\GitHub\\MineViewer\\MineViewerFileSys\\probe");
	vector<wstring> filepath;

	//获取该路径下的所有文件  
	locale::global(locale(""));// 设置本地化字符环境(输出显示、与多字节字符集转化需要语句)
	//locale::global(locale("C"));// 恢复默认字符环境
	wGetFilesPath(folderpath, filepath);
	int fpsize = filepath.size();
	for (int i = 0; i < fpsize; i++)
		wcout << filepath[i] << endl;
}
