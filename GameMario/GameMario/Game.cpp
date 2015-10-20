#include "Game.h"
#define KEY_DOWN(vk_key)((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0)

Game::Game(void)
{
	_d3d = NULL;
	_d3ddev = NULL;
	_backbuffer = NULL;
}

//Init dictect3D
int Game::Init_Direct3D(HWND hWnd, int width, int height, int fullscreen)
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (_d3d == NULL)
	{
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}
	
	//set Direct3D presention parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hWnd;

	
	_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_d3ddev);
	if (_d3ddev == NULL)
	{
		MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
		return 0;
	}
	
	_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_backbuffer);

	return 1;
}

//Init sound
int Game::Init_DirectSound(HWND hWnd)
{
	HRESULT hr;
	hr = DirectSoundCreate8(0, &_lpDirectSound, 0);
	if(FAILED(hr))
	{
		return false;
	}
	hr = _lpDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if(FAILED(hr))
	{
		return false;
	}
	return true;
}

//Init sprite handler
int Game::Init_SpriteHandle()
{
	HRESULT hr = D3DXCreateSprite(_d3ddev, &_spriteHandler);
	if(FAILED(hr))
	{
		return false;
	}
	return true;
}

int Game::Game_Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result;
	DWORD test;
	LPDIRECTSOUND lpDSound;

	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
	{
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	if (!Init_DirectSound(hWnd))
	{
		MessageBox(hWnd, L"Error initializing DirectSound", L"Error", MB_OK);
		return 0;
	}

	if (!Init_SpriteHandle())
	{
		MessageBox(hWnd, L"Error initializing SpriteHandler", L"Error", MB_OK);
		return 0;
	}

	//Init game object 
	//Sprite manager
	SpriteManager::GetInstance()->LoadSprite(_spriteHandler);
	Keyboard::GetInstance()->InitKeyboard(hInstance, hWnd);
	GameStatistics::GetInstance()->Initialize();
	SoundManager::GetInstance()->LoadSounds(_lpDirectSound);
	SceneManager::GetInstance()->Initialize();
	return 1;
}

void Game::Game_Run(HWND hWnd)
{
	Keyboard::GetInstance()->ProcessKeyBoard();
	SceneManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

	if (_d3ddev == NULL)
		return;

	_d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1, NULL);
	if (_d3ddev->BeginScene())
	{
		_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

		SceneManager::GetInstance()->Render();
		EffectManager::GetInstance()->Render();
		TextManager::GetInstance()->RenderScoreOnTop();

		_spriteHandler->End();
		_d3ddev->EndScene();	

	}

	_d3ddev->Present(NULL, NULL, NULL, NULL);

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hWnd, WM_DESTROY, 0, 0);
}

void Game::Game_End(HWND hWnd)
{
	if (_d3ddev != NULL)
		_d3ddev->Release();

	//release the Direct3D object
	if (_d3d != NULL)
		_d3d->Release();

	if (_backbuffer != NULL)
		_backbuffer->Release();

	SceneManager::GetInstance()->Release();
	SpriteManager::GetInstance()->Release();
	EffectManager::GetInstance()->Release();
}

Game::~Game(void)
{

}