#include "stdafx.h"

#include <iostream>
#include <iomanip>
using namespace std;

#include "PubMacroDef.h"
#include "test.h"

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

	system("pause");
}