#include "StartScene.h"
#define WAIT_TIME 1000		//wait 1s plus load time

StartScene::StartScene(void)
{
	_SceneID = eSceneID::eStartMap;
}


StartScene::~StartScene(void)
{
}

void StartScene::Initialize()
{
}

void StartScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME)
	{
		GameStatistics::GetInstance()->ChangeScene(eSceneID::ePlay);
	}
}

void StartScene::Render()
{
	TextManager::GetInstance()->FixedRender("world " + GameStatistics::GetInstance()->GetCurrentWorldName(), SCREEN_WIDTH/2, 160);
	TextManager::GetInstance()->FixedRender("x " + to_string(GameStatistics::GetInstance()->GetLife()), SCREEN_WIDTH/2, 196);
}

void StartScene::Release()
{
}

void StartScene::Load()
{
	_StartTime = GetTickCount();
	//always return to main map if die in other map
	if(GameStatistics::GetInstance()->GetWorldID() == eWorldID::e1_1 || GameStatistics::GetInstance()->GetWorldID() == eWorldID::eHidden1_1)
	{
		GameStatistics::GetInstance()->ChangeWorld(eWorldID::e1_1);
	}
	if(GameStatistics::GetInstance()->GetWorldID() == eWorldID::e1_2 || GameStatistics::GetInstance()->GetWorldID() == eWorldID::eHidden1_2 ||
		GameStatistics::GetInstance()->GetWorldID() == eWorldID::eLeft1_2 || GameStatistics::GetInstance()->GetWorldID() == eWorldID::eRight1_2)
	{
		GameStatistics::GetInstance()->ChangeWorld(eWorldID::e1_2);
	}
	//set mario position
	Mario::GetInstance()->SetPosition(GetMarioStartPosition());
}

D3DXVECTOR2 StartScene::GetMarioStartPosition()
{
	if(GameStatistics::GetInstance()->IsMarioReachCheckpoint())
	{
		GameStatistics::GetInstance()->GetCheckpoint();
	}
	else
	{
		return D3DXVECTOR2(48, 80);	//normal start world position, hard code maybe need fix
	}
}