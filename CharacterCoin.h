#pragma once
#include "Collisions.h"
#include "Texture2D.h"

class Texture2D;
class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float movementSpeed);
	~CharacterCoin();


	Rect2D GetCollisionBox();
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;

	int mCurrentFrame;
	float mFrameDelay;
};
