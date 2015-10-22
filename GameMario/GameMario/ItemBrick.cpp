#include "ItemBrick.h"

#define COIN_SCORE 200	//each coin is 200 score

ItemBrick::ItemBrick(void)
{
}

ItemBrick::~ItemBrick(void)
{
}

ItemBrick::ItemBrick(int objectID, int x, int y, string tag)
{
	Initialize(x, y);
	_IsHitted = false;
	//setup current sprite for brick
	switch (objectID)
	{
	case 17:	//brown brick contain 1up
		_Type = eBlockTypeID::eBrownBlock;
		_CurrentFrame = 0;
		_Tag = eGameTag::eStore1Up;
		break;
	case 18:	//blue brick contain mushroom
		_Type = eBlockTypeID::eBlueBlock;
		_CurrentFrame = 6;
		_Tag = eGameTag::eStoreMushroom;
		break;
	case 19:	//blue brick with 1up
		_Type = eBlockTypeID::eBlueBlock;
		_CurrentFrame = 6;
		_Tag = eGameTag::eStore1Up;
		break;
	case 20:	//brown brick contain coin
		_Type = eBlockTypeID::eBrownBlock;
		_CurrentFrame = 0;
		_CointLeft = 7;
		_Tag = eGameTag::eStoreCoin;
		break;
	case 21:	//blue brick contain coin
		_Type = eBlockTypeID::eBlueBlock;
		_CurrentFrame = 6;
		_CointLeft = 7;
		_Tag = eGameTag::eStoreCoin;
		break;
	case 22:	//brown brick contain star
		_Type = eBlockTypeID::eBrownBlock;
		_CurrentFrame = 0;
		_Tag = eGameTag::eStoreStar;
		break;
	case 23:	//blue brick contain star
		_Type = eBlockTypeID::eBlueBlock;
		_CurrentFrame = 6;
		_Tag = eGameTag::eStoreStar;
		break;
	default:
		break;
	}
	if(tag == "invi")
	{
		_IsInvisible = true;
	}
	else
	{
		_IsInvisible = false;
	}
}

void ItemBrick::Update()
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
				//turn brick into hard block if no coin left or not coin brick
				if(_CointLeft <= 0 || _Tag != eGameTag::eStoreCoin)
				{
					_IsHitted = true;

					if(_Type == eBlockTypeID::eBrownBlock)
					{
						_CurrentFrame = 5;
					}
					else
					{
						if(_Type == eBlockTypeID::eBlueBlock)
						{
							_CurrentFrame = 10;
						}
					}
				}
			}
		}
	}
}

void ItemBrick::Render()
{
	if(_Tag != eGameTag::eDestroyed)
	{
		if(!_IsInvisible)
		{
			_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
		}
	}
}

void ItemBrick::Release()
{
}

void ItemBrick::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if(!_IsHitted)	//if already turn into hardblock, ignore collision
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
				_IsInvisible = false;

				//handle item in brick
				switch (_Tag)
				{
				//Coin brick
				case eStoreCoin:
					if(_CointLeft > 0)	//still have more than 1 coin -> bounce
					{
						GameStatistics::GetInstance()->ChangeScore(COIN_SCORE);		//inscrease score
						GameStatistics::GetInstance()->IncreaseCoin();				//inscrease coin count by 1
						EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eObtainCoin, COIN_SCORE);
						_CointLeft --;
					}
					break;

				//case Mushroom
				case eStoreMushroom:
					//spawn mushroom or flower base on mario status
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
						//PlayScene::GetInstance()->AddObjectToScene(new FireFlower(_Type ,_Position.x, _Position.y));
						{
							GameObject *fireflower = new FireFlower(_Type, _Position.x, _Position.y);
							GameStatistics::GetInstance()->AddObjectToScene(fireflower);
						}
						break;
					default:
						break;
					}
					break;

					//case 1up
				case eStore1Up:
					//Spawn a 1up mushroom here
					{
						DynamicGameObject *mushroom = new Mushroom(_Position.x, _Position.y, _Tag);
						GameStatistics::GetInstance()->AddObjectToScene(mushroom);
					}
					break;

				//case star
				case eStoreStar:
				//-------------------
				//Spawn a star here
				//-------------------
				break;

				default:	//default switch _Tag
					break;
				}
				break;	//break case bottom

			default:	//default switch collisionDirection
				break;
			}

		default:	//default switch objectID
			break;
		}
	}
}
