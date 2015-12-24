#pragma once
#include "gameobject.h"
#include "TextManager.h"

class MushroomRetainer :
	public GameObject
{
private:
	bool _IsCollideMario;	//if collided with mario, render text
	DWORD _TimeCollide;
public:
	MushroomRetainer(void);
	MushroomRetainer(int x, int y);
	~MushroomRetainer(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

