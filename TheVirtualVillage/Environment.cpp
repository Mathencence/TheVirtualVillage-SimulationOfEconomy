#include "Environment.h"

Environment::Environment() {

}
Environment::~Environment() {

}
// Declare a function for updating the env state. Returns void and receives no parameters.
void update() {

}
// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
//void render();

void Environment::updateAllEntities() {
	for(int i =0;i< vec_p_Entities.size();i++)
	{
		vec_p_Entities.at(i)->update();
	}
}
//Return the entity's position vector with the corresponding index
Vector Environment::getEntPosition(int index) {
	return vec_p_Entities.at(index)->getPosition();
}