#include "../include/Environment.h"


Environment::Environment():border(MAPSIZE,MAPSIZE) {
	//Initialize window
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
	drawState();
}
Environment::~Environment() {

}
bool Environment::isInside(Vector pos) {
	if (pos.getX() < 0 || pos.getY() < 0 || pos.getX() > border.getX() || pos.getY() > border.getY())
		return false;
	return true;
}

int Environment::searchItem(Vector pos, item_type itype) {
	//returning the index of the item in vec_Items
	//If there is no return -1
	for (int i = 0; i < vec_Item.size(); i++) {
		if (vec_Item.at(i)->position.EuclideanDistance(pos) <= SIGHT_RADIUS&&vec_Item.at(i)->type==itype)
			return i;
	}
	return -1;
}
void Environment::removeItem(int index) {
	if (index < 0)
		return;
	vec_Item.erase(vec_Item.begin() + index);
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
	drawState();
}
// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
//void render();

void Environment::updateAllEntities() {
	for(int i =0;i< vec_Entities.size();i++)
	{
		vec_Entities.at(i)->update();
	}
}
void Environment::drawState() {
	window.beginDraw();
	//Draw Location
	sf::CircleShape circle;
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(sf::Color::Red);
	circle.setFillColor(sf::Color::Transparent);
	for (int i = 0; i < vec_Location.size(); i++) {
		float x = vec_Location.at(i)->position.getX(),y = vec_Location.at(i)->position.getY();
		float r = vec_Location.at(i)->radius;
		circle.setRadius(r);
		circle.setPosition(x-r,y-r);
		window.draw(circle);
	}
	//Draw entities
	sf::RectangleShape rect(sf::Vector2f(4.f, 4.f));
	rect.setFillColor(sf::Color::White);
	for (int i = 0; i < vec_Entities.size(); i++)
	{
		float x = vec_Entities.at(i)->getPosition().getX();
		float y = vec_Entities.at(i)->getPosition().getY();
		rect.setPosition(x - 2.f, y - 2.f);
		window.draw(rect);
	}
	
	//Draw items
	
	circle.setOutlineColor(sf::Color::Green);
	circle.setRadius(1.0f);
	for (int i = 0; i < vec_Item.size(); i++)
	{
		float x = vec_Item.at(i)->position.getX();
		float y = vec_Item.at(i)->position.getY();
		circle.setPosition(x - 1.0f, y - 1.0f);
		window.draw(circle);
	}
	
	window.endDraw();
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

Location::Location(Environment* p, vector<Item*>& vec_Item, location type, Vector pos, float rad):p_Env(nullptr),itemCount(0) {
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
	this->type = type;

	//Initialize items
	targetItemCount = round(radius * radius * RICHNESS);
	itemCount = targetItemCount;
	for (int i = 0; i < targetItemCount; i++)
	{
		Vector pos = Utility::randomPointInCircle(this->position, this->radius);
		//Check if inside
		while (!p_Env->isInside(pos)){
			pos = Utility::randomPointInCircle(this->position, this->radius);
		}
		switch (this->type)
		{
		case PORTABLEWATER:
			vec_Item.push_back(new Item(WATER,pos,this));
			break;
		case FOREST:
			vec_Item.push_back(new Item(APPLE, pos,this));
			break;
		case PLAIN:
			vec_Item.push_back(new Item(MEAT, pos,this));
			break;
		case MOUNTAIN:
			vec_Item.push_back(new Item(ROCK, pos,this));
			break;
		case COAST:
			vec_Item.push_back(new Item(FISH, pos,this));
			break;
		default:
			break;
		}
	}
	//printf("ItemCount:%d\n", itemCount);
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