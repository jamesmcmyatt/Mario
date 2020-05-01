#ifndef _GAMESCREENMANAGER
#define _GAMESCREENMANAGER

#pragma once
#include "Commons.h"
#include "SDL.h"
#include "GameScreenLevel1.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
	GameScreenLevel1* tempScreen;
};
#endif //_GAMESCREENMANAGER