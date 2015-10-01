#include "SpriteManager.h"

SpriteManager *SpriteManager::Instance = NULL;

SpriteManager::SpriteManager(void)
{
}

SpriteManager::~SpriteManager(void)
{
}

SpriteManager *SpriteManager::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new SpriteManager();
	}
	return Instance;
}

void SpriteManager::LoadSprite(LPD3DXSPRITE &SpriteHandler)
{
	_ListSprite[eSpriteID::eMap1_1] = new Sprite(SpriteHandler, L"resources\\map1.png", 64, 64, 61, 8, D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eBigMario] = new Sprite(SpriteHandler, L"resources\\BigMario.png", (double)810/14, 64, 14, 14, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eFont] = new Sprite(SpriteHandler, L"resources\\font.png", 20, 20, 36, 12, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eMenuBanner] = new Sprite(SpriteHandler, L"resources\\MenuBanner.png", 256, 196, 1, 1, D3DCOLOR_XRGB(111, 133, 255));
}

Sprite *SpriteManager::GetSprite(eSpriteID objectID)
{
	if (_ListSprite.find(objectID) != _ListSprite.end()) 
	{
		return _ListSprite[objectID];
	} 
	else 
	{
		return NULL;
	}
}

void SpriteManager::Release()
{
	_ListSprite.clear();
}

int SpriteManager::NextFrame(int currentFrame, int startFrame, int endFrame)
{
	currentFrame++;
	if (currentFrame < startFrame || currentFrame > endFrame)
		currentFrame = startFrame;
	return currentFrame;
}

int SpriteManager::PreviousFrame(int currentFrame, int startFrame, int endFrame)
{
	currentFrame--;
	if (currentFrame < 0 || currentFrame > endFrame)
		currentFrame = endFrame;
	return currentFrame;
}