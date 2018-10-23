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

void HashFunction::setHashing(int caseNum)
{
	rootA = temRoot / 1000;
	rootB = (temRoot - rootA * 1000) / 100;
	rootC = (temRoot - rootA * 1000 - rootB * 100) / 10;
	rootD = temRoot - rootA * 1000 - rootB * 100 - rootC * 10;
	switch (caseNum) {
	case 1:
		rootA = rootA + CNkey[0];
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
		CN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;
		reNum = CN;
		break;
	case 2:
		rootA = rootA + LNkey[0];
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
		LN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;
		reNum = LN;
		break;
	case 3:
		rootA = rootA + HNkey[0];
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
		HN = rootA * 1000 + rootB * 100 + rootC * 10 + rootD;
		reNum = HN;
		break;
	}
}

void HashFunction::setHashRoot(int caseChar)
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

vector<int> allroot;

void HashFunction::setBaseRoot(vector<int>&allrootB)
{
	r->chooseRoot(allrootB);
	temRoot = r->getRoot();

}

int HashFunction::getHshing()
{
	return reNum;
}

void HashFunction::setKey()
{
	r->setHashKey();
	CNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		//CNkey[i] = CNkeyP[i];
		CNkey[0] = 4;
		CNkey[1] = 9;
		CNkey[2] = 9;
		CNkey[3] = 9;
	}
	r->setHashKey();
	LNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		//LNkey[i] = LNkeyP[i];
		LNkey[0] = 0;
		LNkey[1] = 0;
		LNkey[2] = 0;
		LNkey[3] = 0;
	}
	r->setHashKey();
	HNkeyP = r->getHashKey();
	for (int i = 0; i < 4; i++) {
		//HNkey[i] = HNkeyP[i];
		HNkey[0] = 0;
		HNkey[1] = 0;
		HNkey[2] = 0;
		HNkey[3] = 0;
	}
}
