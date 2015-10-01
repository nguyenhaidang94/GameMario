#include "MapTitle.h"


MapTitle::MapTitle(void)
{
}

MapTitle::MapTitle(int titleID, int x, int y, Sprite *sprite)
{
	_TitleID = titleID;
	SetPosition(x, y);
	_Sprite = sprite;
}

MapTitle::~MapTitle(void)
{
}

void MapTitle::Render()
{
	_Sprite->RenderAtFrame(_X, _Y, _TitleID);
}

void MapTitle::Destroy()
{
	delete this;
}


