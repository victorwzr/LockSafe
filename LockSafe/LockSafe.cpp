// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version

#include "stdafx.h"
#include "random.h"
#include "time.h"
#include "Lock.h"
#include "windows.h"
#include <iostream>




using namespace std;
/*
double timeWin = 0;;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
*/
bool cusafe = false;
int rootNumber;

int main()
{
	//QueryPerformanceFrequency(&nFreq);
	//QueryPerformanceCounter(&nBeginTime);
	srand((int)time(0));                    //random seed
	Lock *l = new Lock();
	cout << "How many root required?" << endl;
	cin >> rootNumber;
	while (cusafe == false) {
		l->runLock(rootNumber);                                //progrom enter
		cusafe = l->reSafe();
	}
	l->OutputLockKey();             //Output
	l->OutputLockSafe();
	l->OutputLockFalse();
	//QueryPerformanceCounter(&nEndTime);
	//timeWin = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	//cout << "running time" << timeWin << endl;
	return 0;
}

