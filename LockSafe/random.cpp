#include "stdafx.h"
#include "random.h"
#include "time.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

random::random()
{
}


random::~random()
{
}

int random::getRoot()
{
	return root;
}



void random::chooseRoot(vector<int>&allrootC)
{
	rootNumber = allrootC.at(0);
	allrootC.erase(allrootC.begin());
	root = rootNumber;
}

int* random::getHashKey()
{

	return key;
}

void random::setHashKey()
{
	for (int i = 0; i < 4; i++) {
		ran = rand() % 10;
		symbol = rand();
		if (symbol % 2)
			ran = -ran;
		key[i] = ran;
	}
}