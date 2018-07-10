#include "stdafx.h"

#include <tchar.h>
#include <iostream>
#include <iomanip>
using namespace std;

#include "PubMacroDef.h"
#include "test.h"
#include "BMPSaveWnd.h"

int main()
{
	// ≤‚ ‘º∆ ±∫Ø ˝”ÎCSafeArray
	double TimeCostInMicrosecond = 0;
	PREPARE_TIME_COST();
	BEGIN_TIME_COST();
	testSafeArray();
	END_TIME_COST(TimeCostInMicrosecond);
	cout << "Time Cost: " << TimeCostInMicrosecond << endl;

	// ≤‚ ‘testGetFilePath
	cout << "≤‚ ‘GetFilePath: "<< endl;
	testGetFilePath();
	cout << endl;
	cout << "≤‚ ‘wGetFilePath: " << endl;
	wtestGetFilePath();
	cout << endl;

	// ≤‚ ‘∆¡ƒªΩÿÕº
	SavaWndBMP("D:\\Users\\JackRen\\Documents\\GitHub\\MineViewer\\MineViewerFileSys\\img\\test.bmp");

	system("pause");
}