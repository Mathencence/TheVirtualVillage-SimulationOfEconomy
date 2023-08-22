#include "../include/Environment.h"


Environment::Environment():border(MAPSIZE,MAPSIZE),turn(0),market(Market()),governmentCashStorage(0) {
	//Initialize window
	window.setSize(sf::Vector2u(WIN_WIDTH, WIN_HEIGHT));
	window.setTitle("Virtual-Village");
	window.redraw();
	//Generate some location
	for (int i = 0; i < LOCATION_LENGTH; i++)
	{
		for (int j = 0; j < INITIAL_LOCATION[i]; j++) {
			vec_Location.push_back(new Location(this,(location)i));
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
	//Initialize env state
	for (int i = 0; i < state::DATATYPE_LENGTH; i++) {
		envState.push_back(0.f);
	}
	
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
	//Deregister the item in its corresponding location
	vec_Item.at(index)->loc->removeItem();
	//Remove the item address in vec_Item
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
	updateState();
	drawState(RENDER_INTERVAL);
	turn++;
	market.prepare();
	updateAllEntities();
	updateAllLocations();
	market.update();
}
// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
//void render();

void Environment::updateAllEntities() {
	vec_Entities.erase(std::remove_if(vec_Entities.begin(), vec_Entities.end(), [](Entity* entity) {
		if (entity->isDead) {
			delete entity;
			return true; // Remove the entity from the vector
		}
	return false; // Keep the entity in the vector
		}), vec_Entities.end());
	vector<int> index; int size = vec_Entities.size();
	for (int i = 0; i < size; i++) {
		index.push_back(i);
	}
	Utility::shuffle(index);
	for (int i = 0; i < size;i++) {
		vec_Entities.at(index.at(i))->update();
	}
	for (int i = 0; i < size; i++) {
		float taxAmount = 0.f;
		if (vec_Entities.at(i)->income > 0) {
			taxAmount = vec_Entities.at(i)->income * TAXRATE;
		}
		vec_Entities.at(i)->cash -= taxAmount;
		governmentCashStorage += taxAmount;
		if (vec_Entities.at(i)->cash < 0)
			vec_Entities.at(i)->cash = 0;
	}
	sortEntityByCash();
	int  compensation = governmentCashStorage / 5;
	for (int i = 0; i <5 && i < vec_Entities.size(); i++)
	{
		vec_Entities.at(i) -> cash += compensation;
		governmentCashStorage -= compensation;
	}
}
void Environment::updateAllLocations(){
	for (int i = 0; i < vec_Location.size(); i++)
	{
		vec_Location.at(i)->update();
	}
}

void Environment::sortEntityByCash() {
	int n = vec_Entities.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (vec_Entities[j]->cash > vec_Entities[j + 1]->cash) {
				// Swap the pointers
				Entity* temp = vec_Entities[j];
				vec_Entities[j] = vec_Entities[j + 1];
				vec_Entities[j + 1] = temp;
			}
		}
	}
}

void Environment::drawState(int interval) {
	if (turn % interval != 0)
		return;
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

//Update the current situation of the environment such as population
void Environment::updateState(){
	setState(TURN, (float)this->turn);
	setState(POPULATION, (float)this->vec_Entities.size());

	int pp=0;
	float baseAmountToSurvive = 0.f;
	baseAmountToSurvive += this->market.avgPrice[0] * HUNGERDECAY_BASE/ 3 /NEED_RECOVERY;
	baseAmountToSurvive += this->market.avgPrice[1] * HUNGERDECAY_BASE/ 3 /NEED_RECOVERY;
	baseAmountToSurvive += this->market.avgPrice[5] * HUNGERDECAY_BASE/ 3 /NEED_RECOVERY;

	baseAmountToSurvive += this->market.avgPrice[2] * TEMPERATUREDECAY_BASE / 2 /NEED_RECOVERY;
	baseAmountToSurvive += this->market.avgPrice[3] * TEMPERATUREDECAY_BASE / 2 /NEED_RECOVERY;

	baseAmountToSurvive += this->market.avgPrice[4] * THIRSTDECAY_BASE/NEED_RECOVERY;

	baseAmountToSurvive *= 0.5;
	for (int i = 0; i < this->vec_Entities.size(); i++)
	{
		if (vec_Entities.at(i)->income < baseAmountToSurvive&&vec_Entities.at(i)->cash < baseAmountToSurvive)
			pp++;
	}
	setState(POVERTYRATE, pp/getState(POPULATION));
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

Location::Location(Environment* p, location type, Vector pos, float rad):p_Env(nullptr),itemCount(0) {
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
	generateItem(targetItemCount);
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
void Location::generateItem(int n) {
	for (int i = 0; i < n; i++)
	{
		Vector pos = Utility::randomPointInCircle(this->position, this->radius);
		//Check if inside
		while (!p_Env->isInside(pos)) {
			pos = Utility::randomPointInCircle(this->position, this->radius);
		}
		switch (this->type)
		{
		case PORTABLEWATER:
			p_Env->vec_Item.push_back(new Item(WATER, pos, this));
			itemCount++;
			break;
		case FOREST:
			p_Env->vec_Item.push_back(new Item(APPLE, pos, this));
			itemCount++;
			break;
		case RAINFOREST:
			p_Env->vec_Item.push_back(new Item(WOOD, pos, this));
			itemCount++;
			break;
		case PLAIN:
			p_Env->vec_Item.push_back(new Item(MEAT, pos, this));
			itemCount++;
			break;
		case MOUNTAIN:
			p_Env->vec_Item.push_back(new Item(FUR, pos, this));
			itemCount++;
			break;
		case COAST:
			p_Env->vec_Item.push_back(new Item(FISH, pos, this));
			itemCount++;
			break;
		default:
			break;
		}
	}
	//printf("ItemCount:%d\n", itemCount);
}

void Location::update() {
	//Recover [RECOVERY_SPEED] of [RICHNESS] items
	int recoveryNum = round(RECOVERY_SPEED * targetItemCount);
	if (targetItemCount > itemCount) {
		if (itemCount + recoveryNum <= targetItemCount) {
			generateItem(recoveryNum);
		}
	}
	//printf("ItemCount:%d\n", itemCount);
}