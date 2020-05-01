#include "PowBlock.h"

string input;
int Mode;
PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap)
{
	string imagePath = "images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load Texture" << imagePath << endl;
		return;
	}
	mLevelMap = levelMap;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; // 3 sprites on the sheet
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

	std::cout << "Do you want to have infinate Pow?" << endl << "enter: Y or N" << endl;
	std::cin >> input;
	if (input == "Y")
	{
		std::cout << "INFINATE POWER!!!!!" << endl;
		Mode = 1;
	}
	else if (input == "N")
	{
		std::cout << "how long will you survive" << endl;
		Mode = 2;
	}
	
	
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//get the portion of the sprite sheet
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

									  //{Xpos,Ypos, Width of sprite , height of sprite}
		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determine where you want to draw it
		SDL_Rect destRect = { (int)(mPosition.X), (int)(mPosition.Y), mSingleSpriteWidth, mSingleSpriteHeight };

		//draw
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mPosition.X = 1000;
	}
}

Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.X, mPosition.Y, mSingleSpriteWidth, mTexture->GetHeight());
}

void PowBlock::TakeAHit()
{
	
	mNumberOfHitsLeft -= 1;
	if (mNumberOfHitsLeft <= 0)
	{
		
		if (Mode == 1)
		{
			mNumberOfHitsLeft = 3;
		}
		else if (Mode == 2)
		{
			mNumberOfHitsLeft = 0;
		}
		
			mLevelMap->ChangeTileAt(8, 7, 0);
			mLevelMap->ChangeTileAt(8, 8, 0);
	}
	
}
