#pragma once
#include "DataViewer.h"

class Logic
{
	//�������̽�, ���Ŀ� �������̽� �Ű����� ���� ������ �ʿ��ϴ�,, env ������ ��°�� �Ѱ��ִ°��� �ƴ� �ʿ��� �͸� �����ؼ� �����Ѵ� �ݵ��!, �̴� ����ڸ� �����̴�
public:
	Logic() {}
	virtual ~Logic() {}
	virtual int BuyPlan(DataViewer &view) = 0;
	virtual int SellPlan(DataViewer &view) = 0;
	virtual int TravelOtherCity(DataViewer &view) = 0;
};