#include "Mario.h"

#define JUMP_VELOCITY_BOOST 8.7f
#define FALLDOWN_VELOCITY_DECREASE 1.0f
#define DEFAULT_VELOCITY -1.0f
#define INCREASE_VELOCITY 0.5 //velocity X
#define SPRITE_BIG_L 13
#define SPRITE_BIG_R 0
#define SPRITE_SMALL_R 6
#define SPRITE_SMALL_L 7
#define VELOCITY_COLLISION_MONSTER_X 0
#define VELOCITY_COLLISION_MONSTER_Y 5
#define MAX_VELOCITY2 11
#define MAX_VELOCITYDEAD 13
#define MAX_VELOCITYX 5.0f
#define MAX_VELOCITYSHOOT 8
#define ANIMATION_FRAME_RATE 20
#define ANIMATION_FRAME_RATE_FLOWER 5
#define MARIO_FRAME_RATE 15
#define MARIO_FRAME_RATE_SLOW 5
#define TIME_STAR 300
#define TIME_BEFORE_BIG_TO_SMALL 50
#define DECREASE_POSITION_Y_SITTING 2
#define POSITION_Y_ANIMATION 150
#define DECREASE_BOX_X 4
#define DECREASE_BOX_Y 2
#define FLAG_DROP_DOWN_VELOCITY 4


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
	SetPosition(D3DXVECTOR2(48,180));
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
	_IsAnimationRight = false;
	_IsRender=true;

	_CanGoLeft = true;
	_CanGoRight = true;
	

	_IsControl=true;

	_Tick_per_frame = 1000 / MARIO_FRAME_RATE;
	_Tick_per_frame_animation = 1000 / ANIMATION_FRAME_RATE;
	_Tick_per_frame_animation_flower = 1000 / ANIMATION_FRAME_RATE_FLOWER;
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
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
	SetSize(D3DXVECTOR2( 32,32));
	_Tag=eMarioIsSmall;

	SetObjectType(eMario);
}


void Mario::HandlingInput()
{

	if(_IsDead==true && _IsControl==true) _State=eMarioState::eDead;

	if(_IsCollide==true && _IsGetMushroom==false && _IsGetFlowerToTranform == false && _IsAnimationPipe == false && _IsAnimationFlag ==false && _IsDead==false
		&& _IsTranferToSmall==false && _IsAnimationRight==false && _IsControl==true )
	{
		if(_Velocity.x ==0 ) 
		{
			_State = eMarioState::eIdle;
		}
		
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

		if(Keyboard::GetInstance()->IsKeyDown(DIK_S))
		{
			if(_Tag==eGameTag::eMarioIsBig || _Tag==eGameTag::eMarioIsBigInvincible)
			{
				_Sprite=SpriteManager::GetInstance()->GetSprite(eBigMarioSitting);
				SetSize(D3DXVECTOR2(32,46));
			}
			_State = eMarioState::eSitting;
		}

		if(Keyboard::GetInstance()->IsKeyRelease(DIK_S))
		{
			ChangeSpriteSitting();
		}

		if(_State != eMarioState::eJump  && _IsCollisionMonster==false && _State!=eMarioState::eSitting)
		{
			if(Keyboard::GetInstance()->IsKeyPress(DIK_K))
			{
				_IsCollide = false;
				_State = eMarioState::eJump;
				SoundManager::GetInstance()->GetSound(eSoundID::eJumpSmall)->Play();
		       _Velocity.y = JUMP_VELOCITY_BOOST;  
			 }
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_3) && _IsDead==false && _Tag!=eGameTag::eMarioIsBig && _Tag!=eGameTag::eMarioIsBigInvincible && _TimeBeforeTranferToSmall==0) //Test Big mario
		{
			InitTranferSmallToBig();
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_4) && _IsDead==false && _TimeBeforeTranferToSmall==0 && (_Tag==eMarioIsBig|| _Tag==eMarioIsBigInvincible))
		{
			InitTranferBigToFlower();
			SetSize(D3DXVECTOR2(32,64));
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_N) && _TimeBeforeTranferToSmall==0) //Test bất tử
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
				InitTranferBigToSmall();
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_State = eMarioState::eDead;
			}
		}

		if(_PipeTag != eGameTag::eEmpty)
		{
			if(_State==eMarioState::eSitting)
			{
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
		if(_Velocity.y < 0 && _IsGetMushroom==false && _IsGetFlowerToTranform == false   && _IsTranferToSmall==false && _IsDead==false && _IsAnimationRight==false
			&& _IsCollide==false && _IsControl==true )
		{
			_State = eMarioState::eFall;
			_CountTimeJump=0;
		}
	}
}

