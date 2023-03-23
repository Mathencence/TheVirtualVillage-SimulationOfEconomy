#include "Environment.h"

Environment::Environment():border(MAPSIZE,MAPSIZE) {
	window.setSize(sf::Vector2u(WIN_WIDTH, WIN_HEIGHT));
	window.setTitle("Virtual-Village");
	window.redraw();
	//Generate some location
	for (int i = 0; i < LOCATION_LENGTH; i++)
	{
		for (int j = 0; j < INITIAL_LOCATION[i]; j++) {
			vec_Location.push_back(new Location(this,this->vec_Item,(location)i));
		}
	}
	/*
	for (int i = 0; i < vec_Location.size(); i++) {
		printf("Pos: %f, %f, radius: %f\n", vec_Location.at(i)->position.getX(), vec_Location.at(i)->position.getY(), vec_Location.at(i)->radius);
	}
	*/
	//Spawn villagers
	for (int i = 0; i < INITIAL_POPULATION; i++)
	{
		vec_Entities.push_back(new Entity(this));
	}
}
Environment::~Environment() {

}
bool Environment::isInside(Vector pos) {
	if (pos.getX() < 0 || pos.getY() < 0 || pos.getX() > border.getX() || pos.getY() > border.getY())
		return false;
	return true;
}

float Environment::getState(state s) {
	return envState.at(s);
}
//Set the value of Environment state s
void Environment::setState(state s, float value) {
	envState.at(s) = value;
}

// Declare a function for updating the env state. Returns void and receives no parameters.
void Environment::update() {
	updateAllEntities();
}
// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
//void render();

void Environment::updateAllEntities() {
	for(int i =0;i< vec_Entities.size();i++)
	{
		vec_Entities.at(i)->update();
	}
}
//Return the entity's position vector with the corresponding index
Vector Environment::getEntPosition(int index) {
	return vec_Entities.at(index)->getPosition();
}
//=================================================================================================================
//
//												Location Class
//
//=================================================================================================================

Location::Location(Environment* p, vector<Item*>& vec_Item, location type, Vector pos, float rad):p_Env(nullptr) {
	if (p)
		this->p_Env = p;
	if (pos.getX() != -1) {
		this->position = pos;
	}
	else {
		this->position.setX(Utility::random(0, MAPSIZE));
		this->position.setY(Utility::random(0, MAPSIZE));
	}
	if (rad > 0) {
		this->radius = rad;
	}
	else {
		this->radius = Utility::random(MIN_LOCATION_RADIUS, MAX_LOCATION_RADIUS);
	}
	this->area = radius * radius * PI;
	this->type = type;

	//Initialize items
	for (int i = 0; i < round(area * INITIAL_RICHNESS); i++)
	{
		Vector pos = Utility::randomPointInCircle(this->position, this->radius);
		//Check if inside
		while (!p_Env->isInside(pos)){
			pos = Utility::randomPointInCircle(this->position, this->radius);
		}
		switch (this->type)
		{
		case PORTABLEWATER:
			vec_Item.push_back(new Item(WATER,pos));
			break;
		case FOREST:
			vec_Item.push_back(new Item(APPLE, pos));
			break;
		case PLAIN:
			vec_Item.push_back(new Item(MEAT, pos));
			break;
		case MOUNTAIN:
			vec_Item.push_back(new Item(ROCK, pos));
			break;
		case COAST:
			vec_Item.push_back(new Item(FISH, pos));
			break;
		default:
			break;
		}
	}
}

Location::~Location() {

}

float Location::getState(state s) {
	return locState.at(s);
}
//Set the value of Environment state s
void Location::setState(state s, float value) {
	locState.at(s) = value;
}

// Declare a function for updating the env state. Returns void and receives no parameters.
void Location::update() {
	
}