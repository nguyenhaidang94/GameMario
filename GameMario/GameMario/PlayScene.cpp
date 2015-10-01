#include "PlayScene.h"

PlayScene *PlayScene::Instance = NULL;

PlayScene::PlayScene(void)
{
	
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
	_Background = new Background();
	_Mario = new Mario();
}

void PlayScene::Update()
{
	_Mario->Update();
	
	for (int i = 0; i < _ListObject.size(); i++)
	{
		_ListObject[i]->Update();
	}
	//Update camera
	Camera::GetInstance()->Update(_Mario->GetPosition());
	if(_Mario->GetPosition().x >= Camera::GetInstance()->GetWorldSize().x)
	{
		LoadMap(eWorldID::e1_2);
	}
}

void PlayScene::Render()
{
	_Background->Render();
	_Mario->Render();
	for (int i = 0; i < _ListObject.size(); i++)
	{
		_ListObject[i]->Render();
	}
}

void PlayScene::Load()
{
	LoadMap(_MapID);
}

void PlayScene::LoadMap(eWorldID mapID)
{
	this->Release();
	_MapID = mapID;
	//Reset some object
	_Background->ReadMapData(_MapID);
	_Mario->SetPosition(D3DXVECTOR2(0,64));
	//Read object data in map
	ReadMapData();
}

void PlayScene::ReadMapData()
{
	string fileName;
	switch (_MapID)
	{
	case e1_1:
		fileName = "1_1";
		break;
	case e1_2:
		fileName = "1_2";
		break;
	case e1_3:
		break;
	case e1_4:
		break;
	default:
		break;
	}

	char BackgroundPath[100];
	sprintf(BackgroundPath, "resources\\MapObjects\\%s.txt", fileName.c_str());	//Merge string
	ifstream infile(BackgroundPath);
	int lineNumber = 0;		//store current line number
	string line;
	int titleID;			//store titleID read in file
	while (getline(infile, line))
	{
		istringstream iss(line);

		int OjbectID, a, b, c;
		if (!(iss >> OjbectID >> a>> b >> c)) { break; } // error
		//----------------
		//Do something with data like create object
		//Ex: _ListObject.push_back(new SomeObject(OjbectID, a, b, c));
		//-----------------
		lineNumber++;
	}
}

vector<GameObject*> PlayScene::GetAllObject()
{
	return _ListObject;
}

void PlayScene::Release()
{
	_Background->Release();
	for (int i = 0; i < _ListObject.size(); i++)
	{
		_ListObject[i]->Release();
	}
}