bool Mario::GetFlagRender()
{
	return _IsRender;
}

bool Mario::SetFlagRender(bool flag)
{
	return _IsRender=flag;
}

bool Mario::GetIsControl()
{
	return _IsControl;
}

bool Mario::SetIsControl(bool flag)
{
	return _IsControl=flag;
}

Box Mario::GetBoundaryBox()
{
	return Box(_Position.x - _Size.x/2 +DECREASE_BOX_X , _Position.y + _Size.y/2 - DECREASE_BOX_Y, _Size.x -DECREASE_BOX_X*2 , _Size.y -  DECREASE_BOX_Y*2, _Velocity.x, _Velocity.y);
}
bool Mario::SetFlagAutoAnimationRight(bool flag)
{
	return _IsAnimationRight = flag;
}

bool Mario::SetDead(bool flag)
{
	return _IsDead=flag;
}
bool Mario::GetDead()
{
	return _IsDead;
}
void Mario::InitDead()
{
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
	_IsDead=true;
	_IsFlower = false;
	_IsAnimationRight = false;
	_Tag = eGameTag::eIgnoreCollision;
	_State = eMarioState::eDead;
	_Velocity.y = MAX_VELOCITYDEAD;
	GameStatistics::GetInstance()->ChangeLife(false);
	SoundManager::GetInstance()->GetSound(eSoundID::eMarioDie)->Play();
}
void Mario::Dead()
{
	if(_Sprite!= SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario))
	{
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
		
	}

	 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 0);
	 _Velocity.x = 0;
	 _Velocity.y--;

	 if(_Velocity.y<=DEFAULT_VELOCITY) _Velocity.y = DEFAULT_VELOCITY * 5;
	

}

