#pragma once

class ICityGetter
{
public:
	ICityGetter() {}
	virtual ~ICityGetter() {}

	virtual char* getName() = 0;
	virtual int curSellPrice() = 0;
	virtual int getPrice(int level) = 0;
	virtual int getEnterfee() = 0;
	virtual int getOwnerID() = 0;
};