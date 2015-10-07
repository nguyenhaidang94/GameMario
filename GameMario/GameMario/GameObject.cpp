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

void GameObject::SetSize(D3DXVECTOR2 size)
{
	_Size = size;
}

D3DXVECTOR2 GameObject::GetPosition()
{
	return _Position;
}

eObjectTypeID GameObject::GetObjectTypeID()
{
	return _ObjectTypeID;
}

void GameObject::SetTag(string tag)
{
	_Tag = tag;
}

string GameObject::GetTag()
{
	return _Tag;
}

Box GameObject::GetBoundaryBox()
{
	return Box(_Position.x - _Size.x/2, _Position.y + _Size.y/2, _Size.x, _Size.y);
}