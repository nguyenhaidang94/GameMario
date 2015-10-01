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

int Game::Game_Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result;
	DWORD test;

	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
	{
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	D3DXCreateSprite(_d3ddev, &_spriteHandler);

	//Init game object 
	//Sprite manager
	SpriteManager::GetInstance()->LoadSprite(_spriteHandler);
	Keyboard::GetInstance()->InitKeyboard(hInstance, hWnd);
	SceneManager::GetInstance()->Initialize();
	SceneManager::GetInstance()->SwitchScene(eSceneID::ePlay);
	GameStatistics::GetInstance()->Initialize();
	return 1;
}

void Game::Game_Run(HWND hWnd)
{
	Keyboard::GetInstance()->ProcessKeyBoard();
	SceneManager::GetInstance()->Update();

	if (_d3ddev == NULL)
		return;

	_d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1, NULL);
	if (_d3ddev->BeginScene())
	{
		SceneManager::GetInstance()->Render();
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
}

Game::~Game(void)
{

}