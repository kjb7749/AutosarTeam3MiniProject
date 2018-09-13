#pragma once

class City
{
private:
	//도시의 최종 레벨
	static const int maxLevel = 4;

	int ownerID;
	int curLevel;
	char *cityName;
	//다른 유저가 타일을 밟았을때 얻을 수 있는 수익
	int benefit[maxLevel];
	//타일의 구매&업그레이드 가격
	int buyPrice[maxLevel];
	//타일의 레벨별 판매 가격
	int sellPrice[maxLevel];

public:
	City(const char* cityName, int price[][4], int sellprice[][4], int benefit[][4]);
	~City();

	char* getName();
	int curSellPrice();
	int getPrice(int level);
	int getEnterfee();
	void setOwnerID(int ownerID);
	int getOwnerID();
	int LevelUp();
	void LevelReset();
};