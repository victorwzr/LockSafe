//Zhaoran Wang 150382450 Breaked lock check safe to resize range of CN key, CN repeat
#include "stdafx.h"
#include "safeed.h"


safeed::safeed()
{
}


safeed::~safeed()
{
}

void safeed::chkCN(int CN[])                              //Check CN repeat
{
	if (CN[0] == CN[1] || CN[0] == CN[2] || CN[0] == CN[3] || CN[1] == CN[2] || CN[1] == CN[3] || CN[2] == CN[3]) {
		safeb = false;
	}
	else {
		safeb = true;
	}
}

bool safeed::reCNSafe()
{
	return safeb;
}
