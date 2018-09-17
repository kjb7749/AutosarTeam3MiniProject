#pragma once
//#include "ICitySetter.h"
#include "IEnvironmentSetter.h"
#include "Player.h"
#include "City.h"

class Environment : public IEnvironmentSetter
{
private:
	Player *caller;
	static const int MAX_PLAYER = 2;
	int noOwnerflag;

	Player **players;
	int numberOfPlayer;
	int deadPlayerCount;

	int cityCount;
	City **board;
	int subsidy;

public:
	Environment();
	virtual ~Environment();

	virtual int getCityCount();
	virtual IPlayerGetter *getCaller();
	virtual int getPlayerCount();
	virtual int getSubsidy();
	virtual IPlayerSetter *whosCity(int cityOwnerID);
	virtual ICityGetter* getCityWithIndex(int index);
	virtual bool buyCity(IPlayerSetter *player, int cityIndex, int level);
	virtual bool sellCity(IPlayerSetter *player, int cityIndex);

	virtual void setCaller(IPlayerSetter *caller);
	virtual IPlayerGetter** getPlayers();
	virtual void setSubsidy(int subsidy);
	virtual void oneMorePlayerDead();
	

	void appendUser(Player *p);
	int randomNoOwner();
	IPlayerGetter *getWinner();
	bool playGame();
};