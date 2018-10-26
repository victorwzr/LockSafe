//Zhaoran Wang 150382450  random set the hash key and random choose root for first time run and to set key file

#include "stdafx.h"
#include "random.h"
#include <vector>

using namespace std;

random::random()
{
}


random::~random()
{
}

int random::getRoot()                //return root
{
	return root;
}



void random::chooseRoot(vector<int>&allrootC)                 //random choose root from all possible root and delete picked one from pool
{
	rootNumber = allrootC.at(0);
	allrootC.erase(allrootC.begin());
	root = rootNumber;
}

int* random::getHashKey()          //return key
{

	return key;
}

void random::setHashKey()                       //random set all 4 digits with the random sign symbol
{
	for (int i = 0; i < 4; i++) {
		ran = rand() % 10;
		symbol = rand();
		if (symbol % 2)
			ran = -ran;
		key[i] = ran;
	}
}