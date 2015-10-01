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
	_CoinCount = 0;
	_Time = 400;
}

void GameStatistics::Reset()
{
	_WolrdID = eWorldID::e1_1;
	_Score = 0;
	_Life = 3;
	_CoinCount = 0;
	_Time = 400;
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
	return _Life;
}

int GameStatistics::GetCoinCount()
{
	return _CoinCount;
}

int GameStatistics::GetTime()
{
	return _Time;
}

string GameStatistics::GetCurrentWorldName()
{
	switch (_WolrdID)
	{
	case e1_1:
		return "1_1";
		break;
	case e1_2:
		return "1_2";
		break;
	case e1_3:
		return "1_3";
		break;
	case e1_4:
		return "1_4";
		break;
	default:
		break;
	}
}

void GameStatistics::ChangeScore(int amount)
{
	_Score += amount;
}

void GameStatistics::ChangeLife(bool isIncrease)
{
	isIncrease? _Life++ : _Life--;
}

void GameStatistics::DecreaseTime()
{
	_Time--;
}

void GameStatistics::IncreaseCoin()
{
	_CoinCount++;
}

void GameStatistics::ChangeWorld(eWorldID worldID)
{
	_WolrdID = worldID;
}
