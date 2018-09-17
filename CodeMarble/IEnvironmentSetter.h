#pragma once
#include "IEnvironmentGetter.h"
#include "IPlayerSetter.h"

class IEnvironmentSetter : public IEnvironmentGetter
{
public:
	IEnvironmentSetter()
	{

	}
	virtual ~IEnvironmentSetter()
	{

	}

	virtual void setCaller(IPlayerSetter *caller) = 0;
	virtual void setSubsidy(int subsidy) = 0;
	virtual void oneMorePlayerDead() = 0;
};