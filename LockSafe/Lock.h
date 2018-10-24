#pragma once
class Lock
{
public:
	Lock();
	~Lock();
	void OutputLockKey();
	void OutputLockSafe();
	void OutputLockFalse();
	void runLock(int rootNumber);
	bool reSafe();

private:
	int Runroot;
	int temp, incounter = 0, temsize, rootsize;
	bool tempsafe, first = true;
	int *CNKey, *LNKey, *HNKey;
	int CNKeyMuSafe[5];
};

