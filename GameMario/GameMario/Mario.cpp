#include "Mario.h"

#define JUMP_VELOCITY_BOOST 2
#define FALLDOWN_VELOCITY_DECREASE 0.5
#define DEFAULT_VELOCITY -1
#define INCREASE_VELOCITY 0.5
#define SPRITE_BIG1 5
#define SPRITE_BIG2 0
#define MAX_VELOCITY 10
#define MAX_VELOCITY2 15
#define MAX_VELOCITYX 5
#define MARIO_FRAME_RATE 20
#define ANIMATION_FRAME_RATE 5

Mario *Mario::Instance = NULL;

Mario::Mario(void)
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
	_PipeTag = eGameTag::eEmpty;
	//temporary Testing
	_Tag = eGameTag::eMarioIsSmall;
	SetVelocity(D3DXVECTOR2(0, DEFAULT_VELOCITY));
	_CurrentFrame = 0;
	/*_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);*/
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
	//SetPosition(D3DXVECTOR2(48, 118));
	SetPosition(D3DXVECTOR2(48, 118));
	_IsCollide = false;
	SetSize(D3DXVECTOR2(32, 32));

	_CountTimeJump=0;
	_IsRight =true;
	_IsGetMushroom = false;
	_IsGetStar = false;
	_IsTranferToSmall= false;
	_CountStar=0;


	_Tick_per_frame = 1000 / MARIO_FRAME_RATE;
	_Tick_per_frame_animation = 1000 / ANIMATION_FRAME_RATE;
	_Frame_start = GetTickCount();
}


Mario::~Mario(void)
{
}

Mario *Mario::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new Mario();
	}
	return Instance;
}

void Mario::Initialize()
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
}

void Mario::HandlingInput()
{
	if(_IsCollide==true && _IsGetMushroom==false)
	{
		if(_Velocity.x ==0) _State = eMarioState::eIdle;
		
		if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
		{
			_IsCollide = false;
			_IsRight = true;
			_State = eMarioState::eRunRight;
		}
		else
		if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
		{
			_IsCollide = false;
			_IsRight = false;
			_State = eMarioState::eRunLeft;
		}

		if(_State != eMarioState::eJump )
		{
			if(Keyboard::GetInstance()->IsKeyPress(DIK_K))
			{
				_IsCollide = false;
				_State = eMarioState::eJump;
				SoundManager::GetInstance()->GetSound(eSoundID::eJumpSmall)->Play();
				
		       _Velocity.y = MAX_VELOCITY;
			 }
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_H))
		{
			_IsGetStar = true;
			_CountStar=0;

			if(_Tag==eGameTag::eMarioIsBig)
			{
				_Tag = eGameTag::eMarioIsBigInvincible;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMarioStar);
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_Tag=eGameTag::eMarioIsSmallInvincible;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMarioStar);
			}
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_C))
		{
			if(_Tag==eGameTag::eMarioIsBig) 
			{
				_Tag = eGameTag::eMarioIsSmall;
				_IsTranferToSmall = true;
				_PreState = _State;
				_State = eMarioState::eIdle;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransform);
				_Velocity.y = 0;
				SoundManager::GetInstance()->GetSound(eSoundID::eVine)->Play();
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_State = eMarioState::eDead;
			}
		}
		if(Keyboard::GetInstance()->IsKeyDown(DIK_S))
		{
			_State = eMarioState::eSitting;
		}

		if(_PipeTag != eGameTag::eEmpty)
		{
			if(_State==eMarioState::eSitting)
			{
				GameStatistics::GetInstance()->ChangeWorld(Unility::GetWorldIDFromTag(_PipeTag));
				
			}
			else
			{
				_PipeTag = eGameTag::eEmpty;
			}
		}
	}
	else
	{
		if(_Velocity.y < 0 && _IsGetMushroom==false)
		{
			_State = eMarioState::eFall;
			_CountTimeJump=0;
		}
	}

	
}

Box Mario::GetMovementRangeBox()
{
	return GetBoundaryBox();
}

