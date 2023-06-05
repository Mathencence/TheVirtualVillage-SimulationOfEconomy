#include "../include/Entity.h"
#include "../include/Environment.h"
// Declare a default constructor and a default destructor.
Entity::Entity(Environment* p):gene(){
	this->p_Env = p;
	//Randomize initial position
	this->setPosition(Vector(Utility::random(0, MAPSIZE), Utility::random(0, MAPSIZE)));
	//Completely random
	this->gene.randomize();
}
Entity::~Entity() {

}
// Methods:
// For eact time step, entity update its state by interacting with the environment
void Entity::update() {
	move();
}

void Entity::move() {
	Vector dir = Vector(Utility::random(-1.f, 1.f), Utility::random(-1, 1));
	//Vector des = Vector(Utility::random(0,MAPSIZE), Utility::random(0, MAPSIZE));
	float speed = SPEED_BASE + SPEED_GENE * Utility::random();
	//Vector distance = des - this->position;
	Vector movement = dir.normalize() * speed;
	/*
	if (movement.magnitude() > distance.magnitude())
		movement = distance;
	*/
	Vector newPosition = this->position + movement;
	// Clamp the new position within the map boundaries
	newPosition.setX(std::max(0.0f, std::min(static_cast<float>(MAPSIZE), newPosition.getX())));
	newPosition.setY(std::max(0.0f, std::min(static_cast<float>(MAPSIZE), newPosition.getY())));
	this->position = newPosition;
}
void Entity::gather() {
	vector<float> vec_pref = gene.getAlleleSet(ITEM_PREF);
	//First approach Completely based on gene at all time.
	for (int i = 0; i < vec_pref.size(); i++)
	{
		//Normalize the vector to range 0-1
		vec_pref.at(i) += 1;
		vec_pref.at(i) /= 2;
	}
	int rv = Utility::random(vec_pref);
	if (rv < 0) {
		return;
	}
	int itemIdx = this->p_Env->searchItem(this->position, (item_type)rv);
	bool isSuccess = true;
	if (isSuccess) {
		//Pick the item, remove  from world and add to property
		vec_Prop.push_back(p_Env->vec_Item.at(itemIdx));
		p_Env->removeItem(itemIdx);
	}
}