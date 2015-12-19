#include "Bridge.h"

#define DESTROY_SPEED 6	//destroy 4 part a sec

Bridge::Bridge(void)
{
}

Bridge::Bridge(int x, int y, int width, int height)
{
	SetPosition(D3DXVECTOR2(x, y));		
	_StartPosition = D3DXVECTOR2(x - width/2 + TITLE_SIZE/2, y);	//bridge in map editor is a block but in here will be devided into small pieces, so this will store position of the 1st block
	_Size.x = width;
	_Size.y = height;
	_ObjectTypeID = eObjectTypeID::eGround;
	_PartLeft = width/TITLE_SIZE;	//number of part = width in map editor/32
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eObjectTitle);
	_StartDestroyBridge = false;

	_CountPerFrame = 1000 / DESTROY_SPEED;
	_FrameStart = GetTickCount();
}


Bridge::~Bridge(void)
{
}

void Bridge::Update()
{
	//testing
	if(Keyboard::GetInstance()->IsKeyPress(DIK_Z))
	{
		_StartDestroyBridge = true;
	}

	if(_StartDestroyBridge)
	{
		//manage frame rate
		DWORD now = GetTickCount();
		if (now - _FrameStart >= _CountPerFrame) 
		{
			_FrameStart = now;
			_PartLeft--;
		}
		if(_PartLeft <= 0)
		{
			_Tag = eGameTag::eDestroyed;	//destroy bridge
		}
	}
}

void Bridge::Render()
{
	for(int i = 0; i < _PartLeft; i++)
	{
		_Sprite->RenderAtFrame(_StartPosition.x + i*TITLE_SIZE, _StartPosition.y , 15);
	}
}

void Bridge::Release()
{

}

void Bridge::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	default:
		break;
	}
}