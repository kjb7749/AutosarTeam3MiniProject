#pragma once
#include "City.h"
//#include "Player.h"
class Player;

class Environment
{
private:
	int noOwnerflag;
	static const int MAX_PLAYER = 2;
	Player *players[MAX_PLAYER];
	int numberOfPlayer;

	int deadPlayerCount;

	const int cityCount = 5;
	City **board;

	int subsidy;

public:
	Environment(int subsidy);
	~Environment();

	int getSubsidy();

	Player *whosCity(int cityOwnerID);
	void appendUser(Player *p);

	int getCityCount();
	void oneMorePlayerDead();

	City* getCityWithIndex(int index);

	bool buyCity(Player *player, int cityIndex, int level);
	bool sellCity(Player *player, int cityIndex);

	bool playGame();
	Player *getWinner();
};