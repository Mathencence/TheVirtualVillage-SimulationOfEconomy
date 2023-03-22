#pragma once
#include <vector>
#define PI 3.14159265358979323846
//Return a random number uniformly distributed between min and max
class Utility {
public:
	//Return 0.0 to 1.0
	float static random() {
		float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return r;
	}
	float static random(float min, float max) {
		if (min > max)
			throw("ERROR Upperbound should larger than lowerbound in random function.");
		float r = random();
		r = r * (max - min) + min;
		return r;
	}
	//Passing float array indicating probabilties and return the index being chosen.
	int static random(std::vector<float> vec) {
		float totalProb = 0.0f;
		float currentProb = 0.0f;
		//r [0.0f,1.0f]
		float r = random();
		for (size_t i = 0; i < vec.size(); i++)
		{
			totalProb += vec.at(i);
		}
		for (size_t i = 0; i < vec.size(); i++)
		{
			currentProb += vec.at(i) / totalProb;
			if (r <= currentProb)
				return (int)i;
		}
		return (int)vec.size();
	}
	//Generate a point in circle using polar coord
	Vector static randomPointInCircle(Vector center, float r) {
		Vector v(0,0);

		// Generate random point in circle with radius r
		float angle = 2 * PI * random();
		float radius = r * random();

		v.setX(center.getX() + radius * cos(angle));
		v.setY(center.getY() + radius * sin(angle));
		return v;
	}
};
