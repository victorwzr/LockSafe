#pragma once
#include <vector>

using namespace std;

struct Locks {
	int index[4];//Root
	int A[4];    //LN0
	int B[4];    //LN1
	int C[4];    //LN2
	int D[4];    //LN3
	int E[4];    //LN4
};

class Locked
{
public:
	Locked();
	~Locked();
	void setLock();
	void setPHF();
	void SplitString(const string& s, vector<string>& v, const string& c);
	int rePHF();
	void setHN();
	void runCN(bool bounsCon);
	void setLHF();
	int reLHF();
	int reUHF();
	void reBuiltLock();



private:

	string line;
	string culine;
	string safe;
	vector<string> vec;
	vector<int> LN0;
	vector<int> LN1;
	vector<int> LN2;
	vector<int> LN3;
	vector<int> LN4;
	vector<int> Root;
	vector<int> vec_tmp;
	vector<string> LINE;
	vector<Locks> lock;
	vector<int*> HN0, HN1, HN2, HN3, HN4;
	vector<int*> validUHF;
	vector<int*> CN0, CN1, CN2, CN3, CN4;
	vector<int> OutCN;
	vector<int> OutLN;
	vector<int> OutHN;
	int UHF[10000][4];
	int ULHF[4];
	int CNKeyMuSafe[4];
	int vVUHF[4];
	int PHF[4];
	int LHF[4];
	int hash[4];
	int *vUHF;
	int temp, sumboumns, passsum, totalsum, finalUHFv, finalPHFv, finalLHFv, reTsize, tempHash, temsize;
	int *HN0temp, *HN1temp, *HN2temp, *HN3temp, *HN4temp, *safetemp;
	bool safeCN, mutilSafe, hashsafe;
	bool RCHK;
	int chkcounter = 0, chkcounter2 = 0;   //for chk
};

