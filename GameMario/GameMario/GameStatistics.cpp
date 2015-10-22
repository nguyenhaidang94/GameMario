#include "GameStatistics.h"
#define GAME_TIME 400

GameStatistics *GameStatistics::Instance = NULL;

GameStatistics::GameStatistics(void)
{
}


GameStatistics::~GameStatistics(void)
{
}

GameStatistics* GameStatistics::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new GameStatistics();
	}
	return Instance;
}

void GameStatistics::Initialize()
{
	_WolrdID = eWorldID::e1_1;
	_CurrentSceneID = eSceneID::eMenu;
	_Score = 0;
	_Life = 3;
	_CoinCount = 0;
	_Time = GAME_TIME;
	_IsTimePause = true;
	_ListObjectAddToScene = new std::vector<GameObject*>();
}

void GameStatistics::Reset()
{
	_WolrdID = eWorldID::e1_1;
	_CurrentSceneID = eSceneID::eMenu;
	_Score = 0;
	_Life = 3;
	_CoinCount = 0;
	_Time = GAME_TIME;
}

eWorldID GameStatistics::GetWorldID()
{
	return _WolrdID;
}

int GameStatistics::GetScore()
{
	return _Score;
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

std::string GameStatistics::GetCurrentWorldName()
{
	switch (_WolrdID)
	{
	case e1_1:
	case eUnderground1_1:
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
	if(!_IsTimePause)
	{
		_Time--;
	}
}

void GameStatistics::IncreaseCoin()
{
	_CoinCount++;
}

void GameStatistics::ChangeWorld(eWorldID worldID)
{
	_WolrdID = worldID;
}

void GameStatistics::ResetTime()
{
	_IsTimePause = false;
	_Time = GAME_TIME;
}

void GameStatistics::PauseTime()
{
	_IsTimePause = true;
}

eSceneID GameStatistics::GetSceneID()
{
	return _CurrentSceneID;
}

void GameStatistics::ChangeScene(eSceneID sceneID)
{
	_CurrentSceneID = sceneID;
}

void GameStatistics::AddObjectToScene(GameObject *object)
{
	_ListObjectAddToScene->push_back(object);
}

std::vector<GameObject*>* GameStatistics::GetListObjectAddToScene()
{
	return _ListObjectAddToScene;
}