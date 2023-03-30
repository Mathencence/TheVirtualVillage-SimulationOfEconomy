#pragma once
#include "Vector.h"
#include "Gene.h"
#include "Item.h"
#include "Utility.h"
#include "Parameters.h"

class Environment;
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
	Entity(Environment* p);
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
	Environment* p_Env;

	Vector position;
	Gene gene;
	vector <Item*> vec_Prop;


	intention decide();
	void move(intention intention);
	void action(intention intention);
	void gather();
	
};