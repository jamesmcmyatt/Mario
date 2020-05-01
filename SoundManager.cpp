#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	//cleans memory
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

void SoundManager::LoadMusic(std::string filePath)
{
	mMusic = Mix_LoadMUS(filePath.c_str());
	if (!mMusic)
	{
		printf("Failed to load music! SDL_Mixer Error: %s\n", Mix_GetError());
	}
}

void SoundManager::PlayMusic(int numOfLoops)
{
	Mix_PlayMusic(mMusic, numOfLoops);
}


void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}


void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}


void SoundManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

Mix_Chunk* SoundManager::LoadSoundEffect(std::string FilePath)
{
	mSound = Mix_LoadWAV(FilePath.c_str());
	if (!mSound)
	{
		printf("Could'nt load music %s", FilePath.c_str(), Mix_GetError());
	}
	return mSound;
}

void SoundManager::PlaySoundEffect(Mix_Chunk* sound)
{	
	Mix_PlayChannel(-1, sound, 0);
}