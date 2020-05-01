#include "CharacterKoopa.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer,imagePath,startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	isAlive = true;

	imagePath = "images/KoopaWalk.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture" << imagePath << endl;
		return;
	}


	mNumberOfFrames = 8;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfFrames; //2 sprites on 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mCollisionRadius = 16;

}

CharacterKoopa::~CharacterKoopa()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//to gain benefit of the code written in the base class Update() function we need to call it 
	if (!mInjured)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;
			mCurrentFrame++;
			
			if (mCurrentFrame > 7)
			{
				mCurrentFrame = 0;
			}
		}
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
			mPosition.X += KOOPA_SPEED;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
			mPosition.X -= KOOPA_SPEED;
		}
	}
	else
	{
		//we should not be moving when injured
		mCurrentFrame = 0;
		mMovingRight = false;
		mMovingLeft = false;

		//count down the injured time
		mInjuredTime -= deltaTime;
		
		if(mInjuredTime <= 0.0)
		{
			FlipRightWayUp();
		}
	}
	Character::Update(deltaTime, e);

	if(mPosition.X < 0)
	{
		mFacingDirection = FACING_LEFT;
		mPosition.X = 0;
	}
	else if (mPosition.X > SCREEN_WIDTH - mSingleSpriteWidth)
	{
		mFacingDirection = FACING_RIGHT;
		mPosition.X = SCREEN_WIDTH - mSingleSpriteWidth;
	}
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	if (mInjured)
	{
		int left = 0.0f;

	}

	//if injured move the left position to be the left position of the second image on the spritesheet
	
	int left = mSingleSpriteWidth * mCurrentFrame;
	

	//get the portion of the spritesheet you want to draw
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.X), (int)(mPosition.Y), mSingleSpriteWidth, mSingleSpriteHeight };

	//draw facing in the correct directon
		if (mFacingDirection == FACING_RIGHT)
		{
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
			
			if (mInjured == true)
			{
				mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_VERTICAL);
			}
		}
		else if (mFacingDirection == FACING_LEFT)
		{
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);

			if (mInjured == true)
			{
				mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_VERTICAL);
			}
		}
		

}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	isAlive = false;
	Jump();
}

void CharacterKoopa::Jump()
{
	
		mJumpForce = INITAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	
}

void CharacterKoopa::SetALive(bool mIsInjured)
{
	mInjured = mIsInjured;
}

void CharacterKoopa::FlipRightWayUp()
{
	mCurrentFrame = 0;
	isAlive = true;
	mInjured = false;
	mMovingLeft = true;
	mMovingRight = true;
}
