#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "./Constants.h"
#include <SDL_render.h>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;
#ifndef _Source_H
#define _Source_H
//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture2D* gTexture = NULL;


//Functions Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void LoadMusic(string path);
void Render();

void FreeTexture(); 
int flip = 10;
#endif _Source_H