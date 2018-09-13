#include "Player.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


Player::Player(Environment *env, int id, char *name, int seedMoney)
{
	warningCount = 0;
	curIndex = 0;
	deadflag = false;

	this->env = env;
}

void Player::setMoney(int money)
{
	this->money = money;
}

Player::~Player()
{

}

int Player::RollDice()
{
	return rand() % 6 + 1;
}

void Player::Move(int value)
{
	//�ε����� �̵������ݴϴ�
	curIndex = (curIndex + value) % env->getCityCount();
	//������ ������ ������ �޾ƿɴϴ�
	City *pCity = env->getCityWithIndex(curIndex);
	if (pCity != NULL)
	{
		//if (ID != pCity->getOwnerID())		///�� ������ �ʿ� ���ٰ� ������ ������ ���� ������ ��� ��Ȳ������ ����Ǿ�� �ϱ� �����̴�
		{
			//������ �ִ� �������� Ȯ���Ѵ�
			Player *cityOwner = env->whosCity(pCity->getOwnerID());

			//���� ������ �ִ� ���ö��
			if (cityOwner != NULL)
			{
				//����Ḧ ����Ѵ�
				int enterfee = pCity->getEnterfee();

				//���� �´µ��� �ܱ��� �����ִٸ�
				int debt;
				if ((debt = giveMoneyTo(enterfee, cityOwner)) != 0)
				{
					//���� SellPlan�� ���۽�Ų��
					int sellOrderp = SellPlan(*env);
					//���� �Ǹ��Ŀ��� ��� ������ �Ұ����ϸ� �й��Ų�� �� ������ �־�� �ҵ�
					//��� ��쿡 ������� �ƿ�ǲ�� �����ϴ� ������ �ʿ��ϴ�
					///����

					//�Ǹ��������� ���ø� �Ǹ� �������� �ұ��ϰ� �������� ���Ѵٸ� �÷��̾�� �Ļ��ϰ� �ȴ�
					if (!giveMoneyTo(debt, cityOwner))
					{
						IamDie();		//�� �׾�~
					}
				}
				TravelOtherCity(*env);
				///�����ڵ�
			}
		}
		//������ ó���մϴ�
		int buyOrder = BuyPlan(*env);
		///�����ڵ�
	}
}

void Player::IamDie()
{
	//������ �ִ� ��� ���ø� �ʱ�ȭ �Ѵ�
	deadflag = true;
}

bool Player::amIDead()
{
	return deadflag;
}

char *Player::getName()
{
	return name;
}

int Player::getCurIndex()
{
	return curIndex;
}

void Player::Execute()
{
	int diceNumber[2] = { RollDice(), RollDice() };

	cout << "�ֻ��� ���� " << diceNumber[0] << ", " << diceNumber[1] << " : " << diceNumber[0] + diceNumber[1] << endl;

	Move(diceNumber[0] + diceNumber[1]);

	if (diceNumber[0] == diceNumber[1])
	{
		//�ֻ��� �ѹ� �� ������
		Execute();
	}
}

int Player::getID()
{
	return ID;
}

int Player::giveMoneyTo(int amount, Player *other)
{
	if (money - amount < 0)
	{
		int remainDebt = amount - money;
		//������� �����Ѵ�, ������ �ǸŰ� �ʿ��� Ư�� ��Ȳ�̴�
		other->money += money;
		money = 0;
		return remainDebt;
	}
	else
	{
		money -= amount;
		other->money += amount;
		return 0;
	}
}