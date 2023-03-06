#pragma once
#include <vector>

int random(std::vector<float> vec) {
	float totalProb = 0.0f;
	float currentProb=0.0f;
	//r [0.0f,1.0f]
	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	for (int i = 0; i < vec.size(); i++)
	{
		totalProb += vec.at(i);
	}
	for (int i = 0; i < vec.size(); i++)
	{
		currentProb += vec.at(i) / totalProb;
		if (r <= currentProb)
			return i;
	}
	return vec.size();
}