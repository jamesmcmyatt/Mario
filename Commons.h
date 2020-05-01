#pragma once



struct Vector2D
{
	float X;
	float Y;

	Vector2D(float initalX = 0.0f, float initalY = 0.0f)
	{
		X = initalX;
		Y = initalY;
	}
};
struct Rect2D
{
	float X;
	float Y;
	float Width;
	float Height;

	Rect2D(float initalX = 0.0f, float initalY = 0.0f, float initalWidth = 0.0f, float initalHeight = 0.0f)
	{
		X = initalX;
		Y = initalY;
		Width = initalWidth;
		Height = initalHeight;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};
enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};



