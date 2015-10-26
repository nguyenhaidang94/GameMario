#include "QuestionBlock.h"

#define FRAME_RATE 4	//coin at top score swap 8 time per sec
#define COIN_SCORE 200	//each coin is 200 score

QuestionBlock::QuestionBlock(void)
{
}

QuestionBlock::QuestionBlock(int objectID, int x, int y)
{
	Initialize(x, y);
	_IsHitted = false;
	count_per_frame = 1000 / FRAME_RATE;
	frame_start = GetTickCount();

	//setup current sprite for brick
	switch (objectID)
	{
	case 6:	//normal question block
		_Color = eColorID::eBrown;	//brown
		_CurrentFrame = 2;
		_Tag = eGameTag::eEmpty;
		break;
	case 16:	//brown brick contain murshroom
		_Color = eColorID::eBrown;	//brown
		_CurrentFrame = 2;
		_Tag = eGameTag::eStoreMushroom;
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
	if(!_IsHitted)
	{
		if(_IsBounce)
		{
			_Position.y += _Velocity.y;
			_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
			if(_Position.y <= _DefaultY)
			{
				_Velocity.y = 0;
				_Position.y = _DefaultY;
				_IsBounce = false;
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
			}
		}
		else
		{
			//control question switch rate
			DWORD now = GetTickCount();
			if (now - frame_start >= count_per_frame) 
			{
				frame_start = now;
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
				//bounce
				_Velocity.y = BOUNCE_VELOCITY;
				_IsBounce = true;	
				switch (_Tag)
				{
				//have mushroom
				case eStoreMushroom:
					switch (object->GetTag())
					{
					case eMarioIsSmall:
					case eMarioIsSmallInvincible:
						//Spawn a mushroom here
						//PlayScene::GetInstance()->AddObjectToScene(new Mushroom(_Position.x, _Position.y, _Tag));
						{
							DynamicGameObject *mushroom = new Mushroom(_Position.x, _Position.y, _Tag);
							GameStatistics::GetInstance()->AddObjectToScene(mushroom);
						}
						break;
					case eMarioIsBig:
					case eMarioIsBigInvincible:
						//Spawn a fire flower here
						//PlayScene::GetInstance()->AddObjectToScene(new FireFlower(_Color ,_Position.x, _Position.y));
						{
							GameObject *fireflower = new FireFlower(_Color, _Position.x, _Position.y);
							GameStatistics::GetInstance()->AddObjectToScene(fireflower);
						}
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