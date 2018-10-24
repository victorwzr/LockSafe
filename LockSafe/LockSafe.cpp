// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version

#include "stdafx.h"
#include "random.h"
#include "time.h"
#include "Lock.h"




using namespace std;

bool cusafe = false;

int main()
{
	srand((int)time(0));                    //random seed
	Lock *l = new Lock();                       
	while (cusafe == false) {
		l->runLock();                                //progrom enter
		cusafe = l->reSafe();
	}
	l->OutputLockKey();             //Output
	l->OutputLockSafe();
	l->OutputLockFalse();

	return 0;
}

