#include <iostream>
#include <time.h>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "include/Simulation.h"
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
float calculateAverageFrameRate(const std::vector<float>& frameTimes) {

    float sumFrameTimes = 0.0f;
    for (int i = 0; i < frameTimes.size(); i++) {
        sumFrameTimes += frameTimes[i];
    }

    float averageFrameTime = sumFrameTimes / (float)frameTimes.size();
    float averageFrameRate = 1.0f / averageFrameTime;

    return averageFrameRate;
    //std::cout << "Average Frame Rate: " << averageFrameRate << " frames per second" << std::endl;
}
void updateFrameHistory(float frameTime,std::vector<float>& frameTimes) {
    if (frameTimes.size() >= RECENTFRAME_NUM)
        frameTimes.erase(frameTimes.begin());

    frameTimes.push_back(frameTime);
        
}

int main()
{
    //Generate a random seed
    srand(time(nullptr));
    Simulation sim = Simulation();
    //sim.consoleData(g);
    //sim.logData();
    sf::RenderWindow* rw = sim.getRW();
    sf::Clock clock;
    sf::Time elapsedTime;
    float deltaTime;
    sf::Time targetFrameTime = sf::seconds(1.0f/1000.0f); // x turns per second
    vector<float> recentFrameTimes;


    while(rw->isOpen())
    {
        // handle events
        sf::Event event;
        while (rw->pollEvent(event))
        {
            // check the type of the event
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                rw->close();
                break;
                // key pressed
            case sf::Event::KeyPressed:
                // handle the key press event
                break;
                // handle other events...
            default:
                break;
            }
        }
        elapsedTime = clock.restart();
        deltaTime = elapsedTime.asSeconds();
        sf::Time remainingTime = targetFrameTime - elapsedTime;
        if (remainingTime > sf::Time::Zero)
            sf::sleep(remainingTime);

        //Tracking performance
        updateFrameHistory(deltaTime, recentFrameTimes);

        //printf("TimeElapsed:%f", deltaTime);
        sim.getEnv()->update();
        if ((int)sim.getEnv()->getState(TURN) % LOG_INTERVAL == 0) {
            sim.logData();
            //Visaulize performance on console
            printf("Turn: %d ------- TurnPerSec: %f\n", (int)sim.getEnv()->getState(TURN),calculateAverageFrameRate(recentFrameTimes));
        }
           
    }

    return 0;
}