#pragma once
#include <string>

using namespace std;

class ICityGetter
{
public:
	ICityGetter() {}
	virtual ~ICityGetter() {}

	virtual string getName() = 0;
	virtual int curSellPrice() = 0;
	virtual int getPrice(int level) = 0;
	virtual int getEnterfee() = 0;
	virtual int getOwnerID() = 0;
};