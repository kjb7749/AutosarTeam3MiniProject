#pragma once
#include "Logic.h"

class LogicDavid : public Logic
{	
	virtual int BuyPlan(DataViewer &view)
	{
		
		return 1;
	}
	virtual int SellPlan(DataViewer &view)
	{
		return 0;
	}
	virtual int TravelOtherCity(DataViewer &view)
	{
		return 1;
	}
};