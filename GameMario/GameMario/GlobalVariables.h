#pragma once

//Game setting
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 448
#define FRAME_RATE 60		//60 FPS
#define FULLSCREEN 0		//Not full screen
#define TITLE_SIZE 64		//a title is 64x64
//Enum
enum eObjectTypeID
{
	eUndefined = 0, 
	eMario = 1,
	eGround,
	ePipe,
};

enum eSpriteID
{ 
	eBigMario = 0, 
	eMap1_1 = 1,
	eFont,
	eMenuBanner,
	eSmallPipe,
	eMediumPipe,
	eBigPipe,
	eHorizontalPipe,
};

enum eMarioState
{
	eIdle = 0,
	eRunLeft = 1,
	eRunRight = 2,
	eJump
};

enum eWorldID
{
	e1_1 = 0,
	e1_2 = 1,
	e1_3,
	e1_4
};

enum eSceneID
{
	eMenu = 0,
	eStartMap = 1,
	ePlay,
	eGameOver,
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
	eCoin,
	eDownTheLlagpole,
	eJumpSmall,
	eJumpSuper,
	ePipeTravel,
	ePowerUp
};