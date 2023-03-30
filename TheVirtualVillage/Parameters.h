#pragma once
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

#define MAPSIZE 1000
#define MIN_LOCATION_RADIUS	20
#define MAX_LOCATION_RADIUS	120
#define INITIAL_POPULATION 100
//Rules
#define SPEED_BASE 10
#define SPEED_GENE SPEED_BASE/2
#define SIGHT_RADIUS 5
//Number of initial location
const int INITIAL_LOCATION[] = { 10, 10, 10, 10, 10 };

//Resources distribution
#define INITIAL_RICHNESS 1.0 //For every unit square, [INITIAL_RICHNESS] items
