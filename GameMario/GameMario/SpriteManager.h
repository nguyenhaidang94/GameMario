#pragma once
#include "Sprite.h"
#include <map>

class SpriteManager
{
private:
	std::map<eSpriteID, Sprite*> _ListSprite;		//Store all sprite of game
	static SpriteManager *Instance;				
public:
	SpriteManager(void);
	~SpriteManager(void);

	//Get instance of sprite manager
	static SpriteManager *GetInstance();

	//Load all sprite of the game
	void LoadSprite(LPD3DXSPRITE &SpriteHandler);

	//Get a selected sprite by objectID
	Sprite *GetSprite(eSpriteID objectID);

	//Release all sprite
	void Release();

	//Advance to next frame between startFrame and endFrame
	static int NextFrame(int currentFrame, int startFrame, int endFrame);
	//Advance to previous frame between startFrame and endFrame
	static int PreviousFrame(int currentFrame, int startFrame, int endFrame);
};

