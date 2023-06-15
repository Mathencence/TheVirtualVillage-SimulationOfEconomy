#include "../include/Entity.h"
#include "../include/Environment.h"
// Declare a default constructor and a default destructor.
Entity::Entity(Environment* p):gene(),homePosition(Vector(-1,-1)){
	this->p_Env = p;
	//Randomize initial position
	this->setPosition(Vector(Utility::random(0, MAPSIZE), Utility::random(0, MAPSIZE)));
	//Completely random
	this->gene.randomize();
	//Get talent gene
	vector<float> talentGene= gene.getAlleleSet(TALENT);
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
	if(idx!=-1)
	printf("idx: %d\n", p_Env->vec_Item.at(idx)->type);
}

void Entity::move() {
	float speed = SPEED_BASE + SPEED_GENE * Utility::random();
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
	for (int i = 0; i < static_cast<int>(TYPELENGTH); i++)
	{
		idx = p_Env->searchItem(this->position, static_cast<item_type>(vec_tal.at(i)));
		if (idx != -1)
			return idx;
	}
	return idx;
}
void Entity::gather() {
	vector<float> vec_pref = gene.getAlleleSet(ITEM_PREF);
	//First approach Completely based on gene at all time.
	for (int i = 0; i < vec_pref.size(); i++)
	{
		//Normalize the vector to range 0-1
		vec_pref.at(i) += 1;
		vec_pref.at(i) /= 2;
	}
	int rv = Utility::random(vec_pref);
	if (rv < 0) {
		return;
	}
	int itemIdx = this->p_Env->searchItem(this->position, (item_type)rv);
	bool isSuccess = true;
	if (isSuccess) {
		//Pick the item, remove  from world and add to property
		vec_Prop.push_back(p_Env->vec_Item.at(itemIdx));
		p_Env->removeItem(itemIdx);
	}
}