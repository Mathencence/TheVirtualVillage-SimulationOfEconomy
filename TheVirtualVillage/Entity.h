#pragma once
#include "Vector.h"
#include "Gene.h"
//Entity is usually related to villagers in this environment
enum intention
{
	//Intention
	GATHER,
	PURCHASE,
	SELL,
	REPRODUCE,
	WANDER,
	REST,
};
class Entity
{
public:
	// Declare a default constructor and a default destructor.
	Entity();
	~Entity();
	// Methods:
	// Move handles the positions of the sprite of the entity
	// And bouncing the mushroom against the window limits.
	// This fucntions returns void and receives no parameters.
	void update();
	//Getter and Setter
	Vector getPosition() {return position;}
	void setPosition(Vector v) {position=v;}
private:
	Vector position;
	Gene gene;

	intention decide();
	void move(intention intention);
	void action(intention intention);
	
};