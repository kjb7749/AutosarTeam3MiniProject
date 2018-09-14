#pragma once

class IPlayerGetter
{
public:
	IPlayerGetter()
	{

	}
	virtual ~IPlayerGetter()
	{

	}

	virtual int getMoney() = 0;
	virtual bool amIDead() = 0;
	virtual char *getName() = 0;
	virtual int getCurIndex() = 0;
	virtual int getID() = 0;
};