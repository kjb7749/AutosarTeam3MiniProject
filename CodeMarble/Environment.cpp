#include "Environment.h"
#include <stdlib.h>
#include "Player.h"
#include <iostream>

using namespace std;

Environment::Environment()
{
	noOwnerflag = -1;		//�������� �������� �Ѵ�
	numberOfPlayer = 0;
	board = NULL;
	deadPlayerCount = 0;
	//���� ������ ���ú�

	//const char *cityNames[] = { "����", "����" };

	////������ ���ø� �������� ��� ����
	//int cityBenefits[][4] = { {1,2,3} };
	////������ ���� ���� ���
	//int cityPrices[][4] = { {} };
	////������ ���� �ǸŰ��� (���� ���� ���ݸ� �ݿ��Ǿ� �Ǹŵ�)
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
