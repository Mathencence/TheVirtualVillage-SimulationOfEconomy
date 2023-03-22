#include <iostream>
#include <time.h>
#include "Simulation.h"
using namespace std;

/*int simpleLoop(Game* g) {//return fps of this loop
    sf::Time t = g->getElapsedTime();
    g->update();
    g->render();
    t = g->getElapsedTime() - t;
    int fps;
    float deltaT = t.asSeconds();
    if (deltaT < 0.00001)
        deltaT = 0.00001;
    fps = (int)(1.0 / deltaT);
    printf("TimePerLoop:%f\nfps:%d\n", t.asSeconds(), fps);
    g->printFps(fps);
    return fps;
}*/
int main()
{
    //Generate a random seed
    srand(time(nullptr));
    Simulation sim = Simulation();
    //sim.consoleData(g);
    //sim.logData();

    return 0;
}