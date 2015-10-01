#include "TextManager.h"
#define TEXT_SIZE 20		//each text sprite is 20x20

TextManager *TextManager::Instance = NULL;

TextManager::TextManager(void)
{
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eFont);
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
	for(int i = 0; i < text.size(); i++)
	{
		_Sprite->RenderAtFrame(x + i * TEXT_SIZE, y, GetFrameNumberFromChar(text[i]));
	}
}

void TextManager::FixedRender(string text, int x, int y)
{
	for(int i = 0; i < text.size(); i++)
	{
		int temp = GetFrameNumberFromChar(text[i]);
		_Sprite->FixedRenderAtFrame(x + i * TEXT_SIZE, y, GetFrameNumberFromChar(text[i]));
	}
}

void TextManager::RenderScoreOnTop()
{
	FixedRender("mario", 32, 32);
	FixedRender(to_string(GameStatistics::GetInstance()->GetScore()), 32, 55);
	FixedRender("x" + to_string(GameStatistics::GetInstance()->GetCoinCount()), 164, 55);
	FixedRender("world", 224, 32);
	FixedRender(GameStatistics::GetInstance()->GetCurrentWorldName(), 240, 55);
	FixedRender("time", 388, 32);
	FixedRender(to_string(GameStatistics::GetInstance()->GetTime()), 388, 55);
}