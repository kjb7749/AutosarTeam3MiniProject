#pragma once
#include "Logic.h"
#include "IPlayerSetter.h"
#include "IEnvironmentSetter.h"


//게터는 단순 정보 접근 기능만
//세터는 정보 접근 이상의 콘크리트 객체 정보의 변화를 초래하는 기능들을 담당한다
class Player : public IPlayerSetter
{
private:
	//플레이어가 의도적으로 정상적이지 않은 처리를 보낼때 이를 경고하고 특정이상 경고를 받았을 경우 사망처리 하기 위한 값
	static const int maximumWarningCount = 5;
	int warningCount;
	bool deadflag;
	char *name;
	int ID;
	int curIndex;
	IEnvironmentSetter *env;
	DataViewer viewer;
	int money;
	Logic *logic;

public:
	Player(IEnvironmentSetter *env, int id, char *name, int seedMoney);
	virtual ~Player();

public:
	virtual int getMoney();
	virtual bool amIDead();
	virtual char *getName();
	virtual int getCurIndex();
	virtual int getID();

	virtual void setMoney(int money);
	virtual int RollDice();
	virtual void Move(int value);
	virtual void IamDie();
	virtual void Execute();
	virtual int giveMoneyTo(int amount, IPlayerSetter *other);
	virtual void increaseWarning();
	virtual void setLogic(Logic &logic);
};





///BuyPlan return value (0:아무것도 안함, 1:땅만 구매, 2:건물1 구매, 3:건물2 구매, 4:건물3 구매, 5:불가사의 건설)
///SellPlan return value ()
///

//class PlayerA : public Player
//{
//public:
//
//	PlayerA(Environment *env, int id, char *name, int seedMoney) : Player(env, id, name, seedMoney)
//	{
//		
//	}
//	~PlayerA()
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
//
//	virtual int TravelOtherCity(Environment &env)
//	{
//		return 0;
//	}
//};

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