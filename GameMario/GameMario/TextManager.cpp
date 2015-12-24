#include "TextManager.h"
#define TEXT_SIZE 16		//each text sprite is 20x20
#define COIN_FRAME_RATE 4	//coin at top score swap 4 time per sec

TextManager *TextManager::_Instance = NULL;

TextManager::TextManager(void)
{
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eFont);
	_CurrentFrame = 0;
	_CountPerFrame = 1000 / COIN_FRAME_RATE;
	_FrameStart = GetTickCount();
}


TextManager::~TextManager(void)
{
}

TextManager *TextManager::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new TextManager();
	}
	return _Instance;
}

int TextManager::GetFrameNumberFromChar(char c)
{
	int value = (int)c;		//convert char to ascii code
	if(c >= '0' && c <= '9')
	{
		return value - 48;
	}
	if(c >= 'A' && c <= 'Z')
	{
		return value - 65 + 10;		//-65 ascii char + 10 number
	}
	if(c >= 'a' && c <= 'z')
	{
		return value - 97 + 10;
	}
	if(c == '-')
	{
		return 37;
	}
	if(c == '*')
	{
		return 38;
	}
	if(c == '!')
	{
		return 39;
	}
	return 40;	//blank
}

void TextManager::Render(string text, int x, int y) const
{
	int startPosition = x - text.length() * TEXT_SIZE / 2;	//allign center for text
	for(int i = 0; i < text.size(); i++)
	{
		_Sprite->RenderAtFrame(startPosition + i * TEXT_SIZE, y, GetFrameNumberFromChar(text[i]));
	}
}

void TextManager::FixedRender(string text, int x, int y) const
{
	int startPosition = x - text.length() * TEXT_SIZE / 2;	//allign center for text
	for(int i = 0; i < text.size(); i++)
	{
		int temp = GetFrameNumberFromChar(text[i]);
		_Sprite->FixedRenderAtFrame(startPosition + i * TEXT_SIZE, y, GetFrameNumberFromChar(text[i]));
	}
}

void TextManager::RenderScoreOnTop()
{
	FixedRender("mario", 92, 27);
	FixedRender(Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetScore(), 6), 102, 50);
	//Render coin effer at score on top
	SpriteManager::GetInstance()->GetSprite(eSpriteID::eTopCoin)->FixedRenderAtFrame(190, 50, _CurrentFrame);
	FixedRender("*" + Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetCoinCount(), 2), 230, 50);
	FixedRender("world", 332, 27);
	FixedRender(GameStatistics::GetInstance()->GetCurrentWorldName(), 338, 50);
	FixedRender("time", 450, 27);
	FixedRender(Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetTime(), 3), 450, 50);


	//control coin rate
	DWORD now = GetTickCount();
	if (now - _FrameStart >= _CountPerFrame) 
	{
		_FrameStart = now;
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
	}
}