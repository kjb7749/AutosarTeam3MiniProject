#pragma once
#include "Logic.h"
#include "IPlayerSetter.h"
#include "IEnvironmentSetter.h"


//���ʹ� �ܼ� ���� ���� ��ɸ�
//���ʹ� ���� ���� �̻��� ��ũ��Ʈ ��ü ������ ��ȭ�� �ʷ��ϴ� ��ɵ��� ����Ѵ�
class Player : public IPlayerSetter
{
private:
	//�÷��̾ �ǵ������� ���������� ���� ó���� ������ �̸� ����ϰ� Ư���̻� ��� �޾��� ��� ���ó�� �ϱ� ���� ��
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





///BuyPlan return value (0:�ƹ��͵� ����, 1:���� ����, 2:�ǹ�1 ����, 3:�ǹ�2 ����, 4:�ǹ�3 ����, 5:�Ұ����� �Ǽ�)
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