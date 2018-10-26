//Zhaoran Wang 150382450         Break lock Hashing only for Hash HN and LN

#include "stdafx.h"
#include "HashFunctioned.h"
#include<iostream>

using namespace std;

HashFunctioned::HashFunctioned()
{
}


HashFunctioned::~HashFunctioned()
{
}

void HashFunctioned::HashCN(int CN[], int CNkey[])                     //Hash CN
{

	CN[0] = CN[0] + CNkey[0];

	if (CN[0] < 0)
		CN[0] = CN[0] + 10;
	if (CN[0] >= 10)
		CN[0] = CN[0] - 10;
	CN[1] = CN[1] + CNkey[1];

	if (CN[1] < 0)
		CN[1] = CN[1] + 10;
	if (CN[1] >= 10)
		CN[1] = CN[1] - 10;
	CN[2] = CN[2] + CNkey[2];

	if (CN[2] < 0)
		CN[2] = CN[2] + 10;
	if (CN[2] >= 10)
		CN[2] = CN[2] - 10;
	CN[3] = CN[3] + CNkey[3];

	if (CN[3] < 0)
		CN[3] = CN[3] + 10;
	if (CN[3] >= 10)
		CN[3] = CN[3] - 10;
	TCN = CN;
	sum = CN[0] + CN[1] + CN[2] + CN[3];               //return CN in number and sum of CN digits
}

int * HashFunctioned::getCN()              //return CN
{
	return TCN;
}

int HashFunctioned::getCNsum()           //return CN sum
{
	return sum;
}

int* HashFunctioned::getHN()            //return HN
{
	return THN;
}

void HashFunctioned::HashHN(int HN[], int HNkey[])                     //return HN after hash LN by PHF
{
	HN[0] = HN[0] + HNkey[0];
	if (HN[0] < 0)
		HN[0] = HN[0] + 10;
	if (HN[0] >= 10)
		HN[0] = HN[0] - 10;
	HN[1] = HN[1] + HNkey[1];
	if (HN[1] < 0)
		HN[1] = HN[1] + 10;
	if (HN[1] >= 10)
		HN[1] = HN[1] - 10;
	HN[2] = HN[2] + HNkey[2];
	if (HN[2] < 0)
		HN[2] = HN[2] + 10;
	if (HN[2] >= 10)
		HN[2] = HN[2] - 10;
	HN[3] = HN[3] + HNkey[3];
	if (HN[3] < 0)
		HN[3] = HN[3] + 10;
	if (HN[3] >= 10)
		HN[3] = HN[3] - 10;
	THN = HN;
}
