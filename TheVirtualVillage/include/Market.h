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
	//Taking off the good, usually because the good is expired or the owner deceased.
    void removeInvalidGoods();

	
	//prepare() is called at turn start and update() is called when turn end
	void prepare();
	void update();
	
	//Calculating average price
	void avgPricing();
private:
	friend class Simulation;
	friend class Environment;
	friend class Entity;

    std::vector<std::pair<Entity*,int>> goods[TYPELENGTH];
	int stock[TYPELENGTH];
	int avgPrice[TYPELENGTH];

	int transactionCount[TYPELENGTH];
	float avgTransactionPrice[TYPELENGTH];

	//requestCount should be clear to zero per turn, it reflects the demand per turn
	float requestCount[TYPELENGTH];
	//supplyCount should be stock at turn start plus stock adding this turn, clear to zero as requestCount
	float supplyCount[TYPELENGTH];
};