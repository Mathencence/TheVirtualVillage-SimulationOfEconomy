#pragma once
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

#define MAPSIZE 1000 //Map is a [MAPSIZE]*[MAPSIZE] square
#define MIN_LOCATION_RADIUS	60
#define MAX_LOCATION_RADIUS	120
#define INITIAL_POPULATION 100

//Simulation
#define RENDER_INTERVAL 20 //Render the environment for every [RENDER_INTERVAL] turns
#define LOG_INTERVAL 20	//Log the environment for every [RENDER_INTERVAL] turns
#define RECENTFRAME_NUM 10 //Number of recent frames tracked to estimate performance
//Rules
#define SPEED_BASE 20
#define SPEED_GENE SPEED_BASE/2
#define SIGHT_RADIUS 15
#define INITIAL_CASH 1000 //Initial amount of cash
#define LIFE_BASE 200 //In turns
#define LIFE_GENE 50 //Lifespan influence by gene

#define HUNGERDECAY_BASE 1.0f //Base of decay rate of needs
#define HUNGERDECAY_GENE 0.5f //The proportion of decay rate influenced by gene
#define THIRSTDECAY_BASE 1.0f
#define	THIRSTDECAY_GENE 0.5f
#define TEMPERATUREDECAY_BASE 1.0f
#define TEMPERATUREDECAY_GENE 0.5f
#define NEED_RECOVERY 5.0f //The rate of recovery when consuming resources

//Number of initial location
const int INITIAL_LOCATION[] = { 10, 10, 10, 10, 10 };

//Resources distribution
#define RICHNESS 0.03 //For every unit square, the area will hold [RICHNESS] items inside the location
#define RECOVERY_SPEED 0.01//For each turn, location would recover this proportion of target max item.