void Mario::Jump()
{
	DWORD now = GetTickCount();

	//Nhảy và di chuyển
	if(_CanGoRight ==true)
	{
		if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
		{
			_Velocity.x +=INCREASE_VELOCITY;
		
			if(Keyboard::GetInstance()->IsKeyDown(DIK_J))
			{
				if(_Velocity.x >=MAX_VELOCITYSHOOT) _Velocity.x = MAX_VELOCITYSHOOT;
			}
			else 
				if(_Velocity.x >=MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
		}
	}

	if(_CanGoLeft==true)
	{
		if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
		{
			_Velocity.x -=INCREASE_VELOCITY;
			if(Keyboard::GetInstance()->IsKeyDown(DIK_J))
			{
				if(_Velocity.x <=-MAX_VELOCITYSHOOT) _Velocity.x = -MAX_VELOCITYSHOOT;
			}
			else 
				if(_Velocity.x <=-MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;
		}
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
	   
		if( _CountTimeJump >=MAX_VELOCITY2) _State = eMarioState::eFall;

		if(_IsAnimationRight==true)//Autoanimation đi qua phải để lên map chính
		{
			_State=eIdle;
		}

	//shoot
		if(Keyboard::GetInstance()->IsKeyDown(DIK_J) && _IsFlower==true && _IsCollisionMonster ==false && _IsGetStar==false && _IsControl==true)
		{
			SetSpriteShoot();
		}
}
void Mario::Fall()
{
	DWORD now = GetTickCount();

	//Rot và di chuyển
	if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
	{
		_Velocity.x +=INCREASE_VELOCITY;
		
		if(Keyboard::GetInstance()->IsKeyDown(DIK_J))
		{
			if(_Velocity.x >=MAX_VELOCITYSHOOT) _Velocity.x = MAX_VELOCITYSHOOT;
		}
		else 
			if(_Velocity.x >=MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
	}

	if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
	{
		_Velocity.x -=INCREASE_VELOCITY;
		if(Keyboard::GetInstance()->IsKeyDown(DIK_J))
		{
			if(_Velocity.x <=-MAX_VELOCITYSHOOT) _Velocity.x = -MAX_VELOCITYSHOOT;
		}
		else 
			if(_Velocity.x <=-MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;
	}

	//chết nếu mario rớt ra ngoài màn hình
	if(_Position.y <= 10 )
	{
		InitDead();
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
	 {
		_State=eMarioState::ePreStandRight;
	 }
	else 
		if(_Velocity.x<0 && _IsCollide==true) 
		{
			_State=eMarioState::ePreStandLeft;
		}
	 
	if(_IsAnimationFlag==true) _State= eMarioState::eIdle;	

	if(_IsAnimationPipe==true) AutoAnimationBottom();//Autoanimation đi xuống ống để qua map hidden

	if(_IsAnimationRight==true)//Autoanimation đi qua phải để lên map chính
	{
		_State=eIdle;
	}

	if(_Sprite==SpriteManager::GetInstance()->GetSprite(eBigMarioSitting)) Sitting(); //Nếu đang đứng mà chuyển qua ngồi thì bị chuyển qua trạng thái rớt, nên phải chuyển sprite qua ngồi để ko bị lỗi
	
	//shoot
	if(Keyboard::GetInstance()->IsKeyDown(DIK_J)&& _IsFlower==true && _IsGetStar==false && _IsControl==true)
	{
		SetSpriteShoot();
	}

}
void Mario::Stand()
{	
	ExitTranferSmallToBig();

	ExitTranferBigToSmall();

	 _Velocity.x = 0; //xét trạng thái đứng yên
	
	if(_IsGetMushroom == true) //Nếu lấy được nấm biến lớn và chưa kết thúc tranfer thì vẫn tiếp tục
	{
		_Velocity.y = 0;
		TranferSmallToBig();
	}
	else
		_Velocity.y = DEFAULT_VELOCITY;

	if(_IsTranferToSmall == true) //Nếu bị biến nhỏ lại và chưa kết thúc tranfer thì vẫn tiếp tục
	{
		_Velocity.y = 0;
		TranferBigToSmall();
		SetSize(D3DXVECTOR2(32,32));
	}

	if(_IsAnimationFlag == true ) //Nếu đang ở auto animation end game mà chưa tới điểm kết thúc thì tiếp túc thực hiện
	{
		AutoAnimationEndGame();
	}
	
	if(_Sprite==SpriteManager::GetInstance()->GetSprite(eBigMarioSitting))
	{
		ChangeSpriteSitting();
	}

	if(_IsAnimationPipe == true ) //Nếu đang trong auto animation chui xuống ống nước mà mario chuyển qua trạng thái đứng thì kết thúc auto animation
	{
		_IsAnimationPipe = false;
		
	}
	
	if(_IsGetFlowerToTranform ==true) //Nếu lấy đc hoa sẽ chuyển trạng thái, giai đoạn transform
	{
		_Velocity.y = 0;
		TranferBigToFlower();
	}

	ExitTranferBigToFlower();

	if(_IsCollisionMonster==true) _IsCollisionMonster = false; //Nếu đang nhảy lên moster mà chuyển qua đứng được thì xét hết va chạm bottom với monster

	if(_IsDead==true) Dead(); //Nếu Flag đang được bật thì tiếp tục thực hiện auto animation chết đết khi kết thúc

	if(_IsRight == false && _IsGetMushroom == false && _IsTranferToSmall ==false && _IsGetFlowerToTranform==false 
		&& _IsAnimationFlag ==false && _IsAnimationRight==false) //Nếu hoàn tất transform thì mới đổi sprite
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
			if(_IsRight ==true && _IsGetMushroom == false&& _IsTranferToSmall == false 
				&& _IsGetFlowerToTranform==false && _IsAnimationFlag ==false && _IsAnimationRight==false)
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

	if(_IsAnimationRight==true)
	{
		AutoAnimationRight(GameStatistics::GetInstance()->GetPositionEndAutoAnimation());
	}

	//shoot
	if(Keyboard::GetInstance()->IsKeyPress(DIK_J) && _IsFlower==true && _IsGetStar==false && _IsControl==true)
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
		if (_CanGoRight)
		{
			_IsCollide = false;
			_Velocity.x += INCREASE_VELOCITY;

			if (Keyboard::GetInstance()->IsKeyDown(DIK_J))
			{
				if (_Velocity.x >= MAX_VELOCITYSHOOT) _Velocity.x = MAX_VELOCITYSHOOT;
			}
			else
				if (_Velocity.x >= MAX_VELOCITYX) _Velocity.x = MAX_VELOCITYX;
		}
	}
	else //Thả phím sẽ dừng từ từ
	{
		_State = eMarioState::ePreStandRight;
	}

	if(_IsCollisionMonster==true) _IsCollisionMonster = false;//ko va chạm với quái

	if(_IsAnimationRight==true)
	{
		AutoAnimationRight(GameStatistics::GetInstance()->GetPositionEndAutoAnimation());
	}

	/*if(!Keyboard::GetInstance()->IsKeyDown(DIK_K) && _Velocity.y > 0 )
	{
		_Velocity.y --;
	}*/

	//shoot
	if(Keyboard::GetInstance()->IsKeyPress(DIK_J) && _IsFlower==true && _IsGetStar==false && _IsControl==true)
	{
		SetSpriteShoot();
	}

	if(_Sprite==SpriteManager::GetInstance()->GetSprite(eBigMarioSitting))
	{
		ChangeSpriteSitting();
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
		if (_CanGoLeft)
		{
			_IsCollide = false;
			_Velocity.x -= INCREASE_VELOCITY;
			if (Keyboard::GetInstance()->IsKeyDown(DIK_J))
			{
				if (_Velocity.x <= -MAX_VELOCITYSHOOT) _Velocity.x = -MAX_VELOCITYSHOOT;
			}
			else
				if (_Velocity.x <= -MAX_VELOCITYX) _Velocity.x = -MAX_VELOCITYX;
		}
	}
	else
		{
			/*_IsCollide = false;
			_Velocity.x += INCREASE_VELOCITY;
			if(_Velocity.x >0) _Velocity.x = 0;*/
			_State = eMarioState::ePreStandLeft;
	}

	if(_IsCollisionMonster==true) _IsCollisionMonster = false;//ko va chạm với quái

	if(_Sprite==SpriteManager::GetInstance()->GetSprite(eBigMarioSitting))
	{
		ChangeSpriteSitting();
	}

	//shoot
	if(Keyboard::GetInstance()->IsKeyPress(DIK_J) && _IsFlower==true && _IsGetStar==false && _IsControl==true)
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

		if(_Velocity.x<=0) _State=eMarioState::eIdle;
		
		_Velocity.x-=INCREASE_VELOCITY;

	 _IsCollide =false;
	

	// if(!Keyboard::GetInstance()->IsKeyDown(DIK_K) && _Velocity.y > 0 && _IsFloatingBarCollision==false)
	//{
	//	_Velocity.y--;
	//}
	 //shoot
	 if(Keyboard::GetInstance()->IsKeyPress(DIK_J) && _IsFlower==true && _IsGetStar==false && _IsControl==true)
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

	if(_Velocity.x>=0) _State=eMarioState::eIdle;
	 _Velocity.x += INCREASE_VELOCITY;



	 _IsCollide =false;
	

	/* if(!Keyboard::GetInstance()->IsKeyDown(DIK_K) && _Velocity.y > 0 && _IsFloatingBarCollision==false)
	{
		_Velocity.y --;
	}
*/
	 //shoot
	 if(Keyboard::GetInstance()->IsKeyDown(DIK_J) && _IsFlower==true && _IsGetStar==false && _IsControl==true )
	{
		SetSpriteShoot();
	}
}
void Mario::ChangeSpriteSitting()
{
	if(_Tag==eMarioIsBig && _IsFlower==true)
	{
		_Sprite=SpriteManager::GetInstance()->GetSprite(eMarioFire);
		SetSize(D3DXVECTOR2(32,64));
	}
	else
		if(_Tag==eMarioIsBig && _IsFlower==false)
		{
			_Sprite=SpriteManager::GetInstance()->GetSprite(eBigMario);
			SetSize(D3DXVECTOR2(32,64));
		}
		else
			if(_Tag==eMarioIsBigInvincible)
			{
				_Sprite=SpriteManager::GetInstance()->GetSprite(eBigMarioStar);
				SetSize(D3DXVECTOR2(32,64));
			}
}
void Mario::Sitting()
{
	if(_IsRight == false) 
	{
		if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 9);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 24, 26);
		}
		else if(_Tag==eGameTag::eMarioIsBig && _IsFlower==false)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0, 0);
		}
		else if(_Tag==eGameTag::eMarioIsSmall)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 6, 6);
		}
		else 
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame,2, 2);
	}
	else
		{
			if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsBigInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 4, 6);
			}
			else if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsSmallInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
			}
			else if(_Tag==eGameTag::eMarioIsBig && _IsFlower==false)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 1, 1);
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 7);
			}
			else 
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 3);
	}

	if(_IsAnimationPipe==true) AutoAnimationBottom();

	_Velocity.x = 0;

	if(_Tag!=eGameTag::eMarioIsSmall && _IsAnimationPipe==false) _Position.y-=DECREASE_POSITION_Y_SITTING;
}

