#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "GameScene.h"
#include "Keyboard.h"
#include "SpriteManager.h"
#include "TextManager.h"
using namespace std;

class MenuScene :
	public GameScene
{
private:
	Sprite *_SpriteBanner;
	static MenuScene *Instance;
	string _TopScore;
public:
	MenuScene(void);
	~MenuScene(void);
	static MenuScene *GetInstance();
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

