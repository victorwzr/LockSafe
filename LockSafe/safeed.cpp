#include "stdafx.h"
#include "safeed.h"


safeed::safeed()
{
}


safeed::~safeed()
{
}

void safeed::chkCN(int CN[])
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
