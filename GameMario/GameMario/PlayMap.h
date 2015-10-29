#pragma once
#include "GameObject.h"
#include "Background.h"
#include "QuadTree.h"
#include "Mario.h"

class PlayMap
{
private:
	eWorldID _WorldID;
	Background *_Background;
	QuadTree *_QuadTree;
	Mario *_Mario;

	//get direction of colision between a dynamic and a static object
	eCollisionDirection CheckCollision(GameObject *dynamicObj, GameObject *unknownObj);
public:
	PlayMap(void);
	PlayMap(eWorldID worldID);
	~PlayMap(void);

	//Free menory use
	void Release();
	//Render scence
	void Render();
	//Update map
	void Update();
	//Handling collision of map object
	void HandlingCollision();
	//Load map
	void Load();
	//Reload map
	void Reload();
	//add object to map
	void AddObjectToMap(GameObject *object);
};

