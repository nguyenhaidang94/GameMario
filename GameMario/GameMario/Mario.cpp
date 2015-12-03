#include "Mario.h"

#define JUMP_VELOCITY_BOOST 2
#define FALLDOWN_VELOCITY_DECREASE 0.5
#define DEFAULT_VELOCITY -1
#define INCREASE_VELOCITY 0.5
#define SPRITE_BIG_L 13
#define SPRITE_BIG_R 0
#define SPRITE_SMALL_R 6
#define SPRITE_SMALL_L 7
#define MAX_VELOCITY 10
#define VELOCITY_COLLISION_MONSTER_X 0
#define VELOCITY_COLLISION_MONSTER_Y 4
#define MAX_VELOCITY2 14.5
#define MAX_VELOCITYDEAD 15
#define MAX_VELOCITYX 4.0f
#define MAX_VELOCITYSHOOT 10
#define ANIMATION_FRAME_RATE 15
#define MARIO_FRAME_RATE 10
#define MARIO_FRAME_RATE_SLOW 5
#define TIME_STAR 200
#define TIME_BEFORE_BIG_TO_SMALL 50

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
	SetPosition(D3DXVECTOR2(48,118));
	_IsCollide = false;
	SetSize(D3DXVECTOR2(32, 32));

	_CountTimeJump=0;
	_IsRight =true;
	_IsGetMushroom = false;
	_IsGetStar = false;
	_IsTranferToSmall= false;
	_CountStar=0;
	_IsGetFlowerToTranform = false;
	_IsFlower = false;
	_IsAnimationPipe = false;
	_IsAnimationFlag = false;
	_IsCollisionMonster = false;
	_IsDead = false;
	_TimeBeforeTranferToSmall=0;

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
	if(_IsDead==true) _State=eMarioState::eDead;

	if(_IsCollide==true && _IsGetMushroom==false && _IsGetFlowerToTranform == false && _IsAnimationPipe == false && _IsAnimationFlag ==false && _IsDead==false
		&& _IsTranferToSmall==false)
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

		if(_State != eMarioState::eJump  && _IsCollisionMonster==false)
		{
			if(Keyboard::GetInstance()->IsKeyPress(DIK_K))
			{
				_IsCollide = false;
				_State = eMarioState::eJump;
				SoundManager::GetInstance()->GetSound(eSoundID::eJumpSmall)->Play();
				
		       _Velocity.y = MAX_VELOCITY;  
			 }
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_V))
		{
			GameStatistics::GetInstance()->ChangeWorld(eWorldID::e1_3);
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_N)) //Test bất tử
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

		if(Keyboard::GetInstance()->IsKeyPress(DIK_C))
		{
			if(_Tag==eGameTag::eMarioIsBig) 
			{
				_Tag = eGameTag::eMarioIsSmall;
				_IsTranferToSmall = true;
				_PreState = _State;
				_State = eMarioState::eIdle;
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformBigToSmall);
				_Velocity.y = 0;

				if(_IsRight==true) _CurrentFrame =  SPRITE_BIG_R;
				else _CurrentFrame=  SPRITE_BIG_L;
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
				_IsAnimationPipe = true;
			}
			else
			{
				_PipeTag = eGameTag::eEmpty;
			}
		}
	}
	else
	{
		if(_Velocity.y < 0 && _IsGetMushroom==false && _IsGetFlowerToTranform == false && _IsAnimationPipe == false  && _IsTranferToSmall==false && _IsDead==false)
		{
			_State = eMarioState::eFall;
			_CountTimeJump=0;
		}
	}

	
}

Box Mario::GetBoundaryBox()
{
	return Box(_Position.x - _Size.x/2 +4   , _Position.y + _Size.y/2, _Size.x -8 , _Size.y, _Velocity.x, _Velocity.y);
}

void Mario::Dead()
{
	 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 0);
	 _Velocity.x = 0;
	 _Velocity.y--;

	 if(_Velocity.y<=DEFAULT_VELOCITY) _Velocity.y = DEFAULT_VELOCITY * 5;

}

