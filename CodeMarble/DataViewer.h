#pragma once
#include <stdlib.h>
#include "IEnvironmentSetter.h"


class CityViewer
{
public:
	int size;
	ICityGetter **cities;
};

class PlayerViewer
{
public:
	int size;
	IPlayerGetter ** player;

//public:
//	IPlayerGetter * getPlayer(int index)
//	{
//		if (index < size)
//			return player[index];
//		else
//			return NULL;
//	}
};

class DataViewer
{
private:
	int cityViewerCount;
	CityViewer* cityViewer;
	int playerViewerCount;
	PlayerViewer* playerViewer;
	IEnvironmentSetter *env;
	IPlayerGetter **playerMemory;
	ICityGetter **cities;

public:
	DataViewer();
	virtual ~DataViewer();
	
	void setEnvironment(IEnvironmentSetter *env);
	void ClearMemory();

	//게임 공통 메소드, 라운드 수 같은
	int getRound_Mine();
	int getRound_Other(int ID);
	int* getRound_Others();

	//금전 메소드
	int getMoney_Mine();
	int getMoney_Other(int ID);
	int getMoney_Maximum();
	int getMoney_Minimum();
	int getMoney_Average();
	int getMoney_Median();
	//int* getMoney_Others();

	PlayerViewer& getPlayers_Other();
	PlayerViewer& getPlayers_All();
	PlayerViewer& getMe();
	PlayerViewer& getPlayer_WithID(int ID);

	CityViewer& getCities_Mine();					//나의 도시를 가져온다
	CityViewer& getCities_All();					//모든 도시 정보를 가져온다
	CityViewer& getCities_Others();
	CityViewer& getCities_Other(int ID);

	int encodeInt(int dst, int size, ...);
};