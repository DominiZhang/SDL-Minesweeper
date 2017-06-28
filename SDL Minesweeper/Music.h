#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_mixer.lib")

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <stdexcept>

//*******************************
//class BaseMixSound
class BaseMixSound
{
private:
	static int MixNUM;
protected:
	BaseMixSound();
public:
	virtual ~BaseMixSound();
};
//*******************************



//*******************************
//class EffectSound
class EffectSound : public BaseMixSound
{
private:
	Mix_Chunk* sound;
public:
	EffectSound(const std::string& sound_fileName);
	~EffectSound();
	void play() const;
};

//*******************************



//*******************************
//class MusicSound
class MusicSound : public BaseMixSound
{
private:
	Mix_Music* music;
public:
	MusicSound(const std::string& music_fileName);
	~MusicSound();
	void play() const;
	void stop() const;
};
//*******************************


//*******************************
//class Music
class Music
{
public:
	Music();
	~Music();

	EffectSound *ding;
};