void Mario::Jump()
{
	DWORD now = GetTickCount();

	//Nhảy và di chuyển
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
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible) //trạng thái bất tử và mario lớn
			{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 30, 32);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) //trạng thái bất tử và mario nhỏ
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

		if(Keyboard::GetInstance()->IsKeyDown(DIK_K) && _IsCollisionMonster == false) //Nhảy cao nếu đè phím
	   {
		 _CountTimeJump++;
	   }
		else 
			_Velocity.y --;
	   
	 if( _CountTimeJump >=MAX_VELOCITY2) _Velocity.y =  DEFAULT_VELOCITY;

	//shoot
	 if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsCollisionMonster ==false && _IsGetStar==false)
	{
		SetSpriteShoot();

	}
}
void Mario::Fall()
{
	DWORD now = GetTickCount();

	if(_IsGetFlowerToTranform==true && _CurrentFrame == 32 || _IsGetFlowerToTranform==true && _CurrentFrame==33) 
	{
		_IsGetFlowerToTranform = false;
		_IsFlower = true;
		if(_Sprite != SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire))
		{
			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire);
		}
	}

	//chết nếu mario rớt ra ngoài màn hình
	if(_Position.y <= 10)
	{
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
		_IsDead=true;
		_Tag = eGameTag::eMarioIsDead;
		_State = eMarioState::eDead;
		_Velocity.y = MAX_VELOCITYDEAD;
		GameStatistics::GetInstance()->ChangeLife(false);
	}


	//transform to flowerman
	
	if(_IsRight == true) 
	{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)  //trạng thái bất tử và lớn
			{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 30, 32);
			}
			else 
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) ////trạng thái bất tử và nhỏ
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

	 if(_Velocity.x >0 && _IsCollide==true) // Nếu rớt xuống mà còn vận tốc sẽ chuyển trạng thái chuẩn bị dừng
		_State=eMarioState::ePreStandRight;
	else if(_Velocity.x<0 && _IsCollide==true) _State=eMarioState::ePreStandLeft;
	 
	if(_IsAnimationFlag==true) _State= eMarioState::eIdle;

	//shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L)&& _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}

}
void Mario::Stand()
{
	DWORD now = GetTickCount();
	
	if(_IsGetMushroom == true && _CurrentFrame== SPRITE_BIG_R  || _IsGetMushroom == true && _CurrentFrame== SPRITE_BIG_L) 
		{
			_IsGetMushroom = false;
			if(_IsGetStar==false && _Tag==eGameTag::eMarioIsBig) //Nếu vừa hết transform và mario lớn thì đổi sprite qua lớn
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
			}
			else 
			if(_IsGetStar==true && _Tag==eGameTag::eMarioIsBigInvincible) //Nếu vừa hết transform  và đang bất tử lớn thì chuyển qua sprite bất tử lớn
			{
				_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMarioStar);
			}
			
			_State = _PreState; // chuyển về trạng thái trước khi transform
	}

	//big to small
	if(_IsTranferToSmall == true && _CurrentFrame== SPRITE_SMALL_R|| _IsTranferToSmall==true && _CurrentFrame== SPRITE_SMALL_L)//Transform về sprite nhỏ 
	{
		_IsTranferToSmall = false;
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
		_State = _PreState;
	}

	_Velocity.x = 0; //xét trạng thái đứng yên

	if(_IsGetMushroom == true) //Nếu lấy được nấm biến lớn 
	{
		_Velocity.y = 0;
		TranferSmallToBig();
	
	}
	else _Velocity.y = DEFAULT_VELOCITY;

	if(_IsTranferToSmall == true) //Nếu bị biến nhỏ lại
	{
		_Velocity.y = 0;
		TranferBigToSmall();
		SetSize(D3DXVECTOR2(32,32));
	}

	if(_IsAnimationFlag == true && _IsCollide ==true)
	{
		AutoAnimationFlag();
	}
	
	if(_IsGetFlowerToTranform ==true) //Nếu lấy đc hoa sẽ chuyển trạng thái, giai đoạn transform
	{
		_Velocity.y = 0;
		TranferBigToFlower();
	}

	if(_IsCollisionMonster==true) _IsCollisionMonster = false;

	if(_IsDead==true) Dead();

	//flower man
	if(_IsGetFlowerToTranform ==true && (_CurrentFrame==8|| _CurrentFrame == 11 ||  _CurrentFrame ==14 || _CurrentFrame==15||_CurrentFrame == 18||_CurrentFrame ==21 
		|| _CurrentFrame==32||_CurrentFrame==33||_CurrentFrame==2|| _CurrentFrame==3 ))
	{
		_IsGetFlowerToTranform = false;
		_IsFlower = true;
		if(_Sprite != SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire))
		{
			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire);
		}
	}


	if(_IsRight == false && _IsGetMushroom == false && _IsTranferToSmall ==false && _IsGetFlowerToTranform==false && _IsAnimationFlag ==false) //Nếu hoàn tất transform thì mới đổi sprite
	{
			if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible) //Đang bất tử và lớn
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 5);
			}
			else
				if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible) //Đang bất tử và nhỏ
				{
					_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 24, 26);
				}
				else
					_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 6, 6);
		}
		else
			if(_IsRight ==true && _IsGetMushroom == false&& _IsTranferToSmall == false && _IsGetFlowerToTranform==false && _IsAnimationFlag ==false)
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

	//shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}
	
}

