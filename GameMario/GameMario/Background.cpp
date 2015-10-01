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
	_BackgroundData = new int*[_TotalHorizontalTitle];
	for(int i = 0; i < _TotalHorizontalTitle; ++i)
		_BackgroundData[i] = new int[_TotalVerticalTitle];

	//Set world size for camera
	Camera::GetInstance()->SetWorldSize(_TotalVerticalTitle * TITLE_SIZE, _TotalHorizontalTitle * TITLE_SIZE);
}

void Background::ReadMapData(eWorldID mapID)
{
	string fileName;
	switch (mapID)
	{
	case e1_1:
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMap1_1);
		fileName = "1_1";
		break;
	case e1_2:
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMap1_1);
		fileName = "1_2";
		break;
	case e1_3:
		break;
	case e1_4:
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
			vector<string> temp = Unility::Split(line, ' ');
			
			for(int i = 0; i < _TotalVerticalTitle; i++)
			{
				//convert string into character
				titleID = atoi(temp[i].c_str());
				_BackgroundData[lineNumber - 1][i] = titleID;
			}
			temp.clear();
		}
		lineNumber++;
	}
}

void Background::Render()
{
	for(int i = 0; i < _TotalHorizontalTitle; i++)
	{
		for(int j = 0; j < _TotalVerticalTitle; j++)
		{
			_Sprite->RenderAtFrame((float)j * TITLE_SIZE, SCREEN_HEIGHT - (float)i * TITLE_SIZE, _BackgroundData[i][j]);
		}
	}
}

void Background::Release()
{
	for(int i = 0; i < _TotalHorizontalTitle; i++)
	{
		delete[] _BackgroundData[i];
	}
	delete[] _BackgroundData;
}