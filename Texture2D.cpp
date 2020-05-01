#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace::std;



Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	
	int mWidth = 0;
	int mHeight = 0;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	//SDL_Texture* mTexture = NULL;
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL)
	{
		//set dimentions
		mWidth = pSurface->w;
		mHeight = pSurface->h;


		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
		}

		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
	}

	
	return mTexture != NULL;
}



void Texture2D::Free()
{

	mWidth = 0;
	mHeight = 0;

}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{

	// Set where to render the texture
	SDL_Rect renderLoaction = {newPosition.X,newPosition.Y, mWidth, mHeight };

	//Render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLoaction, 0, NULL, flip);

}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}



