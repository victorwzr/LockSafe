// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version with most function, combined version, break part code independt from cw1 part
//Main program enter point

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
LARGE_INTEGER nBeginTime;                       //timer
LARGE_INTEGER nEndTime;

bool cusafe;
bool runProgram = true;
bool mutilsafe = false;
int rootNumber, backUHF, backPHF, backLHF, choose, sets;                 //mian variables
char second;

int main()
{
	srand((int)time(0));                    //random seed
	Lock *l = new Lock();

	while (runProgram == true) {                                   //menu
		cout << "Enter the number to choose" << endl;
		cout << "1. Run inital for CourseWork 1, get key mutli safe and lock safe" << endl;
		cout << "2. Break lock" << endl;
		cout << "3. Re Gen Mutil safe by key" << endl;
		cout << "4. Re Gen Key and Mutil safe by Break Lock" << endl;
		cin >> choose;

		switch (choose) {                          //get first set lock and files
		case 1:
			cusafe = false;
			cout << "How many root required?" << endl;
			cin >> rootNumber;
			cout << "With bouns? (Y/N)" << endl;
			cin >> second;
			if (second == 'Y') {
				mutilsafe = true;
			}
			else {
				if (second == 'N') {
					mutilsafe = false;
				}
				else {
					cout << "Error input, run as NO" << endl;
				}
			}
			l->first = true;
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBeginTime);
			while (cusafe == false) {
				l->runLock(rootNumber, mutilsafe);                                //progrom enter
				cusafe = l->reSafe();
			}
			l->OutputLockKey();             //Output
			l->OutputLockSafe("multi-safe.txt");
			l->OutputLockFalse();
			l->~Lock();
			QueryPerformanceCounter(&nEndTime);
			timeWin = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
			cout << "running time" << timeWin << endl;
			break;
		case 2:                              //Break lock with bouns
			cout << "start break lock(with bouns)(Y/N)" << endl;
			cin >> second;
			cout << "How many sets of locks got?" << endl;
			cin >> sets;
			if (second == 'Y') {
				QueryPerformanceFrequency(&nFreq);
				QueryPerformanceCounter(&nBeginTime);
				led->setLock(sets);
				led->setPHF();
				led->setHN();
				led->runCN(true);
				led->setLHF();
				backUHF = led->reUHF();
				backPHF = led->rePHF();
				backLHF = led->reLHF();
				cout << "UHF is : " << backUHF << "  LHF is: " << led->reLHF() << "  PHF is : " << backPHF << endl;;             //out put right key to screen
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
			cout << "read in key and re generate mutilsafe? (with bouns)(Y/N)" << endl;                               //read key file to get valid mutlisafe file
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
			cout << "use breaked key to re generate mutilsafe? (with bouns)(Y/N)" << endl;                 //rebuild lock after break
			cin >> second;
			cout << "How many sets of locks got?" << endl;
			cin >> sets;
			if (second == 'Y') {
				led->setLock(sets);
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

