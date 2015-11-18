#include "Sound.h"
#include "DSutil.h"

Sound::Sound()
{
	this->_SoundBuffer = NULL;
}

Sound::Sound(LPDIRECTSOUND8 lpDSound, LPWSTR Path)
{
	LoadSound(lpDSound, Path);
}
Sound::~Sound()
{
	_SoundBuffer->Release();
}

bool Sound::LoadSound(LPDIRECTSOUND8 lpDSound, LPWSTR Path)
{
	CWaveFile* waveFile = new CWaveFile();
	HRESULT hr;

	hr = waveFile->Open(Path, NULL, WAVEFILE_READ);

	if FAILED(hr)
	{
		return false;
	}
	DSBUFFERDESC _dsbd;
	ZeroMemory(&_dsbd, sizeof(DSBUFFERDESC));
	_dsbd.dwSize		= sizeof(DSBUFFERDESC);
	_dsbd.dwFlags		= DSBCAPS_CTRLVOLUME;
	_dsbd.dwBufferBytes	= waveFile->GetSize();
	_dsbd.guid3DAlgorithm = GUID_NULL;
	_dsbd.lpwfxFormat	= waveFile->m_pwfx;

	hr = lpDSound->CreateSoundBuffer(&_dsbd, &_SoundBuffer, NULL);
	if FAILED(hr)
	{
		return false;
	}
	VOID*	pDSLockedBuffer			= NULL; // pointer to a locked buffer memory
	DWORD	dwDSLockedBufferSize	= 0;	// Size of the locked DirectSound buffer
	DWORD	dwWavDataRead			= 0; // Amount of data from the wav file

	hr = _SoundBuffer->Lock(0, waveFile->GetSize(), &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0L);

	if FAILED(hr)
	{
		return false;
	}

	// Res the wave file to the begin
	waveFile->ResetFile();

	// Read the wave File
	hr = waveFile->Read( (BYTE*)pDSLockedBuffer, 
							dwDSLockedBufferSize,
							&dwWavDataRead ) ;
	if FAILED(hr)
	{
		return false;
	}

	if (dwWavDataRead == 0)
	{
		// Wave is blank, so just fill with silence
		FillMemory( (BYTE*) pDSLockedBuffer, 
			dwDSLockedBufferSize,
			BYTE(waveFile->m_pwfx->wBitsPerSample = 8 ? 128 : 0));
	} else if( dwWavDataRead < dwDSLockedBufferSize)
	{
		// DOn't repeat the wav file, just fill in slience
		FillMemory( (BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			BYTE(waveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 8) );
	}

	// unlock buffer
	_SoundBuffer->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, 0, 0);
	// clean
	delete waveFile;

	return true;
}

void Sound::Play() const
{
	_SoundBuffer->SetCurrentPosition(0);
	_SoundBuffer->Play(0, 0, 0);
}
void Sound::Repeat() const
{
		_SoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
}
void Sound::Stop() const
{
	_SoundBuffer->Stop();
}
LPDIRECTSOUNDBUFFER Sound::GetSoundBuffer() const
{
	return _SoundBuffer;
}
void Sound::Release() const
{
	_SoundBuffer->Release();
}
