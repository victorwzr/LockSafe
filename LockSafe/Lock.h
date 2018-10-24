#pragma once
class Lock
{
public:
	Lock();
	~Lock();
	void OutputLockKey();
	void OutputLockSafe();
	void OutputLockFalse();
	void runLock();
	bool reSafe();

private:
	int Runroot;
	int temp, incounter = 0;
	bool tempsafe, first = true;
	int *CNKey, *LNKey, *HNKey;
};

