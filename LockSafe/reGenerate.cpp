//Zhaoran Wang 150382450
//re generate key mutli safe files for course work 1 by readin key files
#include "stdafx.h"
#include "reGenerate.h"
#include "Lock.h"
#include "HashFunction.h"
#include <iostream>
#include "sstream"
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Safe.h"

using namespace std;

vector<int> allroot;



reGenerate::reGenerate()
{
}


reGenerate::~reGenerate()
{
}

Lock *lre = new Lock();
HashFunction *hre = new HashFunction();
Safe *sn = new Safe();
ofstream newfile;


void reGenerate::SplitString(const string& s, vector<string>& v, const string& c)              //split function, ref
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void reGenerate::readFile()
{
	ifstream infile;
	infile.open("key.txt");                //file stream
	while (getline(infile, line)) {
		LINE.push_back(line);
	}
	std::stringstream s;
	for (auto iter = LINE.cbegin(); iter != LINE.cend(); iter++) {
		culine = (*iter);                                   //input from file into string vector as line
		vec.clear();
		if (culine == "") {                     //split number and id and check id to input number into vector to storage

		}
		else {
			culine.erase(std::remove(culine.begin(), culine.end(), ','), culine.end());
			culine.erase(std::remove(culine.begin(), culine.end(), '+'), culine.end());              //change to common format when input string
			SplitString(culine, vec, " ");
			if (vec[0] == "ROOT") {                 //Check key word and change to number int type
				s << vec[1];
				s >> temp;
				Root.push_back(temp);
				s.clear();
			}
			else {
				if (vec[0] == "UHF") {
					s << vec[1];
					s >> temp;
					UHF.push_back(temp);
					s.clear();
					s << vec[2];
					s >> temp;
					UHF.push_back(temp);
					s.clear();
					s << vec[3];
					s >> temp;
					UHF.push_back(temp);
					s.clear();
					s << vec[4];
					s >> temp;
					UHF.push_back(temp);
					s.clear();
				}
				else {
					if (vec[0] == "LHF") {
						s << vec[1];
						s >> temp;
						LHF.push_back(temp);
						s.clear();
						s << vec[2];
						s >> temp;
						LHF.push_back(temp);
						s.clear();
						s << vec[3];
						s >> temp;
						LHF.push_back(temp);
						s.clear();
						s << vec[4];
						s >> temp;
						LHF.push_back(temp);
						s.clear();
					}
					else {
						if (vec[0] == "PHF") {
							s << vec[1];
							s >> temp;
							PHF.push_back(temp);
							s.clear();
							s << vec[2];
							s >> temp;
							PHF.push_back(temp);
							s.clear();
							s << vec[3];
							s >> temp;
							PHF.push_back(temp);
							s.clear();
							s << vec[4];
							s >> temp;
							PHF.push_back(temp);
							s.clear();
						}
					}
				}
			}
			}
		}
	for (int i = 0; i < 4; i++) {                  //push input to vector
		CNKeyR[i] = UHF.at(i);
		LNKeyR[i] = LHF.at(i);
		HNKeyR[i] = PHF.at(i);
	}

}



void reGenerate::hashLock()                    //Hash lock with setted key
{
		reTsize = Root.size();
		hre->CNkey[0] = CNKeyR[0];
		hre->CNkey[1] = CNKeyR[1];
		hre->CNkey[2] = CNKeyR[2];
		hre->CNkey[3] = CNKeyR[3];           //set key after input
		hre->LNkey[0] = LNKeyR[0];
		hre->LNkey[1] = LNKeyR[1];
		hre->LNkey[2] = LNKeyR[2];
		hre->LNkey[3] = LNKeyR[3];
		hre->HNkey[0] = HNKeyR[0];
		hre->HNkey[1] = HNKeyR[1];
		hre->HNkey[2] = HNKeyR[2];
		hre->HNkey[3] = HNKeyR[3];
		for (auto i = 0; i < reTsize; i++) {            //for any length of mutlilocks
			for (int j = 0; j < 5; j++) {
				if (j == 0) {
					hre->temRoot = Root.at(i);
				}
				else {
					hre->setHashRoot(1);
				}
				hre->setHashing(1);                    //hashing root ot HN
				tempHash = hre->getHshing();
				OutCN.push_back(tempHash);

				sn->CheckCN(tempHash);
				hashsafe = sn->CheckCNResult();             //check repeat safe
				if (hashsafe == false) {
					mutilSafe = false;
				}
				hre->setHashRoot(2);
				hre->setHashing(2);
				tempHash = hre->getHshing();                 //hashing CN
				OutLN.push_back(tempHash);

				hre->setHashRoot(3);
				hre->setHashing(3);
				tempHash = hre->getHshing();            //hashing LN
				OutHN.push_back(tempHash);

				if (i == 4) {
					temsize = OutCN.size();
					CNKeyMuSafe[4] = OutCN.at(temsize - 1);
					CNKeyMuSafe[3] = OutCN.at(temsize - 2);
					CNKeyMuSafe[2] = OutCN.at(temsize - 3);             //Check bouns rule and check result valid
					CNKeyMuSafe[1] = OutCN.at(temsize - 4);
					CNKeyMuSafe[0] = OutCN.at(temsize - 5);
					sn->CheckEven(CNKeyMuSafe);
					hashsafe = sn->CheckEvenResult();
					if (hashsafe == false) {
						mutilSafe = false;
					}
				}
			}
		}

		newfile.open("mutilsafe.txt");                      //output into file
		newfile.unsetf(ios::showpos);
		if(mutilSafe = true) {
			safe = "VALID";
		}else{
			safe = "NOT VALID";                 //valid check
		}
		
		for (int i = 0; i < reTsize; i++) {
			newfile << "NS " << i+1 << " " << safe << endl;
			for (int j = 0; j < 5; j++) {
				
				newfile << "CN" << j << " " << OutCN.front() << ", ";                     //same format
				OutCN.erase(OutCN.begin());
				newfile << "LN" << j << " " << OutLN.front() << ", ";
				OutLN.erase(OutLN.begin());
				newfile << "HN" << j << " " << OutHN.front() << endl;
				OutHN.erase(OutHN.begin());
			}
			newfile << endl;
		}
		newfile.close();
}
