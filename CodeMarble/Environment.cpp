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


	//�ϴ� �ӽ÷� 8�ڸ� ����� ������.. ���߿� �������� �����ؾ���
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


	//���� ������ ���ú�
	string *cityNames = new string[cityCount];
	////������ ���ø� �������� ��� ����
	int **cityBenefits = new int*[cityCount];
	////������ ���� ���� ���
	int **cityPrices = new int*[cityCount];
	////������ ���� �ǸŰ��� (���� ���� ���ݸ� �ݿ��Ǿ� �Ǹŵ�)
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
	do		//�������� �������� �Ѵ�
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

//����� �����Ͱ� �ȵ�� ���� ������ �Ƹ� �������̽��� �޾Ƽ� �׷��� �ƴѰ� �ʹ�
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

	//������ �������� false�� ��ȯ
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
		//���� �����Ҷ� �����Ϸ��Ѵٸ�
		cout << player->getName() << " ���� �����ѵ� ���� " << board[cityIndex]->getName() << "�� �����Ϸ��� �ϼ̽��ϴ�." << endl;
		return false;
	}
	else
	{
		player->setMoney(player->getMoney() - board[cityIndex]->getPrice(level));
		board[cityIndex]->setOwnerID(player->getID());
		cout << player->getName() << " ���� " << board[cityIndex]->getName() << "�� ���� �ϼ̽��ϴ�." << endl;
	}
	return true;
}

bool Environment::sellCity(IPlayerSetter *player, int cityIndex)
{
	//�������ڰ� ���ƾ����� �Ǹ� �� �� �ִ�
	if (board[cityIndex]->getOwnerID() == player->getID())
	{
		//�ǸŰ����� �������ݸ� ���� �� �ִ�..�г�Ƽ��
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
