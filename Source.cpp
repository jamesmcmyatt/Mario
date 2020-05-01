
#include "Source.h"
#include "GameScreenManager.h"

GameScreenManager* gameScreenManager;
Uint32 gOldTime;



int main(int argc, char* args[])
{
	


	if (InitSDL())
	{

	}

	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
	gOldTime = SDL_GetTicks();




	//check if the game is quit
		bool quit = false;
		
		//game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
		
		//closes window
		CloseSDL();
	
	
	return 0;
	
}

bool InitSDL()
{
	//set up screen manager - start level 1
	


	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error:" << Mix_GetError();
			return false;
		}
		
		//Create window
		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cout << "Window was not created! SDL_Error: " << SDL_GetError() << endl;
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			//gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image Could Not Be Initialised. Error: " << IMG_GetError() << endl;
				return false;
			}
			

		}
		else
		{
			cout << "Renderer Could Not Be Initialised. Error: " << IMG_GetError() << endl;
			return false;
		}

		return true;
	}

	
}

void CloseSDL()
{
	

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;


	IMG_Quit();
	SDL_Quit();


	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;


	// destroy game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();

	SDL_Event e;

	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		}
	}
	
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

		// set current time to be old time
	gOldTime = newTime;
	return false;
}

void Render()
{
	//clears the screen to black 
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	
	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}