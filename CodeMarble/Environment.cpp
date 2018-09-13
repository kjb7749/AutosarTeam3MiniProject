#include "Environment.h"
#include <stdlib.h>
#include "Player.h"

Environment::Environment()
{
	numberOfPlayer = 0;
	board = NULL;
	//도시 데이터 세팅부

	//const char *cityNames[] = { "서울", "도쿄" };

	////레벨별 도시를 밞음으로 얻는 이익
	//int cityBenefits[][4] = { {1,2,3} };
	////레벨별 도시 구매 비용
	//int cityPrices[][4] = { {} };
	////레벨별 도시 판매가격 (가장 최종 가격만 반영되어 판매됨)
	//int citySellPrices[][4] = { {} };

	//board = new City*[cityCount];

	//for (int i = 0; i < cityCount; ++i)
	//{
	//	board[i] = new City(cityNames[i], cityPrices, citySellPrices, cityBenefits);
	//}
}
Environment::~Environment()
{

}

Player* Environment::whosCity(int cityOwnerID)
{
	for (int i = 0; i < numberOfPlayer; ++i)
	{
		if (players[i]->getID() == cityOwnerID)
			return players[i];
	}

	return NULL;
}

void Environment::appendUser(Player *p)
{
	players[numberOfPlayer++] = p;
}

int Environment::getCityCount()
{
	return cityCount;
}

City* Environment::getCityWithIndex(int index)
{
	if (index >= cityCount || index < 0)
		return NULL;
	else
	{
		if (board != NULL)
		{
			if (board[index] != NULL)
				return board[index];
			else
				return NULL;
		}
		return NULL;
	}
}

bool Environment::playGame()
{
	for (int i = 0; i < numberOfPlayer; ++i)
	{
		if (!players[i]->amIDead())
			players[i]->Execute();
	}

	//게임이 끝났을때 false를 반환
	if (false)
		return false;
	return true;
}

Player* Environment::getWinner()
{
	Player *winner = NULL;

	return winner;
}