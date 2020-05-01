#pragma once
#pragma once
#include "Character.h"
#include "Texture2D.h"
class Texture2D;
class CharacterKoopa : public Character
{
public:

	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Update(float deltaTime, SDL_Event e)override;
	void Render() override;

	void TakeDamage();
	void Jump();

	void SetALive(bool mIsInjured);
	bool GetAlive() { return isAlive; };

private:
	float mSingleSpriteWidth;
	float  mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	int mCurrentFrame;
	float mFrameDelay;

	bool isAlive;
	void FlipRightWayUp();
};