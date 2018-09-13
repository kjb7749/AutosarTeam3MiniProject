#pragma once
#include "City.h"
//#include "Player.h"
class Player;

class Environment
{
private:
	static const int MAX_PLAYER = 2;
	Player *players[MAX_PLAYER];
	int numberOfPlayer;

	const int cityCount = 5;
	City **board;

public:
	Environment();
	~Environment();

	Player *whosCity(int cityOwnerID);
	void appendUser(Player *p);

	int getCityCount();

	City* getCityWithIndex(int index);

	bool playGame();
	Player *getWinner();
};