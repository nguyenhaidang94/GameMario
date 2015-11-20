#pragma once

#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

#define KEY_DOWN(vk_key)((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0)
#define KEYBOARD_BUFFER_SIZE	1024

class Keyboard
{
protected:
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	HINSTANCE _hInstance;
	HWND _hWnd;
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 
	BYTE _PreviousKeyStates[256];	// DirectInput keyboard previous state buffer 
	static Keyboard *_Instance;
	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
public:
	Keyboard(void);
	virtual ~Keyboard(void);
	static Keyboard *GetInstance();
	void InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void ProcessKeyBoard();
	int IsKeyDown(int KeyCode) const;
	int IsKeyPress(int KeyCode) const;
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	//virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput();
	void Release() const;
};