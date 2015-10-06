#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GlobalVariables.h"
#include "Camera.h"

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;		// The “container”
	LPD3DXSPRITE _SpriteHandler;

	double _Width;   	// Sprite width
	double _Height;		// Sprite height
	int _Count;		// Number of sprites in the container
	int _SpritePerRow;	// Number of sprites per row

public:
	Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR Path, double Width, double Height, int Count, int SpritePerRow, D3DCOLOR TransparentColor);
	Sprite::Sprite(void);
	~Sprite(void);
	//Render at frameNo
	void RenderAtFrame(float x, float y, int frameNo);
	//Render at 1st frame
	void RenderFirstFrame(float x, float y);
	//Render at fixed location on screen, y axis from top
	void FixedRenderAtFrame(float x, float y, int frameNo);
	void Release();
};

