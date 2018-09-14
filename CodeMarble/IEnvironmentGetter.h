#pragma once
#include "IPlayerSetter.h"
#include "ICityGetter.h"

class IEnvironmentGetter
{
public:
	IEnvironmentGetter()
	{

	}
	virtual ~IEnvironmentGetter()
	{

	}

	virtual int getSubsidy() = 0;
	virtual IPlayerSetter *whosCity(int cityOwnerID) = 0;
	virtual int getCityCount() = 0;
	virtual ICityGetter* getCityWithIndex(int index) = 0;
	virtual bool buyCity(IPlayerSetter *player, int cityIndex, int level) = 0;
	virtual bool sellCity(IPlayerSetter *player, int cityIndex) = 0;
};