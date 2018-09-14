#pragma once
#include "ICitySetter.h"

class City : virtual public ICityGetter, public ICitySetter
{
private:
	//������ ���� ����
	static const int maxLevel = 4;

	int ownerID;
	int curLevel;
	char *cityName;
	//�ٸ� ������ Ÿ���� ������� ���� �� �ִ� ����
	int benefit[maxLevel];
	//Ÿ���� ����&���׷��̵� ����
	int buyPrice[maxLevel];
	//Ÿ���� ������ �Ǹ� ����
	int sellPrice[maxLevel];

public:
	City(const char* cityName, int price[][4], int sellprice[][4], int benefit[][4]);
	~City();

	virtual char* getName();
	virtual int curSellPrice();
	virtual int getPrice(int level);
	virtual int getEnterfee();
	virtual int getOwnerID();

	virtual void setOwnerID(int ownerID);
	virtual int LevelUp();
	virtual void LevelReset();
};