void Mario::RunToRight()
{
	
	DWORD now1 = GetTickCount();

	if(_Velocity.x <= MAX_VELOCITYX /2)
		_Tick_per_frame=1000/MARIO_FRAME_RATE_SLOW; 
	else 
		_Tick_per_frame=1000/MARIO_FRAME_RATE; 

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


	if(Keyboard::GetInstance()->IsKeyDown(DIK_D)) //Nếu đè phím di chuyển
	{
		_IsCollide = false;
		_Velocity.x += INCREASE_VELOCITY;

		if(Keyboard::GetInstance()->IsKeyDown(DIK_L))
		{
			if(_Velocity.x >=MAX_VELOCITYSHOOT) _Velocity.x = MAX_VELOCITYSHOOT;
		}
		else 
			if(_Velocity.x >=MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
	}
	else //Thả phím sẽ dừng từ từ
	{
		/*_IsCollide = false;
		_Velocity.x -=INCREASE_VELOCITY;
		if(_Velocity.x <0) _Velocity.x = 0;*/
		_State = eMarioState::ePreStandRight;
	}

	if(_IsCollisionMonster==true) _IsCollisionMonster = false;//ko va chạm với quái

	//shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}
	
}

void Mario::RunToLeft()
{

	DWORD now1 = GetTickCount();

	if(_Velocity.x >=- MAX_VELOCITYX /2)	_Tick_per_frame=1000/MARIO_FRAME_RATE_SLOW; 
	else _Tick_per_frame=1000/MARIO_FRAME_RATE; 

	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame) 
	{
		_Frame_start = now;
		
		 if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 15, 23);
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
		if(Keyboard::GetInstance()->IsKeyDown(DIK_L))
		{
			if(_Velocity.x <=-MAX_VELOCITYSHOOT) _Velocity.x = -MAX_VELOCITYSHOOT;
		}
		else 
			if(_Velocity.x <=-MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;
	}
	else
		{
			/*_IsCollide = false;
			_Velocity.x += INCREASE_VELOCITY;
			if(_Velocity.x >0) _Velocity.x = 0;*/
			_State = eMarioState::ePreStandLeft;
	}

	if(_IsCollisionMonster==true) _IsCollisionMonster = false;//ko va chạm với quái

	//shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}
}

void Mario::PreStandRight()
{
	/*_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 2, 2);*/
	DWORD now1 = GetTickCount();

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
		_Velocity.x-=INCREASE_VELOCITY;
	 if(_Velocity.x<=0) _State=eMarioState::eIdle;

	 _IsCollide =false;
	
	 //shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}
}

void Mario::PreStandLeft()
{
	DWORD now1 = GetTickCount();

	//transform to flower
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame) 
	{
		_Frame_start = now;

	   if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 15, 23);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 12, 20);
		}
		else
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 3, 5);
	}
	
	_Velocity.x += INCREASE_VELOCITY;
	if(_Velocity.x>=0) _State=eMarioState::eIdle;

	 _IsCollide =false;

	 //shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_L) && _IsFlower==true && _IsGetStar==false)
	{
		SetSpriteShoot();
	}
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
		else if(_Tag==eGameTag::eMarioIsBig)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0, 0);
		}
		else if(_Tag==eGameTag::eMarioIsSmall)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 6, 6);
		}
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
			else if(_Tag==eGameTag::eMarioIsBig)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 13, 13);
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 7);
			}
	}

	_Velocity.x = 0;
	if(_Tag!=eGameTag::eMarioIsSmall) _Position.y-=10;
}
void Mario::TranferSmallToBig()
{
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame_animation) 
	{
		_Frame_start = now;
		if(_IsRight==false) _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 7, 13);
		else  _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0,6);
	}
	
}

