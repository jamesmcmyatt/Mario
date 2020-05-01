#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition,map)
{
	mPosition = startPosition;

	imagePath = "images/MarioWalk.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}

	mNumberOfFrames = 8;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
	mCollisionRadius = 16;
	
	
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
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

	//Controls
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Jump();

		case SDLK_LEFT:
			mMovingLeft = false;
			mXVelocity = 0;
			mCurrentFrame = 0;

		case SDLK_RIGHT:
			mMovingRight = false;
			mXVelocity = 0;
			mCurrentFrame = 0;

		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
	
		case SDLK_DOWN:
			break;

		case SDLK_LEFT:
			mMovingRight = false;
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
			break;

		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
			break;

		default:
			break;
		}
		break;
	}
	

	if (mMarioDead == false)
	{
		Character::Update(deltaTime, e);
	}
	else
	{
		mPosition.Y += deltaTime * GRAVITY * 3;
		mCurrentFrame = 7;
	}

	//check if player is moving
	if (mMovingLeft)
	{
		mXVelocity -= 0.1f;
	}
	else if (mMovingRight)
	{
		mXVelocity += 0.1f;
	}

	
}

void CharacterMario::Render()
{
	int left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect SpriteSheet = { left , 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.X), (int)(mPosition.Y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(SpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		mTexture->Render(SpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

void CharacterMario::MarioDeath()
{
	if (!mJumping)
	{
		mMusicSystem->PauseMusic();
		Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/MarioDeath.wav");
		mMusicSystem->PlaySoundEffect(mSound);
		mJumpForce = INITAL_JUMP_FORCE;
		mJumping = true;
		mMarioDead = true;
	}
}
