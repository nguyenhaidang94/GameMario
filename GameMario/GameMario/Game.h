#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "Keyboard.h"
#include "GameStatistics.h"
#include "TextManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

class Game
{
private:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DSURFACE9 _backbuffer;
	LPDIRECT3DSURFACE9 _surface;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECTSOUND8	_lpDirectSound;
	DWORD _start;
public:
	Game(void);
	int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen);
	int Init_DirectSound(HWND hWnd);
	int Init_SpriteHandle();
	int Game_Init(HINSTANCE hInstance, HWND hWnd);
	void Game_Run(HWND hWnd);
	void Game_End(HWND hWnd);
	~Game();
};