void Mario::InitTranferSmallToBig()
{
	_IsGetMushroom=true;

	if(_Tag==eMarioIsSmall) _Tag = eGameTag::eMarioIsBig;
	else 
		if(_Tag==eGameTag::eMarioIsSmallInvincible) _Tag=eGameTag::eMarioIsBigInvincible;

	_PreState = _State;
	_State=eMarioState::eIdle;
	SoundManager::GetInstance()->GetSound(eSoundID::ePowerUp)->Play();
	GameStatistics::GetInstance()->PauseObject(true);

	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformSmallToBig);
	if(_IsRight==true) _CurrentFrame =  SPRITE_SMALL_R;
	else _CurrentFrame =  SPRITE_SMALL_L;
	_Velocity.y = 0;
	SetSize(D3DXVECTOR2(32, 64));
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

void Mario::ExitTranferSmallToBig()
{
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
			GameStatistics::GetInstance()->PauseObject(false);
	}
}

void Mario::InitTranferBigToSmall()
{
	_Tag = eGameTag::eMarioIsSmall;
	_IsTranferToSmall = true;
	_PreState = _State;
	_State = eMarioState::eIdle;
	_IsFlower = false; //Khi va chạm quái sẽ mất trạng thái bắn chuyển về mario nhỏ
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformBigToSmall);
	_Velocity.y = 0;
	if (_IsRight == true) _CurrentFrame = SPRITE_BIG_R;
	else _CurrentFrame = SPRITE_BIG_L;
	SoundManager::GetInstance()->GetSound(eSoundID::eVine)->Play();
	GameStatistics::GetInstance()->PauseObject(true);
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
void Mario::ExitTranferBigToSmall()
{
	//big to small
	if(_IsTranferToSmall == true && _CurrentFrame== SPRITE_SMALL_R|| _IsTranferToSmall==true && _CurrentFrame== SPRITE_SMALL_L)//Transform về sprite nhỏ 
	{
		_IsTranferToSmall = false;
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallMario);
		_State = _PreState;
		GameStatistics::GetInstance()->PauseObject(false);
	/*	SetSize(D3DXVECTOR2(32,32));*/
	}
}


