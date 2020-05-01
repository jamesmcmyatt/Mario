#pragma once

#include "Character.h"

class CharacterMario : public Character
{
public:

	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e)override;
	void Render() override;

	void MarioDeath();

private:

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mCurrentFrame;
	float mFrameDelay;

	bool mMarioDead = false;


};