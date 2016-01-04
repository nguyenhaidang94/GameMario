#include "Bullet.h"
#define DEFAULT_VELOCITY -1
#define BULLET_FRAME_RATE 10
#define SPRITE_EF 2
#define MAX_VELOCITYX 8
Bullet *Bullet::Instance = NULL;

Bullet::Bullet(void)
{
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletSprite);
	_Time  = 0;
	_TimeAlive = 0;
	_CurrentFrame = 0;
	_Velocity.x = 0;
	_Velocity.y = -1;
	_IsAlive = true;
	_IsCollide =false;
	SetSize(D3DXVECTOR2(16,16));
   _Tick_per_frame = 1000 / BULLET_FRAME_RATE;
   SetObjectType(eBullet);

   ////_ObjectTypeID= eObjectTypeID::eBullet;

}

Bullet *Bullet::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new Bullet();
	}
	return Instance;
}

int Bullet::SetTimeAlive(int Time)
{
	return _TimeAlive= Time;
}
int Bullet::SetTime(int Time)
{
	return _Time= Time;
}
bool Bullet::SetCollision(bool collision)
{
	return _IsCollide =collision;
}
Box Bullet::GetMovementRangeBox()
{
	return GetBoundaryBox();
}

bool Bullet::SetRight(bool IsRight)
{
	return _IsRight=IsRight;
}
D3DXVECTOR2 Bullet::VanTocNemXien(int time, float v, float alpha)
{
	D3DXVECTOR2 velocity;
	velocity.x = v * cos(alpha);
	velocity.y = v * sin(alpha )+ DEFAULT_VELOCITY*_Time/2;

	return velocity;
}

int Bullet::GetTime()
{
	return _TimeAlive;
}
D3DXVECTOR2 Bullet::SetPosition(D3DXVECTOR2 Position)
{
	return _Position = Position;
}
D3DXVECTOR2 Bullet::SetVelocity(D3DXVECTOR2 Velocity)
{
	return _Velocity = Velocity;
}
bool Bullet:: SetIsEF(bool ef)
{
	return _IsAlive =ef;
}

bool Bullet::GetEFStatus()
{
	return _IsAlive;
}
void Bullet::Update()
{
	 DWORD now = GetTickCount();

	 if(_IsAlive ==false && _Sprite!=SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletEF))
	 {
		 _Sprite=SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletEF);
		 SetSize(D3DXVECTOR2(32,32));
	 }

	  if(_IsAlive ==true && _Sprite!=SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletSprite))
	 {
		 _Sprite=SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletSprite);
		  SetSize(D3DXVECTOR2(16,16));
	 }

	  if(_CurrentFrame==SPRITE_EF && _IsAlive==false)
	   {
		 _IsAlive==true;
	 	 _TimeAlive=100;
	  }
	 
	if(_IsAlive ==true)
	{ 
		
		SetObjectType(eObjectTypeID::eBullet);

		_Time ++;
		_TimeAlive ++;

		if (now - _Frame_start >= _Tick_per_frame) 
		{
			_Frame_start = now;
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 3);
		}

		if(_IsCollide==true)
		{
			_Velocity = VanTocNemXien(_Time,MAX_VELOCITYX,0.523);

			 if(_IsRight==true) 
				 _Position.x += _Velocity.x;
			 else 
				 _Position.x += -_Velocity.x;

			 _Position.y += _Velocity.y;
		}
		else
		{
			_Velocity = VanTocNemXien(_Time,MAX_VELOCITYX,-0.785);
			
			 if(_IsRight==true) 
				 _Position.x += _Velocity.x;
			 else 
				 _Position.x += -_Velocity.x;

			 _Position.y += _Velocity.y;
		}
	}
	else
	{
		if (now - _Frame_start >= _Tick_per_frame) 
		{
			_Frame_start = now;
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
		}

	}
	
}
void Bullet::Render()
{
	_Sprite->RenderAtFrame(_Position.x,_Position.y, _CurrentFrame);
}

void Bullet::Release()
{
}

void Bullet::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	switch (object->GetObjectTypeID())
	{
	case eGround:
		switch (collisionDirection)
		{
		case eBottom:
			_Time = 0;
			_IsCollide = true;
			break;
		case eLeft:
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			break;
		case eRight:
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			break;
		default:
			break;
		}
		break;
	case ePipe:
		if(collisionDirection== eCollisionDirection::eBottom)
		{
			_Time = 0;
			_IsCollide = true;
		}
		else if(collisionDirection!= eCollisionDirection::eBottom && collisionDirection!= eCollisionDirection::eNone)
		{
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			
		}
		break;
	case ePipeHorizontal:
		if(collisionDirection== eCollisionDirection::eBottom)
		{
			_Time = 0;
			_IsCollide = true;
		}
		else if(collisionDirection!= eCollisionDirection::eBottom && collisionDirection!= eCollisionDirection::eNone)
		{
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			
		}
		break;
	case eBrick:
	if(collisionDirection== eCollisionDirection::eBottom)
		{
			_Time = 0;
			_IsCollide = true;
		}
		else if(collisionDirection!= eCollisionDirection::eBottom && collisionDirection!= eCollisionDirection::eNone)
		{
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			
		}
		break;
	case eHardBrick:
		if(collisionDirection== eCollisionDirection::eBottom)
		{
			_Time = 0;
			_IsCollide = true;
		}
		else if(collisionDirection!= eCollisionDirection::eBottom && collisionDirection!= eCollisionDirection::eNone)
		{
			_IsAlive=false;
			_Velocity.x =0;
			_Velocity.y =0;
			
		}
		break;
	
	case eMonster:
		switch (collisionDirection)
		{
			case eBottom:
				_Position.y = object->GetBoundaryBox().fY + _Size.y / 2;
				_Velocity.y = 0;
				_IsAlive=false;
				_Tag=eIgnoreCollision;
				break;
			case eRight:
				_Position.x = object->GetBoundaryBox().fX - _Size.x / 2 + 4;
				_Velocity.x = 0;
				_Tag=eIgnoreCollision;
				_IsAlive=false;
				break;
			case eLeft:
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x / 2 - 4;
				_Velocity.x = 0;
				_IsAlive=false;
				_Tag=eIgnoreCollision;
				break;
			case eTop:
				_IsAlive=false;
				_Velocity.y = 0;
				_Tag=eIgnoreCollision;
				break;
			default:
				break;
		}
		case eMonsterDead:
			switch (collisionDirection)
			{
				case eBottom:
					_Position.y = object->GetBoundaryBox().fY + _Size.y / 2;
					_Velocity.y = 0;
					_IsAlive=false;
					_Tag=eIgnoreCollision;
					break;
				case eRight:
					_Position.x = object->GetBoundaryBox().fX - _Size.x / 2 + 4;
					_Velocity.x = 0;
					_Tag=eIgnoreCollision;
					_IsAlive=false;
					break;
				case eLeft:
					_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x / 2 - 4;
					_Velocity.x = 0;
					_IsAlive=false;
					_Tag=eIgnoreCollision;
					break;
				case eTop:
					_IsAlive=false;
					_Velocity.y = 0;
					_Tag=eIgnoreCollision;
					break;
				default:
					break;
			}
	}	
}

Bullet::~Bullet(void)
{
}
