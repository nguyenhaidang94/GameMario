#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "Keyboard.h"
#include "GameStatistics.h"

class Game
{
private:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DSURFACE9 _backbuffer;
	LPDIRECT3DSURFACE9 _surface;
	LPD3DXSPRITE _spriteHandler;
	DWORD _start;
public:
	Game(void);
	int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen);
	int Game_Init(HINSTANCE hInstance, HWND hWnd);
	void Game_Run(HWND hWnd);
	void Game_End(HWND hWnd);
	~Game();
};