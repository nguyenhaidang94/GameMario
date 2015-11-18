#pragma once
#include <string>
#include "SpriteManager.h"
#include "GameStatistics.h"
#include "Unility.h"
using namespace std;

class TextManager
{
	Sprite *_Sprite;
	static TextManager *_Instance;
	static int GetFrameNumberFromChar(char c);
	//variable to manage coin at top score
	int _CurrentFrame;		
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	TextManager(void);
	~TextManager(void);
	static TextManager *GetInstance();
	void Render(string text, int x, int y) const;
	void FixedRender(string text, int x, int y) const;
	void RenderScoreOnTop();
};

