
#include "GameScreenLevel1.h"
#include "GameScreenManager.h" 


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);

}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//clear up the old screens
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	GameScreenLevel1* tempScreen;

	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	/*case SCREEN_LEVEL2:
		tempScreen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_MENU:
		tempScreen = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_GAMEOVER:
		tempScreen = new GameScreenGameOver(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_HIGHSCORES:
		tempScreen = new GameScreenHighScores(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
		*/
		



	}

}

