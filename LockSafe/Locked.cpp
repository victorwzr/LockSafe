#include "stdafx.h"
#include "sstream"
#include "Locked.h"
#include<iostream>
#include<string>
#include "HashFunctioned.h"
#include "safeed.h"
#include<fstream>
#include<algorithm>

HashFunctioned *hfun = new HashFunctioned();
safeed *sf = new safeed();


Locked::Locked()
{
}


Locked::~Locked()
{
}

void Locked::SplitString(const string& s, vector<string>& v, const string& c)              //split function
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


void Locked::setLock()
{
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
			culine.erase(std::remove(culine.begin(), culine.end(), ' '), culine.end());
			SplitString(culine, vec, ":");
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
	for (int i = 0; i < 100; i++) {                                //split digit and pass to 100 locks data type in vector
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
	Root.clear();               //release the vector
	LN0.clear();
	LN1.clear();
	LN2.clear();
	LN3.clear();
	LN4.clear();
}

void Locked::setPHF()
{
	PHF[0] = lock[0].B[0] - lock[0].A[0] - lock[0].A[0] + lock[0].index[0];           //PHF digit set
	PHF[1] = lock[0].B[1] - lock[0].A[1] - lock[0].A[1] + lock[0].index[1];
	PHF[2] = lock[0].B[2] - lock[0].A[2] - lock[0].A[2] + lock[0].index[2];
	PHF[3] = lock[0].B[3] - lock[0].A[3] - lock[0].A[3] + lock[0].index[3];

	for (int i = 0; i < 4; i++) {
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
		//cout << PHF[i] << endl;
	}
}

int Locked::rePHF()
{
	finalPHFv = PHF[0] * 1000 + PHF[1] * 100 + PHF[2] * 10 + PHF[3];
	return finalPHFv;
}

void Locked::setHN()
{
	for (int i = 0; i < 100; i++) {
		hfun->HashHN(lock[i].A, PHF);
		HN0.push_back(hfun->getHN());
		//cout << hfun->getHN() << endl;
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
	for (int i = 0; i < 4; i++) {                       //fix the total to positive
		if (ULHF[i] >= 10) {
			ULHF[i] = (ULHF[i] - 10);
		}
		if (ULHF[i] < 0)
			ULHF[i] = ULHF[i] + 10;
		//	cout << ULHF[i] << endl;
	}
	for (int i = 0; i < 10000; i++) {                                  //inital UHF for 0-9999
		UHF[i][0] = i / 1000;
		UHF[i][1] = i / 100 - UHF[i][0] * 10;
		UHF[i][2] = i / 10 - UHF[i][0] * 100 - UHF[i][1] * 10;
		UHF[i][3] = i - UHF[i][0] * 1000 - UHF[i][1] * 100 - UHF[i][2] * 10;
	}

	for (int i = 0; i < 10000; i++) {

		for (int j = 0; j < 100; j++) {
			hash[0] = lock[j].index[0];
			hash[1] = lock[j].index[1];
			hash[2] = lock[j].index[2];
			hash[3] = lock[j].index[3];
			hfun->HashCN(hash, UHF[i]);         //
			safetemp = hfun->getCN();
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN0[j][0];
			hash[1] = HN0[j][1];
			hash[2] = HN0[j][2];
			hash[3] = HN0[j][3];
			hfun->HashCN(hash, UHF[i]);         //
			safetemp = hfun->getCN();
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN1[j][0];
			hash[1] = HN1[j][1];
			hash[2] = HN1[j][2];
			hash[3] = HN1[j][3];
			hfun->HashCN(hash, UHF[i]);         //
			safetemp = hfun->getCN();
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN2[j][0];
			hash[1] = HN2[j][1];
			hash[2] = HN2[j][2];
			hash[3] = HN2[j][3];
			hfun->HashCN(hash, UHF[i]);         //
			safetemp = hfun->getCN();
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			hash[0] = HN3[j][0];
			hash[1] = HN3[j][1];
			hash[2] = HN3[j][2];
			hash[3] = HN3[j][3];
			hfun->HashCN(hash, UHF[i]);         //
			safetemp = hfun->getCN();
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false)
				break;
			if (j == 99) {
				validUHF.push_back(UHF[i]);
			}
		}
	}



	if (bounsCon == true) {

		for (unsigned int m = 0; m < validUHF.size(); m++)
		{
			if (RCHK == true)
				break;
			vUHF = validUHF.at(m);
			for (int k = 0; k < 100; k++) {
				totalsum = 0;
				sumboumns = 0;
				passsum = 0;
				hash[0] = lock[k].index[0];
				hash[1] = lock[k].index[1];
				hash[2] = lock[k].index[2];
				hash[3] = lock[k].index[3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				passsum = sumboumns;
				hash[0] = HN0[k][0];
				hash[1] = HN0[k][1];
				hash[2] = HN0[k][2];
				hash[3] = HN0[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {
					break;
				}
				//cout << vUHF[0] << vUHF[1] << vUHF[2] << vUHF[3] << endl;
				passsum = sumboumns;
				hash[0] = HN1[k][0];
				hash[1] = HN1[k][1];
				hash[2] = HN1[k][2];
				hash[3] = HN1[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {
					break;
				}
				passsum = sumboumns;
				hash[0] = HN2[k][0];
				hash[1] = HN2[k][1];
				hash[2] = HN2[k][2];
				hash[3] = HN2[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {
					break;
				}
				passsum = sumboumns;
				hash[0] = HN3[k][0];
				hash[1] = HN3[k][1];
				hash[2] = HN3[k][2];
				hash[3] = HN3[k][3];
				hfun->HashCN(hash, vUHF);
				sumboumns = hfun->getCNsum();
				totalsum = totalsum + sumboumns;
				if (sumboumns <= passsum) {
					break;
				}
				if (totalsum % 2 == 1) {
					break;
				}
				else {
					if (k == 99) {
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
	for (int i = 0; i < 4; i++) {
		LHF[i] = ULHF[i] - vVUHF[i];
		if (LHF[i] < 0) {
			LHF[i] = LHF[i] + 10;
		}
		if (LHF[i] >= 10) {
			LHF[i] = LHF[i] - 10;
		}
	}
	finalLHFv = LHF[0] * 1000 + LHF[1] * 100 + LHF[2] * 10 + LHF[3];
}

int Locked::reLHF()
{
	return finalLHFv;
}

int Locked::reUHF()
{

	finalUHFv = (vVUHF[0] * 1000) + (vVUHF[1] * 100) + (vVUHF[2] * 10) + (vVUHF[3]);
	return finalUHFv;
}
