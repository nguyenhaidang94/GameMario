﻿#pragma once

//Game setting
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define FRAME_RATE 60		//60 FPS
#define FULLSCREEN 0		//Not full screen
#define TITLE_SIZE 32		//a title is 32x32
#define BUFFER_FOR_SCREEN 50
//Enum
enum eObjectTypeID
{
	eUndefined = 0, 
	eMario,
	eGround,
	ePipe,
	ePipeHorizontal,
	eBrick,
	eHardBrick,
	eMagicMushroom,
	eFireFlower,
	e1upMushroom,
	eStarMan,
	eFloatingBar,
	eFlagpole,
	eMonster,
	eMonsterDead,
	eBullet,
};

enum eSpriteID
{ 
	eBigMario = 0,
	eMapTile = 1,
	eFont,
	eMenuBanner,
	eMenuMushroom,
	eSmallPipe,
	eMediumPipe,
	eBigPipe,
	eHorizontalPipe,
	eTallPipe,
	eTallerPipe,
	eCoin,
	eObjectTitle,
	eBrickDebris,
	eItems,
	eBarSprite,
	eFlagpoleSprite,
	eFlagSprite,
	eGoomba,
	eGoombaDead,
	eKoopaTroopa,
	eKoopaTroopaStop,
	eKoopaTroopaDanger,
	eKoopaTroopaDead,
	eKoopaParatroopa,
	eKoopaParatroopaDead,
	ePiranhaPlant,
	ePiranhaPlantDead,
	eSmallMario,
	eMarioTransformBigToSmall,
	eMarioTransformSmallToBig,
	eSmallMarioStar,
	eBigMarioStar,
	eMarioFire,
	eBulletSprite,
	eMarioTransformFlower,
	eBulletEF
};

enum eMarioState
{
	eIdle = 0,
	eRunLeft = 1,
	eRunRight = 2,
	eFall = 3,
	ePreStandRight = 4,
	ePreStandLeft = 5,
	eSitting = 6,
	eDead,
	eJump
};

enum eWorldID
{
	e1_1 = 0,
	e1_2 = 1,
	e1_3,
	e1_4,
	eUnderground1_1,
	eUnderground1_2,
	eRight1_2,
};

enum eSceneID
{
	eMenu = 0,
	eStartMap = 1,
	ePlay,
	eGameOver,
	eTimeUp,
};

enum eCollisionDirection
{
	eNone = 0,
	eTop = 1,
	eBottom,
	eLeft,
	eRight,
};

enum eSoundID
{
	eSoundGameOver = 0,
	eMarioDie = 1,
	eRunningOutOfTime,
	eStageClear,
	eWorldClear,
	e1Up,
	eBrickSmash,
	eBump,
	eCoinAppear,
	eDownTheFlagpole,
	eJumpSmall,
	eJumpSuper,
	ePipeTravel,
	ePowerUp,
	eVine,
	ePowerUpAppears
};

//game tag use in game
enum eGameTag
{
	eEmpty = 0,	//no tag

	//object state
	eDestroyed = 1,		//object is destroyed
	eRemove,	//object is remove in quatree
	eIgnoreCollision,	//stop checking collison
	eBrickBounceUp,		//brick kill enemy when it bounce up(?)

	//world tag
	eToUnderground1_1,	//underground of world 1_1
	eToMiddleOnGround1_1,	//middle on ground of world 1_1
	
	//item store by object tag
	eStoreMushroom,
	eStoreCoin,
	eStoreStar,
	eStore1Up,

	//mario tag to check if mario status
	eMarioIsSmall,			//mario is in small state only
	eMarioIsSmallInvincible,	//mario is in small state and invincible
	eMarioIsBig,				//mario is in big state only
	eMarioIsBigInvincible,	//mario is in big state and invincible
	eMarioIsDead,
	eMarioNotCollision, //trạng thái mario ko xét va chạm với những vật khác
			
};

enum eEffectID
{
	eBreakBrick = 0,
	eObtainCoin = 1,
	eFloatingText,
};

enum eColorID
{
	eBrown = 0,
	eBlue = 1,
};

enum eNodePosition
{
	eTopLeft = 1,
	eTopRight = 2,
	eBotLeft = 3,
	eBotRight = 4
};