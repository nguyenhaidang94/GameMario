#include "Background.h"

Background::Background(void)
{
	_TotalHorizontalTitle = 0;
	_TotalVerticalTitle = 0;
}


Background::~Background(void)
{
}

void Background::Initialize(int totalHorizontal, int totalVertical)
{
	//Initate _BackgroundData array
	_TotalHorizontalTitle = totalHorizontal;
	_TotalVerticalTitle = totalVertical;
	_BackgroundData = new int*[_TotalVerticalTitle];
	for(int i = 0; i < _TotalVerticalTitle; ++i)
		_BackgroundData[i] = new int[_TotalHorizontalTitle];

	//Set world size for camera
	Camera::GetInstance()->SetWorldSize(_TotalHorizontalTitle * TITLE_SIZE, _TotalVerticalTitle * TITLE_SIZE);

	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMapTile);
}

void Background::ReadMapData(eWorldID mapID)
{
	string fileName;
	switch (mapID)
	{
	case e1_1:
		fileName = "1_1";
		break;
	case e1_2:
		fileName = "1_2";
		break;
	case e1_3:
		break;
	case e1_4:
		break;
	case eUnderground1_1:
		fileName = "u1_1";
		break;
	default:
		break;
	}

	char BackgroundPath[100];
	sprintf(BackgroundPath, "resources\\Maps\\%s.txt", fileName.c_str());	//Merge string
	ifstream infile(BackgroundPath);
	int lineNumber = 0;		//store current line number
	string line;
	int titleID;			//store titleID read in file
	while (getline(infile, line))
	{
		istringstream iss(line);
		if(lineNumber == 0)
		{
			int totalHorizontal, totalVertical;
			if (!(iss >> totalHorizontal >> totalVertical)) { break; } // error
			Initialize(totalHorizontal, totalVertical);
		}
		else
		{
			//Read Background - each line is a Background horizontal title
			vector<string> temp = Unility::Split(line, ',');
			
			for(int i = 0; i < _TotalHorizontalTitle; i++)
			{
				//convert string into character
				titleID = atoi(temp[i].c_str());
				_BackgroundData[lineNumber - 1][i] = titleID -1;	//TiledMap generate base 1, so we have to -1
			}
			temp.clear();
		}
		lineNumber++;
	}
}

void Background::Render()
{
	int minRange = Camera::GetInstance()->GetBoundaryBox().fX / TITLE_SIZE;
	int maxRange = minRange + SCREEN_HEIGHT/TITLE_SIZE + 2;
	for(int i = 0; i < _TotalVerticalTitle; i++)
	{
		//only render background on sight
		for(int j = minRange; j < maxRange; j++)
		{
			_Sprite->RenderAtFrame((float)j * TITLE_SIZE + TITLE_SIZE/2, SCREEN_HEIGHT - (float)i * TITLE_SIZE - TITLE_SIZE/2, _BackgroundData[i][j], 0.4);
		}
	}
}

void Background::Release()
{
	for(int i = 0; i < _TotalVerticalTitle; i++)
	{
		delete[] _BackgroundData[i];
	}
	delete[] _BackgroundData;
}