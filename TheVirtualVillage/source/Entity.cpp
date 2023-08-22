#include "../include/Entity.h"
#include "../include/Environment.h"
#include "../include/Market.h"

// Declare a default constructor and a default destructor.
Entity::Entity(Environment* p):gene(),homePosition(Vector(-1,-1)),homeRating(0.f)
,isDead(false), isBreeding(false), age(0), targetAge(0), cash(INITIAL_CASH), income(0)
,hunger(80.f), thirst(80.f), bodyTemperature(80.f)
,hDecay(HUNGERDECAY_BASE),tDecay(THIRSTDECAY_BASE), btDecay(TEMPERATUREDECAY_BASE)
{
	this->p_Env = p;

	//Needs
	targetAge = (LIFE_BASE + round(gene.getAllele(LIFESPAN) * LIFE_GENE));
	hDecay -= gene.getAllele(HUNGER) * HUNGERDECAY_GENE;
	tDecay -= gene.getAllele(THRIST) * THIRSTDECAY_GENE;
	btDecay -= gene.getAllele(COLDRES) * THIRSTDECAY_GENE;
	for (int i = 0; i < TYPELENGTH; i++)
	{
		itemCount[i] = 0;
		if (p_Env->market.avgPrice[i] >0) {
			itemPrice[i] = p_Env->market.avgPrice[i] + Utility::random(-MAX_INITIAL_PRICING/10, MAX_INITIAL_PRICING/10);
			if (itemPrice[i] < 0)
				itemPrice[i] = 1;
		}
		else {
			itemPrice[i] = Utility::random(1, MAX_INITIAL_PRICING);
		}
		itemIndex[i]=i;
	}
	Utility::shuffle(itemIndex,TYPELENGTH);

	
	//Randomize initial position
	this->setPosition(Vector(Utility::random(0, MAPSIZE), Utility::random(0, MAPSIZE)));
	//Completely random
	this->gene.randomize();
	//Get talent gene
	talentGene = gene.getAlleleSet(TALENT);
	for (int i = 0; i < talentGene.size(); i++)
	{
		vec_tal.push_back(i);
	}
	Utility::sortIdx(talentGene,vec_tal, false);
	//Get preference
	foodGene.push_back(gene.getAllele(PREF_APPLE));
	foodGene.push_back(gene.getAllele(PREF_MEAT));
	foodGene.push_back(gene.getAllele(PREF_FISH));
	vec_food.push_back(APPLE);
	vec_food.push_back(MEAT);
	vec_food.push_back(FISH);
	Utility::sortIdx(foodGene, vec_food, false);

	warmGene.push_back(gene.getAllele(PREF_WOOD));
	warmGene.push_back(gene.getAllele(PREF_FUR));
	vec_warm.push_back(WOOD);
	vec_warm.push_back(FUR);
	Utility::sortIdx(warmGene, vec_warm, false);
}
Entity::~Entity() {
	vec_tal.clear();
}
// Methods:
// For eact time step, entity update its state by interacting with the environment
void Entity::update() {
	income = 0;

	checkNeed();
	trade();
	consume();

	move();
	int idx = search();
	//If idx!=-1, item found
	if (idx != -1) {
		//printf("idx: %d\n", p_Env->vec_Item.at(idx)->type);
		gather(idx);
	}
}
void Entity::reproduce() {
	p_Env->vec_Entities.push_back(new Entity(p_Env));
	isBreeding = false;
}