void Mario::Jump()
{
	if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
	{
		_Velocity.x +=INCREASE_VELOCITY;
		if(_Velocity.x >=MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
	}

	if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
	{
		_Velocity.x -=INCREASE_VELOCITY;
		if(_Velocity.x <=-MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;  
	}

	if(_IsRight == true) 
		{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible) 
			{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 30, 32);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) 
				{
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 21, 23);
				}
				else
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 12);
	}
	else
		if(_IsRight == false)
		{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
			{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 33, 35);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) 
				{
					_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 27, 29);
				}
			else
				_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 1, 1);
		}

	if(Keyboard::GetInstance()->IsKeyDown(DIK_K))
	 {
		 _CountTimeJump++;
	 }

	else
		_Velocity.y --;

	 if( _CountTimeJump >=MAX_VELOCITY2) _Velocity.y =  DEFAULT_VELOCITY;

	
}
void Mario::Fall()
{
	if(_IsRight == true) 
		{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible) 
			{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 30, 32);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) 
				{
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 21, 23);
				}
				else
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 12);
	}
	else
		if(_IsRight == false)
		{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
			{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 33, 35);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) 
				{
					_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 27, 29);
				}
			else
				_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 1, 1);
		}
	
 	_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;

	 if(_Velocity.x >0 && _IsCollide==true)
		_State=eMarioState::ePreStandRight;
	else if(_Velocity.x<0 && _IsCollide==true) _State=eMarioState::ePreStandLeft;
	 

}
void Mario::Stand()
{
	
	if(_IsGetMushroom == true && _CurrentFrame==SPRITE_BIG1 || _IsGetMushroom == true && _CurrentFrame==SPRITE_BIG2) 
		{
			_IsGetMushroom = false;
			if(_IsGetStar==false && _Tag==eGameTag::eMarioIsBig) 
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
			}
			else if(_IsGetStar==false && _Tag==eGameTag::eMarioIsSmall) 
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
			}
			else 
			if(_IsGetStar==true && _Tag==eGameTag::eMarioIsBigInvincible) 
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMarioStar);
			}
			else
			if(_IsGetStar==true && _Tag==eGameTag::eMarioIsSmallInvincible) 
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMarioStar);
			}

			_State = _PreState;
	}

	if(_IsTranferToSmall == true && _CurrentFrame==2|| _IsTranferToSmall==true && _CurrentFrame==3)
	{
		_IsTranferToSmall = false;
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
		_State = _PreState;
	}

	_Velocity.x = 0;

	if(_IsGetMushroom == true)
	{
		_Velocity.y = 0;
		TranferSmallToBig();
		SetSize(D3DXVECTOR2(32, 64));
	}
	else _Velocity.y = DEFAULT_VELOCITY;

	if(_IsTranferToSmall == true)
	{
		_Velocity.y = 0;
		TranferBigToSmall();
		SetSize(D3DXVECTOR2(32,32));
	}

	if(_IsRight == false && _IsGetMushroom == false && _IsTranferToSmall ==false)
		{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 5);
			}
			else
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
				{
					_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 24, 26);
				}
				else
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 6, 6);
		}
		else
			if(_IsRight ==true && _IsGetMushroom == false&& _IsTranferToSmall ==false)
			{
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
				{
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
				}
				else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
				{
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
				}
				else
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 7, 7);
			}

	
}

void Mario::RunToRight()
{
	
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame) 
	{
		_Frame_start = now;
		if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 6, 14);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 11);
		}
		else
		 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 8, 10);
	}


	if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
	{
		_IsCollide = false;
		_Velocity.x += INCREASE_VELOCITY;
		if(_Velocity.x >=MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
	}
		else
		{
			_IsCollide = false;
			_Velocity.x -=INCREASE_VELOCITY;
			if(_Velocity.x <0) _Velocity.x = 0;
	}
	
}

void Mario::RunToLeft()
{

	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame) 
	{
		_Frame_start = now;
		if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 15, 21);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 12, 20);
		}
		else
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 5);
	}
	
	if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
	{
		_IsCollide = false;
		_Velocity.x -= INCREASE_VELOCITY;
		if(_Velocity.x <=-MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;
	}
	else
		{
			_IsCollide = false;
			_Velocity.x += INCREASE_VELOCITY;
			if(_Velocity.x >0) _Velocity.x = 0;
	}
}

void Mario::PreStandRight()
{
	/*_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 2, 2);*/
	if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 6, 14);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 11);
		}
		else
		 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 8, 10);
	_Velocity.x-=0.5;
	 if(_Velocity.x<=0) _State=eMarioState::eIdle;

	 _IsCollide =false;
	
}

void Mario::PreStandLeft()
{
	/*_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 11, 11);*/
	if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 15, 21);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 12, 20);
		}
		else
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 5);

	_Velocity.x+=0.5;
	if(_Velocity.x>=0) _State=eMarioState::eIdle;

	 _IsCollide =false;
}
void Mario::Sitting()
{
	if(_IsRight == false) 
	{
		if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 27, 29);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 24, 26);
		}
		else
		_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0, 0);
	}
	else
		{
			if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsBigInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 24, 26);
			}
			else if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsSmallInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
			}
			else
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 13, 13);
	}

	_Velocity.x = 0;
	_Position.y-=10;
}
void Mario::TranferSmallToBig()
{
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame_animation) 
	{
		_Frame_start = now;
		if(_IsRight==false) _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 5);
		else  _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0,2);
	}
	
}

