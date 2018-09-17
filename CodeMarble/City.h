#pragma once
#include "ICitySetter.h"
#include <string>

using namespace std;

class City : public ICitySetter
{
private:
	//도시의 최종 레벨
	static const int maxLevel = 4;

	int ownerID;
	int curLevel;
	string cityName;
	//다른 유저가 타일을 밟았을때 얻을 수 있는 수익 
	int benefit[maxLevel];
	//타일의 구매&업그레이드 가격
	int buyPrice[maxLevel];
	//타일의 레벨별 판매 가격
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