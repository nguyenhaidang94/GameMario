#include "GameOverScene.h"
#define WAIT_TIME 5000		//wait 5s

GameOverScene::GameOverScene(void)
{
	_SceneID = eSceneID::eGameOver;
}


GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Initialize()
{
	
}

void GameOverScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME || Keyboard::GetInstance()->IsKeyDown(DIK_SPACE));
	{
		GameStatistics::GetInstance()->ChangeScene(eSceneID::eMenu);
	}
}

void GameOverScene::Render()
{
	TextManager::GetInstance()->FixedRender("Game Over", SCREEN_WIDTH/2, 160);
}

void GameOverScene::Release()
{
}

void GameOverScene::Load()
{
	_StartTime = GetTickCount();
	//save score to file
	try
	{
		fstream file(L"resources\\TopScore.txt");
		string line;
		int topScore;
		while (getline(file, line))
		{
			topScore = atoi(line.c_str());
		}

		//if current score higher than top score, save
		int currentScore = GameStatistics::GetInstance()->GetScore() ;
		if(currentScore > topScore)
		{
			//cant write file directly, so have to reopen the file
			file.close();
			file.open(L"resources\\TopScore.txt", std::fstream::out | std::fstream::trunc);
			file << currentScore;	//write to file
		}
		file.close();
	}
	catch(exception e)
	{
		//handle sth here
	}
}