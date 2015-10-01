#include "GameObject.h"


GameObject::GameObject(void)
{
	_ObjectTypeID = eObjectTypeID::eUndefined;
}

GameObject::GameObject(eObjectTypeID objectTypeID, D3DXVECTOR2 pos)
{
	_ObjectTypeID = objectTypeID;
	_Position = pos;
}

GameObject::~GameObject(void)
{
}

void GameObject::SetPosition(D3DXVECTOR2 position)
{
	_Position = position;
}

void GameObject::SetObjectType(eObjectTypeID objectTypeID)
{
	_ObjectTypeID = objectTypeID;
}

D3DXVECTOR2 GameObject::GetPosition()
{
	return _Position;
}

eObjectTypeID GameObject::GetObjectTypeID()
{
	return _ObjectTypeID;
}
