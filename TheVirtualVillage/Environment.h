#pragma once
#include "Vector.h"
#include "Entity.h"
#include <vector>

//The environment would be a village that contains villagers (agents) to interact
//The environment is a map hold certain special areas and every agent need to have a valid position to project the entity on the map
class Environment
{
public:
	// Declare a default constructor and a default destructor.
	Environment();
	~Environment();
	// Declare a function for updating the env state. Returns void and receives no parameters.
	void update();
	// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
	//void render();
private:
	//ent_ type stands for pointer of entity
	std::vector<Entity*> vec_p_Entities;
	//Entity* ent_player;
	void updateAllEntities();

	//Return the entity's position vector with the corresponding index
	Vector getEntPosition(int index);
};