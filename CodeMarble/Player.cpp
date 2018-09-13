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
	//인덱스를 이동시켜줍니다
	curIndex = (curIndex + value) % env->getCityCount();
	//여행한 도시의 정보를 받아옵니다
	City *pCity = env->getCityWithIndex(curIndex);
	if (pCity != NULL)
	{
		//if (ID != pCity->getOwnerID())		///이 구문이 필요 없다고 생각한 이유는 구매 로직은 어떠한 상황에서건 실행되어야 하기 때문이다
		{
			//주인이 있는 도시인지 확인한다
			Player *cityOwner = env->whosCity(pCity->getOwnerID());

			//만약 주인이 있는 도시라면
			if (cityOwner != NULL)
			{
				//통행료를 계산한다
				int enterfee = pCity->getEnterfee();

				//돈을 냈는데도 잔금이 남아있다면
				int debt;
				if ((debt = giveMoneyTo(enterfee, cityOwner)) != 0)
				{
					//먼저 SellPlan을 동작시킨다
					int sellOrderp = SellPlan(*env);
					//만약 판매후에도 대금 지급이 불가능하면 패배시킨다 그 조건을 넣어야 할듯
					//모든 경우에 사용자의 아웃풋을 검증하는 과정이 필요하다
					///검증

					//판매전략으로 도시를 판매 했음에도 불구하고 지불하지 못한다면 플레이어는 파산하게 된다
					if (!giveMoneyTo(debt, cityOwner))
					{
						IamDie();		//나 죽어~
					}
				}
				TravelOtherCity(*env);
				///검증코드
			}
		}
		//연산을 처리합니다
		int buyOrder = BuyPlan(*env);
		///검증코드
	}
}

void Player::IamDie()
{
	//가지고 있는 모든 도시를 초기화 한다
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

	cout << "주사위 굴림 " << diceNumber[0] << ", " << diceNumber[1] << " : " << diceNumber[0] + diceNumber[1] << endl;

	Move(diceNumber[0] + diceNumber[1]);

	if (diceNumber[0] == diceNumber[1])
	{
		//주사위 한번 더 굴리기
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
		//전재산을 몰수한다, 하지만 판매가 필요한 특수 상황이다
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