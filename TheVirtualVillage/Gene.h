#pragma once
#include <vector>
enum alleleType {
	INTENTION,
	PHYSIQUE,
};
enum allele
{
	//Intention
	PREF_GATHER,
	PREF_PURCHASE,
	PREF_SELL,
	PREF_REPRODUCE,
	PREF_WANDER,
	PREF_REST,
	//Physique
	LIFESPAN,
	//Number of allele
	TOTALLENGTH,
};

class Gene {
private:
	int totalLength = TOTALLENGTH;
	int offset[TOTALLENGTH] = {PREF_REST,LIFESPAN};
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
	vector<float> getAlleleSet(alleleType type) {
		vector<float> v;
		int i = 0;
		if (type != INTENTION)
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