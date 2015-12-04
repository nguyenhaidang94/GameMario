#include "SpriteManager.h"

SpriteManager *SpriteManager::_Instance = NULL;

SpriteManager::SpriteManager(void)
{
}

SpriteManager::~SpriteManager(void)
{
}

SpriteManager *SpriteManager::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new SpriteManager();
	}
	return _Instance;
}

void SpriteManager::LoadSprite(LPD3DXSPRITE &SpriteHandler)
{
	_ListSprite[eSpriteID::eMapTile] = new Sprite(SpriteHandler, L"resources\\Sprites\\MapTile.png", 32, 32, 29, 6, D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eFont] = new Sprite(SpriteHandler, L"resources\\Sprites\\font.png", 16, 16, 41, 16, D3DCOLOR_XRGB(92, 148, 252));
	_ListSprite[eSpriteID::eMenuBanner] = new Sprite(SpriteHandler, L"resources\\Sprites\\MenuBanner.png", 355, 179, 1, 1, D3DCOLOR_XRGB(111, 133, 255));
	_ListSprite[eSpriteID::eSmallPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\SmallPipe.png", 64, 64, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eMediumPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\MediumPipe.png", 64, 96, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eBigPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\BigPipe.png", 64, 128, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eHorizontalPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\HorizontalPipe.png", 96, 64, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eTallPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\TallPipe.png", 64, 256, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eTallerPipe] = new Sprite(SpriteHandler, L"resources\\Sprites\\TallerPipe.png", 64, 352, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	_ListSprite[eSpriteID::eCoin] = new Sprite(SpriteHandler, L"resources\\Sprites\\coin.png", 32, 32, 8, 4,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eObjectTitle] = new Sprite(SpriteHandler, L"resources\\Sprites\\ObjectTitle.png", 32, 32, 12, 12,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eBrickDebris] = new Sprite(SpriteHandler, L"resources\\Sprites\\BrickDebris.png", 16, 16, 8, 8,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eItems] = new Sprite(SpriteHandler, L"resources\\Sprites\\Items.png", 32, 32, 35, 8,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eMenuMushroom] = new Sprite(SpriteHandler, L"resources\\Sprites\\MenuMushroom.png", 22, 22, 1, 1,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eBarSprite] = new Sprite(SpriteHandler, L"resources\\Sprites\\FloatingBar.png", 96, 16, 1, 1,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eFlagpoleSprite] = new Sprite(SpriteHandler, L"resources\\Sprites\\Flagpole.png", 16, 304, 1, 1,D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eFlagSprite] = new Sprite(SpriteHandler, L"resources\\Sprites\\Flag.png", 32, 32, 1, 1,D3DCOLOR_XRGB(255, 0, 255));
	//Monster
	_ListSprite[eSpriteID::eGoomba] = new Sprite(SpriteHandler, L"resources\\Sprites\\Goomba.png", 32, 32, 12, 3, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eGoombaDead] = new Sprite(SpriteHandler, L"resources\\Sprites\\GoombaDead.png", 32, 32, 4, 1, D3DCOLOR_XRGB(55, 0, 255));
	_ListSprite[eSpriteID::eKoopaTroopa] = new Sprite(SpriteHandler, L"resources\\Sprites\\KoopaTroopa.png", 32, 48, 16, 4, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eKoopaTroopaStop] = new Sprite(SpriteHandler, L"resources\\Sprites\\KoopaTroopaStop.png", 32, 32, 8, 2, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eKoopaTroopaDead] = new Sprite(SpriteHandler, L"resources\\Sprites\\KoopaTroopaDead.png", 32, 32, 4, 1, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eKoopaParatroopa] = new Sprite(SpriteHandler, L"resources\\Sprites\\KoopaParatroopa.png", 32, 48, 16, 4, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::ePiranhaPlant] = new Sprite(SpriteHandler, L"resources\\Sprites\\PiranhaPlant.png", 32, 48, 8, 2, D3DCOLOR_XRGB(255, 0, 255));
	//
	_ListSprite[eSpriteID::eBigMario] = new Sprite(SpriteHandler, L"resources\\Sprites\\BigMario.png", 32, 64, 14, 14, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eSmallMario]= new Sprite(SpriteHandler,L"resources\\Sprites\\SmallMario.png",32,32,14,14, D3DCOLOR_XRGB(255, 0, 255));
	_ListSprite[eSpriteID::eMarioTransformBigToSmall] = new Sprite(SpriteHandler,L"resources\\Sprites\\MarioTranformBigToSmall.png",32,64,14,14,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eMarioTransformSmallToBig] = new Sprite(SpriteHandler,L"resources\\Sprites\\MarioTranformSmallToBig.png",32,64,14,14,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eBigMarioStar]= new Sprite(SpriteHandler,L"resources\\Sprites\\StarBigMario.png",32,64,36,24,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eSmallMarioStar] = new Sprite(SpriteHandler,L"resources\\Sprites\\StarSmallMario.png",32,32,30,18,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eBulletSprite] = new Sprite(SpriteHandler,L"resources\\Sprites\\Bullet.png",16,16,4,4,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eBulletEF] = new Sprite(SpriteHandler,L"resources\\Sprites\\BulletEF.png",32,32,3,3,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eMarioFire] =  new Sprite(SpriteHandler,L"resources\\Sprites\\MarioFire.png",32,64,24,24,D3DCOLOR_XRGB(255,0,255));
	_ListSprite[eSpriteID::eMarioTransformFlower] = new Sprite(SpriteHandler,L"resources\\Sprites\\MarioTransformFlower.png",32,64,36,24,D3DCOLOR_XRGB(255,0,255));
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
	if (currentFrame < startFrame || currentFrame > endFrame)
		currentFrame = endFrame;
	return currentFrame;
}