bool Mario::GetFlagAutoAnimationRight()
{
	return _IsAnimationRight != _IsAnimationPipe;
}

void Mario::AutoAnimationBottom()
{
	if((_Tag==eGameTag::eMarioIsBig || _Tag==eGameTag::eMarioIsBigInvincible)
		&& _Sprite!=SpriteManager::GetInstance()->GetSprite(eBigMarioSitting))
	{
		_Sprite=SpriteManager::GetInstance()->GetSprite(eBigMarioSitting);
		SetSize(D3DXVECTOR2(32,46));
	}

	if(_IsRight == false) 
	{
		if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsBigInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 9);
		}
		else if(_IsGetStar ==true && _Tag==eGameTag::eMarioIsSmallInvincible)
		{
			 _CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 24, 26);
		}
		else if(_Tag==eGameTag::eMarioIsBig && _IsFlower==false)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 0, 0);
		}
		else if(_Tag==eGameTag::eMarioIsSmall)
		{
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 6, 6);
		}
		else 
			_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame,2, 2);
	}
	else
		{
			if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsBigInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 4, 6);
			}
			else if(_IsGetStar ==true && _Tag ==eGameTag::eMarioIsSmallInvincible)
			{
				 _CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
			}
			else if(_Tag==eGameTag::eMarioIsBig && _IsFlower==false)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 1, 1);
			}
			else if(_Tag==eGameTag::eMarioIsSmall)
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 7, 7);
			}
			else 
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 3);
	}

	_Velocity.x = 0;
    _Velocity.y = DEFAULT_VELOCITY*10;
}

