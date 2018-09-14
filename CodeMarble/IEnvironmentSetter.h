#pragma once
#include "IEnvironmentGetter.h"
#include "IPlayerSetter.h"

class IEnvironmentSetter : virtual public IEnvironmentGetter
{
public:
	IEnvironmentSetter()
	{

	}
	virtual ~IEnvironmentSetter()
	{

	}

	virtual void setSubsidy(int subsidy) = 0;
	virtual void appendUser(IPlayerSetter *p) = 0;
	virtual void oneMorePlayerDead() = 0;
};