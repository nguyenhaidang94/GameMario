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
	eWorldID _WorldID;
	eSceneID _CurrentSceneID;
	static GameStatistics *_Instance;
	bool _IsTimePause;
	std::vector<GameObject*> *_ListObjectAddToScene;
	bool _IsReachCheckpoint;	//if mario reach check point in the map
	bool _IsPerformWorldClearStatus;	//mario reach FlagPole to perform count down time and increase score
public:
	GameStatistics(void);
	~GameStatistics(void);
	static GameStatistics *GetInstance();
	//Initialize GameStatistics
	void Initialize();
	

	//------Game stats----
	//Reset statistics, use after start new playthrought in menuscene
	void Reset();
	//Get current score
	int GetScore();
	//Increase/decrease score by a amount
	void ChangeScore(int amount);
	//Get current life
	int GetLife();
	//Set current life
	void SetLife(int life);
	//Increase/decrease life by 1, true if increase, false if decrease
	void ChangeLife(bool isIncrease);
	//Increase/decrease life by 1, true if increase, false if decrease
	void IncreaseCoin();
	//Get current coint count
	int GetCoinCount();

	//Get current time
	int GetTime();
	//Decrease time by 1
	void DecreaseTime();
	//Reset when start new world (set time = 400s and unpause game, stop perform mario reach flagpole status)
	void ResetWorld();
	//Pause game time
	void PauseTime(bool isPause);
	//----------------------------

	//------world, scene and objects----
	//Get current worldID
	eWorldID GetWorldID();
	//Get current SceneID
	eSceneID GetSceneID();
	//Change current worldID to next world
	void GoToNextWorld();
	//Change current worldID
	void ChangeWorld(eWorldID worldID);
	//Change current sceneID
	void ChangeScene(eSceneID sceneID);
	//Get current WorldName in string
	std::string GetCurrentWorldName();
	//Call this when mario reach FlagPole to Perform count down time and increase score
	void PerformMarioReachFlagpoleStatus();
	//Check if mario reach FlagPole to Perform count down time and increase score
	bool IsPerformMarioReachFlagpoleStatus();

	//Add a object to Scene
	void AddObjectToScene(GameObject *object);
	//Get list object add to scene
	std::vector<GameObject*> *GetListObjectAddToScene();
	//----------------------------

	//------control switch world, checkpoint----
	//Get checkpoint in current world
	D3DXVECTOR2 GetCheckpoint();
	//Get Position end game
	D3DXVECTOR2 GetPositionEndGame();
	//Get Position end Automation
	D3DXVECTOR2 GetPositionEndAutoAnimation();
	//Change status of mario reach checkpoint or not, true if yes, false if no
	void ChangeCheckpointStatus(bool isReachCheckpoint);
	//Check if mario reach checkpoint or not
	bool IsMarioReachCheckpoint();
	//Get new position for mario in new world base on tag
	D3DXVECTOR2 GetNewMarioPosition(eGameTag tag);
	//----------------------------
};

