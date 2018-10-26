//Zhaoran Wang 150382450 Breaked lock main part for break, bouns include here together

#include "stdafx.h"
#include "sstream"
#include "Locked.h"
#include<iostream>
#include<string>
#include "HashFunctioned.h"
#include "safeed.h"
#include<fstream>
#include "HashFunction.h"
#include "Safe.h"
#include<algorithm>

HashFunctioned *hfun = new HashFunctioned();
safeed *sf = new safeed();
HashFunction *hreB = new HashFunction();
Safe *sb = new Safe();
ofstream breaked;

Locked::Locked()
{
}


Locked::~Locked()
{
}

void Locked::SplitString(const string& s, vector<string>& v, const string& c)              //split function, ref
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


void Locked::setLock(int sets)
{
	Insets = sets;
	ifstream infile;
	infile.open("locked-safe.txt");                //file stream
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
			culine.erase(std::remove(culine.begin(), culine.end(), ' '), culine.end());              //delete all " " in the line
			SplitString(culine, vec, ":");                                              //check by "£º" to split string get variables, suitable for most input files format
			if (vec[0] == "ROOT") {
				s << vec[1];
				s >> temp;
				Root.push_back(temp);
				s.clear();
			}
			else {
				if (vec[0] == "LN0") {
					s << vec[1];
					s >> temp;
					LN0.push_back(temp);
					s.clear();
				}
				else {
					if (vec[0] == "LN1") {
						s << vec[1];
						s >> temp;
						LN1.push_back(temp);
						s.clear();
					}
					else {
						if (vec[0] == "LN2") {
							s << vec[1];
							s >> temp;
							LN2.push_back(temp);
							s.clear();
						}
						else {
							if (vec[0] == "LN3") {
								s << vec[1];
								s >> temp;
								LN3.push_back(temp);
								s.clear();
							}
							else {
								if (vec[0] == "LN4") {
									s << vec[1];
									s >> temp;
									LN4.push_back(temp);
									s.clear();
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < Insets; i++) {                                //split digit and pass to any number locks data type in vector
		lock.push_back(Locks());
		lock[i].index[0] = Root[i] / 1000;
		lock[i].index[1] = Root[i] / 100 - lock[i].index[0] * 10;
		lock[i].index[2] = Root[i] / 10 - lock[i].index[0] * 100 - lock[i].index[1] * 10;
		lock[i].index[3] = Root[i] - lock[i].index[0] * 1000 - lock[i].index[1] * 100 - lock[i].index[2] * 10;
		lock[i].A[0] = LN0[i] / 1000;
		lock[i].A[1] = LN0[i] / 100 - lock[i].A[0] * 10;
		lock[i].A[2] = LN0[i] / 10 - lock[i].A[0] * 100 - lock[i].A[1] * 10;
		lock[i].A[3] = LN0[i] - lock[i].A[0] * 1000 - lock[i].A[1] * 100 - lock[i].A[2] * 10;
		lock[i].B[0] = LN1[i] / 1000;
		lock[i].B[1] = LN1[i] / 100 - lock[i].B[0] * 10;
		lock[i].B[2] = LN1[i] / 10 - lock[i].B[0] * 100 - lock[i].B[1] * 10;
		lock[i].B[3] = LN1[i] - lock[i].B[0] * 1000 - lock[i].B[1] * 100 - lock[i].B[2] * 10;
		lock[i].C[0] = LN2[i] / 1000;
		lock[i].C[1] = LN2[i] / 100 - lock[i].C[0] * 10;
		lock[i].C[2] = LN2[i] / 10 - lock[i].C[0] * 100 - lock[i].C[1] * 10;
		lock[i].C[3] = LN2[i] - lock[i].C[0] * 1000 - lock[i].C[1] * 100 - lock[i].C[2] * 10;
		lock[i].D[0] = LN3[i] / 1000;
		lock[i].D[1] = LN3[i] / 100 - lock[i].D[0] * 10;
		lock[i].D[2] = LN3[i] / 10 - lock[i].D[0] * 100 - lock[i].D[1] * 10;
		lock[i].D[3] = LN3[i] - lock[i].D[0] * 1000 - lock[i].D[1] * 100 - lock[i].D[2] * 10;
		lock[i].E[0] = LN4[i] / 1000;
		lock[i].E[1] = LN4[i] / 100 - lock[i].E[0] * 10;
		lock[i].E[2] = LN4[i] / 10 - lock[i].E[0] * 100 - lock[i].E[1] * 10;
		lock[i].E[3] = LN4[i] - lock[i].E[0] * 1000 - lock[i].E[1] * 100 - lock[i].E[2] * 10;
	}
	               //release the vector
	LN0.clear();
	LN1.clear();
	LN2.clear();
	LN3.clear();
	LN4.clear();
}

void Locked::setPHF()
{
	PHF[0] = lock[0].B[0] - lock[0].A[0] - lock[0].A[0] + lock[0].index[0];           //PHF digit setted
	PHF[1] = lock[0].B[1] - lock[0].A[1] - lock[0].A[1] + lock[0].index[1];
	PHF[2] = lock[0].B[2] - lock[0].A[2] - lock[0].A[2] + lock[0].index[2];
	PHF[3] = lock[0].B[3] - lock[0].A[3] - lock[0].A[3] + lock[0].index[3];

	for (int i = 0; i < 4; i++) {                   //turn digit to valid, check twice because PHF get by two times opreator
		if (PHF[i] >= 10) {
			PHF[i] = (PHF[i] - 10);
		}
		if (PHF[i] < 0)
			PHF[i] = PHF[i] + 10;
	}
	for (int i = 0; i < 4; i++) {
		if (PHF[i] >= 10) {
			PHF[i] = (PHF[i] - 10);
		}
		if (PHF[i] < 0)
			PHF[i] = PHF[i] + 10;
	}
}

int Locked::rePHF()                       //return PHF in number
{
	finalPHFv = PHF[0] * 1000 + PHF[1] * 100 + PHF[2] * 10 + PHF[3];
	return finalPHFv;
}

void Locked::setHN()
{
	for (int i = 0; i < Insets; i++) {                         //hash HN by LN and PHF
		hfun->HashHN(lock[i].A, PHF);
		HN0.push_back(hfun->getHN());
		hfun->HashHN(lock[i].B, PHF);
		HN1.push_back(hfun->getHN());
		hfun->HashHN(lock[i].C, PHF);
		HN2.push_back(hfun->getHN());
		hfun->HashHN(lock[i].D, PHF);
		HN3.push_back(hfun->getHN());
		hfun->HashHN(lock[i].E, PHF);
		HN4.push_back(hfun->getHN());
	}
}

void Locked::runCN(bool bounsCon)
{
	ULHF[0] = lock[0].A[0] - lock[0].index[0] - PHF[0];                     //set UHF + LHF
	ULHF[1] = lock[0].A[1] - lock[0].index[1] - PHF[1];
	ULHF[2] = lock[0].A[2] - lock[0].index[2] - PHF[2];
	ULHF[3] = lock[0].A[3] - lock[0].index[3] - PHF[3];
	for (int i = 0; i < 4; i++) {
		if (ULHF[i] >= 10) {
			ULHF[i] = (ULHF[i] - 10);
		}
		if (ULHF[i] < 0)
			ULHF[i] = ULHF[i] + 10;
	}
	for (int i = 0; i < 4; i++) {                       //fix the total to positive, same check twice
		if (ULHF[i] >= 10) {
			ULHF[i] = (ULHF[i] - 10);
		}
		if (ULHF[i] < 0)
			ULHF[i] = ULHF[i] + 10;
	}
	for (int i = 0; i < 10000; i++) {                                  //inital UHF for 0-9999 and split to digit
		UHF[i][0] = i / 1000;
		UHF[i][1] = i / 100 - UHF[i][0] * 10;
		UHF[i][2] = i / 10 - UHF[i][0] * 100 - UHF[i][1] * 10;
		UHF[i][3] = i - UHF[i][0] * 1000 - UHF[i][1] * 100 - UHF[i][2] * 10;
	}

	for (int i = 0; i < 10000; i++) {                          //go through all UHF

		for (int j = 0; j < Insets; j++) {               //go through all sets of mutlilocks any length
			hash[0] = lock[j].index[0];
			hash[1] = lock[j].index[1];
			hash[2] = lock[j].index[2];
			hash[3] = lock[j].index[3];
			hfun->HashCN(hash, UHF[i]);         //Hash HN by possiable UHF get CN
			safetemp = hfun->getCN();           //Check CN if is valid
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN0[j][0];
			hash[1] = HN0[j][1];
			hash[2] = HN0[j][2];
			hash[3] = HN0[j][3];
			hfun->HashCN(hash, UHF[i]);         //Hash HN by possiable UHF get CN
			safetemp = hfun->getCN();           //Check CN if is valid
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN1[j][0];
			hash[1] = HN1[j][1];
			hash[2] = HN1[j][2];
			hash[3] = HN1[j][3];
			hfun->HashCN(hash, UHF[i]);         //Hash HN by possiable UHF get CN
			safetemp = hfun->getCN();           //Check CN if is valid
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN2[j][0];
			hash[1] = HN2[j][1];
			hash[2] = HN2[j][2];
			hash[3] = HN2[j][3];
			hfun->HashCN(hash, UHF[i]);         //Hash HN by possiable UHF get CN
			safetemp = hfun->getCN();           //Check CN if is valid
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN3[j][0];
			hash[1] = HN3[j][1];
			hash[2] = HN3[j][2];
			hash[3] = HN3[j][3];
			hfun->HashCN(hash, UHF[i]);        //Hash HN by possiable UHF get CN
			safetemp = hfun->getCN();          //Check CN if is valid
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)              
				break;
			if (j == (Insets - 1)) {                          //Check All CN in one set of locks valid and output result into vector
				validUHF.push_back(UHF[i]);
			}
		}
	}



	if (bounsCon == true) {                                        //For bouns condition
		vUHFsize = validUHF.size();
		for (auto m = 0; m < vUHFsize; m++)                        //Go through all valid CN after first part repeat check
		{
			if (RCHK == true)
				break;
			vUHF = validUHF.at(m);
			for (int k = 0; k < Insets; k++) {
				totalsum = 0;
				sumboumns = 0;
				passsum = 0;
				hash[0] = lock[k].index[0];
				hash[1] = lock[k].index[1];
				hash[2] = lock[k].index[2];
				hash[3] = lock[k].index[3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();                      //Get sum of all digits on all locks in one set and sum of one lock
				totalsum = totalsum + sumboumns;
				passsum = sumboumns;
				hash[0] = HN0[k][0];
				hash[1] = HN0[k][1];
				hash[2] = HN0[k][2];
				hash[3] = HN0[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {                                    //Check if current lock bigger than last one
					break;
				}
				passsum = sumboumns;
				hash[0] = HN1[k][0];                                  //Get sum of all digits on all locks in one set and sum of one lock
				hash[1] = HN1[k][1];
				hash[2] = HN1[k][2];
				hash[3] = HN1[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {                          //Check if current lock bigger than last one
					break;
				}
				passsum = sumboumns;
				hash[0] = HN2[k][0];                                 //Get sum of all digits on all locks in one set and sum of one lock
				hash[1] = HN2[k][1];
				hash[2] = HN2[k][2];
				hash[3] = HN2[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {                                //Check if current lock bigger than last one
					break;
				}
				passsum = sumboumns;
				hash[0] = HN3[k][0];
				hash[1] = HN3[k][1];
				hash[2] = HN3[k][2];
				hash[3] = HN3[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;                              //Get sum of all digits on all locks in one set and sum of one lock
				if (sumboumns <= passsum) {                                   //Check if current lock bigger than last one
					break;
				}
				if (totalsum % 2 == 1) {                               //Check if even on final sum of one sets locks
					break;
				}
				else {
					if (k == (Insets - 1)) {                        //output valid UHF
						RCHK = true;                            
						vVUHF[0] = vUHF[0];
						vVUHF[1] = vUHF[1];
						vVUHF[2] = vUHF[2];
						vVUHF[3] = vUHF[3];
					}
				}
									
		
				
			}
		}

	}
}

void Locked::setLHF()
{
	for (int i = 0; i < 4; i++) {                                             //get LHF after UHF and PHF
		LHF[i] = ULHF[i] - vVUHF[i];
		if (LHF[i] < 0) {                                                    //Check valid digits
			LHF[i] = LHF[i] + 10;
		}
		if (LHF[i] >= 10) {
			LHF[i] = LHF[i] - 10;
		}
	}
	finalLHFv = LHF[0] * 1000 + LHF[1] * 100 + LHF[2] * 10 + LHF[3];            //output number
}

int Locked::reLHF()
{
	return finalLHFv;                      //return LHF number
}

int Locked::reUHF()
{

	finalUHFv = (vVUHF[0] * 1000) + (vVUHF[1] * 100) + (vVUHF[2] * 10) + (vVUHF[3]);                   //return UHF in number
	return finalUHFv;
}

void Locked::reBuiltLock()                                                            //rebuilt lock after break locks wihtout old key and mutlisafe
{
	reTsize = Root.size();
	//cout << reTsize << endl;
	hreB->CNkey[0] = vVUHF[0];                                                     //set all three hash key
	hreB->CNkey[1] = vVUHF[1];
	hreB->CNkey[2] = vVUHF[2];
	hreB->CNkey[3] = vVUHF[3];
	hreB->LNkey[0] = LHF[0];
	hreB->LNkey[1] = LHF[1];
	hreB->LNkey[2] = LHF[2];
	hreB->LNkey[3] = LHF[3];
	hreB->HNkey[0] = PHF[0];
	hreB->HNkey[1] = PHF[1];
	hreB->HNkey[2] = PHF[2];
	hreB->HNkey[3] = PHF[3];
	for (auto i = 0; i < reTsize; i++) {                      //for any length of mutlilocks
		for (int j = 0; j < 5; j++) {                       //5 locks in one set
			if (j == 0) {
				hreB->temRoot = Root.at(i);
			}
			else {
				hreB->setHashRoot(1);                  //Hash root or HN
			}
			hreB->setHashing(1);
			tempHash = hreB->getHshing();
			OutCN.push_back(tempHash);

			sb->CheckCN(tempHash);                     //Check safe again
			hashsafe = sb->CheckCNResult();
			if (hashsafe == false) {
				mutilSafe = false;
			}
			hreB->setHashRoot(2);                       //Hash CN
			hreB->setHashing(2);
			tempHash = hreB->getHshing();
			OutLN.push_back(tempHash);

			hreB->setHashRoot(3);
			hreB->setHashing(3);                      //Hash LN
			tempHash = hreB->getHshing();
			OutHN.push_back(tempHash);

			if (i == 4) {
				temsize = OutCN.size();
				CNKeyMuSafe[4] = OutCN.at(temsize - 1);
				CNKeyMuSafe[3] = OutCN.at(temsize - 2);                  //Check bouns safe again
				CNKeyMuSafe[2] = OutCN.at(temsize - 3);
				CNKeyMuSafe[1] = OutCN.at(temsize - 4);
				CNKeyMuSafe[0] = OutCN.at(temsize - 5);
				sb->CheckEven(CNKeyMuSafe);
				hashsafe = sb->CheckEvenResult();
				if (hashsafe == false) {
					mutilSafe = false;
				}
			}
		}
	}

	breaked.open("mutilsafeNEW.txt");                   //output into new files
	breaked.unsetf(ios::showpos);
	if (mutilSafe = true) {
		safe = "VALID";                       //Valid check output
	}
	else {
		safe = "NOT VALID";
	}

	for (int i = 0; i < reTsize; i++) {
		breaked << "NS " << i + 1 << " " << safe << endl;
		for (int j = 0; j < 5; j++) {

			breaked << "CN" << j << " " << OutCN.front() << ", ";                         //mutlisafe file NEW
			OutCN.erase(OutCN.begin());
			breaked << "LN" << j << " " << OutLN.front() << ", ";
			OutLN.erase(OutLN.begin());
			breaked << "HN" << j << " " << OutHN.front() << endl;
			OutHN.erase(OutHN.begin());
		}
		breaked << endl;
	}
	breaked.close();

	breaked.open("keyNEW.txt");
	breaked << "*** HashFunction will be same whether + ot - with origin file, eg +7 is same as -3***" << endl;                  //Key file NEW and comment
	breaked << "NS " << reTsize << endl;
	for (auto iter = Root.cbegin(); iter != Root.cend(); iter++) {
		breaked.unsetf(ios::showpos);
		breaked << "ROOT " << (*iter) << endl;
		breaked.setf(ios::showpos);
		breaked << "UHF " << vUHF[0] << ", " << vUHF[1] << ", " << vUHF[2] << ", " << vUHF[3] << endl;
		breaked << "LHF " << LHF[0] << ", " << LHF[1] << ", " << LHF[2] << ", " << LHF[3] << endl;
		breaked << "PHF " << PHF[0] << ", " << PHF[1] << ", " << PHF[2] << ", " << PHF[3] << endl;
	}
	breaked.close();
}
