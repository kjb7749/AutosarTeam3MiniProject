#pragma once

class City
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

	char* getName();
	int curSellPrice();
	int getPrice(int level);
	int getEnterfee();
	void setOwnerID(int ownerID);
	int getOwnerID();
	int LevelUp();
	void LevelReset();
};