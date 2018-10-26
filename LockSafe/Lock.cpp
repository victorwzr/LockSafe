//program flow here
//Zhaoran Wang 150382450 main program flow for inital run
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

HashFunction *hf = new HashFunction();
Safe *s = new Safe();
ofstream myfile;


Lock::Lock()
{
}


Lock::~Lock()
{
}

void Lock::OutputLockKey()                  //out put key files
{
	myfile.open("key.txt");
	myfile << "NS " << resultRoot.size() << endl;
	for (auto iter = resultRoot.cbegin(); iter != resultRoot.cend(); iter++) {                          //wirite in all hash key by format
		myfile.unsetf(ios::showpos);
		myfile << "ROOT " << (*iter) << endl;
		myfile.setf(ios::showpos);
		myfile << "UHF " << CNKey[0] << ", " << CNKey[1] << ", " << CNKey[2] << ", " << CNKey[3] << endl;
		myfile << "LHF " << LNKey[0] << ", " << LNKey[1] << ", " << LNKey[2] << ", " << LNKey[3] << endl;
		myfile << "PHF " << HNKey[0] << ", " << HNKey[1] << ", " << HNKey[2] << ", " << HNKey[3] << endl;
	}
	myfile.close();
}

void Lock::OutputLockSafe(char *name)                  //out put mutlisafe file
{
	allLNBackup.assign(allLN.begin(), allLN.end());
	myfile.open(name);
	myfile.unsetf(ios::showpos);
	rootsize = resultRoot.size();
	myfile << "NS " << rootsize << endl;
	for (int i = 0; i < rootsize; i++) {                                       //write in all hash value and result by format
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

void Lock::OutputLockFalse()               //out put lock safe file
{
	myfile.open("locked-safe.txt");
	myfile << "NL " << resultRoot.size() << endl;
	for (auto iter = resultRoot.cbegin(); iter != resultRoot.cend(); iter++) {                          //write in lock safe file with root and LN by format
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


void Lock::runLock(int rootNumber, bool mutilsafeIN)
{
	mutilsafe = mutilsafeIN;
	if (first == true) {                                             //first time run program
		allroot.reserve(10000);
		for (int i = 0; i < 10000; i++) {                            //random all possiable root
			allroot.push_back(i);
		}
		random_shuffle(allroot.begin(), allroot.end());              //random sort vector witn 0 - 9999
		hf->setKey();
		CNKey = hf->outputKeyCN();
		LNKey = hf->outputKeyLN();                                   //call function to random set key
		HNKey = hf->outputKeyHN();
		first = false;
	}

	for (int i = 0; i < 5; i++) {                                       //main hash part
		if (i == 0) {
			if (allroot.size() == 0) {
				allroot.clear();                                        //0 possiable root remain, not enough require, clear all vector and back to change hash key
				resultRoot.clear();
				allCN.clear();
				allLN.clear();
				allHN.clear();
				incounter = 0;
				first = true;
				break;
			}
			hf->setBaseRoot(allroot);	                                //set first root by the random root vector
			resultRoot.push_back(hf->outputRoot());
		}
		else {
			hf->setHashRoot(1);                     //inside mutile lock set value as hash root
		}
		hf->setHashing(1);                          //hash CN function
		temp = hf->getHshing();
		allCN.push_back(temp);                      //send back all result
		s->CheckCN(temp);                           //check safe rule for CN repeat
		tempsafe = s->CheckCNResult();
		if (tempsafe == false) {                    //not valid to cn repeat rule, delete all wrong result from vector
			resultRoot.pop_back();
			allCN.pop_back();
			for (int j = 0; j < i; j++) {
				allCN.pop_back();
				allLN.pop_back();
				allHN.pop_back();
			}
			break;
		}
		hf->setHashRoot(2);                 //hash LN function
		hf->setHashing(2);
		temp = hf->getHshing();
		allLN.push_back(temp);              //send back all result
		hf->setHashRoot(3);
		hf->setHashing(3);                  //hash HN function
		temp = hf->getHshing();
		allHN.push_back(temp);              //send back all result
		if (i == 4) {                       //At end of one set mutlilocks
			if (mutilsafe == true) {                                     //if using bouns rule
				temsize = allCN.size();                                  //get five CN from back
				CNKeyMuSafe[4] = allCN.at(temsize - 1);
				CNKeyMuSafe[3] = allCN.at(temsize - 2);
				CNKeyMuSafe[2] = allCN.at(temsize - 3);
				CNKeyMuSafe[1] = allCN.at(temsize - 4);
				CNKeyMuSafe[0] = allCN.at(temsize - 5);
				s->CheckEven(CNKeyMuSafe);
				tempsafe = s->CheckEvenResult();                         //Check cn even and sum
				if (tempsafe == false) {                                 //if not as require, delete this set of wrong result from vvector
					resultRoot.pop_back();
					for (int k = 0; k < 5; k++) {
						allCN.pop_back();
						allLN.pop_back();
						allHN.pop_back();
					}
					break;
				}
			}
			
			incounter++;                                                //counter for check how many valid solution got
			if (incounter < rootNumber)
				tempsafe = false;
		}
	}


}

bool Lock::reSafe()
{
	return tempsafe;
}
