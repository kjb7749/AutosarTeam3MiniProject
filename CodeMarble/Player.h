#pragma once
#include "City.h"
#include "Environment.h"


//���¡�� ���ƾ� �ϴϱ� �������̽� ���·� �����ؾ߰ڴ�
//��� ��ҵ��� �Ķ���� �������̽���!

class Player
{
private:
	//�÷��̾ �ǵ������� ���������� ���� ó���� ������ �̸� ����ϰ� Ư���̻� ��� �޾��� ��� ���ó�� �ϱ� ���� ��
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

	//�������̽�, ���Ŀ� �������̽� �Ű����� ���� ������ �ʿ��ϴ�,, env ������ ��°�� �Ѱ��ִ°��� �ƴ� �ʿ��� �͸� �����ؼ� �����Ѵ� �ݵ��!, �̴� ����ڸ� �����̴�
public:
	virtual int BuyPlan(Environment &env) = 0;
	virtual int SellPlan(Environment &env) = 0;
	virtual int TravelOtherCity(Environment &env) = 0;
};





///BuyPlan return value (0:�ƹ��͵� ����, 1:���� ����, 2:�ǹ�1 ����, 3:�ǹ�2 ����, 4:�ǹ�3 ����, 5:�Ұ����� �Ǽ�)
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