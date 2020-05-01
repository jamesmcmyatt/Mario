#pragma once
#include "Character.h"
#include "Texture2D.h"

class CharacterLuigi : public Character
{
public:

	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e)override;
	void Render() override;
	void luigiDeath();

private:
	float mSingleSpriteWidth;
	float  mSingleSpriteHeight;
	
	bool mLuigiDead = false;
	int mCurrentFrame;
	float mFrameDelay;
};