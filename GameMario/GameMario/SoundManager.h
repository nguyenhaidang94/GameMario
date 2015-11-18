#pragma once
#include <dsound.h>
#include <map>
#include "GlobalVariables.h"
#include "Sound.h"

class SoundManager
{
private:
	std::map<eSoundID, Sound*> _ListSound;
	static SoundManager *_Instance;
public:
	SoundManager(void);
	~SoundManager(void);
	static SoundManager *GetInstance();
	void LoadSounds(LPDIRECTSOUND8 lpDSound);
	Sound *GetSound(eSoundID soundID);
	void Release();
};

