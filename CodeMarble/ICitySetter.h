#pragma once
#include "ICityGetter.h"

class ICitySetter : virtual public ICityGetter
{
public:
	ICitySetter() {}
	virtual ~ICitySetter() {}

	virtual void setOwnerID(int ownerID) = 0;
	virtual int LevelUp() = 0;
	virtual void LevelReset() = 0;
};