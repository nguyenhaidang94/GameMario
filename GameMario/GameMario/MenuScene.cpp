#include "MenuScene.h"

MenuScene *MenuScene::Instance = NULL;

MenuScene::MenuScene(void)
{
	_SceneID = eSceneID::eMenu;
	_SpriteBanner = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuBanner);
}


MenuScene::~MenuScene(void)
{
}

MenuScene *MenuScene::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new MenuScene();
	}
	return Instance;
}

void MenuScene::Initialize()
{
	_SpriteBanner = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuBanner);
}

void MenuScene::Update()
{
	HandlingInput();
}

void MenuScene::Render()
{
	_SpriteBanner->RenderFirstFrame(SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3);
	TextManager::GetInstance()->Render("1 Player Game", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 48);
	TextManager::GetInstance()->Render("2 Player Game", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 80);
	TextManager::GetInstance()->Render("Top - " + _TopScore, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 128);
}

void MenuScene::Release()
{
}

void MenuScene::Load()
{
	try
	{
		ifstream infile(L"resources\\TopScore.txt");
		string line;
		while (getline(infile, line))
		{
			_TopScore = Unility::IntToFixedLengthString(atoi(line.c_str()), 6);
		}
	}
	catch(exception e)
	{
		
	}
}
	
void MenuScene::HandlingInput()
{
	if(Keyboard::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap);
	}
}
