#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
private:
	Sprite *_Sprite;
	int _CurrentFrame;	//manage brick frame in sprite
	int _DefaultX;		//store default brick's position to bring back after brick bounce
public:
	Brick(void);
	//Object ID is id of brick from map editor
	Brick(int objectID, int x, int y);
	~Brick(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

