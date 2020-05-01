#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <iostream>
using namespace std;


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{	

	coinIndexToDelete = -1;
	enemyIndexToDelete = -1;
	mRenderer = renderer;
	mLevelMap = NULL;
	
	SetUpLevel();
	mMusicSystem = new SoundManager();
	mMusicSystem->LoadMusic("Audio/Mario.mp3");
	mMusicSystem->PlayMusic();
}

	GameScreenLevel1::~GameScreenLevel1()
	{
		delete mBackgroundTexture;
		mBackgroundTexture = NULL;
		delete Mario;
		Mario = NULL;
		delete Luigi;
		Luigi = NULL;

		delete mScoreSystem;
		mScoreSystem = NULL;

		delete mPowBlock;
		mPowBlock = NULL;
		mLevelMap = NULL;

		mEnemies.clear();
		mCoins.clear();

	}

	void GameScreenLevel1::Render()
	{
		//draws background
		mBackgroundTexture->Render(Vector2D(0.0, mBackgroundYPos), SDL_FLIP_NONE);
		mPowBlock->Render();

		//draws character
		Mario->Render();
		Luigi->Render();
		
		
		
		//draws enemies
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Render();
		}

		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Render();
		}
	}

	void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
	{
		
		Mario->Update(deltaTime, e);
		Luigi->Update(deltaTime, e);
		UpdatePowBlock();
		UpdateEnemies(deltaTime, e);
		UpdateCoins(deltaTime, e);
		//if (Collisions::Instance()->Circle(Mario, Luigi));
		//if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()));

		//do screen shake
		if (mScreenShake)
		{
			mScreenShakeTime -= deltaTime;
			mWobble++;
			mBackgroundYPos = sin(mWobble);
			mBackgroundYPos *= 3.0f;
			
			//end the shake
			if (mScreenShakeTime <= 0.0f)
			{
				mScreenShake = false;
				mBackgroundYPos = 0.0f;
			}
		}
		
		if (mEnemyRespawnTime < 0.0f)
		{
			cout << "respawn"<< endl;
			mEnemyRespawnTime = KOOPA_RESPAWN_RATE;
			CreateKoopa(Vector2D(325, 320), FACING_LEFT, KOOPA_SPEED);
		}
	}

	void GameScreenLevel1::UpdatePowBlock()
	{
		if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Mario->GetCollisionBox()))
		{
			if (Mario->mJumping == true)
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				Mario->CancelJump();
				mScoreSystem->Score += 100;
				cout << "Score: " << mScoreSystem->Score << endl;
				Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/PowBlock.wav");
				
				mMusicSystem->PlaySoundEffect(mSound);
				
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}
			}
		}
		else if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), Luigi->GetCollisionBox()))
		{
			if (Luigi->mJumping == true)
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				Luigi->CancelJump();
				mScoreSystem->Score += 100;
				cout << "Score: " << mScoreSystem->Score <<endl;
				Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/PowBlock.wav");
				mMusicSystem->PlaySoundEffect(mSound);

				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}
			}
		}
	}
	

	

	void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
	{
		if (!mEnemies.empty())
		{
			//if the enemy is no longer alive then delete
			if (enemyIndexToDelete != -1)
			{
				mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
				enemyIndexToDelete = -1;
			}

			for (unsigned int i = 0; i < mEnemies.size(); i++)
			{
				//check if enemy of on the bottom row of the level map
				if (mEnemies[i]->GetPosition().Y > 300.0f)
				{
					//check if enemy is offscreen
					if (mEnemies[i]->GetPosition().X < 50 )
					{
						mEnemies[i]->SetPosition(Vector2D(420, 32));
					}
					else if (mEnemies[i]->GetPosition().X > ( SCREEN_WIDTH - 50))
					{
						mEnemies[i]->SetPosition(Vector2D(32, 32));
					}
				}

				//update enemies
				mEnemies[i]->Update(deltaTime, e);

				//check if enemies collides with player
				if (Collisions::Instance()->Circle(mEnemies[i], Mario))
				{
					//Mario.SetState(CHARACTER_PLAYER_DEATH);
					if (mEnemies[i]->GetAlive() == true)
					{
						//player dies
						Mario->MarioDeath();
					}
					else
					{
						//koopa dies
						Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Kick.wav");
						mMusicSystem->PlaySoundEffect(mSound);
						enemyIndexToDelete = i;
					}
				}
				else if (Collisions::Instance()->Circle(mEnemies[i], Luigi))
				{
					//Mario.SetState(CHARACTER_PLAYER_DEATH);
					if (mEnemies[i]->GetAlive() == true)
					{
						//player dies
						Luigi->luigiDeath();
					}
					else
					{
						//koopa dies
						Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Kick.wav");
						mMusicSystem->PlaySoundEffect(mSound);
						enemyIndexToDelete = i;
					}
					
				}
				
			}
			
			
		}
		else
		{
			
			for (int i = 0; i < j; i++)
			{
				CreateKoopa(Vector2D(rand() % 500, 32), FACING_RIGHT, KOOPA_SPEED);
			}
			j++;
		}
	}

	void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
	{
		if (!mCoins.empty())
		{
			//kill coins
			if (coinIndexToDelete != -1)
			{
				mCoins.erase(mCoins.begin() + coinIndexToDelete);
				coinIndexToDelete = -1;
			}
			for (unsigned int i = 0; i < mCoins.size(); i++)
			{
				if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), Mario->GetCollisionBox()))
				{
					mScoreSystem->Score += 100;
					coinIndexToDelete = i;
					Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Coin.wav");
					mMusicSystem->PlaySoundEffect(mSound);
					cout << "Score: "<< mScoreSystem->Score << endl;
				}
				else if (Collisions::Instance()->Box(mCoins[i]->GetCollisionBox(), Luigi->GetCollisionBox()))
				{
					mScoreSystem->Score += 100;
					coinIndexToDelete = i;
					Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Coin.wav");
					mMusicSystem->PlaySoundEffect(mSound);
					cout << "Score: " << mScoreSystem->Score << endl;
				}

				mCoins[i]->Update(deltaTime, e);
			}
		}
	}

	void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
	{
		mCharacterKoopa = new CharacterKoopa(mRenderer, "images/Koopa.png", position, mLevelMap, direction, speed);
		mEnemies.push_back(mCharacterKoopa);
	}

	void GameScreenLevel1::CreateCoin(Vector2D position)
	{
		mCharacterCoin = new CharacterCoin(mRenderer, "images/Coin.png", position, mLevelMap, 0);
		mCoins.push_back(mCharacterCoin);
	}

	void GameScreenLevel1::ScreenShake()
	{
		mScreenShake = true;
		mScreenShakeTime = SCREENSHAKE_DURATION;
		mWobble = 0.0f;

		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->TakeDamage();
		}
	}
	

	bool GameScreenLevel1::SetUpLevel()
	{
		mScreenShake = false;
		mBackgroundYPos = 0.0f;

		setLevelMap();
		//set players up
		Mario = new CharacterMario(mRenderer, "images/Mario.png", Vector2D(64, 330), mLevelMap);
		Luigi = new CharacterLuigi(mRenderer, "images/Luigi.png", Vector2D(128, 330), mLevelMap);

		mScoreSystem = new ScoreSystem();
		//set up pow block
		mPowBlock = new PowBlock(mRenderer, mLevelMap);


	


		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

		CreateCoin(Vector2D(160, 128));
		CreateCoin(Vector2D(192, 128));
		CreateCoin(Vector2D(224, 128));
		CreateCoin(Vector2D(256, 128));
		CreateCoin(Vector2D(288, 128));
		CreateCoin(Vector2D(320, 128));
		


		mBackgroundTexture = new Texture2D(mRenderer);
		if (!mBackgroundTexture->LoadFromFile("images/BackgroundMB.png"))
		{
			cout << "Failed to load Background Texture!";
			return false;
		}
		//set up the player character
		
		return false;
	}

	void GameScreenLevel1::setLevelMap()
	{
		int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,0,2,2,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

		//clear up any old map
		if (mLevelMap != NULL)
		{
			delete mLevelMap;
		}
		//set the new one up

		mLevelMap = new LevelMap(map);
	}
