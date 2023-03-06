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
    //Declare an object of type "Game"
    //Simulation sim(); //nEntites
    //i_Fps = simpleLoop(&game);
    //printf("\nAverageFps:%d\n", i_AvgFps);
    Gene g = Gene();
    g.randomize();
    vector<float> v = g.getAlleleSet(INTENTION);
    for (int i = 0; i < v.size(); i++) {
        printf("%f ",v.at(i));
    }
    printf("\n");
    vector<float> v2 = g.getAlleleSet(PHYSIQUE);
    for (int i = 0; i < v2.size(); i++) {
        printf("%f ", v2.at(i));
    }
    Simulation sim = Simulation();
    //sim.logData();
    return 0;
}