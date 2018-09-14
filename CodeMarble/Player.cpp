#include "Player.h"
#include <stdlib.h>
#include <iostream>
#include <cstdarg>
using namespace std;


Player::Player(IEnvironmentSetter *env, int id, char *name, int seedMoney)
{
	warningCount = 0;
	curIndex = 0;
	deadflag = false;
	money = seedMoney;

	this->env = env;
}

void Player::setMoney(int money)
{
	this->money = money;
}

int Player::getMoney()
{
	return money;
}

Player::~Player()
{

}

int Player::RollDice()
{
	return rand() % 6 + 1;
}

void Player::increaseWarning()
{
	++warningCount;
	if (warningCount > maximumWarningCount)
	{
		IamDie();
	}
}

int encodeInt(int dst, int size, ...)
{
	va_list al;
	va_start(al, size);
	for (int i = 0; i < size; ++i)
	{
		int n = va_arg(al, int);
		if (n >= 0 && n < 32)
		{
			int bit = 0x00000001 << n;
			dst |= bit;
		}			
	}
	va_end(al);

	return dst;
}

void Player::Move(int value)
{
	//�ε����� �̵������ݴϴ�
	if ((curIndex + value) >= env->getCityCount())
	{
		//�ѹ����� ���ұ� ������ �߰����� �����մϴ�
		setMoney(getMoney() + env->getSubsidy());
		cout << "�ѹ����� ���Ƽ� ������" << env->getSubsidy() << "�� �޾ҽ��ϴ�!" << endl;
	}
	curIndex = (curIndex + value) % env->getCityCount();
	//������ ������ ������ �޾ƿɴϴ�
	ICityGetter *pCity = env->getCityWithIndex(curIndex);
	if (pCity != NULL)
	{
		//if (ID != pCity->getOwnerID())		///�� ������ �ʿ� ���ٰ� ������ ������ ���� ������ ��� ��Ȳ������ ����Ǿ�� �ϱ� �����̴�
		{
			//������ �ִ� �������� Ȯ���Ѵ�
			IPlayerSetter *cityOwner = env->whosCity(pCity->getOwnerID());

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
					int sellOrder = logic->SellPlan((DataViewer&)*env);
					///������ �ƿ�ǲ ����
					//���ڵ� �� �Ǹ��Ѵ�
					//���ڵ��� �Լ��� ���� �ʴ� ������ �Լ��� ����� �����Ƽ� �̴�... �迭 ���·� �޴°� ȿ���������� �������� �ʴ� �׳� ���� �ڵ忡 ��������
					for (int i = 0; i < 32; ++i)
					{
						int flag = sellOrder & (0x00000001 << i);
						if (flag > 0)
						{
							if (env->sellCity(this, i) == false)
							{
								//������ �ʴ� ���ø� �Ǹ��Ϸ��� �����Ƿ� ��� ī��Ʈ�� �����Ų��
								increaseWarning();
							}
						}
					}
					//�Ǹ��������� ���ø� �Ǹ� �������� �ұ��ϰ� �������� ���Ѵٸ� �÷��̾�� �Ļ��ϰ� �ȴ�
					if (!giveMoneyTo(debt, cityOwner))
					{
						IamDie();		//�� �׾�~
					}
				}
				//logic->TravelOtherCity(*env);
				///�����ڵ�
				//������ ���� �ǹ̰� ����
			}
		}
		//������ ó���մϴ�
		int buyLevel = logic->SellPlan((DataViewer&)*env);
		///�����ڵ�
		if (env->buyCity(this, curIndex, buyLevel) == false)
		{
			increaseWarning();
		}
	}
}

void Player::setLogic(Logic &logic)
{
	this->logic = &logic;
}

void Player::IamDie()
{
	//������ �ִ� ��� ���ø� �ʱ�ȭ �Ѵ�
	deadflag = true;
	env->oneMorePlayerDead();
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
		cout << "����! �ֻ��� �ѹ� �� ������!" << endl;
		Execute();
	}
}

int Player::getID()
{
	return ID;
}

int Player::giveMoneyTo(int amount, IPlayerSetter *other)
{
	if (money - amount < 0)
	{
		int remainDebt = amount - money;
		//������� �����Ѵ�, ������ �ǸŰ� �ʿ��� Ư�� ��Ȳ�̴�
		other->setMoney(other->getMoney() + money);
		money = 0;
		return remainDebt;
	}
	else
	{
		money -= amount;
		other->setMoney(other->getMoney() + amount);
		return 0;
	}
}