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
	int static random(int min, int max) {
		if (min > max)
			throw("ERROR Upperbound should larger than lowerbound in random function.");
		int r = rand() % (max - min + 1);
		return r + min;
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
		float angle = static_cast<float>(2 * PI * random());
		float radius = r * random();

		v.setX(center.getX() + radius * cos(angle));
		v.setY(center.getY() + radius * sin(angle));
		return v;
	}

	bool static isSuccess(float p) {
		if (p <= 0.f)
			return false;
		if (p >= 1.f)
			return true;
		if (Utility::random() < p)
			return true;
		return false;
	}
	void static sortIdx(vector<float> vec, vector<int>& outvec, bool isAscending = true) {
		for (int i = 0; i < vec.size() - 1; i++) {
			for (int j = 0; j < vec.size() - i - 1; j++) {
				if (isAscending) {
					if (vec.at(j) > vec.at(j + 1)) {
						// Swap the elements
						float temp = vec.at(j);
						vec.at(j) = vec.at(j + 1);
						vec.at(j + 1) = temp;
						int tempI = outvec.at(j);
						outvec.at(j) = outvec.at(j + 1);
						outvec.at(j + 1) = tempI;
					}
				}
				else {
					if (vec.at(j) < vec.at(j + 1)) {
						// Swap the elements
						float temp = vec.at(j);
						vec.at(j) = vec.at(j + 1);
						vec.at(j + 1) = temp;
						int tempI = outvec.at(j);
						outvec.at(j) = outvec.at(j + 1);
						outvec.at(j + 1) = tempI;
					}
				}
				
			}
		}
	}
	void static shuffle(std::vector<int>& outvec) {
		int n = outvec.size();
		for (int i = n - 1; i > 0; --i) {
			// Generate a random index between 0 and i (inclusive)
			int j = rand() % (i + 1);

			// Swap elements at indices i and j
			std::swap(outvec[i], outvec[j]);
		}
	}
	void static shuffle(int* arr, int size) {
		for (int i = size - 1; i > 0; --i) {
			// Generate a random index between 0 and i (inclusive)
			int j = rand() % (i + 1);
			// Swap elements at indices i and j
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
};
