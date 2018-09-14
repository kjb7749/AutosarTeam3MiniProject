#pragma once
#include "City.h"
#include "IEnvironmentSetter.h"
#include "Logic.h"

class Player;

class Environment : virtual public IEnvironmentGetter, public IEnvironmentSetter
{
private:
	static const int MAX_PLAYER = 2;
	int noOwnerflag;

	IPlayerSetter *players[MAX_PLAYER];
	int numberOfPlayer;
	int deadPlayerCount;

	const int cityCount = 5;
	ICitySetter **board;
	int subsidy;

public:
	Environment();
	virtual ~Environment();

	virtual int getSubsidy();
	virtual IPlayerSetter *whosCity(int cityOwnerID);
	virtual int getCityCount();
	virtual ICityGetter* getCityWithIndex(int index);
	virtual bool buyCity(IPlayerSetter *player, int cityIndex, int level);
	virtual bool sellCity(IPlayerSetter *player, int cityIndex);


	virtual void setSubsidy(int subsidy);
	virtual void appendUser(IPlayerSetter *p);
	virtual void oneMorePlayerDead();
	
	IPlayerGetter *getWinner();
	bool playGame();
};