#include "CharacterLuigi.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;

	imagePath = "images/LuigiWalk.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}

	mNumberOfFrames = 8;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();

}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	if (mMovingLeft == true || mMovingRight == true)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;

			mCurrentFrame++;

			if (mCurrentFrame > 5)
			{
				mCurrentFrame = 0;
			}
		}
	}

	//if the player jumps change animation
	if (mJumping == true && mTouchingFloor == true)
	{
		mCurrentFrame = 6;
	}
	else if (mCurrentFrame > 5 && mTouchingFloor == true)
	{
		mCurrentFrame = 0;
	}
	
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
		case SDLK_d:
			mMovingRight = false;
			mXVelocity = 0;
			mCurrentFrame = 0;
			break;
		case SDLK_a:
			mMovingLeft = false;
			mXVelocity = 0;
			mCurrentFrame = 0;
			break;
		}
		default:
			break;
	
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_s:
			break;

		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
			break;

		case SDLK_d:
			
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
			break;
		default:
			break;
		}
	}

	if (mLuigiDead == false)
	{
		Character::Update(deltaTime, e);
	}
	else
	{
		mPosition.Y += deltaTime * GRAVITY * 3;
		mCurrentFrame = 7;
	}


	//checks if player is moving then add velocity
	if (mMovingLeft)
	{
		mXVelocity -= 0.1f;
	}
	else if (mMovingRight)
	{
		mXVelocity += 0.1f;
	}
}

void CharacterLuigi::Render()
{
	int left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect SpriteSheet = { left , 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.X), (int)(mPosition.Y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(SpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(SpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

void CharacterLuigi::luigiDeath()
{
	if (!mJumping)
	{
		mMusicSystem->PauseMusic();
		Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/MarioDeath.wav");
		mMusicSystem->PlaySoundEffect(mSound);
		mJumpForce = INITAL_JUMP_FORCE;
		mJumping = true;
		mLuigiDead = true;
	}
}
