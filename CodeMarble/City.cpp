#include "City.h"
#include <string>

City::City(string cityName, int price[], int sellprice[], int benefit[])
{
	curLevel = 0;
	//this->cityName = new char[strlen(cityName) + 1];
	//strcpy(this->cityName, cityName);
	this->cityName = cityName;

	for (int i = 0; i < 4; ++i)
	{
		this->benefit[i] = benefit[i];
		this->buyPrice[i] = price[i];
		this->sellPrice[i] = sellprice[i];
	}
}
City::~City()
{

}

void City::setOwnerID(int ownerID)
{
	this->ownerID = ownerID;
}

int City::getPrice(int level)
{
	if (level >= 0 && level < maxLevel)
		return buyPrice[level];
	else
		return INT32_MAX;
}

int City::getEnterfee()
{
	return benefit[curLevel];
}

int City::getOwnerID()
{
	return ownerID;
}

int City::LevelUp()
{
	return ++curLevel;
}

int City::curSellPrice()
{
	return sellPrice[curLevel];
}

void City::LevelReset()
{
	curLevel = 0;
}

char* City::getName()
{
	return (char*)cityName.c_str();
}