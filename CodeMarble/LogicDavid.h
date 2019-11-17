#pragma once
#include "Logic.h"
#include <iostream>

using namespace std;

class LogicDavid : public Logic
{
	virtual int BuyPlan(DataViewer &view)
	{		
		int my_money = view.getMoney_Mine();
		PlayerViewer other = view.getPlayers_Other();
		PlayerViewer me = view.getMe();

		view.getCities_Mine();

		return 1;
	}
	virtual int SellPlan(int debt, DataViewer &view)
	{
		int result = 0;
		//5번을 판매한다

		result = view.encodeInt(result, 1, 5);
		return result;
	}
	virtual int TravelOtherCity(DataViewer &view)
	{
		return 1;
	}
};