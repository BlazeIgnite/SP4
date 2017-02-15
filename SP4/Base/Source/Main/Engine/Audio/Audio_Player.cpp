#include "Audio_Player.h"

AudioPlayer::AudioPlayer()
{}

AudioPlayer::~AudioPlayer()
{}

void AudioPlayer::Init()
{
	SoundEngine = createIrrKlangDevice();
}

void AudioPlayer::PlayBGM()
{
	
}

void AudioPlayer::Exit()
{
	if (SoundEngine)
	{
		SoundEngine->drop();
		SoundEngine = false;
	}
}