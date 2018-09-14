#pragma once
#include "IEnvironmentSetter.h"

class DataViewer
{
private:
	IEnvironmentSetter *env;

public:
	DataViewer();
	virtual ~DataViewer();

	//데이터 접근 메소드들을 여기서 구현해준다
	int getMyMoney();
};