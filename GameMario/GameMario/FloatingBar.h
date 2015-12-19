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
	int _NumberOfBlock;	//number of sprite need to use to render bar
	D3DXVECTOR2 _LeftPosition;	//position of 1st block on the left
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

