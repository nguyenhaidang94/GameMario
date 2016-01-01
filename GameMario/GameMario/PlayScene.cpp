#include "PlayScene.h"
#define INGAME_SECOND 400	//1 second ingame is 0.4s irl
#define SCORE_PER_SECOND_LEFT 50	//when clear map, each second left inscrease 50 score

PlayScene::PlayScene(void)
{
	_SceneID = eSceneID::ePlay;
}

PlayScene::~PlayScene(void)
{
}

void PlayScene::Initialize()
{

}

void PlayScene::Load()
{
	this->Release();
	_WorldID = GameStatistics::GetInstance()->GetWorldID();
	switch (_WorldID)
	{
	case e1_1:
	case eHidden1_1:
		_ListMap[eWorldID::e1_1] = new PlayMap(e1_1);
		_ListMap[eWorldID::eHidden1_1] = new PlayMap(eHidden1_1);
		break;
	case e1_2:
	case eLeft1_2:
	case eRight1_2:
	case eHidden1_2:
		_ListMap[eWorldID::e1_2] = new PlayMap(e1_2);
		_ListMap[eWorldID::eLeft1_2] = new PlayMap(eLeft1_2);
		_ListMap[eWorldID::eRight1_2] = new PlayMap(eRight1_2);
		_ListMap[eWorldID::eHidden1_2] = new PlayMap(eHidden1_2);
		break;
	case e1_3:
		_ListMap[eWorldID::e1_3] = new PlayMap(e1_3);
		break;
	case e1_4:
		_ListMap[eWorldID::e1_4] = new PlayMap(e1_4);
		break;
	default:
		break;
	}
	_ListMap[_WorldID]->Load();
	GameStatistics::GetInstance()->ResetWorld();
	_FrameStart = GetTickCount();
}


void PlayScene::Update()
{
	//update map
	_ListMap[_WorldID]->Update();

	//manage game time
	DWORD now = GetTickCount();
	//reduce time normally and check if timeup when not perform mario reach flagpole status
	if(!GameStatistics::GetInstance()->IsPerformMarioReachFlagpoleStatus())
	{
		if (now - _FrameStart >= INGAME_SECOND) 
		{
			_FrameStart = now;
			GameStatistics::GetInstance()->DecreaseTime();
		}
	
		if(GameStatistics::GetInstance()->GetTime() > 0 )
		{
			_currentLife = GameStatistics::GetInstance()->GetLife();
		}
	
		if(GameStatistics::GetInstance()->GetTime() == 0 )
		{
			Mario::GetInstance()->SetDead(true);
			GameStatistics::GetInstance()->SetLife(_currentLife-1);
		//Play mario death animation here and move to timeup scene
		}
	}
	else	//mario reach flagpole, countdown time fast and inscrease score, this affect by current fps of the game...
	{
		if (GameStatistics::GetInstance()->GetTime() > 0)
		{
			GameStatistics::GetInstance()->DecreaseTime();
			GameStatistics::GetInstance()->ChangeScore(SCORE_PER_SECOND_LEFT);
			Mario::GetInstance()->SetFlagRender(false);
			Mario::GetInstance()->SetIsControl(false);
		}
		//change to next world after finish countdown
		else
		{
			Mario::GetInstance()->SetFlagRender(true);
			Mario::GetInstance()->SetIsControl(true);
			GameStatistics::GetInstance()->GoToNextWorld();	//just change world id, change scene will update below
		}
	}

	//If there's any objects in ListObjectAddToScene in GameStatistics, add it to this scene
	std::vector<GameObject*>* listObjectToAdd = GameStatistics::GetInstance()->GetListObjectAddToScene();
	while (!listObjectToAdd->empty())
	{
		_ListMap[_WorldID]->AddObjectToMap(listObjectToAdd->back());
		listObjectToAdd->pop_back();
	}


	//If game world change somewhere, switch map
	eWorldID targetWorldID = GameStatistics::GetInstance()->GetWorldID();
	if(_WorldID != targetWorldID)
	{
		if(Unility::IsInSameMap(_WorldID, targetWorldID))
		{
			_WorldID = targetWorldID;
			_ListMap[_WorldID]->Load();
			Camera::GetInstance()->Reset();
			GameStatistics::GetInstance()->PauseTime(false);	//stop pause time in case of pause time when mario perform animation 
		}
		else	//change to startscene
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap);	//move to startmap scene when switch world
		}
	}


}

void PlayScene::Render()
{
	_ListMap[_WorldID]->Render();
}

void PlayScene::Release()
{
	std::map<eWorldID, PlayMap*>::iterator itr;
	for( itr = _ListMap.begin(); itr!= _ListMap.end(); itr++){
        if((*itr).second){
			(*itr).second->Release();
            delete ((*itr).second);
        }
    }
	_ListMap.clear();
}

void PlayScene::HandlingCollision()
{
	_ListMap[_WorldID]->HandlingCollision();
}