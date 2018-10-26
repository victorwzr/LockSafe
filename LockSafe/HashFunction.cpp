//Zhaoran Wang 150382450 main hash function
#include "stdafx.h"
#include "HashFunction.h"
#include "random.h"
#include "windows.h"
#include <iostream>


random *r = new random();

HashFunction::HashFunction()
{
}


HashFunction::~HashFunction()
{
}

void HashFunction::setHashing(int caseNum)                    //hashing by one same hashing method
{
	rootA = temRoot / 1000;                    //change to digit
	rootB = (temRoot - rootA * 1000) / 100;
	rootC = (temRoot - rootA * 1000 - rootB * 100) / 10;
	rootD = temRoot - rootA * 1000 - rootB * 100 - rootC * 10;
	switch (caseNum) {                              //hashing by different hash function
	case 1:               //CN
		rootA = rootA + CNkey[0];                  //change on the digit
		if (rootA < 0)
			rootA = rootA + 10;
		if (rootA >= 10)
			rootA = rootA - 10;
		rootB = rootB + CNkey[1];
		if (rootB < 0)
			rootB = rootB + 10;
		if (rootB >= 10)
			rootB = rootB - 10;
		rootC = rootC + CNkey[2];
		if (rootC < 0)
			rootC = rootC + 10;
		if (rootC >= 10)
			rootC = rootC - 10;
		rootD = rootD + CNkey[3];
		if (rootD < 0)
			rootD = rootD + 10;
		if (rootD >= 10)
			rootD = rootD - 10;
		CN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;               //change back to value
		reNum = CN;
		break;
	case 2:                           //LN
		rootA = rootA + LNkey[0];                               //change on the digit
		if (rootA < 0)
			rootA = rootA + 10;
		if (rootA >= 10)
			rootA = rootA - 10;
		rootB = rootB + LNkey[1];
		if (rootB < 0)
			rootB = rootB + 10;
		if (rootB >= 10)
			rootB = rootB - 10;
		rootC = rootC + LNkey[2];
		if (rootC < 0)
			rootC = rootC + 10;
		if (rootC >= 10)
			rootC = rootC - 10;
		rootD = rootD + LNkey[3];
		if (rootD < 0)
			rootD = rootD + 10;
		if (rootD >= 10)
			rootD = rootD - 10;
		LN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;             //change back to value
		reNum = LN;
		break;
	case 3:                  //HN
		rootA = rootA + HNkey[0];                      //change on the digit
		if (rootA < 0)
			rootA = rootA + 10;
		if (rootA >= 10)
			rootA = rootA - 10;
		rootB = rootB + HNkey[1];
		if (rootB < 0)
			rootB = rootB + 10;
		if (rootB >= 10)
			rootB = rootB - 10;
		rootC = rootC + HNkey[2];
		if (rootC < 0)
			rootC = rootC + 10;
		if (rootC >= 10)
			rootC = rootC - 10;
		rootD = rootD + HNkey[3];
		if (rootD < 0)
			rootD = rootD + 10;
		if (rootD >= 10)
			rootD = rootD - 10;
		HN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;                 //change back to value
		reNum = HN;
		break;
	}
}

void HashFunction::setHashRoot(int caseChar)                 //set current hash value
{
	switch (caseChar) {
	case 1:
		temRoot = HN;
		break;
	case 2:
		temRoot = CN;
		break;
	case 3:
		temRoot = LN;
		break;
	}
}



void HashFunction::setBaseRoot(vector<int>&allrootB)                    //set base root for first key files
{
	r->chooseRoot(allrootB);
	temRoot = r->getRoot();

}

int HashFunction::getHshing()                       //ggetter
{
	return reNum;
}

void HashFunction::setKey()                 //set random hash key(hashing function)
{
	r->setHashKey();
	CNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		CNkey[i] = CNkeyP[i];
	}
	r->setHashKey();
	LNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		LNkey[i] = LNkeyP[i];
	}
	r->setHashKey();
	HNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		HNkey[i] = HNkeyP[i];
	}
}

int * HashFunction::outputKeyCN()
{
	return CNkey;
}

int * HashFunction::outputKeyLN()
{
	return LNkey;
}

int * HashFunction::outputKeyHN()
{
	return HNkey;
}

int HashFunction::outputRoot()
{
	return temRoot;
}
