#include "DataViewer.h"
#include "Player.h"
#include <stdlib.h>
#include <cstdarg>

DataViewer::DataViewer()
{
}

DataViewer::~DataViewer()
{
	delete[] cityViewer;
	delete[] playerViewer;
}

void DataViewer::ClearMemory()
{
	cityViewerCount = 0;
	playerViewerCount = 0;
}

void DataViewer::setEnvironment(IEnvironmentSetter *env)
{
	this->env = env;

	////해당 로직은 종속성으로 인해 env 다음에 설정되어야 한다. 하지만 이 위치가 좋지 않은것 같다
	cityViewerCount = 8;
	playerViewerCount = 8;

	cityViewer = new CityViewer[cityViewerCount];
	for (int i = 0; i < cityViewerCount; ++i)
	{
		cityViewer[i].cities = new ICityGetter*[env->getCityCount()];
		cityViewer[i].size = 0;
	}

	playerViewer = new PlayerViewer[playerViewerCount];
	for (int i = 0; i < playerViewerCount; ++i)
	{
		playerViewer[i].player = new IPlayerGetter*[env->getPlayerCount()];
		playerViewer[i].size = 0;
	}
///
}

int DataViewer::getMoney_Mine()
{
	return env->getCaller()->getMoney();
}

PlayerViewer& DataViewer::getMe()
{
	PlayerViewer playerViewer = this->playerViewer[playerViewerCount++];

	playerViewer.size = 0;
	playerViewer.player[playerViewer.size++] = env->getCaller();
	return playerViewer;
}

PlayerViewer& DataViewer::getPlayers_All()
{
	PlayerViewer playerViewer = this->playerViewer[playerViewerCount++];
	
	playerViewer.size = 0;
	for (int i = 0; i < env->getPlayerCount(); ++i)
	{
		playerViewer.player[playerViewer.size++] = env->getPlayers()[i];
	}
	return playerViewer;
}

PlayerViewer& DataViewer::getPlayers_Other()
{
	PlayerViewer *playerViewer = &this->playerViewer[playerViewerCount++];

	IPlayerGetter **players = env->getPlayers();
	playerViewer->size = 0;
	for (int i = 0; i < env->getPlayerCount(); ++i)
	{
		int myid = env->getCaller()->getID();
		int otherid = players[i]->getID();
		if (myid != otherid)
		{
			playerViewer->player[playerViewer->size++] = players[i];	
		}
	}
	return *playerViewer;
}

int DataViewer::encodeInt(int dst, int size, ...)
{
	va_list al;
	va_start(al, size);
	for (int i = 0; i < size; ++i)
	{
		int n = va_arg(al, int);
		if (n >= 0 && n < 32)
		{
			int bit = 0x00000001 << n;
			dst |= bit;
		}
	}
	va_end(al);

	return dst;
}