void Mario::TranferBigToSmall()
{
	DWORD now = GetTickCount();
	if (now - _Frame_start >= _Tick_per_frame_animation) 
	{
		_Frame_start = now;
		if(_IsRight==false) _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 13);
		else  _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0,6);
	}
}

void Mario::AutoAnimationPipe()
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
	_Velocity.y = DEFAULT_VELOCITY;
}

void Mario::AutoAnimationFlag()
{
	DWORD now1 = GetTickCount();

	//transform to flower
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

	_Velocity.x = MAX_VELOCITYX;
}
void Mario::SetSpriteShoot()
{
	if( _CurrentFrame ==1)
	{
		_CurrentFrame = 19; //jump L
	}
	else if(_CurrentFrame == 3) //run L
	{
		 _CurrentFrame =  23;
	}
	else if( _CurrentFrame == 4)
	{
		 _CurrentFrame = 22;
	}
	else if( _CurrentFrame == 5)
	{
		 _CurrentFrame = 21;
	}
	else if( _CurrentFrame==6)
	{
		_CurrentFrame = 21;//stand L
	}
	else if( _CurrentFrame==7)
	{
		_CurrentFrame =  16; //stand R
	}
	else if( _CurrentFrame == 8)//run R
	{
		_CurrentFrame = 16;
	}
	else if( _CurrentFrame == 9)
	{
		_CurrentFrame = 15;
	}
	else if( _CurrentFrame == 10)
	{
		_CurrentFrame =  14;
	}
	else if( _CurrentFrame == 12)
	{
		 _CurrentFrame =  18; //jump R
	}
}

void Mario::TranferBigToFlower()
{
	DWORD now = GetTickCount();
	
	if (now - _Frame_start >= _Tick_per_frame_animation) 
	{
		_Frame_start = now;

		if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 1)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 33, 35); //jump L
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 5) //run L
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 21, 23);
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 4)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 18, 20);
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 3)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 15, 17);
		}
		else if(_IsGetFlowerToTranform==true && _currentFrameBeforeTransformToFlower==6)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 5);//stand L
		}
		else if(_IsGetFlowerToTranform==true && _currentFrameBeforeTransformToFlower==7)
		{
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2); //stand R
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 8)//run R
		{
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 14);
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 9)
		{
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 9, 11);
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 10)
		{
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 6, 8);
		}
		else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 12)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 30, 32); //jump R
		}
	}
}
void Mario::Update()
{
	//Just testing
	HandlingInput();
	switch (_State)
	{
	case eIdle:
		{
			Stand();
			break;
		}
	case eRunLeft:
		{
			RunToLeft();
			break;
		}
	case eRunRight:
		{
			RunToRight();
			break;
		}
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
	case eDead:
		{
			Dead();
			break;
		}
	default:
		break;
	}
	//_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;

	_Position.x += _Velocity.x;
	_Position.y += _Velocity.y;

	if(_Position.x <= Camera::GetInstance()->GetViewPort().x  + _Size.x /2) _Position.x = Camera::GetInstance()->GetViewPort().x + _Size.x /2;
	
	if(_Velocity.y == 0 && _IsGetMushroom == false && _IsTranferToSmall == false && _IsGetFlowerToTranform == false)
	{
		_Velocity.y = DEFAULT_VELOCITY;
	}

	if(_IsFlower == true ) // nếu ăn hoa rồi mới update đạn
	{
		Gun::GetInstance()->Shoot(_Position,_IsRight);
	}

	if (_IsTranferToSmall == true|| _TimeBeforeTranferToSmall > 0)
	{
		_TimeBeforeTranferToSmall += 0.5;
		_Tag=eGameTag::eMarioNotCollision;
	}

	if(_TimeBeforeTranferToSmall >=TIME_BEFORE_BIG_TO_SMALL)
	{
		_TimeBeforeTranferToSmall = 0;
		_Tag=eGameTag::eMarioIsSmall;
	}

	if(_IsGetStar == true ) _CountStar++; //Đếm thời gian bất tử

	if(_CountStar >=TIME_STAR ) // Nếu thời gian lâu hơn thời gian bất tử thì set lại sprite trc khi ăn
		{
			_IsGetStar = false;
			if(_Tag ==eGameTag::eMarioIsBigInvincible && _IsFlower ==false) 
				{
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
					_Tag = eGameTag::eMarioIsBig;
			}
			else if(_Tag ==eGameTag::eMarioIsBigInvincible && _IsFlower==true ) 
				{
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire);
					_Tag = eGameTag::eMarioIsBig;
			}
			else if(_Tag ==eGameTag::eMarioIsSmallInvincible)
				{
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
					_Tag = eGameTag::eMarioIsSmall;
			}
	}

	//Nếu chết thì chuyển màn chơi về lại checkpoint nếu đã qua checkpoint hoặc gameover nếu hết mạng
	if(_IsDead==true && _Position.y <= 0)
	{
		_IsDead=false;
		if(GameStatistics::GetInstance()->GetLife() <0)	GameStatistics::GetInstance()->ChangeScene(eSceneID::eGameOver); //Chuyển về màn hình gameovern nếu hết mạng
		else 
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap); 
			if(_Position.x >GameStatistics::GetInstance()->GetCheckpoint().x) //Quay về checkpoint nếu đã qua checkpoint
			{
				GameStatistics::GetInstance()->ChangeCheckpointStatus(true);
			}
			_Tag=eGameTag::eMarioIsSmall;
			SetSize(D3DXVECTOR2(32,32));
		
		}
	}
	//if _PipeTag != empty mean switch scene, set mario posion in new world and reset _PipeTag
	if(_PipeTag != eGameTag::eEmpty)
	{
		SetPosition(GetNewMarioPosition(_PipeTag));
		_PipeTag = eGameTag::eEmpty;
	}
}

