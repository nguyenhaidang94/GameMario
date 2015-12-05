#include "PlayScene.h"

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
		_ListMap[eWorldID::e1_3] = new PlayMap(e1_4);
		break;
	default:
		break;
	}
	_ListMap[_WorldID]->Load();
	GameStatistics::GetInstance()->ResetTime();
}


void PlayScene::Update()
{
	_ListMap[_WorldID]->Update();

	//If there's any objects in ListObjectAddToScene in GameStatistics, add it to this scene
	std::vector<GameObject*>* listObjectToAdd = GameStatistics::GetInstance()->GetListObjectAddToScene();
	while (!listObjectToAdd->empty())
	{
		_ListMap[_WorldID]->AddObjectToMap(listObjectToAdd->back());
		listObjectToAdd->pop_back();
	}

	if(GameStatistics::GetInstance()->GetTime() <= 0)
	{
		//Play mario death animation here and move to timeup scene
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
		}
		else	//change to startscene
		{
			GameStatistics::GetInstance()->ChangeCheckpointStatus(false);
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap);
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