#pragma once
#include <string>
#include "GameObject.h"

class Pipe :public GameObject
{
private:
	
public:
	Pipe(void);
	Pipe(int x, int y, int width, int height, eSpriteID spriteID, std::string destination = NULL);
	~Pipe(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

