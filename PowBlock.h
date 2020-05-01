#pragma once
#ifndef _POWBLOCK
#define _POWBLOCK

#include "SDL.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;
class LevelMap;

class PowBlock
{

public:

	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap);
	~PowBlock();

	virtual void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool isAvaliable();

private:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;


};
#endif // _POWBLOCK