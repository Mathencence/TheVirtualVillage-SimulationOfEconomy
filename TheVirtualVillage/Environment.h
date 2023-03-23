#pragma once
#include "Window.h"

#include "Vector.h"
#include "Entity.h"
#include "Item.h"
#include <vector>
#include "Parameters.h"
enum location {
	PORTABLEWATER,
	FOREST,
	PLAIN,
	MOUNTAIN,
	COAST,
	LOCATION_LENGTH
};
enum state {

};
class Location;

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
	
	bool isInside(Vector pos);

	Window* getWindow() { return &window; }
	//Return the value of Environment state s
	float getState(state s);
	//Set the value of Environment state s
	void setState(state s, float value);
private:
	Window window;

	vector<float> envState;
	//The map is a square start from 0,0, to the point border.
	Vector border;
	//Pointers of objects
	std::vector<Entity*> vec_Entities;
	std::vector<Location*> vec_Location;
	std::vector<Item*> vec_Item;
	//Entity* ent_player;
	void updateAllEntities();

	//Return the entity's position vector with the corresponding index
	Vector getEntPosition(int index);
};
// Location is an area specified for usage, however the location may not contain any mechanic.
class Location {
public:
	// Declare a default constructor and a default destructor.
	Location(Environment* p, vector<Item*> &vec_Item, location type, Vector pos = Vector(-1, -1), float radius = -1);
	~Location();
	// Declare a function for updating the env state. Returns void and receives no parameters.
	void update();
	// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
	//void render();
	//Return the value of Environment state s
	float getState(state s);
	//Set the value of Environment state s
	void setState(state s, float value);
private:
	Environment* p_Env;

	vector<float> locState;
	Vector position;
	float radius;
	float area;
	location type;

	friend class Environment;
};