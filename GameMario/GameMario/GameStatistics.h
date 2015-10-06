#pragma once
#include "GlobalVariables.h"
#include <string>
using namespace  std;

class GameStatistics
{
private:
	int _Score;
	int _Life;
	int _Time;
	int _CoinCount;
	eWorldID _WolrdID;
	static GameStatistics *Instance;
	bool _IsTimePause;
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
	//Get current score
	int GetScore();
	//Get current life
	int GetLife();
	//Get current time
	int GetTime();
	//Get current coint count
	int GetCoinCount();
	//Get current WorldName in string
	string GetCurrentWorldName();
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
	//Reset time = 400s and unpause game
	void ResetTime();
	//Pause game time
	void PauseTime();
};

