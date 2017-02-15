#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <irrKlang.h>
#include "../Internal/SingletonTemplate.h"
using namespace irrklang;

class AudioPlayer : public SingletonTemplate<AudioPlayer>
{
	ISoundEngine* SoundEngine;
public:
	AudioPlayer();
	~AudioPlayer();
	void Init();
	void PlayBGM();
	void Exit();
};

#endif