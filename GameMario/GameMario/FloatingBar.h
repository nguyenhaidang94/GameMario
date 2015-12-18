#pragma once
#include "DynamicGameObject.h"
#include <string>

class FloatingBar
	: public DynamicGameObject
{
private:
	int _ObjectID;
	float _Acceleration;
	bool _Direction;	//true mean go right or up, false mean go left or down
public:
	FloatingBar(void);
	FloatingBar(int x, int y, int width, int height, std::string tag);
	~FloatingBar(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

