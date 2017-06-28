#include "Music.h"

int BaseMixSound::MixNUM = 0;

BaseMixSound::BaseMixSound()
{
	if (MixNUM == 0)
	{
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			throw std::runtime_error("Mix_Open ERROR");
			exit(-1);
		}
	}
	MixNUM++;
}

BaseMixSound::~BaseMixSound()
{
	MixNUM--;
	if (MixNUM == 0) 
	{
		Mix_CloseAudio();
	}
}

EffectSound::EffectSound(const std::string & sound_fileName)
{
	sound = Mix_LoadWAV(sound_fileName.c_str());
	if (sound == 0) 
	{
		throw std::runtime_error(sound_fileName+":load failed!");
	}
}

EffectSound::~EffectSound()
{
	Mix_FreeChunk(sound);
}

void EffectSound::play() const
{
	if (Mix_PlayChannel(-1, sound, 0) == -1)
	{
		throw std::runtime_error("Mix_PlayChannel() ERROR");
	}
}

MusicSound::MusicSound(const std::string & music_fileName)
{
	music = Mix_LoadMUS(music_fileName.c_str());
	if (music == 0)
	{
		throw std::runtime_error(music_fileName + ":load failed!");
	}
}

MusicSound::~MusicSound()
{
	Mix_FreeMusic(music);
}

void MusicSound::play() const
{
	if (Mix_PlayingMusic() == false) 
	{
		if (Mix_PlayMusic(music, 1) == -1)
		{
			throw std::runtime_error("Mix_PlayMusic() ERROR");
		}
	}
	else 
	{
		if (Mix_PausedMusic() == true) 
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
}

void MusicSound::stop() const
{
	Mix_HaltMusic();
}

//=================================
Music::Music()
{

}


Music::~Music()
{
	
}