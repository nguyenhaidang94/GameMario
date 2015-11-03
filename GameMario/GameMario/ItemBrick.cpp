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
	_SpawmItem = nullptr;
	_SpawmItemTag = eGameTag::eEmpty;
	//setup current sprite for brick
	switch (objectID)
	{
	case 17:	//brown brick contain 1up
		_Color = eColorID::eBrown;
		_CurrentFrame = 0;
		_SpawmItemTag = eGameTag::eStore1Up;
		break;
	case 18:	//blue brick contain mushroom
		_Color = eColorID::eBlue;
		_CurrentFrame = 6;
		_SpawmItemTag = eGameTag::eStoreMushroom;
		break;
	case 19:	//blue brick with 1up
		_Color = eColorID::eBlue;
		_CurrentFrame = 6;
		_SpawmItemTag = eGameTag::eStore1Up;
		break;
	case 20:	//brown brick contain coin
		_Color = eColorID::eBrown;
		_CurrentFrame = 0;
		_CointLeft = 7;
		_SpawmItemTag = eGameTag::eStoreCoin;
		break;
	case 21:	//blue brick contain coin
		_Color = eColorID::eBlue;
		_CurrentFrame = 6;
		_CointLeft = 7;
		_SpawmItemTag = eGameTag::eStoreCoin;
		break;
	case 22:	//brown brick contain star
		_Color = eColorID::eBrown;
		_CurrentFrame = 0;
		_SpawmItemTag = eGameTag::eStoreStar;
		break;
	case 23:	//blue brick contain star
		_Color = eColorID::eBlue;
		_CurrentFrame = 6;
		_SpawmItemTag = eGameTag::eStoreStar;
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
}

void ItemBrick::Render()
{
	if(!_IsInvisible)
	{
		_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
	}
}

void ItemBrick::Release()
{
}

void ItemBrick::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
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
				//turn brick into hard block if no coin left or not coin brick
				if(_SpawmItemTag != eStoreCoin || _CointLeft <= 1)
				{
					_IsHitted = true;
					if(_Color == eColorID::eBrown)
					{
						_CurrentFrame = 5;
					}
					else
					{
						if(_Color == eColorID::eBlue)
						{
							_CurrentFrame = 11;
						}
					}
				}

				//bounce
				_Velocity.y = BOUNCE_VELOCITY;
				_IsBounce = true;	
				_IsInvisible = false;
				_Tag = eGameTag::eBrickBounceUp;	//kill enemy if bounce up(?)

				//handle item in brick
				switch (_SpawmItemTag)
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

					//case 1up
				case eStore1Up:
					//Spawn a 1up mushroom here
					_SpawmItem = new Mushroom(_Position.x, _Position.y, _SpawmItemTag);
					break;

				//case star
				case eStoreStar:
				//Spawn a star here
					_SpawmItem = new Starman(_Color, _Position.x, _Position.y);
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