void Mario::TranferBigToSmall()
{
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame_animation) 
	{
		_Frame_start = now;
		if(_IsRight==false) _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 5);
		else  _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0,2);
	}
}
void Mario::Update()
{
	//Just testing
	HandlingInput();
	switch (_State)
	{
	case eIdle:
		Stand();
		break;
	case eRunLeft:
		RunToLeft();
		break;
	case eRunRight:
		RunToRight();
		break;
	case eJump:
		{
			Jump();
			break;
		}
	case eFall:
		{
			Fall();
			break;
		}
	case ePreStandRight:
		{
		    PreStandRight();
			break;
		}
	case ePreStandLeft:
		{
			PreStandLeft();
			break;
		}
	case eSitting:
		{
			Sitting();
			break;
		}
	default:
		break;
	}
	//_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
	_Position.x += _Velocity.x;
    _Position.y += _Velocity.y;

	if(_Velocity.y == 0 && _IsGetMushroom == false && _IsTranferToSmall == false)
	{
		_Velocity.y = DEFAULT_VELOCITY;
	}
	
	if(_IsGetStar == true ) _CountStar++;

	if(_CountStar >=100)
		{
			_IsGetStar = false;
			if(_Tag ==eGameTag::eMarioIsBigInvincible) 
				{
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
					_Tag = eGameTag::eMarioIsBig;
			}
			else if(_Tag ==eGameTag::eMarioIsSmallInvincible)
				{
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
					_Tag = eGameTag::eMarioIsSmall;
			}
	}

	//if _PipeTag != empty mean switch scene, set mario posion in new world and reset _PipeTag
	if(_PipeTag != eGameTag::eEmpty)
	{
		SetPosition(GetNewMarioPosition(_PipeTag));
		_PipeTag = eGameTag::eEmpty;
	}
}



void Mario::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Mario::Release()
{

}

void Mario::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object goes here
	switch (object->GetObjectTypeID())
	{
	case eGround:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = 0;
			_IsCollide = true;
			break;
		default:
			break;
		}
		break;
	case ePipe:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = 0;
			if(object->GetTag() != eGameTag::eEmpty)
			{
				_PipeTag = object->GetTag();
			}
			_IsCollide = true;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2;
			_Velocity.x = 0;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2;
			_Velocity.x = 0;
			break;
		default:
			break;
		}
		break;
	case ePipeHorizontal:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = 0;
			_IsCollide = true;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2;
			_PipeTag = object->GetTag();
			if(_PipeTag != eGameTag::eEmpty)
			{
				GameStatistics::GetInstance()->ChangeWorld(Unility::GetWorldIDFromTag(_PipeTag));
				SetPosition(GetNewMarioPosition(_PipeTag));
			}
			_Velocity.x = 0;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2;
			_Velocity.x = 0;
			break;
		default:
			break;
		}
		break;
	case eBrick:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y =0 ;
			_IsCollide = true;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2 - 1;
			_Velocity.x = 0;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 +1;
			_Velocity.x = 0;
			break;
		case eTop:
			_Velocity.y = -_Velocity.y;
		default:
			break;
		}
		break;
	case eHardBrick:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y =0 ;
			_IsCollide = true;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2 - 1;
			_Velocity.x = 0;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 +1;
			_Velocity.x = 0;
			break;
		case eTop:
			_Velocity.y = -_Velocity.y;
		default:
			break;
		}
		break;
	case eMagicMushroom:
		if(collisionDirection!=eCollisionDirection::eNone)
		{
			_IsGetMushroom=true;
			_Tag = eGameTag::eMarioIsBig;
			_PreState = _State;
			_State=eMarioState::eIdle;
			SoundManager::GetInstance()->GetSound(eSoundID::ePowerUp)->Play();

			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransform);
			
			_Velocity.y = 0;
		}
		break;
	case eStarMan :
		if(collisionDirection!=eCollisionDirection::eNone)
		{	
			_IsGetStar = true;
			_CountStar=0;
			if(_Tag==eGameTag::eMarioIsBig)
			{
				_Tag = eGameTag::eMarioIsBigInvincible;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMarioStar);
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_Tag=eGameTag::eMarioIsSmallInvincible;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMarioStar);
			}
		
			_Velocity.y = 0;
		}
		break;
	default:
		break;
	}
}

D3DXVECTOR2 Mario::GetNewMarioPosition(eGameTag tag)
{
	switch (tag)
	{
	case eToUnderground1_1:
		return D3DXVECTOR2(48, 448);
	case eToMiddleOnGround1_1:
		return D3DXVECTOR2(5250, 128);
	default:
		break;
	}
	return D3DXVECTOR2();
}