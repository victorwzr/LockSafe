#pragma once
class Lock
{
public:
	Lock();
	~Lock();
	void setLock();
	int* getLockKey();
	void runLock();
	bool reSafe();

private:
	int Runroot;
	int temp, counter = 0, incounter = 0;
	bool tempsafe, first = true;
	int CNKey[4], LNKey[4], HNKey[4];
};

