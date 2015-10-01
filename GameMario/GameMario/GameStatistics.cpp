#include "GameStatistics.h"

GameStatistics *GameStatistics::Instance = new GameStatistics();

GameStatistics::GameStatistics(void)
{
}


GameStatistics::~GameStatistics(void)
{
}

GameStatistics* GameStatistics::GetInstance()
{
	if(Instance == 0)
	{
		Instance = new GameStatistics();
	}
	return Instance;
}

void GameStatistics::Initialize()
{
	_WolrdID = eWorldID::e1_1;
	_Score = 0;
	_Life = 3;
}

eWorldID GameStatistics::GetWorldID()
{
	return _WolrdID;
}

int GameStatistics::GetScore()
{
	return _WolrdID;
}

int GameStatistics::GetLife()
{
	return _WolrdID;
}

void GameStatistics::ChangeScore(int amount)
{
	_Score += amount;
}

void GameStatistics::ChangeLife(bool isIncrease)
{
	isIncrease? _Life++ : _Life--;
}

void GameStatistics::ChangeWorld(eWorldID worldID)
{
	_WolrdID = worldID;
}
