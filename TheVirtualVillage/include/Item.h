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
class Location;
class Item {
public:
	Item(item_type type, Vector initPos, Location* loc){
		this->type = type;
		position = initPos;
		this->loc = loc;
	}
	~Item(){
	}
	Location* loc;
	Vector position;
	item_type type=(item_type)0;
private:
};
