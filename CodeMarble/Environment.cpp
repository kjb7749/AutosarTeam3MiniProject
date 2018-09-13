#include "Environment.h"
#include <stdlib.h>
#include "Player.h"

Environment::Environment()
{
	numberOfPlayer = 0;
	board = NULL;
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

	//������ �������� false�� ��ȯ
	if (false)
		return false;
	return true;
}

Player* Environment::getWinner()
{
	Player *winner = NULL;

	return winner;
}