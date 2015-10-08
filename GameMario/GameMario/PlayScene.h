#pragma once
#include "GameScene.h"
#include <vector>
#include "GameObject.h"
#include "Background.h"
#include "Mario.h"
#include "GameStatistics.h"
#include "SceneManager.h"
#include "Ground.h"
#include "Pipe.h"
#include "Brick.h"

class PlayScene :
	public GameScene
{
private:
	eWorldID _MapID;
	//Map object
	Background *_Background;
	vector<GameObject*> _ListObject;
	Mario *_Mario;
	static PlayScene *Instance;
	vector<GameObject*> GetListObjectOnScreen();

	//get direction of colision between a dynamic and a static object
	eCollisionDirection CheckCollision(DynamicGameObject *dynamicObj, GameObject *unknownObj, float &moveX, float &moveY);
public:
	PlayScene(void);
	~PlayScene(void);
	static PlayScene *GetInstance();
	//Initialize scene
	virtual void Initialize();
	//Free menory use
	virtual void Release();
	//Render scence
	virtual void Render();
	//Update scene
	virtual void Update();
	//Load scene
	virtual void Load();
	//---New function---//
	//Load new map
	void LoadMap(eWorldID mapID);
	//Read object data of map
	void ReadMapData();
	//Get list of all object in map
	vector<GameObject*> GetAllObject();
	//Handling collision of map object
	void HandlingCollision();
};

