#include "MushroomRetainer.h"

#define TIME_1ST_SPEAK 2000	//2s after mario collide with MushroomRetainer, speak 1st line
#define TIME_2ND_SPEAK 6000	//6s after mario collide with MushroomRetainer, speak 2nd line
#define TIME_WAIT 10000	//10s after mario collide with MushroomRetainer, return to menu

MushroomRetainer::MushroomRetainer(void)
{
}

MushroomRetainer::MushroomRetainer(int x, int y)
{
	SetPosition(D3DXVECTOR2(x, y));
	_Size = D3DXVECTOR2(48, 32);	//width larger than actual sprite
	_ObjectTypeID = eObjectTypeID::eGround;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMushroomRetainer);
	_IsCollideMario = false;
}


MushroomRetainer::~MushroomRetainer(void)
{
}

void MushroomRetainer::Update()
{
	if(_IsCollideMario)
	{
		if(GetTickCount() - _TimeCollide >= TIME_WAIT)
		{
			GameStatistics::GetInstance()->ChangeScene(eMenu);
		}
	}
}

void MushroomRetainer::Render()
{
	_Sprite->RenderFirstFrame(_Position.x, _Position.y);
	if(_IsCollideMario)
	{
		if(GetTickCount() - _TimeCollide >= TIME_1ST_SPEAK)
		{
			TextManager::GetInstance()->Render("THANK YOU MARIO!", _Position.x - 32, _Position.y + 224);

			if(GetTickCount() - _TimeCollide >= TIME_2ND_SPEAK)
			{
				TextManager::GetInstance()->Render("BUT OUR PRINCESS IS IN", _Position.x - 32, _Position.y + 160);
				TextManager::GetInstance()->Render("ANOTHER CASTLE!", _Position.x - 32, _Position.y + 128);
			}
		}
	}

}

void MushroomRetainer::Release()
{

}

void MushroomRetainer::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if(!_IsCollideMario)
	{
		//Handling collision by object type here
		switch (object->GetObjectTypeID())
		{
		case eMario:
			_IsCollideMario = true;
			_TimeCollide = GetTickCount();
			break;
		default:
			break;
		}
	}
}