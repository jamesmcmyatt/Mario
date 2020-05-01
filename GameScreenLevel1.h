#pragma once

#ifndef _GAMESCREENLEVEL1
#define _GAMESCREENLEVEL1

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include <vector>
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "SoundManager.h"
#include "ScoreSystem.h"




class Texture2D;
class PowBlock;


class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void CreateKooperRepeat();
	void UpdatePowBlock();
	void ScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);

private:
	SDL_Renderer* mRenderer;
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	Character* myCharacter;
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	CharacterKoopa* mCharacterKoopa;
	CharacterCoin* mCharacterCoin;
	ScoreSystem* mScoreSystem;
	SoundManager* mMusicSystem;



	void setLevelMap();
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;
	std::vector<CharacterKoopa*> mEnemies;
	int enemyIndexToDelete;
	std::vector<CharacterCoin*> mCoins;
	int coinIndexToDelete;


	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	float mEnemyRespawnTime;
	int j = 2;
	
};
#endif // _GAMESCREENLEVEL1