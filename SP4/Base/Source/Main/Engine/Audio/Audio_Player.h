#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <string>
#include <irrKlang.h>
#include "../Internal/SingletonTemplate.h"
using namespace irrklang;
using std::string;
class AudioPlayer : public SingletonTemplate<AudioPlayer>
{
	ISoundEngine* SoundEngine;

public:
	AudioPlayer();
	~AudioPlayer();
	void Init();

	void PlayMusic(string MusicName = "");
	void PlayBGM();
	void PlayBattleMusic();
	
	void SetVolume(float vol);
	void Exit();
};

#endif