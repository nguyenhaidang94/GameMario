#include "TextManager.h"
#define TEXT_SIZE 20		//each text sprite is 20x20
#define COIN_FRAME_RATE 8	//coin at top score swap 8 time per sec

TextManager *TextManager::Instance = NULL;

TextManager::TextManager(void)
{
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eFont);
	_CurrentFrame = 0;
	count_per_frame = 1000 / COIN_FRAME_RATE;
	frame_start = GetTickCount();
}


TextManager::~TextManager(void)
{
}

TextManager *TextManager::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new TextManager();
	}
	return Instance;
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
	return -1;
}

void TextManager::Render(string text, int x, int y)
{
	int startPosition = x - text.length() * TEXT_SIZE / 2;	//allign center for text
	for(int i = 0; i < text.size(); i++)
	{
		_Sprite->RenderAtFrame(startPosition + i * TEXT_SIZE, y, GetFrameNumberFromChar(text[i]));
	}
}

void TextManager::FixedRender(string text, int x, int y)
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
	FixedRender("mario", 92, 32);
	FixedRender(Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetScore(), 6), 102, 55);
	//Render coin effer at score on top
	SpriteManager::GetInstance()->GetSprite(eSpriteID::eCoin)->FixedRenderAtFrame(180, 55, _CurrentFrame);
	FixedRender("x" + Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetCoinCount(), 2), 230, 55);
	FixedRender("world", 332, 32);
	FixedRender(GameStatistics::GetInstance()->GetCurrentWorldName(), 338, 55);
	FixedRender("time", 450, 32);
	FixedRender(Unility::IntToFixedLengthString(GameStatistics::GetInstance()->GetTime(), 3), 450, 55);


	//control coin rate
	DWORD now = GetTickCount();
	if (now - frame_start >= count_per_frame) 
	{
		frame_start = now;
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 3);
	}
}