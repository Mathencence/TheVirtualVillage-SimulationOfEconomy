#include "Entity.h"


// Declare a default constructor and a default destructor.
Entity::Entity(Environment* p):gene(){
	this->p_Env = p;
	//Completely random
	this->gene.randomize();
}
Entity::~Entity() {

}
// Methods:
// For eact time step, entity update its state by interacting with the environment
void Entity::update() {
	intention decision = decide();
	move(decision);
	action(decision);
}
intention Entity::decide() {
	//Get gene set
	vector<float> vec_intention = gene.getAlleleSet(INTENTION);

	//First approach Completely based on gene at all time.
	for (int i = 0; i < vec_intention.size(); i++)
	{
		//Normalize the vector to range 0-1
		vec_intention.at(i) += 1;
		vec_intention.at(i) /= 2;
	}
	int rv = Utility::random(vec_intention);
	if (rv >= 0) {
		return (intention)rv;
	}
	return REST;
}

void Entity::move(intention decision) {
	Vector des = Vector(Utility::random(0,MAPSIZE), Utility::random(0, MAPSIZE));
	float speed = SPEED_BASE + SPEED_GENE * Utility::random();
	//if (decision == WANDER) {
		Vector distance = des - this->position;
		Vector movement = distance.normalize() * speed;
		if (movement.magnitude() > distance.magnitude())
			movement = distance;
		this->position += movement;
	//}
}
void Entity::action(intention decision) {
	switch (decision)
	{
		case GATHER:
			break;
		case PURCHASE:
			break;
		case SELL:
			break;
		case REPRODUCE:
			break;
		case WANDER:
			break;
		case REST:
			break;
		default:
			break;
	}
}