#pragma once
#include "GlobalVariables.h"

class GameStatistics
{
private:
	int _Score;
	int _Life;
	eWorldID _WolrdID;
	static GameStatistics *Instance;
public:
	GameStatistics(void);
	~GameStatistics(void);
	static GameStatistics *GetInstance();
	//Initialize GameStatistics
	void Initialize();
	//Get current worldID
	eWorldID GetWorldID();
	//Get current score
	int GetScore();
	//Get current life
	int GetLife();
	//Increase/decrease score by a amount
	void ChangeScore(int amount);
	//Increase/decrease life by 1, true if increase, false if decrease
	void ChangeLife(bool isIncrease);
	//Change current worldID
	void ChangeWorld(eWorldID worldID);
};

