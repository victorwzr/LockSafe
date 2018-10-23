// LockSafe.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Final Version

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream OUT;
	OUT.open("key.txt");
	OUT.close();
	OUT.open("multisafe.txt");
	OUT.close();
	OUT.open("locksafe.txt");
	OUT.close();

	return 0;
}

