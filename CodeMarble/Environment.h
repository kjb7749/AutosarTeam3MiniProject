#pragma once
#include "IEnvironmentSetter.h"
#include "Player.h"
#include "City.h"
#include <string>

class Environment : public IEnvironmentSetter
{
private:
	Player *caller;
	static const int MAX_PLAYER = 2;
	int noOwnerflag;

	Player **players;
	int playerCount;
	int deadPlayerCount;

	int cityCount;
	City **board;
	int subsidy;

public:
	Environment(std::string path);
	virtual ~Environment();

	virtual int getCityCount();
	virtual IPlayerGetter *getCaller();
	virtual int getPlayerCount();
	virtual int getSubsidy();
	virtual IPlayerSetter *whosCity(int cityOwnerID);
	virtual ICityGetter** getCities();
	virtual ICityGetter* getCity(int index);
	virtual bool buyCity(IPlayerSetter *player, int cityIndex, int level);
	virtual bool sellCity(IPlayerSetter *player, int cityIndex);

	virtual void setCaller(IPlayerSetter *caller);
	virtual IPlayerGetter** getPlayers();
	virtual IPlayerGetter* getPlayer(int ID);
	virtual void setSubsidy(int subsidy);
	virtual void oneMorePlayerDead();
	

	void appendUser(Player *p);
	int randomNoOwner();
	IPlayerGetter *getWinner();
	bool playGame();
};