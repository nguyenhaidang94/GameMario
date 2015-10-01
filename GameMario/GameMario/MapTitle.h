#pragma once
#include "GameObject.h"
#include "SpriteManager.h"

class MapTitle : GameObject
{
	int _TitleID;
public:
	MapTitle(void);
	MapTitle(int titleID, int x, int y, Sprite *sprite);
	~MapTitle(void);
	void Render();
	void Destroy();
	void GetColisionBox();
};

