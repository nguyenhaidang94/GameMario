#pragma once
#include <string>
#include "GameObject.h"
#include "Unility.h"

class Pipe :public GameObject
{
private:
	float _RenderPriority;	//default 0.5, horizoltal pipe will have higher priority when render
public:
	Pipe(void);
	//Object ID is id of pipe from map editor
	Pipe(int objectID, int x, int y, std::string destination = NULL);
	~Pipe(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

