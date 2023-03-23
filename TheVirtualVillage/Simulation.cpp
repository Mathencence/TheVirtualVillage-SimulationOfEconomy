#include "Simulation.h"


Simulation::Simulation(){
    this->env = new Environment();
    this->rw = this->env->getWindow()->getRWin();
}
Simulation::~Simulation(){
}
void Simulation::consoleData(Gene g) {
    vector<float> v = g.getAlleleSet(INTENTION);
    for (int i = 0; i < v.size(); i++) {
        printf("%f ", v.at(i));
    }
    printf("\n");
    vector<float> v2 = g.getAlleleSet(PHYSIQUE);
    for (int i = 0; i < v2.size(); i++) {
        printf("%f ", v2.at(i));
    }
}
void Simulation::logData(){
    std::time_t t = std::time(nullptr); // get current time
    std::tm* now = std::localtime(&t); // convert time to struct tm
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", now); // format time as string
    std::string str_time(buffer); // convert char array to string

    // Open the log file in append mode
    std::ostringstream oss;
    oss << pathOfLog << str_time << ".txt";
    std::string logFileName = oss.str();
    // construct log file name
    std::ofstream logFile(logFileName, std::ios::trunc);
    cout << logFileName << endl;

    if (logFile.is_open())
    {
        printf("log file opened sucessful.");
        // Write a message to the log file
        logFile << "Simulation data logged." << std::endl;
        logFile << str_time << std::endl;
        // Close the log file
        logFile.close();
    }
    else {
        cerr << "Error creating log file: " << logFileName << std::endl;
    }
}