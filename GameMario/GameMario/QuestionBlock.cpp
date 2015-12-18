#include "QuestionBlock.h"

#define FRAME_RATE 4	//coin at top score swap 4 time per sec
#define COIN_SCORE 200	//each coin is 200 score

QuestionBlock::QuestionBlock(void)
{
}

QuestionBlock::QuestionBlock(int objectID, int x, int y)
{
	Initialize(x, y);
	_IsHitted = false;
	_SpawmItem = nullptr;
	_CountPerFrame = 1000 / FRAME_RATE;
	_FrameStart = GetTickCount();
	_SpawmItemTag = eGameTag::eEmpty;

	//setup current sprite for brick
	switch (objectID)
	{
	case 6:	//normal question block
		_Color = eColorID::eBrown;	//brown
		_CurrentFrame = 2;
		_SpawmItemTag = eGameTag::eEmpty;
		break;
	case 16:	//brown brick contain murshroom
		_Color = eColorID::eBrown;	//brown
		_CurrentFrame = 2;
		_SpawmItemTag = eGameTag::eStoreMushroom;
		break;
	default:
		break;
	}
}

QuestionBlock::~QuestionBlock(void)
{
}

void QuestionBlock::Update()
{
	if(_IsBounce)
	{
		_Position.y += _Velocity.y;
		_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;

		//set tag to empty when brick no longer bounce up
		if(_Velocity.y < 0 && _Tag != eGameTag::eEmpty)
		{
			_Tag = eGameTag::eEmpty;
		}

		if(_Position.y <= _DefaultY)
		{
			_Velocity.y = 0;
			_Position.y = _DefaultY;
			_IsBounce = false;

			//Spawm item after finished bounce
			if(_SpawmItem != nullptr)
			{
				GameStatistics::GetInstance()->AddObjectToScene(_SpawmItem);
			}
		}
	}

	if(!_IsHitted)
	{
		//control question switch rate
		DWORD now = GetTickCount();
		if (now - _FrameStart >= _CountPerFrame) 
		{
			_FrameStart = now;
			if(_Color == eColorID::eBrown)
			{
				_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 2, 4);
			}
			else
			{
				if(_Color == eColorID::eBlue)
				{
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 7, 9);
				}
			}
		}
	}
}

void QuestionBlock::Render()
{
	if(_Tag != eGameTag::eDestroyed)
	{
		_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
	}
}

void QuestionBlock::Release()
{

}

void QuestionBlock::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if(!(_IsHitted || _IsBounce))	//if already turn into hardblock or is bouncing, ignore collision
	{
		//Handling collision by object type here
		switch (object->GetObjectTypeID())
		{
		case eMario:
			switch (collisionDirection)
			{
			case eBottom:	
				_IsHitted = true;
				if(_Color == eColorID::eBrown)
				{
					_CurrentFrame = 5;
				}
				else
				{
					if(_Color == eColorID::eBlue)
					{
						_CurrentFrame = 10;
					}
				}
				//bounce
				_Velocity.y = BOUNCE_VELOCITY;
				_IsBounce = true;	
				_Tag = eGameTag::eBrickBounceUp;	//kill enemy if bounce up(?)
				switch (_SpawmItemTag)
				{
				//have mushroom
				case eStoreMushroom:
					switch (object->GetTag())
					{
					case eMarioIsSmall:
					case eMarioIsSmallInvincible:
						//Spawn a mushroom here
						_SpawmItem = new Mushroom(_Position.x, _Position.y, _SpawmItemTag);
						break;
					case eMarioIsBig:
					case eMarioIsBigInvincible:
						//Spawn a fire flower here
						_SpawmItem = new FireFlower(_Color, _Position.x, _Position.y);
						break;
					default:
						break;
					}
					break;

				//normal
				case eEmpty:
						GameStatistics::GetInstance()->ChangeScore(COIN_SCORE);		//inscrease score
						GameStatistics::GetInstance()->IncreaseCoin();				//inscrease coin count by 1
						EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eObtainCoin, COIN_SCORE);
					break;
				}
				break;

			default:	//default switch collisionDirection
				break;
			break;
			}

		default:	//default switch objectTypeID
			break;
		}
	}
}