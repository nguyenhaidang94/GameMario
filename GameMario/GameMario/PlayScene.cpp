#include "PlayScene.h"

PlayScene *PlayScene::Instance = NULL;

PlayScene::PlayScene(void)
{
	_SceneID = eSceneID::ePlay;
}

PlayScene::~PlayScene(void)
{
}

PlayScene *PlayScene::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new PlayScene();
	}
	return Instance;
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
	case eUnderground1_1:
		_ListMap[eWorldID::e1_1] = new PlayMap(e1_1);
		_ListMap[eWorldID::eUnderground1_1] = new PlayMap(eUnderground1_1);
		break;
	case e1_2:
		_ListMap[eWorldID::e1_2] = new PlayMap(e1_2);
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

	//If game world change somewhere, switch map
	eWorldID targetWorldID = GameStatistics::GetInstance()->GetWorldID();
	if(_WorldID != targetWorldID)
	{
		if(Unility::IsInSameMap(_WorldID, targetWorldID))
		{
			_WorldID = targetWorldID;
			_ListMap[_WorldID]->Load();
		}
		else	//change to startscene
		{
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