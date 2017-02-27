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
	if (MusicName == "Bleed Effect")
		PlayBleedEffect();
	if (MusicName == "Buff Effect")
		PlayBuffEffect();
	if (MusicName == "Debuff Effect")
		PlayDebuffEffect();
	if (MusicName == "StunEffect")
		PlayStunEffect();
	if (MusicName == "Warrior Attack")
		PlayWarriorAttack();
	if (MusicName == "Mage Attack")
		PlayMageAttack();
	if (MusicName == "Priest Attack")
		PlayPriestAttack();
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

void AudioPlayer::PlayBleedEffect()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Bleed.wav"))
	{
		return;
	}
	SoundEngine->play2D("Music/Bleed.wav");
}
void AudioPlayer::PlayDebuffEffect()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Debuff.wav"))
	{
		return;
	}
	SoundEngine->play2D("Music/Debuff.wav");
}
void AudioPlayer::PlayBuffEffect()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Buff.mp3"))
	{
		return;
	}
	SoundEngine->play2D("Music/Buff.mp3");
}
void AudioPlayer::PlayStunEffect()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Stun.mp3"))
	{
		return;
	}
	SoundEngine->play2D("Music/Stun.mp3");
}

void AudioPlayer::PlayWarriorAttack()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Sword_Attack.mp3"))
	{
		return;
	}
	SoundEngine->play2D("Music/Sword_Attack.mp3");
}

void AudioPlayer::PlayMageAttack()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Mage_Attack.wav"))
	{
		return;
	}
	SoundEngine->play2D("Music/Mage_Attack.wav");
}

void AudioPlayer::PlayPriestAttack()
{
	if (SoundEngine->isCurrentlyPlaying("Music/Priest_Attack.wav"))
	{
		return;
	}
	SoundEngine->play2D("Music/Priest_Attack.wav");
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