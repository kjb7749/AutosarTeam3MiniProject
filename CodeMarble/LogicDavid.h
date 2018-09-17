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

		cout << other.size << me.size << endl;


		return 1;
	}
	virtual int SellPlan(DataViewer &view)
	{
		int result = 0;
		//5���� �Ǹ��Ѵ�

		result = view.encodeInt(result, 1, 5);
		return result;
	}
	virtual int TravelOtherCity(DataViewer &view)
	{
		return 1;
	}
};