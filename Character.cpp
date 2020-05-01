#include "Character.h"
#include "Texture2D.h"
#include <iostream>
using namespace std;



Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	//Collisions
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
	mFacingDirection = FACING_RIGHT;

	//facing driection
	mRenderer = renderer;
	mPosition = startPosition;
	

	//set position to start position
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	mMusicSystem = new SoundManager();
}

Character::~Character()
{
	mRenderer = NULL;
}



void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
}


void Character::Update(float deltaTime, SDL_Event e)
{

	float newXPos = GetPosition().X;
	float newYPos = GetPosition().Y;
	
	//deal with jumping first
	if (mJumping)
	{
		mCanJump = false;
		//Adjust the position
		newYPos -= mJumpForce * deltaTime;

		//reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//has the jump force reduced to zero?
		if (mJumpForce <= 0.0f) 
		{
			mJumping = false;
		}
	}

	if (mXVelocity != 0.0f)
	{
		newXPos += mXVelocity * deltaTime;
	}

	//limit character speed
	if (mXVelocity > PLAYER_VELOCITY)
	{
		mXVelocity = PLAYER_VELOCITY;
	}
	else if (mXVelocity < -PLAYER_VELOCITY)
	{
		mXVelocity = -PLAYER_VELOCITY;
	}
	
	CheckCollisions(newXPos, newYPos, deltaTime);
}

void::Character::CheckCollisions(float newXPos, float newYPos, float deltaTime)
{
	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + (mTexture->GetWidth() / mNumberOfFrames)) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + mTexture->GetHeight()) / TILE_HEIGHT;

	//Left Collision
	if (mCurrentLevelMap->GeTileAt(bottomTile - 1, leftTile) == 1)
	{
		newXPos = GetPosition().X;
	}

	//Right Collision
	if (mCurrentLevelMap->GeTileAt(bottomTile - 1, rightTile) == 1)
	{
		newXPos = GetPosition().X;
	}

	//Bottom Collision
	if ((mCurrentLevelMap->GeTileAt(bottomTile, rightTile) == 1 || mCurrentLevelMap->GeTileAt(bottomTile, leftTile) == 1))
	{
		mCanJump = true;
		mTouchingFloor = true;
	}
	//update y position with gravity
	else
	{
		newYPos += GRAVITY * deltaTime;
	}

	//Top Collision
	if (mCurrentLevelMap->GeTileAt(topTile, rightTile) == 1)
	{
		mJumpForce = 0.0f;
	}
	if (mCurrentLevelMap->GeTileAt(topTile, leftTile) == 1)
	{
		mJumpForce = 0.0f;
	}

	//restricts X Position
	if (newXPos < 0.0f || newXPos + (mTexture->GetWidth() / mNumberOfFrames)> SCREEN_WIDTH)
	{
		newXPos = GetPosition().X;
	}

	//restricts Y Position
	if (newYPos < 0.0f || newYPos + mTexture->GetHeight() > SCREEN_WIDTH)
	{
		newYPos = GetPosition().Y + 1;
		mJumpForce = 0.0f;
	}

	SetPosition(Vector2D(newXPos, newYPos));
}

//sets the position of mario
void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

//gets the position of mario
Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::AddGravity(float deltaTime)
{

	mPosition.Y += GRAVITY * deltaTime;

}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.X, mPosition.Y, (mTexture->GetWidth()/ mNumberOfFrames), mTexture->GetHeight());
}

void Character::Jump()
{
	mCanJump = false;
	if (!mJumping)
	{
		Mix_Chunk* mSound = mMusicSystem->LoadSoundEffect("Audio/Jump.wav");
		mMusicSystem->PlaySoundEffect(mSound);
		mJumpForce = INITAL_JUMP_FORCE;
		mJumping = true;
	}

}

//collision radius
float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

void Character::CancelJump()
{
	mJumpForce = 0;
}



