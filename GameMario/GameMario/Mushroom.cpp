#include "Mushroom.h"

#define DEFAULT_VELOCITY_X 2.5
#define DEFAULT_VELOCITY_Y -8.5
#define MUSHROOM_SPAWM_VELOCITY_Y 0.5
#define MUSHROOM_WIDTH 31
#define MUSHROOM_HEIGHT 32
#define MUSHROOM_SCORE 1000

Mushroom::Mushroom(void)
{
}

Mushroom::Mushroom(int x, int y, eGameTag mushroomType)
{
	_Position = D3DXVECTOR2(x, y);
	_Velocity = D3DXVECTOR2(DEFAULT_VELOCITY_X, 0);
	_Size = D3DXVECTOR2(MUSHROOM_WIDTH, MUSHROOM_HEIGHT);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eItems);
	_IsSpawnDone = false;
	_BeginningPositionY = y;
	_IsGoingRight = true;
	_IsStandOnObject = false;
	_Tag = eGameTag::eIgnoreCollision;	//ignore collision when on spawn animation
	_ObjectTypeID = eObjectTypeID::eMagicMushroom;
	switch (mushroomType)
	{
	case eStoreMushroom:
		_ObjectTypeID = eObjectTypeID::eMagicMushroom;
		_CurrentFrame = 32;
		break;
	case eStore1Up:
		_ObjectTypeID = eObjectTypeID::e1upMushroom;
		_CurrentFrame = 33;
		break;
	default:
		break;
	}
}


Mushroom::~Mushroom(void)
{
}

void Mushroom::Update()
{
	if(_IsSpawnDone)
	{
		_Position.x += _Velocity.x;
		_Position.y += _Velocity.y;

		//destroy mushroom if it goes off screen
		Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
		if(_Position.x < cameraBox.fX - TITLE_SIZE|| _Position.x > cameraBox.fX + cameraBox.fWidth + TITLE_SIZE||
			_Position.y > cameraBox.fY + TITLE_SIZE|| _Position.y < cameraBox.fY - cameraBox.fHeight - TITLE_SIZE)
		{
			_Tag = eGameTag::eDestroyed;
		}

		if (!_IsStandOnObject)
		{
			_Velocity.y = DEFAULT_VELOCITY_Y;
		}
		if(_IsGoingRight)
		{
			_Velocity.x = DEFAULT_VELOCITY_X;
		}
		else
		{
			_Velocity.x = -DEFAULT_VELOCITY_X;
		}
	}
	else
	{
		_Position.y += MUSHROOM_SPAWM_VELOCITY_Y;
		if(_Position.y > _BeginningPositionY + TITLE_SIZE)
		{
			_Position.y = _BeginningPositionY + TITLE_SIZE;
			_IsSpawnDone = true;
			_Tag = eGameTag::eEmpty;	//stop ignore collison
		}
	}
	_IsStandOnObject = false;
}

void Mushroom::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame, 0.4);
}

void Mushroom::Release()
{

}

void Mushroom::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	Box objectBox = object->GetBoundaryBox();
	switch (object->GetObjectTypeID())
	{
	case eBrick:
	case eHardBrick:
	case eGround:
	case ePipe:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = objectBox.fY + _Size.y/2;
			_Velocity.y = 0.0f;
			_IsStandOnObject = true;
			break;
		case eLeft:
			_Position.x = objectBox.fX + objectBox.fWidth + _Size.y/2 + 1;
			_Velocity.x = 0;
			_IsGoingRight = true;
			break;
		case eRight:
			_Position.x = objectBox.fX - _Size.y/2 - 1;
			_Velocity.x = 0;
			_IsGoingRight = false;
			break;
		default:
			break;
		}
		break;

	//case mario
	case eMario:
		_Tag = eGameTag::eDestroyed;
		if(_ObjectTypeID == eObjectTypeID::e1upMushroom)
		{
			GameStatistics::GetInstance()->ChangeLife(true);		//inscrease life by 1
			EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, -2);	//show 1up text
		}
		if(_ObjectTypeID == eObjectTypeID::eMagicMushroom)
		{
			GameStatistics::GetInstance()->ChangeScore(MUSHROOM_SCORE);		//inscrease score
			EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, MUSHROOM_SCORE);
		}
		break;
	default:
		break;
	}
}
