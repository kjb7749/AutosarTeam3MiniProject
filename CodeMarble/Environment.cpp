#include "Environment.h"
#include <stdlib.h>
#include "Player.h"
#include "City.h"
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

Environment::Environment()
{
	numberOfPlayer = 0;
	board = NULL;
	deadPlayerCount = 0;
	cityCount = 0;


	//�ϴ� �ӽ÷� 8�ڸ� ����� ������.. ���߿� �������� �����ؾ���
	players = new Player*[8];

	XMLDocument readDoc;

	readDoc.LoadFile("D:/Projects/AutosarTeam3MiniProject/Resources/mapinfo.xml");
	XMLElement* rootNode = readDoc.FirstChildElement();
	XMLElement* node = rootNode->FirstChildElement("cities")->FirstChildElement("city");

	while (node != NULL)
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

	while (node != NULL)
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
		for (int i = 0; i < numberOfPlayer; ++i)
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
	return numberOfPlayer;
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

//����� �����Ͱ� �ȵ�� ���� ������ �Ƹ� �������̽��� �޾Ƽ� �׷��� �ƴѰ� �ʹ�
void Environment::appendUser(Player *p)
{
	players[numberOfPlayer++] = p;
	randomNoOwner();
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

	//������ �������� false�� ��ȯ
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
		//���� �����Ҷ� �����Ϸ��Ѵٸ�
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
