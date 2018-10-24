//program flow here

#include "stdafx.h"
#include "Lock.h"
#include "safe.h"
#include "HashFunction.h"
#include <iostream>
#include <fstream>
#include "windows.h"
#include <algorithm>
#include <vector>

using namespace std;
vector<int> allroot;
vector<int> resultRoot;
vector<int> allCN;
vector<int> allLN;
vector<int> allLNBackup;
vector<int> allHN;
HashFunction *hf = new HashFunction();
Safe *s = new Safe();
ofstream myfile;


Lock::Lock()
{
}


Lock::~Lock()
{
}

void Lock::OutputLockKey()
{
	myfile.open("key.txt");
	myfile << "NS " << resultRoot.size() << endl;
	for (auto iter = resultRoot.cbegin(); iter != resultRoot.cend(); iter++) {
		myfile.unsetf(ios::showpos);
		myfile << "ROOT " << (*iter) << endl;
		myfile.setf(ios::showpos);
		myfile << "UHF " << CNKey[0] << "," << CNKey[1] << "," << CNKey[2] << "," << CNKey[3] << endl;
		myfile << "LHF " << LNKey[0] << "," << LNKey[1] << "," << LNKey[2] << "," << LNKey[3] << endl;
		myfile << "PHF " << HNKey[0] << "," << HNKey[1] << "," << HNKey[2] << "," << HNKey[3] << endl;
	}
	myfile.close();
}

void Lock::OutputLockSafe()
{
	allLNBackup.assign(allLN.begin(), allLN.end());
	myfile.open("multi-safe.txt");
	myfile.unsetf(ios::showpos);
	rootsize = resultRoot.size();
	myfile << "NS " << rootsize << endl;
	for (int i = 0; i < rootsize; i++) {
		for (int j = 0; j < 5; j++) {
			myfile << "CN" << j << " " << allCN.front() << ", ";
			allCN.erase(allCN.begin());
			myfile << "LN" << j << " " << allLN.front() << ", ";
			allLN.erase(allLN.begin());
			myfile << "HN" << j << " " << allHN.front() << endl;
			allHN.erase(allHN.begin());
		}
		myfile << endl;
	}
	myfile.close();
}

void Lock::OutputLockFalse()
{
	myfile.open("locked-safe.txt");
	myfile << "NL " << resultRoot.size() << endl;
	for (auto iter = resultRoot.cbegin(); iter != resultRoot.cend(); iter++) {
		myfile.unsetf(ios::showpos);
		myfile << "ROOT: " << (*iter) << endl;
		for (int j = 0; j < 5; j++) {
			myfile << "LN" << j << ": " << allLNBackup.front() << endl;
			allLNBackup.erase(allLNBackup.begin());
		}
		myfile << endl;
	}
	myfile.close();
}


void Lock::runLock(int rootNumber)
{
	if (first == true) {
		allroot.reserve(10000);
		for (int i = 0; i < 10000; i++) {
			allroot.push_back(i);
		}
		random_shuffle(allroot.begin(), allroot.end());              //random sort vector witn 0 - 9999
		hf->setKey();
		CNKey = hf->outputKeyCN();
		LNKey = hf->outputKeyLN();
		HNKey = hf->outputKeyHN();
		/*cout << "UHF: ";
		for (int i = 0; i < 4; i++) {
			cout << CNKey[i];
		}
		cout << endl;
		cout << "LHF: ";
		for (int i = 0; i < 4; i++) {
			cout << LNKey[i];
		}
		cout << endl;
		cout << "PHF: ";
		for (int i = 0; i < 4; i++) {
			cout  << HNKey[i];
		}
		cout << endl; */
		first = false;
	}

	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			if (allroot.size() == 0) {
				allroot.clear();
				resultRoot.clear();
				allCN.clear();
				allLN.clear();
				allHN.clear();
				incounter = 0;
				first = true;
				break;
			}
			hf->setBaseRoot(allroot);	
			resultRoot.push_back(hf->outputRoot());
			//cout << hf->outputRoot() << endl;
		}
		else {
			hf->setHashRoot(1);
		}
		hf->setHashing(1);
		temp = hf->getHshing();
		allCN.push_back(temp);
		s->CheckCN(temp);
		tempsafe = s->CheckCNResult();
		//cout << "CN" << i << " is: " << temp << endl;
		if (tempsafe == false) {
			resultRoot.pop_back();
			allCN.pop_back();
			for (int j = 0; j < i; j++) {
				allCN.pop_back();
				allLN.pop_back();
				allHN.pop_back();
			}
			break;
		}
		//cout << "CN" << i << " is: "<< temp << endl;
		hf->setHashRoot(2);
		hf->setHashing(2);
		temp = hf->getHshing();
		allLN.push_back(temp);
		//cout << "LN" << i << " is: " << temp << endl;
		hf->setHashRoot(3);
		hf->setHashing(3);
		temp = hf->getHshing();
		allHN.push_back(temp);
		//cout << "HN" << i << " is: " << temp << endl;
		if (i == 4) {
			temsize = allCN.size();
			CNKeyMuSafe[4] = allCN.at(temsize - 1);
			CNKeyMuSafe[3] = allCN.at(temsize - 2);
			CNKeyMuSafe[2] = allCN.at(temsize - 3);
			CNKeyMuSafe[1] = allCN.at(temsize - 4);
			CNKeyMuSafe[0] = allCN.at(temsize - 5);
			s->CheckEven(CNKeyMuSafe);
			tempsafe = s->CheckEvenResult();
			if (tempsafe == false) {
				resultRoot.pop_back();
				for (int k = 0; k < 5; k++) {
					allCN.pop_back();
					allLN.pop_back();
					allHN.pop_back();
				}
				break;
			}
			//cout << tempsafe << endl;
			incounter++;
			if (incounter < rootNumber)
				tempsafe = false;
		}
	}


}

bool Lock::reSafe()
{
	return tempsafe;
}
