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
	_ListSound[eSoundID::e1Up] =  new Sound(lpDSound, L"resources\\Sounds\\smb_1-up.wav");
	_ListSound[eSoundID::eBrickSmash] =  new Sound(lpDSound, L"resources\\Sounds\\smb_breakblock.wav");
	_ListSound[eSoundID::eBump] = new Sound(lpDSound, L"resources\\Sounds\\smb_bump.wav");
	_ListSound[eSoundID::eCoinAppear] = new Sound(lpDSound, L"resources\\Sounds\\smb_coin.wav");
	_ListSound[eSoundID::eDownTheFlagpole] = new Sound(lpDSound, L"resources\\Sounds\\smb_flagpole.wav");
	_ListSound[eSoundID::eMarioDie] = new Sound(lpDSound, L"resources\\Sounds\\smb_mariodie.wav"); 
	_ListSound[eSoundID::ePipeTravel] = new Sound(lpDSound, L"resources\\Sounds\\smb_pipe.wav"); 
	_ListSound[eSoundID::eSoundGameOver] = new Sound(lpDSound, L"resources\\Sounds\\smb_gameover.wav"); 
	_ListSound[eSoundID::eStageClear] =  new Sound(lpDSound, L"resources\\Sounds\\smb_stage_clear.wav"); 
	_ListSound[eSoundID::eWorldClear] = new Sound(lpDSound, L"resources\\Sounds\\smb_world_clear.wav"); 
	_ListSound[eSoundID::eWorldMusic] = new Sound(lpDSound, L"resources\\Sounds\\smb_world_music.wav"); 
	_ListSound[eSoundID::eMonsterMusic] = new Sound(lpDSound, L"resources\\Sounds\\smb_stomp.wav"); 
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