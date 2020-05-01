#ifndef _CHARACTER_H
#define _CHARACTER_H

#pragma once
#include <iostream>
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "SoundManager.h"

using namespace std;



class Texture2D;

class Character
{

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	SoundManager* mMusicSystem;

	
	void AddGravity(float deltaTime);
	void Jump();
	void CheckCollisions(float newXPos, float newYPos, float deltaTime);

	
	
	FACING mFacingDirection;

	bool mTouchingFloor;


	float mXVelocity;

	bool mMovingLeft;
	bool mMovingRight;
	bool mCanJump;
	float mJumpForce;
	int currentYPos;

	float mCollisionRadius;
	int mNumberOfFrames = 6;

	int mSingleSpriteWidth;
	int mSingleSpriteHeight;

	

public:
	
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition,LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	

	void SetPosition(Vector2D newPosition);
	
	Vector2D GetPosition();

	
	float GetCollisionRadius();

	void CancelJump();

	Rect2D GetCollisionBox();
	bool mJumping;

	Mix_Chunk* mSound;

private:
	LevelMap* mCurrentLevelMap;

	
};
#endif // _CHARACTER_H