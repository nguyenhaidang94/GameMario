#include "TimeUpScene.h"
#define WAIT_TIME 2000		//wait 2s

TimeUpScene::TimeUpScene(void)
{
	_SceneID = eSceneID::eTimeUp;
}


TimeUpScene::~TimeUpScene(void)
{
}

void TimeUpScene::Initialize()
{
	
}

void TimeUpScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME || Keyboard::GetInstance()->IsKeyDown(DIK_SPACE))
	{ 
		if(GameStatistics::GetInstance()->GetLife() <= 0)
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eGameOver);
		}
		else
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap);
		}
	}
}

void TimeUpScene::Render()
{
	TextManager::GetInstance()->FixedRender("Time Up", SCREEN_WIDTH/2, 160);
}

void TimeUpScene::Release()
{
}

void TimeUpScene::Load()
{
	_StartTime = GetTickCount();
}