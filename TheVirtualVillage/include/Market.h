#pragma once
#include "Vector.h"
#include "Item.h"
#include <vector>
#include "Parameters.h"
#include "Utility.h"
#include <memory>

class Entity;
class Market
{
public:
	// Declare a default constructor and a default destructor.
	Market();
	~Market();
	
    //Posting good for sale
    void registerGood(Entity* owner, item_type type, int price);

	//Buy good of type, and return the price
	//Pass in the available amount of cash and number of good
	int buyGood(Entity* buyer, item_type type, int cash);

    // Check the status of registered goods
    void removeInvalidGoods();

	//Taking off the good, usually because the good is expired or the owner deceased.
	//void deregisterGood();
	void update();
	
	//Calculating average price
	void avgPricing();
private:
	friend class Simulation;
	friend class Entity;

    std::vector<std::pair<Entity*,int>> goods[TYPELENGTH];
	int stock[TYPELENGTH];
	int avgPrice[TYPELENGTH];
};