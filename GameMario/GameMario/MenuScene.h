#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "GameScene.h"
#include "Keyboard.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "PlayMap.h"
using namespace std;

class MenuScene :
	public GameScene
{
private:
	Sprite *_SpriteBanner;
	Sprite *_SpriteMushroom;
	string _TopScore;
	PlayMap *_DemoMap;
	int _MushroomPositionY;
	DWORD _StartTime;
	bool _IsAutoRun;	//mario will start auto run
	Sprite *_HelpSprite;//sprite to show help
	bool _IsShowHelp;	//stop update scene if player show help
public:
	MenuScene(void);
	~MenuScene(void);
	//Initialize scene
	void Initialize();
	//Free menory use
	void Release();
	//Render scence
	void Render();
	//Update scene
	void Update();
	//Load scene
	void Load();
	//---New---//
	void HandlingInput();
};

