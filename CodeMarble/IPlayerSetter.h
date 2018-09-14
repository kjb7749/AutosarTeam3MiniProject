#pragma once
#include "IPlayerGetter.h"

class IPlayerSetter : virtual public IPlayerGetter
{
public:
	IPlayerSetter()
	{

	}
	virtual ~IPlayerSetter()
	{

	}

	virtual void setMoney(int money) = 0;
	virtual int RollDice() = 0;
	virtual void Move(int value) = 0;
	virtual void IamDie() = 0;
	virtual void Execute() = 0;
	virtual int giveMoneyTo(int amount, IPlayerSetter *other) = 0;
	virtual void increaseWarning() = 0;
};