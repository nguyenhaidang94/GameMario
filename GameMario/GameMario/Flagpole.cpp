#include "Flagpole.h"

#define POPE_WIDTH 4
#define POLE_HEIGHT 304
#define SCORE1 100
#define SCORE2 400
#define SCORE3 800
#define SCORE4 2000
#define SCORE5 4000
#define FLAG_DROP_DOWN_VELOCITY 3

Flagpole::Flagpole(void)
{
}

Flagpole::Flagpole(int x, int y)
{
	_Position = D3DXVECTOR2(x, y);
	_Size = D3DXVECTOR2(POPE_WIDTH, POLE_HEIGHT);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eFlagpoleSprite);
	_FlagSprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eFlagSprite);
	_ObjectTypeID = eObjectTypeID::eFlagpole;
	_FlagPosition = D3DXVECTOR2(x + POLE_HEIGHT/2 - 32, y - 14);
	_IsFlagHittedGround = false;
	_IsHitted = false;
}


Flagpole::~Flagpole(void)
{
}

void Flagpole::Update()
{
	if(_IsHitted)
	{
		if(!_IsFlagHittedGround)
		{
			_FlagPosition.y -= FLAG_DROP_DOWN_VELOCITY;
			//drop to bottom of the pole
			if(_FlagPosition.y <= _Position.y - POLE_HEIGHT/2 + 16)
			{
				_FlagPosition.y = _Position.y - POLE_HEIGHT/2 + 16;
				_IsFlagHittedGround = true;
			}
		}
	}
}

void Flagpole::Render()
{
	_Sprite->RenderFirstFrame(_Position.x, _Position.y);
	_FlagSprite->RenderFirstFrame(_FlagPosition.x, _FlagPosition.y);
}

void Flagpole::Release()
{

}

void Flagpole::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if(!_IsHitted)
	{
		int height = 0;
		//Handling collision by object type here
		switch (object->GetObjectTypeID())
		{
		case eMario:
			height = object->GetPosition().y - (_Position.y - POLE_HEIGHT/2);	//height from center of mario to bottom of the pole
			if(height <= 34)
			{
				GameStatistics::GetInstance()->ChangeScore(SCORE1);		//inscrease score
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, SCORE1);
			}
			if(height > 34 && height <= 114)
			{
				GameStatistics::GetInstance()->ChangeScore(SCORE2);		//inscrease score
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, SCORE2);
			}
			if(height > 114 && height <= 162)
			{
				GameStatistics::GetInstance()->ChangeScore(SCORE3);		//inscrease score
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, SCORE3);
			}
			if(height > 162 && height <= 254)
			{
				GameStatistics::GetInstance()->ChangeScore(SCORE4);		//inscrease score
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, SCORE4);
			}
			if(height > 254 && height <= 306)
			{
				GameStatistics::GetInstance()->ChangeScore(SCORE5);		//inscrease score
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, SCORE5);
			}
			if(height > 306)
			{
				GameStatistics::GetInstance()->ChangeLife(true);		//inscrease life by 1
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, -2);	//show 1up text
			}
			_IsHitted = true;
			break;
		default:
			break;
		}
	}
}