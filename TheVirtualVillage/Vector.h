#pragma once
#include <cmath>
#include <algorithm>
using namespace std;
class Vector {
private:
	float x, y;
public:
	Vector() {//Default constructor
		this->x = 0;
		this->y = 0;
	}
	Vector(float x, float y) {
		this->x = x;
		this->y = y;
	}
	float getX() {
		return this->x;
	}
	float getY() {
		return this->y;
	}
	void setX(float valueX)
	{
		x = valueX;
	}

	void setY(float valueY)
	{
		y = valueY;
	}

	Vector operator+(const Vector& v) {
		return Vector(this->x + v.x, this->y + v.y);
	}
	Vector& operator+=(const Vector& v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}
	Vector operator-(const Vector& v) {
		return Vector(this->x - v.x, this->y - v.y);
	}
	Vector& operator-=(const Vector& v) {
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}
	Vector operator*(const float& f) {
		return Vector(this->x*f, this->y*f);
	}
	Vector& operator*=(const float& f) {
		this->x *= f;
		this->y *= f;
		return *this;
	}
	Vector operator/(const float& f) {
		return Vector(this->x/f, this->y/f);
	}
	Vector& operator/=(const float& f) {
		this->x /= f;
		this->y /= f;
		return *this;
	}
	float magnitude() {
		return sqrt(x*x + y*y);
	}
	Vector normalize() {
		float mag = this->magnitude();
		return Vector(x/mag, y/mag);
	}
	bool operator==(const Vector& v) const {
		return x == v.x && y == v.y;
	}
	bool operator!=(const Vector& v) const {
		return !(*this == v);
	}
	float EuclideanDistance(const Vector& other) const {
		float dx = this->x - other.x;
		float dy = this->y - other.y;
		return sqrt(dx * dx + dy * dy);
	}
	//Manhattan distance
	float ManhattanDistance(const Vector& other) const {
		return abs(this->x - other.x) + abs(this->y - other.y);
	}
	//Chebyshev distance
	float ChebyshevDistance(const Vector& other) const {
		return max(abs(this->x - other.x), abs(this->y - other.y));
	}
};
