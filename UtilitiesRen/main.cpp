#include "stdafx.h"

#include <iostream>
#include <iomanip>
using namespace std;

#include "PubMacroDef.h"
#include "test.h"

int main()
{
	// 测试计时函数与CSafeArray
	double TimeCostInMicrosecond = 0;
	PREPARE_TIME_COST();
	BEGIN_TIME_COST();
	testSafeArray();
	END_TIME_COST(TimeCostInMicrosecond);
	cout << "Time Cost: " << TimeCostInMicrosecond << endl;
	system("pause");
}