void Mario::AutoAnimationEndGame()
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

	if(_Position.x >=GameStatistics::GetInstance()->GetPositionEndGame().x) 
		{
			SoundManager::GetInstance()->GetSound(eSoundID::eStageClear)->Play();

			//countdown time and inscrease time before change map
			GameStatistics::GetInstance()->PerformMarioReachFlagpoleStatus();

			_IsAnimationFlag = false;
	}
}

void Mario::AutoAnimationRight(D3DXVECTOR2 PositionEndAutoAnimation)
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

	if(_IsCollide==false && _IsDead==false) 
	 {
		_Velocity.x = 0;
		_Velocity.y = 10*DEFAULT_VELOCITY;
	 }
	 else
	 {
		_Velocity.x = MAX_VELOCITYX;
	 }
  
	if(_Position.x >= PositionEndAutoAnimation.x)  
	{
		_IsAnimationRight = false;
		_Velocity.x = 0;

		if(_PipeTag != eGameTag::eEmpty) 
		{
				GameStatistics::GetInstance()->ChangeWorld(Unility::GetWorldIDFromTag(_PipeTag));
				if(_PipeTag==eToRight1_2) Camera::GetInstance()->Reset();
				SetPosition(GameStatistics::GetInstance()->GetNewMarioPosition(_PipeTag));
		}
	}
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

