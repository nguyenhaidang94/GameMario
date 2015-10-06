#include "SoundManager.h"

SoundManager *SoundManager::Instance = NULL;

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}

SoundManager *SoundManager::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new SoundManager();
	}
	return Instance;
}

void SoundManager::LoadSounds(LPDIRECTSOUND8 lpDSound)
{
	_ListSound[eSoundID::eJumpSmall] = new Sound(lpDSound, L"resources\\Sounds\\smb_jump-small.wav");
}

Sound *SoundManager::GetSound(eSoundID soundID)
{
	if (_ListSound.find(soundID) != _ListSound.end()) 
	{
		return _ListSound[soundID];
	} 
	else 
	{
		return NULL;
	}
}

void SoundManager::Release()
{
	_ListSound.clear();
}