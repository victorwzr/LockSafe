//program flow here

#include "stdafx.h"
#include "Lock.h"
#include "safe.h"
#include "HashFunction.h"
#include <iostream>
#include "windows.h"
#include <algorithm>
#include <vector>

using namespace std;
vector<int> allroot;
HashFunction *hf = new HashFunction();
Safe *s = new Safe();


Lock::Lock()
{
}


Lock::~Lock()
{
}

void Lock::setLock()
{

}

int* Lock::getLockKey()
{
	return CNKey;
}

void Lock::runLock()
{
	if (first == true) {
		allroot.reserve(10000);
		for (int i = 0; i < 10000; i++) {
			allroot.push_back(i);
		}
		random_shuffle(allroot.begin(), allroot.end());              //random sort vector witn 0 - 9999
		hf->setKey();
		first = false;
		system("pause");
	}
	
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			hf->setBaseRoot(allroot);
			
		}
		else {
			hf->setHashRoot(1);
		}
		hf->setHashing(1);
		temp = hf->getHshing();
		s->CheckCN(temp);
		tempsafe = s->CheckCNResult();
		//cout << "CN" << i << " is: " << temp << endl;
		if (tempsafe == false) {
			break;
		}
		//cout << "CN" << i << " is: "<< temp << endl;
		hf->setHashRoot(2);
		hf->setHashing(2);
		temp = hf->getHshing();
		//cout << "LN" << i << " is: " << temp << endl;
		hf->setHashRoot(3);
		hf->setHashing(3);
		temp = hf->getHshing();
		
	//	cout << "HN" << i << " is: " << temp << endl;
		if (i == 4) {
			
			incounter++;
			if (incounter < 9999) {
				cout << "incounter-----------------------" << incounter << endl;
				tempsafe = false;
			}
		}
	}


}

bool Lock::reSafe()
{
	return tempsafe;
}
