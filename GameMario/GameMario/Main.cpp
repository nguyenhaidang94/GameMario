#include <Windows.h>
#include "GlobalVariables.h"
#include "Game.h"

//Macro
#define APPTITLE L"TESTING GAME"
#define SCREEN WS_OVERLAPPEDWINDOW

//window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;

	//set up the window with the class info
	return RegisterClassEx(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game *game = new Game();

	//devlare variables
	MSG msg;
	HWND hWnd;

	//regidter the class
	MyRegisterClass(hInstance);

	//create a new window
	hWnd = CreateWindow(
		APPTITLE,
		APPTITLE,
		SCREEN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	//display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!game->Game_Init(hInstance, hWnd))
	{
		return 0;
	}

	DWORD frame_start = GetTickCount();	
	DWORD count_per_frame = 1000 / FRAME_RATE;
	DWORD game_time_start = GetTickCount();		//to minus current game time 

	//main message loop
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		if (now - frame_start >= count_per_frame) 
		{
			frame_start = now;
			game->Game_Run(hWnd);
			if(now - game_time_start > 1000)
			{
				GameStatistics::GetInstance()->DecreaseTime();
				game_time_start = now;
			}
		}
	}

	game->Game_End(hWnd);
	return msg.wParam;
}