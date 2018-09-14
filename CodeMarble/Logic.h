#pragma once
#include "DataViewer.h"

class Logic
{
	//인터페이스, 추후에 인터페이스 매개인자 값에 변동이 필요하다,, env 변수를 통째로 넘겨주는것이 아닌 필요한 것만 추출해서 제공한다 반드시!, 이는 사용자를 위함이다
public:
	Logic() {}
	virtual ~Logic() {}
	virtual int BuyPlan(DataViewer &view) = 0;
	virtual int SellPlan(DataViewer &view) = 0;
	virtual int TravelOtherCity(DataViewer &view) = 0;
};