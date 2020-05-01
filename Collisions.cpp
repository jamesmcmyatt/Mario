#include "Character.h"
#include "Collisions.h"

//initalise the instance to null

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().X - character2->GetPosition().X),
							(character1->GetPosition().Y - character2->GetPosition().Y));

	double distance = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));
	double character1Radius = character1->GetCollisionRadius();
	double character2Radius = character2->GetCollisionRadius();
	double combinedDistance = character1Radius + character2Radius;


	return distance < combinedDistance;
	return false;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.X + (rect1.Width / 2) > rect2.X&&
		rect1.X + (rect1.Width / 2) < rect2.X + rect2.Width &&
		rect1.Y + (rect1.Height / 2) > rect2.Y&&
		rect1.Y + (rect1.Height / 2) < rect2.Y + rect2.Height)
	{
		return true;
	}

	return false;
}
