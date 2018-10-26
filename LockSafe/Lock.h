//Header files for Lock.cpp
//Zhaoran Wang 150382450

#include <vector>
#pragma once

using namespace std;

class Lock
{
public:
	Lock();
	~Lock();
	void OutputLockKey();
	void OutputLockSafe(char *name);
	void OutputLockFalse();
	void runLock(int rootNumber, bool mutilsafeIN);
	bool reSafe();
	bool first = false;
	vector<int> allroot;

private:
	
	vector<int> resultRoot;
	vector<int> allCN;
	vector<int> allLN;
	vector<int> allLNBackup;
	vector<int> allHN;
	int temp, incounter = 0, temsize, rootsize;
	bool tempsafe, mutilsafe;
	int *CNKey, *LNKey, *HNKey;
	int CNKeyMuSafe[5];
};

