#include "City.h"
#include <string>

City::City(const char* cityName, int price[][4], int sellprice[][4], int benefit[][4])
{
	curLevel = 0;
	this->cityName = new char[strlen(cityName) + 1];
	strcpy_s(this->cityName, sizeof(char) * strlen(cityName), cityName);

	////for(int j = 0; j < )
	//for (int i = 0; i < 4; ++i)
	//{
	//	this->benefit[i] = benefit[i][];
	//	this->price[i] = price[i];
	//}
}
City::~City()
{
	delete this->cityName;
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