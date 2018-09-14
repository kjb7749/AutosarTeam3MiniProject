#include "Environment.h"
#include <stdlib.h>
#include "Player.h"
#include <iostream>

using namespace std;

Environment::Environment()
{
	noOwnerflag = -1;		//랜덤으로 정해져야 한다
	numberOfPlayer = 0;
	board = NULL;
	deadPlayerCount = 0;
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

void Environment::setSubsidy(int subsidy)
{
	this->subsidy = subsidy;
}

int Environment::getSubsidy()
{
	return subsidy;
}

IPlayerSetter* Environment::whosCity(int cityOwnerID)
{
	for (int i = 0; i < numberOfPlayer; ++i)
	{
		if (players[i]->getID() == cityOwnerID)
			return players[i];
	}

	return NULL;
}

void Environment::appendUser(IPlayerSetter *p)
{
	players[numberOfPlayer++] = p;
}

int Environment::getCityCount()
{
	return cityCount;
}

ICityGetter* Environment::getCityWithIndex(int index)
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
	if (deadPlayerCount >= (MAX_PLAYER - 1))
	{
		return false;
	}
	return true;
}

IPlayerGetter* Environment::getWinner()
{
	IPlayerGetter *winner = NULL;

	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		if (!players[i]->amIDead())
		{
			winner = players[i];
			break;
		}
	}
	return winner;
}


bool Environment::buyCity(IPlayerSetter *player, int cityIndex, int level)
{
	if (player->getMoney() < board[cityIndex]->getPrice(level))
	{
		//돈이 부족할때 구매하려한다면
		return false;
	}
	else
	{
		player->setMoney(player->getMoney() - board[cityIndex]->getPrice(level));
		board[cityIndex]->setOwnerID(player->getID());
		cout << board[cityIndex]->getName() << endl;
	}
	return true;
}
bool Environment::sellCity(IPlayerSetter *player, int cityIndex)
{
	//소유권자가 같아야지만 판매 할 수 있다
	if (board[cityIndex]->getOwnerID() == player->getID())
	{
		//판매가격은 최종가격만 받을 수 있다..패널티임
		player->setMoney(player->getMoney() + board[cityIndex]->curSellPrice());
		board[cityIndex]->LevelReset();
		board[cityIndex]->setOwnerID(noOwnerflag);
	}
	return true;
}

void Environment::oneMorePlayerDead()
{
	++deadPlayerCount;
}
