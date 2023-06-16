#include "../include/Simulation.h"

Simulation::Simulation(){
    this->env = new Environment();
    this->rw = this->env->getWindow()->getRWin();
    openLogFile();
}
Simulation::~Simulation(){
    closeLogFile();
}
void Simulation::consoleData(Gene g) {
    vector<float> v = g.getAlleleSet(PHYSIQUE);
    for (int i = 0; i < v.size(); i++) {
        printf("%f ", v.at(i));
    }
    printf("\n");
    vector<float> v2 = g.getAlleleSet(ITEM_PREF);
    for (int i = 0; i < v2.size(); i++) {
        printf("%f ", v2.at(i));
    }
}
void Simulation::openLogFile() {
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
    logFile = new std::ofstream(logFileName, std::ios::trunc);
    cout << logFileName << endl;
}
void Simulation::closeLogFile() {
    // Close the log file
    logFile->close();
}
void Simulation::logData(){
    if (logFile->is_open())
    {
        //printf("Log file opened sucessful.");
        // Write a message to the log file
        //*logFile << "Simulation data logged." << std::endl;
        //*logFile << str_time << std::endl;
        *logFile << "Turn: " << env->getState(TURN) << std::endl;
        *logFile << "Population: " << env->getState(POPULATION) << std::endl;
        *logFile << std::endl;
    }
    else {
        cerr << "Error writing log file: " << std::endl;
    }
}