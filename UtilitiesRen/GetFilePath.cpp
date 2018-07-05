//getFilepath.cpp

#include "stdafx.h"

#include<io.h>
#include<string>
#include<vector>
#include <tchar.h>
using namespace std;

#include "getFilepath.h"

void GetFilesPath(string folderpath, vector<string>& filespath)
{
	//文件句柄 ,文件信息   
	long   hFile = 0;
	struct _finddata_t *fileinfo = new _finddata_t;
	string pathPrefix;

	if ((hFile = _findfirst(pathPrefix.assign(folderpath).append("\\*").c_str(), fileinfo)) != -1) {
		do {
			//如果是子目录,递归查找子文件夹
			if ((fileinfo->attrib &  _A_SUBDIR)) {
				if (strcmp(fileinfo->name, ".") != 0 && strcmp(fileinfo->name, "..") != 0)
					GetFilesPath(pathPrefix.assign(folderpath).append("\\").append(fileinfo->name), filespath);
			}
			//如果是文件，则加入查找结果
			else {
				filespath.push_back(pathPrefix.assign(folderpath).append("\\").append(fileinfo->name));
			}
		} while (_findnext(hFile, fileinfo) == 0);
		//通过句柄关闭当前目录查找
		_findclose(hFile);
	}
}

void wGetFilesPath(wstring folderpath, vector<wstring>& filespath)
{
	//文件句柄 ,文件信息   
	long   hFile = 0;
	struct _wfinddata_t *fileinfo = new _wfinddata_t;
	wstring pathPrefix;

	if ((hFile = _wfindfirst(pathPrefix.assign(folderpath).append(_T("\\*")).c_str(), fileinfo)) != -1) {
		do {
			//如果是子目录,递归查找子文件夹
			if ((fileinfo->attrib &  _A_SUBDIR)) {
				if (wcscmp(fileinfo->name, _T(".")) != 0 && wcscmp(fileinfo->name, _T("..")) != 0)
					wGetFilesPath(pathPrefix.assign(folderpath).append(_T("\\")).append(fileinfo->name), filespath);
			}
			//如果是文件，则加入查找结果
			else {
				filespath.push_back(pathPrefix.assign(folderpath).append(_T("\\")).append(fileinfo->name));
			}
		} while (_wfindnext(hFile, fileinfo) == 0);
		//通过句柄关闭当前目录查找
		_findclose(hFile);
	}
}
