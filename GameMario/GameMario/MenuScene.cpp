#include "MenuScene.h"

MenuScene *MenuScene::Instance = NULL;

MenuScene::MenuScene(void)
{
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
	_SpriteBanner->RenderFirstFrame(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void MenuScene::Release()
{
}

void MenuScene::Load()
{
	
}
	
void MenuScene::HandlingInput()
{
	if(Keyboard::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		SceneManager::GetInstance()->SwitchScene(eSceneID::eStartMap);
	}
}
