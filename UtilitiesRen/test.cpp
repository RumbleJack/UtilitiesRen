#include "stdafx.h"

#include <iostream>
#include <iomanip>
using namespace std;

#include "SafeArray.h"
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