void Mario::SetSpriteBeforeTransfromFlower()
{
	
	if( _currentFrameBeforeTransformToFlower == 1)
	{
		_CurrentFrame = 35; //jump L
	}
	else if(_currentFrameBeforeTransformToFlower == 5) //run L
	{
		 _CurrentFrame =  23;
	}
	else if( _currentFrameBeforeTransformToFlower == 4)
	{
		 _CurrentFrame = 20;
	}
	else if( _currentFrameBeforeTransformToFlower == 3)
	{
		 _CurrentFrame = 15;
	}
	else if( _currentFrameBeforeTransformToFlower==6)
	{
		_CurrentFrame = 3;//stand L
	}
	else if( _currentFrameBeforeTransformToFlower==7)
	{
		_CurrentFrame =  0; //stand R
	}
	else if( _currentFrameBeforeTransformToFlower == 8)//run R
	{
		_CurrentFrame = 12;
	}
	else if( _currentFrameBeforeTransformToFlower == 9)
	{
		_CurrentFrame = 9;
	}
	else if( _currentFrameBeforeTransformToFlower == 10)
	{
		_CurrentFrame =  6;
	}
	else if( _currentFrameBeforeTransformToFlower == 12)
	{
		 _CurrentFrame =  30; //jump R
	}
}

void Mario::Render()
{
	if(_TimeBeforeTranferToSmall==0) 
		_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame); //Nếu ko phải chuyển từ dạng mario to sang nhỏ thì render bình thường
	else //Nếu từ mario to sang nhỏ lúc gặp quái thì render nhấp nháy ( lúc này ko xét va chạm với quái)
		if(_TimeBeforeTranferToSmall >0 && (int)_TimeBeforeTranferToSmall % 2 ==0)
		{
			_Sprite->RenderAtFrameWithAlpha(_Position.x, _Position.y, _CurrentFrame,125);
		}
		else 
			if(_TimeBeforeTranferToSmall >0 && (int)_TimeBeforeTranferToSmall % 2 !=0)
			{
				_Sprite->RenderAtFrameWithAlpha(_Position.x, _Position.y, _CurrentFrame,0);
			}

	Gun::GetInstance()->Render();
}

void Mario::Release()
{

}

