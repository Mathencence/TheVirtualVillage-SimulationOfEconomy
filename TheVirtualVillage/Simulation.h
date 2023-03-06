#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
//#include <vector>
class Simulation
{
public:
	// Declare a default constructor and a default destructor.
	Simulation();
	~Simulation();
	// Declare a function for updating the env state. Returns void and receives no parameters.
	// void update();
	void logData();
	// Declare a function for rendering the env to the screen. Returns void and receives no parameters.
	// void render();
private:
	const std::string pathOfLog = "./log/";
};