#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__
#include <iostream>
#include <string>
#include <map> 
#include <SDL_mixer.h>

enum SoundType
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public: // Public methods.
	static void Init();
	static void AllocateChannels(const int channels);
	static bool Load(const std::string& file_name, const std::string& id, const SoundType type);
	static void Unload(const std::string& id, const SoundType type);
	static void PlayMusic(const std::string& id, const int loop = -1, const int fade_in = 0);
	static void StopMusic(const int fade_out = 0);
	static void PauseMusic(); 
	static void ResumeMusic();
	static void PlaySound(const std::string& id, const int loop = 0, const int channel = -1);
	static void StopSound(int channel = -1);
	static void SetMusicVolume(const int vol);
	static void SetSoundVolume(const int vol, const int channel = -1);
	static void SetAllVolume(const int vol);
	
	// Panning converts a single slider value from 0 to 100 to the stereo speaker volumes.
	static void PanLeft(const unsigned increment = 5U, const int channel = MIX_CHANNEL_POST);
	static void PanRight(const unsigned increment = 5U, const int channel = MIX_CHANNEL_POST);
	static void PanReset(const int channel = MIX_CHANNEL_POST);
	static void PanSet(const int amount, const int channel = MIX_CHANNEL_POST);
	static void Quit();
	
private: // Private members.
	static std::map<std::string, Mix_Chunk*> s_sfxs;
	static std::map<std::string, Mix_Music*> s_music;
	static int s_pan; // A slider value from 0 to 100. 0 = full left, 100 = full right.
	SoundManager() = default;
};

typedef SoundManager SOMA;

#endif 