#pragma once
#include <string.h>
#include <sstream>
#include <fstream>
#include "Camera.h"
#include "Unility.h"
#include "SpriteManager.h"
#include "GlobalVariables.h"
using namespace std;

class Background
{
private:	
	int _TotalVerticalTitle;		//total vertical title of Background
	int	_TotalHorizontalTitle;		//total horizontal title of Background
	int** _BackgroundData;			//Store Background data in 2d array
	Sprite *_Sprite;
public:
	Background(void);
	~Background(void);
	//Initial background object
	void Initialize(int totalHorizontal, int totalVertical);

    // Read from file to get Background data
	void ReadMapData(eWorldID MapID);

    //Render Background to screen
	void Render();

    //Release Background menory
	void Release();
};

