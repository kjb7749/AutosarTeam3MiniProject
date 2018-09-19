#include "Environment.h"
#include <stdlib.h>
#include "Player.h"
#include "City.h"
#include <iostream>
#include "tinyxml2.h"
#include <tchar.h>

using namespace std;
using namespace tinyxml2;

Environment::Environment()
{
	playerCount = 0;
	board = nullptr;
	deadPlayerCount = 0;
	cityCount = 0;


	//일단 임시로 8자리 만들어 놓은것.. 나중에 동적으로 변경해야함
	players = new Player*[8];

	XMLDocument readDoc;

	readDoc.LoadFile("D:/Projects/AutosarTeam3MiniProject/Resources/mapinfo.xml");
	XMLElement* rootNode = readDoc.FirstChildElement();
	XMLElement* node = rootNode->FirstChildElement("cities")->FirstChildElement("city");

	while (node != nullptr)
	{
		++cityCount;
		node = node->NextSiblingElement();
	}


	//도시 데이터 세팅부
	string *cityNames = new string[cityCount];
	////레벨별 도시를 밞음으로 얻는 이익
	int **cityBenefits = new int*[cityCount];
	////레벨별 도시 구매 비용
	int **cityPrices = new int*[cityCount];
	////레벨별 도시 판매가격 (가장 최종 가격만 반영되어 판매됨)
	int **citySellPrices = new int*[cityCount];


	node = rootNode->FirstChildElement("cities")->FirstChildElement("city");
	int indexForCount = 0;

	while (node != nullptr)
	{
		cityNames[indexForCount] = node->FirstChildElement("cityName")->GetText();
		int localIndex;

		cityBenefits[indexForCount] = new int[4];
		localIndex = 0;
		const XMLAttribute* atrb = node->FirstChildElement("cityBenefit")->FirstAttribute();
		do
		{
			cityBenefits[indexForCount][localIndex++] = atoi(atrb->Value());
		} while (atrb = atrb->Next());

		////////////////////////////
		cityPrices[indexForCount] = new int[4];
		localIndex = 0;
		atrb = node->FirstChildElement("cityBuyPrice")->FirstAttribute();
		do
		{
			cityPrices[indexForCount][localIndex++] = atoi(atrb->Value());
		} while (atrb = atrb->Next());

		//////////////////////////////////
		citySellPrices[indexForCount] = new int[4];
		localIndex = 0;
		atrb = node->FirstChildElement("citySellPrice")->FirstAttribute();
		do
		{
			citySellPrices[indexForCount][localIndex++] = atoi(atrb->Value());
		} while (atrb = atrb->Next());

		++indexForCount;
		node = node->NextSiblingElement();
	}


	board = new City*[cityCount];

	for (int i = 0; i < cityCount; ++i)
	{
		board[i] = new City(cityNames[i], cityPrices[i], citySellPrices[i], cityBenefits[i]);
	}

	randomNoOwner();

	delete[] cityNames;
	for (int i = 0; i < cityCount; ++i)
	{
		delete[] cityBenefits[i];
		delete[] cityPrices[i];
		delete[] citySellPrices[i];
	}
	delete[] cityBenefits;
	delete[] cityPrices;
	delete[] citySellPrices;

}
Environment::~Environment()
{

}

int Environment::randomNoOwner()
{
	bool flag = false;
	do		//랜덤으로 정해져야 한다
	{
		noOwnerflag = rand();
		flag = false;
		for (int i = 0; i < playerCount; ++i)
		{
			if (players[i]->getID() == noOwnerflag)
			{
				flag = true;
				break;
			}
		}
	} while (flag);
	for (int i = 0; i < cityCount; ++i)
	{
		board[i]->setOwnerID(noOwnerflag);
	}
	return noOwnerflag;
}

int Environment::getPlayerCount()
{
	return playerCount;
}

IPlayerGetter * Environment::getCaller()
{
	return caller;
}

void Environment::setCaller(IPlayerSetter *caller)
{
	this->caller = (Player*)caller;
}

void Environment::setSubsidy(int subsidy)
{
	this->subsidy = subsidy;
}

IPlayerGetter** Environment::getPlayers()
{
	return (IPlayerGetter**)players;
}

IPlayerGetter* Environment::getPlayer(int ID)
{
	for (int i = 0; i < playerCount; ++i)
	{
		if (players[i]->getID() == ID)
			return (IPlayerGetter*)players[i];
	}
	return nullptr;
}
int Environment::getSubsidy()
{
	return subsidy;
}

IPlayerSetter* Environment::whosCity(int cityOwnerID)
{
	for (int i = 0; i < playerCount; ++i)
	{
		if (players[i]->getID() == cityOwnerID)
			return players[i];
	}

	return nullptr;
}

//제대로 데이터가 안들어 오는 이유는 아마 인터페이스로 받아서 그런게 아닌가 싶다
void Environment::appendUser(Player *p)
{
	players[playerCount++] = p;
	randomNoOwner();
}

int Environment::getCityCount()
{
	return cityCount;
}

ICityGetter* Environment::getCity(int index)
{
	if (index >= cityCount || index < 0)
		return nullptr;
	else
	{
		if (board != nullptr)
		{
			if (board[index] != nullptr)
				return board[index];
			else
				return nullptr;
		}
		return nullptr;
	}
}

ICityGetter** Environment::getCities()
{
	return (ICityGetter**)board;
}

bool Environment::playGame()
{
	for (int i = 0; i < playerCount; ++i)
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
	IPlayerGetter *winner = nullptr;

	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		if (!players[i]->amIDead())
		{
			break;
			winner = players[i];
		}
	}
	return winner;
}


bool Environment::buyCity(IPlayerSetter *player, int cityIndex, int level)
{
	if (player->getMoney() < board[cityIndex]->getPrice(level))
	{
		//돈이 부족할때 구매하려한다면
		cout << player->getName() << " 돈이 부족한데 도시 " << board[cityIndex]->getName() << "를 구입하려고 하셨습니다." << endl;
		return false;
	}
	else
	{
		player->setMoney(player->getMoney() - board[cityIndex]->getPrice(level));
		board[cityIndex]->setOwnerID(player->getID());
		cout << player->getName() << " 도시 " << board[cityIndex]->getName() << "를 구입 하셨습니다." << endl;
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
