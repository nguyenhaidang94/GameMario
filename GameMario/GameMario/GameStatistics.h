#pragma once
#include "GlobalVariables.h"
#include "GameObject.h"
#include <string>
#include <vector>

class GameStatistics
{
private:
	int _Score;
	int _Life;
	int _Time;
	int _CoinCount;
	eWorldID _WolrdID;
	eSceneID _CurrentSceneID;
	static GameStatistics *Instance;
	bool _IsTimePause;
	std::vector<GameObject*> *_ListObjectAddToScene;
public:
	GameStatistics(void);
	~GameStatistics(void);
	static GameStatistics *GetInstance();
	//Initialize GameStatistics
	void Initialize();
	//Reset statistics
	void Reset();
	//Get current worldID
	eWorldID GetWorldID();
	//Get current SceneID
	eSceneID GetSceneID();
	//Get current score
	int GetScore();
	//Get current life
	int GetLife();
	//Get current time
	int GetTime();
	//Get current coint count
	int GetCoinCount();
	//Get current WorldName in string
	std::string GetCurrentWorldName();
	//Increase/decrease score by a amount
	void ChangeScore(int amount);
	//Increase/decrease life by 1, true if increase, false if decrease
	void ChangeLife(bool isIncrease);
	//Decrease time by 1
	void DecreaseTime();
	//Increase/decrease life by 1, true if increase, false if decrease
	void IncreaseCoin();
	//Change current worldID
	void ChangeWorld(eWorldID worldID);
	//Change current sceneID
	void ChangeScene(eSceneID sceneID);
	//Reset time = 400s and unpause game
	void ResetTime();
	//Pause game time
	void PauseTime();
	//Add a object to Scene
	void AddObjectToScene(GameObject *object);
	//Get list object add to scene
	std::vector<GameObject*> *GetListObjectAddToScene();
};