void Mario::InitTranferBigToFlower()
{
	if(_Tag==eMarioIsBig)
	{
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioTransformFlower);
		_IsGetFlowerToTranform = true;
		_PreState=_State;
		_Velocity.y = 0;
		_Velocity.x = 0;
		_currentFrameBeforeTransformToFlower = _CurrentFrame;
		SoundManager::GetInstance()->GetSound(eSoundID::ePowerUpAppears)->Play();
		SetSpriteBeforeTransfromFlower();
		_State=eMarioState::eIdle;
		GameStatistics::GetInstance()->PauseObject(true);
	}
	else if(_Tag==eMarioIsBigInvincible)
	{
		_State=eMarioState::eIdle;
		SoundManager::GetInstance()->GetSound(eSoundID::ePowerUpAppears)->Play();
		_IsFlower = true;
	}
}
void Mario::TranferBigToFlower()
{
	DWORD now = GetTickCount();

	if (now - _Frame_start >= _Tick_per_frame_animation_flower) 
	{
		_Frame_start = now;

		if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 1 )
			{
				_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 33, 35); //jump L
			}
			else if(_IsGetFlowerToTranform ==true && _currentFrameBeforeTransformToFlower == 5 && _Tag==eMarioIsBig) //run L
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
void Mario::ExitTranferBigToFlower()
{
	//flower man
	if(_IsGetFlowerToTranform ==true && (_CurrentFrame==8|| _CurrentFrame == 11 ||  _CurrentFrame ==14 || _CurrentFrame==15||_CurrentFrame == 18||_CurrentFrame ==21 
		|| _CurrentFrame==32||_CurrentFrame==33||_CurrentFrame==2|| _CurrentFrame==3 ))
	{
		_IsGetFlowerToTranform = false;
		_IsFlower = true;
		if(_Sprite != SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire) && _Tag==eMarioIsBig)
		{
			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMarioFire);
		}
		else if (_Tag==eMarioIsBigInvincible)
		{
			_Sprite= SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMarioStar);
		}
		GameStatistics::GetInstance()->PauseObject(false);
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

	_Position.x += _Velocity.x;
	_Position.y += _Velocity.y;

	if(_Position.x <= Camera::GetInstance()->GetViewPort().x  + _Size.x /2) _Position.x = Camera::GetInstance()->GetViewPort().x + _Size.x /2;
	
	if(_Velocity.y == 0 && _IsGetMushroom == false && _IsTranferToSmall == false && _IsGetFlowerToTranform == false)
	{
		_Velocity.y = DEFAULT_VELOCITY;
	}

	if(_IsFlower == true || Gun::GetInstance()->GetSizeListBullet() > 0) // nếu ăn hoa rồi mới update đạn hoặc còn đạn trên màn hình
	{
		Gun::GetInstance()->Shoot(_Position,_IsRight);
	}

	if (_IsTranferToSmall == true|| _TimeBeforeTranferToSmall > 0)
	{
		_TimeBeforeTranferToSmall += 0.5;
	}

	if(_TimeBeforeTranferToSmall >=TIME_BEFORE_BIG_TO_SMALL)
	{
		_TimeBeforeTranferToSmall = 0;
		_Tag=eGameTag::eMarioIsSmall;
	}

	if(_IsGetStar == true ) _CountStar++; //Đếm thời gian bất tử

	//Xét autoaniamtion chui xuống ống nước
	if(_IsAnimationPipe==true && _Position.y <=POSITION_Y_ANIMATION && _PipeTag != eGameTag::eEmpty )
	{
		GameStatistics::GetInstance()->ChangeWorld(Unility::GetWorldIDFromTag(_PipeTag));	
		SetPosition(GameStatistics::GetInstance()->GetNewMarioPosition(_PipeTag));
		_PipeTag = eGameTag::eEmpty;
	}

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
		/*_IsDead=false;*/
		if(GameStatistics::GetInstance()->GetLife() <=0)
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eGameOver); //Chuyển về màn hình gameover nếu hết mạng
			_Tag=eGameTag::eMarioIsSmall;
			_State=eMarioState::eIdle;
			_IsControl=false;
		}
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

	_CanGoLeft = true;
	_CanGoRight = true;
	_IsCollide=false;
}

void Mario::SetSpriteBeforeTransfromFlower()
{
	if(_Tag==eMarioIsBig)
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
	else if(_Tag==eMarioIsBigInvincible)
	{
		_CurrentFrame = _currentFrameBeforeTransformToFlower;
	}
}

