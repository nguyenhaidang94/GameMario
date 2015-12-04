#include "GameStatistics.h"
#define GAME_TIME 400

GameStatistics *GameStatistics::_Instance = NULL;

GameStatistics::GameStatistics(void)
{
}


GameStatistics::~GameStatistics(void)
{
}

GameStatistics* GameStatistics::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new GameStatistics();
	}
	return _Instance;
}

void GameStatistics::Initialize()
{
	_WorldID = eWorldID::e1_1;
	_CurrentSceneID = eSceneID::ePlay;
	_Score = 0;
	_Life = 3;
	_CoinCount = 0;
	_IsReachCheckpoint = false;
	_Time = GAME_TIME;
	_IsTimePause = true;
	_ListObjectAddToScene = new std::vector<GameObject*>();
}

#pragma region Game stats
void GameStatistics::Reset()
{
	_WorldID = eWorldID::e1_1;
	_Score = 0;
	_Life = 3;
	_CoinCount = 0;
	_Time = GAME_TIME;
	_IsReachCheckpoint = false;

	//clear list object add
	for(int i = _ListObjectAddToScene->size() - 1; i >= 0; i--)
	{
		delete _ListObjectAddToScene->at(i);
		_ListObjectAddToScene->pop_back();
	}
}
eWorldID GameStatistics::GetWorldID()
{
	return _WorldID;
}

int GameStatistics::GetScore()
{
	return _Score;
}

int GameStatistics::GetLife()
{
	return _Life;
}

void GameStatistics::SetLife(int life)
{
	_Life = life;
}

int GameStatistics::GetCoinCount()
{
	return _CoinCount;
}

void GameStatistics::IncreaseCoin()
{
	_CoinCount++;
}

int GameStatistics::GetTime()
{
	return _Time;
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

void GameStatistics::ResetTime()
{
	_IsTimePause = false;
	_Time = GAME_TIME;
}

void GameStatistics::PauseTime()
{
	_IsTimePause = true;
}
#pragma endregion

#pragma region World, Scene and Objects
std::string GameStatistics::GetCurrentWorldName()
{
	switch (_WorldID)
	{
	case e1_1:
	case eUnderground1_1:
		return "1-1";
		break;
	case e1_2:
	case eUnderground1_2:
	case eRight1_2:
		return "1-2";
		break;
	case e1_3:
		return "1-3";
		break;
	case e1_4:
		return "1-4";
		break;
	default:
		break;
	}
}

void GameStatistics::ChangeWorld(eWorldID worldID)
{
	_WorldID = worldID;
}

void GameStatistics::GoToNextWorld()
{
	int index = _WorldID;
	if(_WorldID == eWorldID::e1_4)	//if not the last world
	{
		_WorldID = static_cast<eWorldID>(index);
	}
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

D3DXVECTOR2 GameStatistics::GetCheckpoint()
{
	//hard code...
	switch (_WorldID)
	{
	case e1_1:
		return D3DXVECTOR2(2640, 80);
		break;
	case e1_3:
		return D3DXVECTOR2(2160, 80);
	default:
		return D3DXVECTOR2(10000, 10000); //to make sure noone can reach checkpoint
		break;
	}
}

D3DXVECTOR2 GameStatistics::GetPositionEndGame()
{
	switch (_WorldID)
	{
	case e1_1:
		return D3DXVECTOR2(6540, 96);
		break;
	case e1_3:
		return D3DXVECTOR2(2160, 80);
	default:
		return D3DXVECTOR2(10000, 10000); //to make sure noone can reach checkpoint
		break;
	}
}
void GameStatistics::ChangeCheckpointStatus(bool isReachCheckpoint)
{
	_IsReachCheckpoint = isReachCheckpoint;
}

bool GameStatistics::IsMarioReachCheckpoint()
{
	return _IsReachCheckpoint;
}
#pragma endregion