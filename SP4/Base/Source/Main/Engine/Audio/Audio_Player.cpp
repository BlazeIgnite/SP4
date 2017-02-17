#include "Audio_Player.h"

AudioPlayer::AudioPlayer()
{}

AudioPlayer::~AudioPlayer()
{}

void AudioPlayer::Init()
{
	SoundEngine = createIrrKlangDevice();
	SetVolume(1.f);
}

void AudioPlayer::PlayMusic(string MusicName)
{
	if (MusicName == "BGM")
		PlayBGM();
}

void AudioPlayer::SetVolume(float volume)
{
	SoundEngine->setSoundVolume(volume);
}

void AudioPlayer::PlayBGM()
{
	if (SoundEngine->isCurrentlyPlaying("Music/BGM.mp3"))
		return;
	SoundEngine->play2D("Music/BGM.mp3", true);
}

void AudioPlayer::Exit()
{
	if (SoundEngine)
	{
		SoundEngine->drop();
		SoundEngine = false;
	}
}