#pragma once
#include "Window.h"
#include "Vector.h"
#include "Entity.h"
#include "Item.h"
#include <vector>
#include "Parameters.h"
#include "Market.h"

enum location {
	PORTABLEWATER,
	FOREST,
	RAINFOREST,
	PLAIN,
	MOUNTAIN,
	COAST,
	LOCATION_LENGTH
};
enum state {
	TURN,
	POPULATION,
	POVERTYRATE,
	DATATYPE_LENGTH
};
class Entity;
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

	//Game Mechanic
	int searchItem(Vector pos, item_type itype);
	void removeItem(int index);

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
	//Turn pass
	int turn;
	Market market;
	int governmentCashStorage;
	//Pointers of objects
	std::vector<Entity*> vec_Entities;
	std::vector<Location*> vec_Location;
	std::vector<Item*> vec_Item;
	
	void updateAllEntities();
	void updateAllLocations();
	//Utility
	void sortEntityByCash();

	//Graphics
	void drawState(int interval);
	
	void updateState();


	//Return the entity's position vector with the corresponding index
	Vector getEntPosition(int index);

	friend class Simulation;
	friend class Entity;
	friend Location;
};
// Location is an area specified for usage, however the location may not contain any mechanic.
class Location {
public:
	// Declare a default constructor and a default destructor.
	Location(Environment* p, location type, Vector pos = Vector(-1, -1), float radius = -1);
	~Location();
	//Generate n item to the location
	void generateItem(int n);

	// Declare a function for updating the env state. Returns void and receives no parameters.
	void update();
	// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
	//void render();
	//Return the value of Environment state s
	float getState(state s);
	//Set the value of Environment state s
	void setState(state s, float value);

	//Notify the location if a item is deleted because of gathered or expired or whatever reason
	void removeItem() { itemCount--; }
private:
	Environment* p_Env;

	vector<float> locState;
	Vector position;
	float radius;
	location type;

	int targetItemCount;
	int itemCount;
	friend class Environment;
};