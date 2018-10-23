#pragma once
#include <vector>

using namespace std;



class random
{
public:
	random();
	~random();
	int getRoot();
	void chooseRoot(vector<int>&allrootC);
	int* getHashKey();
	void setHashKey();
	vector<int> allroot;

private:
	int ran;
	int rootNumber, root, symbol;
	int *key = new int[4];
};

