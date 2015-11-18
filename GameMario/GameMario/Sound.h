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
	LPDIRECTSOUNDBUFFER GetSoundBuffer() const;
	void Play() const;
	void Repeat() const;
	void Stop() const;
	void Release() const;
};

