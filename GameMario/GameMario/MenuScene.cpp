#include "MenuScene.h"
#define WAIT_TIME 5000		//wait 5s before mario auto run

MenuScene::MenuScene(void)
{
	_SceneID = eSceneID::eMenu;
	_SpriteBanner = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuBanner);
	_SpriteMushroom =  SpriteManager::GetInstance()->GetSprite(eSpriteID::eMenuMushroom);
	_DemoMap = new PlayMap(eWorldID::e1_1);
	_MushroomPositionY = SCREEN_HEIGHT/2 - 32;
	_IsAutoRun = false;
	_IsShowHelp = false;	//not show help
	_HelpSprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eHelp);
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
	if(!_IsShowHelp)
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
		_DemoMap->Update();
	}
	HandlingInput();
}

void MenuScene::Render()
{
	if(!_IsShowHelp)	//render normally if not show help
	{
		_SpriteBanner->RenderFirstFrame(SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3);
		_SpriteMushroom->RenderFirstFrame(SCREEN_WIDTH/2 - 144, _MushroomPositionY);
		TextManager::GetInstance()->Render("1 Player Game", SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 32);
		TextManager::GetInstance()->Render("2 Player Game", SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 64);
		TextManager::GetInstance()->Render("Press F1 To See Help", SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 96);
		TextManager::GetInstance()->Render("Top - " + _TopScore, SCREEN_WIDTH/2 + 5, SCREEN_HEIGHT/2 - 128);
		_DemoMap->Render();
	}
	else	//show help
	{
		_HelpSprite->FixedRenderAtFrame(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0.6);
	}
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
		//read file high score
		fstream file(L"resources\\TopScore.txt");
		string line;
		int topScore;
		while (getline(file, line))
		{
			topScore = atoi(line.c_str());
		}

		 //save score to file
		//if current score higher than top score, save
		int currentScore = GameStatistics::GetInstance()->GetScore() ;
		if(currentScore > topScore)
		{
			//cant write file directly, so have to reopen the file
			file.close();
			file.open(L"resources\\TopScore.txt", std::fstream::out | std::fstream::trunc);
			file << currentScore;	//write to file
			_TopScore = Unility::IntToFixedLengthString(atoi(to_string(currentScore).c_str()),6);	//top score = current score and convert to string with 6 character
		}
		else
		{
			_TopScore = Unility::IntToFixedLengthString(atoi(to_string(topScore).c_str()),6);		//top score is score in file and convert to string with 6 character
		}
		file.close();
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
		if(!_IsShowHelp)	//normal menu scene
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
				if(_MushroomPositionY == SCREEN_HEIGHT/2 - 32)
				{
					_MushroomPositionY -= 32;
				}
				else
				{
					_MushroomPositionY += 32;
				}
			}

			if(Keyboard::GetInstance()->IsKeyPress(DIK_F1))
			{
				_IsShowHelp = true;
			}
		}
		else	//help
		{
			if(Keyboard::GetInstance()->IsKeyPress(DIK_F1))
			{
				_StartTime = GetTickCount();
				_IsShowHelp = false;
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
