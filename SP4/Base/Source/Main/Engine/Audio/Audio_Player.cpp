#include "Audio_Player.h"

AudioPlayer::AudioPlayer()
{}

AudioPlayer::~AudioPlayer()
{}

void AudioPlayer::Init()
{
	SoundEngine = createIrrKlangDevice();
	SetVolume(0.1f);
}

void AudioPlayer::PlayMusic(string MusicName)
{
	if (MusicName == "BGM")
		PlayBGM();
	if (MusicName == "Battle Music")
		PlayBattleMusic();
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

void AudioPlayer::PlayBattleMusic()
{
	if (SoundEngine->isCurrentlyPlaying("Music/BattleMusic.mp3"))
		return;
	SoundEngine->play2D("Music/BattleMusic.mp3", true);
}

void AudioPlayer::StopAllMusic()
{
	SoundEngine->stopAllSounds();
}

void AudioPlayer::Exit()
{
	if (SoundEngine)
	{
		SoundEngine->drop();
		SoundEngine = false;
	}
}