#include "../include/Entity.h"
#include "../include/Environment.h"
// Declare a default constructor and a default destructor.
Entity::Entity(Environment* p):gene(),homePosition(Vector(-1,-1)),homeRating(0.f){
	this->p_Env = p;
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
}
Entity::~Entity() {

}
// Methods:
// For eact time step, entity update its state by interacting with the environment
void Entity::update() {
	move();
	for (size_t i = 0; i < vec_tal.size(); i++)
	{
		printf("%d,", vec_tal.at(i));
	}
	int idx = search();
	//If idx!=-1, item found
	if (idx != -1) {
		printf("idx: %d\n", p_Env->vec_Item.at(idx)->type);
		gather(idx);
	}
	
	
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
	int idx = -1;
	for (int i = 0; i < vec_tal.size(); i++)
	{
		idx = p_Env->searchItem(this->position, static_cast<item_type>(vec_tal.at(i)));
		if (idx != -1) {
			if (homeRating < i) {
				//Better place found
				homeRating = (float)i;
				homePosition = this->position;
			}
			else if (homeRating > i) {
				//Home may be not suitable
				homeRating = (homeRating + (float)i) / 2.f;
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
			vec_Prop.push_back(new Item(p_Env->vec_Item.at(idx)->type));
		}
		p_Env->removeItem(idx);
	}
}