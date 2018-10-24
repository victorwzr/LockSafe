#pragma once
#include <vector>
using namespace std;
class HashFunction
{
public:
	HashFunction();
	~HashFunction();
	void setHashing(int caseNum);
	void setHashRoot(int caseChar);
	void setBaseRoot(vector <int>&allrootB);
	int getHshing();
	void setKey();
	int* outputKeyCN();
	int* outputKeyLN();
	int* outputKeyHN();
	int outputRoot();
	
private:
	int temRoot;
	int rootA, rootB, rootC, rootD;
	int* CNkeyP,* LNkeyP,* HNkeyP;
	int CNkey[4], LNkey[4], HNkey[4];
	int CN, LN, HN, reNum;
};

