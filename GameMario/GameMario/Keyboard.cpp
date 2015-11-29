#include "Keyboard.h"

Keyboard *Keyboard::_Instance = NULL;

Keyboard::Keyboard(void)
{
	_di = NULL;
	_Keyboard = NULL;
}

Keyboard::~Keyboard(void)
{

}

Keyboard *Keyboard::GetInstance()
{
	if (_Instance == NULL)
	{
		_Instance = new Keyboard();
	}
	return _Instance;
}

void Keyboard::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	_hInstance = hInstance;
	_hWnd = hWnd;
	HRESULT
		hr = DirectInput8Create
		(
		_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;


	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	_Keyboard->SetDataFormat(&c_dfDIKeyboard);

	_Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size


	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;
}

void Keyboard::ProcessKeyBoard()
{
	//store previous keyboard states
	memcpy(_PreviousKeyStates, _KeyStates, 256);
	// Collect all key states first
	_Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	if (FAILED(hr))
	{
		_Keyboard->Acquire();
	}

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

int Keyboard::IsKeyDown(int KeyCode) const
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

int Keyboard::IsKeyPress(int keyCode) const
{
	if((_KeyStates[keyCode] & 0x00000080) && !(_PreviousKeyStates[keyCode] & 0x00000080))
	{
		return true;
	}
	return false;
}

//void Keyboard::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) { }
void Keyboard::ProcessInput() { }
void Keyboard::OnKeyUp(int KeyCode) { }
void Keyboard::OnKeyDown(int KeyCode) { }

void Keyboard::Release() const
{
	if (_di == NULL)
		_di->Release();

	if (_Keyboard == NULL)
		_Keyboard->Release();
}
