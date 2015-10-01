#pragma once
#include <d3dx9.h>
#include "GlobalVariables.h"
#include "Sprite.h"
#include "Collision.h"
#include <string>
using namespace std;;

class GameObject
{
protected:
	eObjectTypeID _ObjectTypeID;	//Object ID
	D3DXVECTOR2 _Position;
	Sprite *_Sprite;
	string _Tag;					//Custom tag for use if needed
public:
	GameObject(void);
	GameObject(eObjectTypeID objectTypeID, D3DXVECTOR2 pos);
	~GameObject(void);

	//Set type of object
	void SetObjectType(eObjectTypeID objectTypeID);

	//Set positon of object
	void SetPosition(D3DXVECTOR2 position);

	//Set tag of object
	void SetTag(string tag);

	//Get colision box of object
	D3DXVECTOR2 GetPosition();

	//Get object type ID
	eObjectTypeID GetObjectTypeID();

	//Get colision box of object
	string GetTag();

	//Get colision box of object
	virtual Box GetBoundaryBox() = 0;

	//Update object
	virtual void Update() = 0;

	//Draw object to screen
	virtual void Render() = 0;

	//Removes a gameobject, component or asset.
	virtual void Release() = 0;

	//Handling object when colision happened
	virtual void OnCollision(GameObject *object, eCollisionDirection collisionDirection) = 0;
};

