#pragma once
#include "ICitySetter.h"
#include <string>

using namespace std;

class City : public ICitySetter
{
private:
	//������ ���� ����
	static const int maxLevel = 4;

	int ownerID;
	int curLevel;
	string cityName;
	//�ٸ� ������ Ÿ���� ������� ���� �� �ִ� ���� 
	int benefit[maxLevel];
	//Ÿ���� ����&���׷��̵� ����
	int buyPrice[maxLevel];
	//Ÿ���� ������ �Ǹ� ����
	int sellPrice[maxLevel];

public:
	City(string cityName, int price[], int sellprice[], int benefit[]);
	~City();

	virtual string getName();
	virtual int curSellPrice();
	virtual int getPrice(int level);
	virtual int getEnterfee();
	virtual int getOwnerID();

	virtual void setOwnerID(int ownerID);
	virtual int LevelUp();
	virtual void LevelReset();
};