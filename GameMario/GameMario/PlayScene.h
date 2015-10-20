#pragma once
#include "GameScene.h"
#include <vector>
#include <math.h>
#include "GameObject.h"
#include "Background.h"
#include "GameStatistics.h"
#include "SceneManager.h"
#include "Mario.h"
#include "QuadTree.h"

class PlayScene :
	public GameScene
{
private:
	eWorldID _MapID;
	//Map object
	Background *_Background;
	Mario *_Mario;
	static PlayScene *Instance;

	//get direction of colision between a dynamic and a static object
	eCollisionDirection CheckCollision(GameObject *dynamicObj, GameObject *unknownObj, float &moveX, float &moveY);

	//Get new position for mario in new world base on tag
	D3DXVECTOR2 GetNewMarioPosition(eGameTag tag);
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
	void LoadMap();
	//Handling collision of map object
	void HandlingCollision();
};

