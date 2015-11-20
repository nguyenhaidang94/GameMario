#include "Monster.h"


Monster::Monster()
{
	//Object
	SetObjectType(eMonster);												//set id

	// Monster
	_MonsterAlive = true;													//set alive
}

Monster::~Monster()
{
}

void Monster::DirectionsCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	Box objectBox = object->GetBoundaryBox();
	switch (collisionDirection)
	{
	case eBottom:
		_Velocity.y = 0.0f;
		_Velocity.x = _MonsterVelocity;
		_Position.y = objectBox.fY + _Size.y / 2;
		break;
	case eRight:
		_Position.x = objectBox.fX - _Size.y / 2 - 1;
		_MonsterVelocity = -_MonsterVelocity;
		_Velocity.x = 0.0f;
		break;
	case eLeft:
		_Position.x = objectBox.fX + objectBox.fWidth + _Size.y / 2 + 1;
		_MonsterVelocity = -_MonsterVelocity;
		_Velocity.x = 0.0f;
		break;
	default:
		break;
	}
}
