#include "SoundManager.h"

SoundManager *SoundManager::_Instance = NULL;

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}

SoundManager *SoundManager::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new SoundManager();
	}
	return _Instance;
}

void SoundManager::LoadSounds(LPDIRECTSOUND8 lpDSound)
{
	_ListSound[eSoundID::eJumpSmall] = new Sound(lpDSound, L"resources\\Sounds\\smb_jump-small.wav");
	_ListSound[eSoundID::ePowerUp] = new Sound(lpDSound, L"resources\\Sounds\\smb_powerup.wav");
	_ListSound[eSoundID::eVine] = new Sound(lpDSound, L"resources\\Sounds\\smb_vine.wav");
	_ListSound[eSoundID::ePowerUpAppears] = new Sound(lpDSound, L"resources\\Sounds\\smb_powerup_appears.wav");
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