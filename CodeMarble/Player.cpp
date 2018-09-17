#include "Player.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


Player::Player(IEnvironmentSetter *env, int id, char *name, int seedMoney)
{
	viewer.setEnvironment(env);
	warningCount = 0;
	curIndex = 0;
	deadflag = false;


	this->name = new char[sizeof(char)*strlen(name)+1];
	memset(this->name, NULL, strlen(name+1));
	strcpy(this->name, name);

	this->money = seedMoney;
	this->ID = id;
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

void Player::Move(int value)
{
	//인덱스를 이동시켜줍니다
	if ((curIndex + value) >= env->getCityCount())
	{
		//한바퀴를 돌았기 때문에 추가금을 지원합니다
		setMoney(getMoney() + env->getSubsidy());
		cout << "한바퀴를 돌아서 지원금" << env->getSubsidy() << "을 받았습니다!" << endl;
	}
	curIndex = (curIndex + value) % env->getCityCount();
	//여행한 도시의 정보를 받아옵니다
	ICityGetter *pCity = env->getCityWithIndex(curIndex);
	if (pCity != NULL)
	{
		//if (ID != pCity->getOwnerID())		///이 구문이 필요 없다고 생각한 이유는 구매 로직은 어떠한 상황에서건 실행되어야 하기 때문이다
		{
			//주인이 있는 도시인지 확인한다
			env->setCaller(this);
			IPlayerSetter *cityOwner = env->whosCity(pCity->getOwnerID());

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
					viewer.ClearMemory();
					int sellOrder = logic->SellPlan(viewer);
					///유저의 아웃풋 검증
					//디코딩 후 판매한다
					//디코딩을 함수로 하지 않는 이유는 함수를 만들기 귀찮아서 이다... 배열 형태로 받는건 효율적이지도 편하지도 않다 그냥 직접 코드에 구현하자
					for (int i = 0; i < 32; ++i)
					{
						int flag = sellOrder & (0x00000001 << i);
						if (flag > 0)
						{
							if (env->sellCity(this, i) == false)
							{
								//있지도 않는 도시를 판매하려고 했으므로 경고 카운트를 증기시킨다
								increaseWarning();
							}
						}
					}
					//판매전략으로 도시를 판매 했음에도 불구하고 지불하지 못한다면 플레이어는 파산하게 된다
					if (!giveMoneyTo(debt, cityOwner))
					{
						IamDie();		//나 죽어~
					}
				}
				//viewer.ClearMemory();
				//logic->TravelOtherCity(viewer);
				///검증코드
				//하지만 아직 의미가 없다
			}
		}
		//연산을 처리합니다
		env->setCaller(this);
		viewer.ClearMemory();
		int buyLevel = logic->BuyPlan(viewer);
		///검증코드
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
	//가지고 있는 모든 도시를 초기화 한다
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

	cout << "주사위 굴림 " << diceNumber[0] << ", " << diceNumber[1] << " : " << diceNumber[0] + diceNumber[1] << endl;

	Move(diceNumber[0] + diceNumber[1]);

	if (diceNumber[0] == diceNumber[1])
	{
		cout << "더블! 주사위 한번 더 굴리기!" << endl;
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
		//전재산을 몰수한다, 하지만 판매가 필요한 특수 상황이다
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