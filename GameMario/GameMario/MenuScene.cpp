#include "MenuScene.h"
#define WAIT_TIME 5000		//wait 5s before mario auto run

MenuScene::MenuScene(void)
{
	_SceneID = eSceneID::eMenu;
	_SpriteBanner = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuBanner);
	_SpriteMushroom =  SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuMushroom);
	_DemoMap = new PlayMap(eWorldID::e1_1);
	_MushroomPositionY = SCREEN_HEIGHT/2 - 48;
	_IsAutoRun = false;
}


MenuScene::~MenuScene(void)
{
}

void MenuScene::Initialize()
{
	_SpriteBanner = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuBanner);

}

void MenuScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME) _IsAutoRun=true;

	if(_IsAutoRun==true)
	{
		//Set mario state to auto run here
		Mario::GetInstance()->SetFlagAutoAnimationRight(true);
		Mario::GetInstance()->AutoAnimationRight(D3DXVECTOR2(896,96));
	}
	else	//testing, delete this after mario have auto run state
	{
			Mario::GetInstance()->SetFlagAutoAnimationRight(false);
		
	}
	HandlingInput();
	_DemoMap->Update();
}

void MenuScene::Render()
{
	_SpriteBanner->RenderFirstFrame(SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3);
	_SpriteMushroom->RenderFirstFrame(SCREEN_WIDTH/2 - 144, _MushroomPositionY);
	TextManager::GetInstance()->Render("1 Player Game", SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 48);
	TextManager::GetInstance()->Render("2 Player Game", SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 80);
	TextManager::GetInstance()->Render("Top - " + _TopScore, SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 128);
	_DemoMap->Render();
}

void MenuScene::Release()
{
	_DemoMap->Release();
}

void MenuScene::Load()
{
	_StartTime = GetTickCount();
	GameStatistics::GetInstance()->SetLife(1);
	_DemoMap->Reload();
	Mario::GetInstance()->SetPosition(D3DXVECTOR2(48, 80));
	Mario::GetInstance()->SetFlagAutoAnimationRight(false);
	Mario::GetInstance()->Initialize();
	Camera::GetInstance()->Reset();
	_IsAutoRun = false;
	try
	{
		ifstream infile(L"resources\\TopScore.txt");
		string line;
		while (getline(infile, line))
		{
			_TopScore = Unility::IntToFixedLengthString(atoi(line.c_str()), 6);
		}
		infile.close();
	}
	catch(exception e)
	{
		//handle sth here
	}
}
	
void MenuScene::HandlingInput()
{
	if(!_IsAutoRun)
	{
		if(Keyboard::GetInstance()->IsKeyPress(DIK_SPACE))
		{
			GameStatistics::GetInstance()->ChangeScene(eSceneID::eStartMap);
			GameStatistics::GetInstance()->Reset();
			Mario::GetInstance()->SetIsControl(true);
		}

		if(Keyboard::GetInstance()->IsKeyPress(DIK_T))
		{
			_StartTime = GetTickCount();	//reset wait time
			if(_MushroomPositionY == SCREEN_HEIGHT/2 - 48)
			{
				_MushroomPositionY -= 32;
			}
			else
			{
				_MushroomPositionY += 32;
			}
		}
	}
	else
	{
		if(Keyboard::GetInstance()->IsKeyPress(DIK_SPACE))
		{
			Load();	//reload
		}
	}
}
