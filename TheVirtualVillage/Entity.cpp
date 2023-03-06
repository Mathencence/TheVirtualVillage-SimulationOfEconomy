#include "Entity.h"
#include "Utility.h"

// Declare a default constructor and a default destructor.
Entity::Entity():gene(){
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
	int rv = random(vec_intention);
	if (rv >= 0) {
		return (intention)rv;
	}
	return REST;
}
void Entity::move(intention decision) {

}
void Entity::action(intention decision) {
	
}