void Entity::move() {
	float speed = SPEED_BASE + SPEED_GENE * gene.getAllele(SPEED) - (1.5 * homeRating); //For better home rating, less exploration
	//Wander from home if has valid home position, else completely random
	if (homePosition.getX() >= 0&& homePosition.getY()>=0) {
		this->position = homePosition;
	}
	Vector dir = Vector(Utility::random(-1.f, 1.f), Utility::random(-1, 1));
	Vector movement = dir.normalize() * speed;
	Vector newPosition = this->position + movement;
	// Clamp the new position within the map boundaries
	newPosition.setX(std::max(0.0f, std::min(static_cast<float>(MAPSIZE), newPosition.getX())));
	newPosition.setY(std::max(0.0f, std::min(static_cast<float>(MAPSIZE), newPosition.getY())));
	this->position = newPosition;
}
int Entity::search() {
	int r = Utility::random(1, vec_tal.size() - 1);
	if ((float)p_Env->market.avgPrice[vec_tal.at(r)]/(float)p_Env->market.avgPrice[vec_tal.at(0)] > (talentGene.at(vec_tal.at(0)) + 1.01 / talentGene.at(vec_tal.at(r)) + 1.01)) {
		int temp = vec_tal.at(r);
		for (int i = r; i > 0; i--)
		{
			vec_tal.at(i) = vec_tal.at(i - 1);
		}
		vec_tal.at(0) = temp;
	}
	else if ((talentGene.at(vec_tal.at(r)) + 1.01 / talentGene.at(vec_tal.at(0)) + 1.01) > (float)p_Env->market.avgPrice[vec_tal.at(0)] / (float)p_Env->market.avgPrice[vec_tal.at(r)])
	{
		int temp = vec_tal.at(r);
		for (int i = r; i > 0; i--)
		{
			vec_tal.at(i) = vec_tal.at(i - 1);
		}
		vec_tal.at(0) = temp;
	}
	int idx = -1;
	for (int i = 0; i < vec_tal.size(); i++)
	{
		idx = p_Env->searchItem(this->position, static_cast<item_type>(vec_tal.at(i)));
		if (idx != -1) {
			if (homeRating < vec_tal.size()-i) {
				//Better place found
				homeRating = (float)(vec_tal.size() - i);
				homePosition = this->position;
			}
			else if (homeRating > vec_tal.size() - i) {
				//Home may be not suitable
				homeRating = (homeRating + (float)(vec_tal.size() - i)) / 2.f;
			}
			return idx;
		}	
	}
	homeRating = 0.f;
	homePosition = Vector(-1, -1);
	return idx;
}
void Entity::gather(int idx) {

	int obtainCount = 1;
	float tal = talentGene.at(static_cast<int> (p_Env->vec_Item.at(idx)->type));
	if (tal != 0.f) {
		if (tal > 0) {
			if (Utility::isSuccess(tal))
				obtainCount++;
		}
		else{
			if (Utility::isSuccess(tal*(-1.f)))
				obtainCount--;
		}
	}
	if (obtainCount>0) {
		//Pick the item, remove  from world and add to property
		for (size_t i = 0; i < obtainCount; i++)
		{
			//vec_Prop.push_back(new Item(p_Env->vec_Item.at(idx)->type));
			itemCount[p_Env->vec_Item.at(idx)->type]++;
		}
		p_Env->removeItem(idx);
	}
}

void Entity::checkNeed() {
	age++;
	if (age > targetAge)
		death();
	//Check if ready to reproduce
	if (age == (int)(targetAge/2))
		isBreeding = true;

	hunger -= hDecay;
	thirst -= tDecay;
	bodyTemperature -= btDecay;
	if (hunger < 0.f || thirst < 0.f || bodyTemperature < 0.f)
		death();
}
void Entity::consume() {
	//Check if sufficent to breed
	if (isBreeding) {
		bool canBreed = true;
		for (int i = 0; i < TYPELENGTH; i++)
		{
			if (itemCount[i] < REPRODUCE_AMOUNT)
			{
				//printf("I:%d, Cash:%d, itemcount:%d\n", i, cash, itemCount[i]);
				canBreed = false;
				break;
			}
		}
		if (canBreed)
		{
			for (int i = 0; i < TYPELENGTH; i++)
			{
				itemCount[i] -= REPRODUCE_AMOUNT;
			}
			for (int i = 0; i < CHILDREN_AMOUNT; i++) {
				reproduce();
			}
		}
	}
	if (hunger < 95.f) {
		for (int i = 0; i < vec_food.size(); i++)
		{
			if (itemCount[vec_food.at(i)] > 0) {
				hunger += NEED_RECOVERY;
				itemCount[vec_food.at(i)]--;
			}
		}
	}
	if (thirst < 95.f) {
		if (itemCount[WATER]>0)
		{
			thirst += NEED_RECOVERY;
			itemCount[WATER]--;
		}
	}
	if (bodyTemperature < 95.f) {
		for (int i = 0; i < vec_warm.size(); i++)
		{
			if (itemCount[vec_warm.at(i)] > 0) {
				bodyTemperature += NEED_RECOVERY;
				itemCount[vec_warm.at(i)]--;
			}
		}
	}
}

void Entity::trade() {
	bool isShortage = false;
	for (int i = 0; i < TYPELENGTH; i++)
	{
		int j = itemIndex[i]; //Itemindex is a randomize array to shuffle the order of item types
		if (itemCount[j] == 0) {
			isShortage = true;
			break;
		}
	}
	//Sell spare items
	for (int i = 0; i < TYPELENGTH; i++) {
		int j = itemIndex[i]; //Itemindex is a randomize array to shuffle the order of item types
		int spare = itemCount[j] - RESERVE_AMOUNT;
		if (spare > 0) {
			//Sell them
			for (int s = 0; s < spare; s++)
			{
				itemCount[j]--;
				p_Env->market.registerGood(this, item_type(j), itemPrice[j]);
			}
		}
	}
	//Buy need items
	for (int i = 0; i < TYPELENGTH; i++)
	{
		int j = itemIndex[i]; //Itemindex is a randomize array to shuffle the order of item types
		if (isShortage) {
			//Only buy item which is out of reserve.
			if (itemCount[j] == 0) {
				p_Env->market.buyGood(this, item_type(j), cash);
			}
		}
		//Buy items untill the stock reach the expected reserve amount
		int want = RESERVE_AMOUNT - itemCount[j];
		if (want > 0) {
			for (int w = 0; w < want; w++)
			{
				p_Env->market.buyGood(this, item_type(j), cash);
			}
		}
	}
}

void Entity::death() {
	isDead = true;
}