#pragma once
#include <dsound.h>

class Sound
{
private:
	LPDIRECTSOUNDBUFFER _SoundBuffer;
public:
	Sound();
	Sound(LPDIRECTSOUND8 lpDSound, LPWSTR Path);
	~Sound();

	bool LoadSound(LPDIRECTSOUND8 lpDSound, LPWSTR Path);
	LPDIRECTSOUNDBUFFER GetSoundBuffer();
	void Play();
	void Repeat();
	void Stop();
	void Release();
};

