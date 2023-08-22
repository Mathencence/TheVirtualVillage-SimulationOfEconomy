#pragma once
#include "Vector.h"
#include "Gene.h"
#include "Item.h"
#include "Utility.h"
#include "Parameters.h"
#include <memory>

class Market;
class Environment;
//Entity is usually related to villagers in this environment
class Entity
{
public:
	// Declare a default constructor and a default destructor.
	Entity(Environment* p);
	~Entity();

	void update();
	//Getter and Setter
	Vector getPosition() {return position;}
	void setPosition(Vector v) {position=v;}

	void death();
	bool isDead;
	bool isBreeding;

	friend class Market;
	friend class Environment;
	friend class Simulation;
private:
	Environment* p_Env;

	Vector homePosition;
	float homeRating;
	Vector position;
	Gene gene;
	vector<float> talentGene;

	vector<float> foodGene;
	vector<int> vec_food;

	vector<float> warmGene;
	vector<int> vec_warm;
	//vector <Item*> vec_Prop;
	//The descending order of talent types
	//The index in vec_tal represent the type of item
	vector<int> vec_tal;

	//State
	int cash, income;
	int targetAge;
	int age;

	int itemIndex[TYPELENGTH];
	int itemCount[TYPELENGTH];
	int itemPrice[TYPELENGTH]; //It is the recognition by the village of the price of the item type.

	//Needs is 100 when fullfilled and if under 0, villager dies.
	float thirst,tDecay;
	float hunger,hDecay;
	float bodyTemperature,btDecay;


	void checkNeed();
	void trade();
	void consume();

	void reproduce();

	void move();
	int search();
	void gather(int idx);
	
};