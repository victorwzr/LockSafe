//Zhaoran Wang 150382450            Check CN repeat safe and bouns safe return boolean

#include "stdafx.h"
#include "Safe.h"
#include <iostream>
using namespace std;

Safe::Safe()
{
}


Safe::~Safe()
{
}

bool Safe::CheckCNResult()            //return result
{
	return safe;
}

void Safe::CheckCN(int CN)                                      //split into digits and check repeat safe
{
	d1 = CN / 1000;
	d2 = (CN - d1 * 1000) / 100;
	d3 = (CN - d1 * 1000 - d2 * 100) / 10;
	d4 = CN - d1 * 1000 - d2 * 100 - d3 * 10;
	if ((d1 == d2 ) || ( d1 == d3 ) || ( d1 == d4 ) || ( d2 == d3 ) || ( d2 == d4 ) || ( d3 == d4)) {
		safe = false;
	}
	else {
		safe = true;
	}
}

bool Safe::CheckEvenResult()
{
	return safe;                        //return result
}

void Safe::CheckEven(int LN[5])
{
	sum = 0;
	for (int i = 0; i < 5; i++) {
		d1 = LN[i] / 1000;
		d2 = (LN[i] - d1 * 1000) / 100;
		d3 = (LN[i] - d1 * 1000 - d2 * 100) / 10;
		d4 = LN[i] - d1 * 1000 - d2 * 100 - d3 * 10;                                //split into digits and get sum
		sumS[i] = d1 + d2 + d3 + d4;
		sum = sum + d1 + d2 + d3 + d4;
	
	}
	if ((sum % 2) == 0) {
		if ((sumS[0] < sumS[1]) && (sumS[1] < sumS[2]) && (sumS[2] < sumS[3]) && (sumS[3] < sumS[4])) {              //check even and the bigger smaller rule
			safe = true;
		}
		else
		{
			safe = false;
		}
	}
	else {
		safe = false;
	}
}

bool Safe::CheckSumResult()                      //return result
{
	return safe;
}
