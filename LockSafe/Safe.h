//Header files for Safe.cpp
//Zhaoran Wang 150382450
#pragma once
class Safe
{
public:
	Safe();
	~Safe();
	bool CheckCNResult();
	void CheckCN(int CN);
	bool CheckEvenResult();
	void CheckEven(int LN[5]);
	bool CheckSumResult();
private:
	bool safe;
	int d1, d2, d3, d4, sum;
	int sumS[5];
};

