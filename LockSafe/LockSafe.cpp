// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version

#include "stdafx.h"
#include "random.h"
#include "time.h"
#include "Lock.h"
#include "Locked.h"
#include "windows.h"
#include <iostream>
#include "reGenerate.h"

Locked *led = new Locked();
reGenerate *reG = new reGenerate();

using namespace std;

double timeWin = 0;;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;

bool cusafe = false;
bool runProgram = true;
int rootNumber, backUHF, backPHF, backLHF, choose;
char second;

int main()
{
	srand((int)time(0));                    //random seed
	Lock *l = new Lock();

	while (runProgram == true) {
		cout << "Enter the number to choose" << endl;
		cout << "1. Run inital for CourseWork 1, get key mutli safe and lock safe" << endl;
		cout << "2. Break lock" << endl;
		cout << "3. Re Gen Mutil safe by key" << endl;
		cout << "4. Re Gen Key and Mutil safe by Break Lock" << endl;
		cin >> choose;

		switch (choose) {
		case 1:
			cout << "How many root required?(with bouns)" << endl;
			cin >> rootNumber;
			l->first = true;
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBeginTime);
			while (cusafe == false) {
				l->runLock(rootNumber);                                //progrom enter
				cusafe = l->reSafe();
			}
			l->OutputLockKey();             //Output
			l->OutputLockSafe("multi-safe.txt");
			l->OutputLockFalse();
			QueryPerformanceCounter(&nEndTime);
			timeWin = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
			cout << "running time" << timeWin << endl;
			break;
		case 2:
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
			break;
		case 3:
			cout << "read in key and re generate mutilsafe? (with bouns)(Y/N)" << endl;
			cin >> second;
			if (second == 'Y') {
				reG->readFile();
				reG->hashLock();
			}
			else {
				if (second == 'N') {

				}
				else {
					cout << "Error input" << endl;
				}
			}
			break;
		case 4:
			cout << "use breaked key to re generate mutilsafe? (with bouns)(Y/N)" << endl;
			cin >> second;
			if (second == 'Y') {
				led->setLock();
				led->setPHF();
				led->setHN();
				led->runCN(true);
				led->setLHF();
				led->reBuiltLock();
			}
			else {
				if (second == 'N') {

				}
				else {
					cout << "Error input" << endl;
				}
			}
			break;
		}
		
		runProgram = false;

		cout << "Program finsish" << endl;
		cout << "Run again? (Y/N)" << endl;
		cin >> second;
		if (second == 'Y') {
			runProgram = true;
		}
		else {
			if (second == 'N') {

			}
			else {
				cout << "Error input" << endl;
			}
		}
	}




	return 0;
}

