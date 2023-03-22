#pragma once
enum item_type{
	APPLE,
	MEAT,
	ROCK,
	IRON,
	WOOD,
	WATER,
	FISH,
};
class Item {
public:
	Item(item_type type, Vector initPos){
		this->type = type;
		position = initPos;
	}
	~Item(){
	}
	Vector position;
	item_type type=(item_type)0;
private:
};