void Mario::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	eSpriteID _SpriteMosterDead = object->GetSpriteID(); //xác định va chạm vào mai rùa ko chết
	//Handling collision by object goes here
	switch (object->GetObjectTypeID())
	{
	case eGround:
		if(_IsDead==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
				_Velocity.y = 0;
				_IsCollide = true;
				_IsAnimationPipe = false;
				break;
			case eLeft:
				_Velocity.x = 0;
				_Velocity.y = DEFAULT_VELOCITY;
			case eRight:
				_Velocity.x = 0;
				_Velocity.y = DEFAULT_VELOCITY;
			default:
				break;
			}
		}
		break;
	case ePipe:
		if(_IsDead==false)
		{
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
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 +4;
				_Velocity.x = 0;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -4 ;
				_Velocity.x = 0;
				break;
			default:
				break;
			}
		}
		break;
	case ePipeHorizontal:
		if(_IsDead==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
				_Velocity.y = 0;
				_IsCollide = true;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 ;
				_PipeTag = object->GetTag();
				if(_PipeTag != eGameTag::eEmpty)
				{
					GameStatistics::GetInstance()->ChangeWorld(Unility::GetWorldIDFromTag(_PipeTag));
					SetPosition(GetNewMarioPosition(_PipeTag));
					_IsAnimationPipe = false; //flag auto animation
				}
				_Velocity.x = 0;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 ;
				_Velocity.x = 0;
				break;
			default:
				break;
			}
		}
		break;
	case eBrick:
		if(_IsDead==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
				_Velocity.y =0 ;
				_IsCollide = true;
				_IsAnimationPipe = false;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 - 4;
				_Velocity.x = 0;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 +4;
				_Velocity.x = 0;
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
			default:
				break;
			}
		}
		break;
	case eHardBrick:
		if(_IsDead==false && _IsAnimationFlag==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
				_Velocity.y =0 ;
				_IsCollide = true;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 - 4;
				_Velocity.x = 0;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 +4;
				_Velocity.x = 0;
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
			default:
				break;
			}
		}
		break;
	case eMagicMushroom:
		if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false && _Tag!=eGameTag::eMarioIsBig && _Tag!=eGameTag::eMarioIsBigInvincible)
		{
			_IsGetMushroom=true;
			_Tag = eGameTag::eMarioIsBig;
			_PreState = _State;
			_State=eMarioState::eIdle;
			SoundManager::GetInstance()->GetSound(eSoundID::ePowerUp)->Play();

			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformSmallToBig);
			if(_IsRight==true) _CurrentFrame =  SPRITE_SMALL_R;
			else _CurrentFrame =  SPRITE_SMALL_L;
			_Velocity.y = 0;
			SetSize(D3DXVECTOR2(32, 64));
		}
		break;
	case eStarMan :
		if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false)
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
	case eFireFlower:
		if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false)
		{	
			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformFlower);
			_IsGetFlowerToTranform = true;
			_Velocity.y = 0;
			_Velocity.x = 0;
			_currentFrameBeforeTransformToFlower = _CurrentFrame;
			SoundManager::GetInstance()->GetSound(eSoundID::ePowerUpAppears)->Play();
			SetSpriteBeforeTransfromFlower();
			_State=eMarioState::eIdle;
		}
		break;
	case eFlagpole:
		{
			_IsAnimationFlag = true;
			
		}
		break;
	case e1upMushroom:
		{
			if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false)
			{
				GameStatistics::GetInstance()->SetLife(GameStatistics::GetInstance()->GetLife() + 1);
			}
			break;
		}
	case eMonster:
		{
			if(_IsDead==false && _IsTranferToSmall==false && _Tag!=eGameTag::eMarioIsBigInvincible && _Tag!=eGameTag::eMarioIsSmallInvincible && _TimeBeforeTranferToSmall ==0 )
			{
				if(collisionDirection== eCollisionDirection::eBottom )
				{
					_IsCollisionMonster = true;
					_State = eMarioState::eJump;
					_Velocity.y = VELOCITY_COLLISION_MONSTER_Y;  
					break;
				}
				else if(collisionDirection!= eCollisionDirection::eBottom && collisionDirection!= eCollisionDirection::eNone)
				{
					if(_Tag==eGameTag::eMarioIsBig) 
					{
						_Tag = eGameTag::eMarioIsSmall;
						_IsTranferToSmall = true;
						_PreState = _State;
						_State = eMarioState::eIdle;
						_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformBigToSmall);
						_Velocity.y = 0;
						if(_IsRight==true) _CurrentFrame =  SPRITE_BIG_R;
						else _CurrentFrame=  SPRITE_BIG_L;
						SoundManager::GetInstance()->GetSound(eSoundID::eVine)->Play();
					}
					else if(_Tag==eGameTag::eMarioIsSmall)
					{
						_IsDead=true;
						_Tag=eGameTag::eMarioIsDead;
						_Velocity.y =  MAX_VELOCITYDEAD ;  
						_State = eMarioState::eDead;
			
					}
				}
			}
		break;
		}
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