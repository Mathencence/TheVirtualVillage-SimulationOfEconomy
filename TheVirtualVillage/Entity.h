#pragma once
#include "Vector.h"

class Entity
{
public:
	// Declare a default constructor and a default destructor.
	Entity();
	~Entity();
	// Methods:
	// Move handles the positions of the sprite of the entity
	// And bouncing the mushroom against the window limits.
	// This fucntions returns void and receives no parameters.
	void update();
	// Draw the sprite onscreen
	//void draw();
private:
};