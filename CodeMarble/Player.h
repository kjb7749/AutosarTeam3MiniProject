#pragma once
#include "City.h"
#include "Environment.h"


//어뷰징을 막아야 하니까 인터페이스 형태로 제공해야겠다
//모든 요소들을 파라미터 인터페이스로!

class Player
{
private:
	//플레이어가 의도적으로 정상적이지 않은 처리를 보낼때 이를 경고하고 특정이상 경고를 받았을 경우 사망처리 하기 위한 값
	static const int maximumWarningCount = 5;
	int warningCount;
	bool deadflag;
	char *name;
	int ID;
	int curIndex;
	Environment *env;
	int money;

public:
	Player(Environment *env, int id, char *name, int seedMoney);
	void setMoney(int money);
	int getMoney();

	virtual ~Player();

protected:
	int RollDice();

	void Move(int value);

public:

	void IamDie();

	bool amIDead();

	char *getName();
	int getCurIndex();

	void Execute();

	int getID();

	int giveMoneyTo(int amount, Player *other);

	void increaseWarning();

	//인터페이스, 추후에 인터페이스 매개인자 값에 변동이 필요하다,, env 변수를 통째로 넘겨주는것이 아닌 필요한 것만 추출해서 제공한다 반드시!, 이는 사용자를 위함이다
public:
	virtual int BuyPlan(Environment &env) = 0;
	virtual int SellPlan(Environment &env) = 0;
	virtual int TravelOtherCity(Environment &env) = 0;
};





///BuyPlan return value (0:아무것도 안함, 1:땅만 구매, 2:건물1 구매, 3:건물2 구매, 4:건물3 구매, 5:불가사의 건설)
///SellPlan return value ()
///

class PlayerA : public Player
{
public:

	PlayerA(Environment *env, int id, char *name, int seedMoney) : Player(env, id, name, seedMoney)
	{

	}
	~PlayerA()
	{

	}

	virtual int BuyPlan(Environment &env)
	{
		return 0;
	}

	virtual int SellPlan(Environment &env)
	{
		return 0;
	}

	virtual int TravelOtherCity(Environment &env)
	{
		return 0;
	}
};

//class PlayerB : public Player
//{
//public:
//
//	PlayerB(Environment *env) : Player(env)
//	{
//	
//	}
//	~PlayerB()
//	{
//
//	}
//
//	virtual int BuyPlan(Environment &env)
//	{
//		return 0;
//	}
//
//	virtual int SellPlan(Environment &env)
//	{
//		return 0;
//	}
//};