void Mario::Render()
{
	if(_IsRender==true)
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
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2 - DECREASE_BOX_Y;
				_Velocity.y = 0;
				_IsCollide = true;
				_IsAnimationPipe=false;
				break;
			case eLeft:
				_Velocity.x = 0;
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X;
				_CanGoLeft=false;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 +DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoRight=false;
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
				break;
			default:
				break;
			}
		}
		break;
	case ePipe:
		if(_IsDead==false && _IsAnimationPipe==false && _IsAnimationRight==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2- DECREASE_BOX_Y;;
				_Velocity.y = 0;
				if(object->GetTag() != eGameTag::eEmpty && Keyboard::GetInstance()->IsKeyDown(DIK_S))
				{
					_PipeTag = object->GetTag();
				    
				}
				_IsCollide = true;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 +DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoRight=false;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoLeft=false;
				break;
			default:
				break;
			}
		}
		break;
	case ePipeHorizontal:
		if(_IsDead==false && _IsAnimationRight ==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2- DECREASE_BOX_Y;;
				_Velocity.y = 0;
				_IsCollide = true;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 + DECREASE_BOX_X;
				_PipeTag = object->GetTag();
				if(_PipeTag != eGameTag::eEmpty)
				{
					_IsAnimationRight = true;
					_State=eIdle;
				}
				_Velocity.x = 0;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X ;
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
				if(object->GetTag()!=eGameTag::eInvisible)
				{
					_Position.y = object->GetBoundaryBox().fY + _Size.y/2- DECREASE_BOX_Y;
					_Velocity.y =0 ;
					_IsCollide = true;
				}
				break;
			case eRight:
				if(object->GetTag()!=eGameTag::eInvisible)
				{
					_Position.x = object->GetBoundaryBox().fX - _Size.x/2 + DECREASE_BOX_X;
					_Velocity.x = 0;
					_CanGoRight = false;
				}
				break;
			case eLeft:
				if(object->GetTag()!=eGameTag::eInvisible)
				{
					_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X;
					_Velocity.x = 0;
					_CanGoLeft = false;
				}
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
				SoundManager::GetInstance()->GetSound(eSoundID::eBump)->Play();
				break;
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
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2- DECREASE_BOX_Y;;
				_Velocity.y =0 ;
				_IsCollide = true;
				
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 + DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoRight = false;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X;
				_Velocity.x = 0;
				
				_CanGoLeft = false;
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
				SoundManager::GetInstance()->GetSound(eSoundID::eBump)->Play();
				break;
			default:
				break;
			}
		}
		break;
	case eMagicMushroom:
		if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false && _Tag!=eGameTag::eMarioIsBig && _Tag!=eGameTag::eMarioIsBigInvincible)
		{
			_TimeBeforeTranferToSmall = 0;
			InitTranferSmallToBig();
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
		if(collisionDirection!=eCollisionDirection::eNone && _IsDead==false  )
		{	
			if(_Tag==eGameTag::eMarioIsBig ||_Tag==eGameTag::eMarioIsBigInvincible)
			{
				InitTranferBigToFlower();
				
			}
			else if(_Tag==eGameTag::eMarioIsSmall|| _Tag==eGameTag::eMarioIsSmallInvincible|| _TimeBeforeTranferToSmall!=0)
			{
				_TimeBeforeTranferToSmall = 0;
				InitTranferSmallToBig();
			}
		}
		break;
	case eFlagpole:
		{
			_IsAnimationFlag = true;
			_Velocity.x = 0;
			_Velocity.y= -FLAG_DROP_DOWN_VELOCITY;
			
		}
		break;
	case eMonster:
		{
			if (_IsDead == false && _IsTranferToSmall == false && _Tag != eGameTag::eMarioIsBigInvincible && _Tag != eGameTag::eMarioIsSmallInvincible 
				&& _SpriteMosterDead != eKoopaTroopaStop)
			{
				if (collisionDirection == eCollisionDirection::eBottom && _SpriteMosterDead!=ePiranhaPlant && _SpriteMosterDead!=eKingBowser && _SpriteMosterDead!=eBulletFire)
				{
					_IsCollisionMonster = true;
					_State = eMarioState::eJump;
					_Velocity.y = VELOCITY_COLLISION_MONSTER_Y;
					SoundManager::GetInstance()->GetSound(eSoundID::eMonsterMusic)->Play();
					break;
				}
				else if (collisionDirection != eCollisionDirection::eBottom && _TimeBeforeTranferToSmall ==0 && (collisionDirection != eCollisionDirection::eNone|| _SpriteMosterDead==ePiranhaPlant 
					|| _SpriteMosterDead!=eKingBowser || _SpriteMosterDead!=eBulletFire))
				{
					if (_Tag == eGameTag::eMarioIsBig)
					{
						InitTranferBigToSmall();
					}
					else if (_Tag == eGameTag::eMarioIsSmall)
					{
						InitDead();
					}
				}
			}
		break;
		}
	case eAxeBoss:
		{
			_IsControl=false;
			_Velocity.x = 0;
			break;
		}
	case eFloatingBar:
		if(_IsDead==false && _IsAnimationFlag==false)
		{
			switch (collisionDirection)
			{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y/2- DECREASE_BOX_Y;;
				_Velocity.y =0 ;
				_IsCollide = true;
			
				//update position of mario base on floating bar velocity
				_Position.y += object->GetBoundaryBox().fVy;
				_Position.x += object->GetBoundaryBox().fVx;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x/2 + DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoRight = false;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 -DECREASE_BOX_X;
				_Velocity.x = 0;
				_CanGoLeft = false;
				break;
			case eTop:
				_Velocity.y = -_Velocity.y;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
