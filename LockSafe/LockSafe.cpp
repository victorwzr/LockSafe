// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version

#include "stdafx.h"
#include "random.h"
#include "time.h"
#include "Lock.h"
#include "Locked.h"
#include "windows.h"
#include <iostream>

Locked *led = new Locked();


using namespace std;

double timeWin = 0;;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;

bool cusafe = false;
int rootNumber, backUHF, backPHF, backLHF;
char second;

int main()
{
	srand((int)time(0));                    //random seed
	Lock *l = new Lock();
	cout << "How many root required?(with bouns)" << endl;
	cin >> rootNumber;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);
	while (cusafe == false) {
		l->runLock(rootNumber);                                //progrom enter
		cusafe = l->reSafe();
	}
	l->OutputLockKey();             //Output
	l->OutputLockSafe();
	l->OutputLockFalse();
	QueryPerformanceCounter(&nEndTime);
	timeWin = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	cout << "running time" << timeWin << endl;

	cout << "start break lock(with bouns)(Y/N)" << endl;
	cin >> second;
	if (second == 'Y') {
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		led->setLock();
		led->setPHF();
		led->setHN();
		led->runCN(true);
		led->setLHF();
		backUHF = led->reUHF();
		backPHF = led->rePHF();
		backLHF = led->reLHF();
		cout << "UHF is : " << backUHF << "  LHF is: " << led->reLHF() << "  PHF is : " << backPHF << endl;;
		QueryPerformanceCounter(&nEndTime);
		timeWin = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		cout << "running time" << timeWin << endl;
	}
	else {
		if (second == 'N') {
			
		}
		else {
			cout << "Error input" << endl;
		}
	}

	cout << "Program finsish" << endl;
	system("pause");
	return 0;
}

