#pragma once
#include "IEnvironmentSetter.h"

class DataViewer
{
private:
	IEnvironmentSetter *env;

public:
	DataViewer();
	virtual ~DataViewer();

	//������ ���� �޼ҵ���� ���⼭ �������ش�
	int getMyMoney();
};