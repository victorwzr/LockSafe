#pragma once

#include <vector>
using namespace std;
class reGenerate
{
public:
	reGenerate();
	~reGenerate();
	void SplitString(const string & s, vector<string>& v, const string & c);
	void readFile();
	void hashLock();

private:
	string line;
	string culine;
	string safe;
	vector<string> vec;
	vector<string> LINE;
	vector<int> Root;
	vector<int> UHF;
	vector<int> LHF;
	vector<int> PHF;
	vector<int> OutCN;
	vector<int> OutLN;
	vector<int> OutHN;
	bool cusafe = false;
	int CNKeyR[4], LNKeyR[4], HNKeyR[4];
	int CN, LN, HN;
	int temp, reTsize, tempHash, temsize;
	int CNKeyMuSafe[5];
	bool hashsafe;
	bool mutilSafe = true;
};

