#pragma once
#include <vector>
enum alleleType {
	PHYSIQUE,
	TALENT,
	ITEM_PREF,
	ALLELETYPE_LENGTH
};
enum allele
{
	//Physique
	THRIST, //Resistance to thirst, the higher the better to survive generally
	HUNGER, //Resistance to hunger
	COLDRES,//Cold resistance
	SPEED,
	LIFESPAN,
	//Item talent
	TAL_APPLE,
	TAL_MEAT,
	TAL_FUR,
	TAL_WOOD,
	TAL_WATER,
	TAL_FISH,
	//Item prefence
	PREF_APPLE,
	PREF_MEAT,
	PREF_FUR,
	PREF_WOOD,
	PREF_WATER,
	PREF_FISH,
	//Number of allele
	ALLELE_LENGTH,
};

class Gene {
private:
	int totalLength = ALLELE_LENGTH;
	int offset[ALLELETYPE_LENGTH] = {LIFESPAN,TAL_FISH,PREF_FISH};
	vector<float> chromsome;
public:
	Gene() {//Default constructor
		//Arbitary gene
		for (int i = 0; i < totalLength; i++)
		{
			chromsome.push_back(0.0);
		}
	}
	//Completely randomize the gene, every allele range from -1.0 to 1.0
	void randomize() {
		for (int i = 0; i < totalLength; i++)
		{
			// Generate a float between 0 and 1
			float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); 
			r = 2.0f * r - 1.0f;
			chromsome.at(i) = r;
		}
	}
	float getAllele(allele g) {
		return chromsome.at(g);
	}
	vector<float> getAlleleSet(alleleType type) {
		vector<float> v;
		int i = 0;
		if (type != (alleleType)0)
			i = offset[type - 1] + 1;
		for (i; i <=offset[type];i++)
		{
			v.push_back(chromsome.at(i));
		}
		return v;
	}
	/*
	Gene operator+(const Gene& v) {
		return Vector(this->x + v.x, this->y + v.y);
	}
	Gene& operator+=(const Gene& v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}*/
};