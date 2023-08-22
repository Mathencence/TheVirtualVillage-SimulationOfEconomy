#include "../include/Simulation.h"

Simulation::Simulation(){
    this->currentRun = 1;
    this->env = new Environment();
    this->rw = this->env->getWindow()->getRWin();
    this->tempPopulation = 0;
    this->tempPovRate = 0;
    for (int i = 0; i < TYPELENGTH; i++)
    {
        tempStock[i] = 0;
        tempPrice[i] = 0;
        tempDemand[i] = 0;
        tempSupply[i] = 0;
    }
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
    oss << pathOfLog << str_time << ".csv";
    std::string logFileName = oss.str();
    // construct log file name
    logFile = new std::ofstream(logFileName, std::ios::trunc);
    cout << logFileName << endl;

    // Write header row
    if (!ISRECORDING_WEALTH) {
        *logFile << "Turn,Population,PovertyRate";
        for (size_t i = 0; i < TYPELENGTH; i++) {
            *logFile << ",Market stock " << i + 1;
        }
        for (size_t i = 0; i < TYPELENGTH; i++) {
            *logFile << ",Price " << i + 1;
        }
        for (size_t i = 0; i < TYPELENGTH; i++) {
            *logFile << ",Transaction Price " << i + 1;
        }
        for (size_t i = 0; i < TYPELENGTH; i++) {
            *logFile << ",Demand " << i + 1;
        }
        for (size_t i = 0; i < TYPELENGTH; i++) {
            *logFile << ",Supply " << i + 1;
        }
        *logFile << std::endl;
    }
    else {
        *logFile << "Stacked population percentage, Stacked wealth percentage";
        *logFile << std::endl;
    }
}
void Simulation::closeLogFile() {
    // Close the log file
    logFile->close();
}
void Simulation::logData(bool isExtincted){
    //Data header is written in openLogFile()
    if (logFile->is_open()) {
        if (RUNS == 1) {
            // Write data row
            *logFile << env->getState(TURN) << ","
                << env->getState(POPULATION) << ","
                << env->getState(POVERTYRATE);
            for (size_t i = 0; i < TYPELENGTH; i++) {
                *logFile << "," << env->market.stock[i];
            }
            for (size_t i = 0; i < TYPELENGTH; i++) {
                *logFile << "," << env->market.avgPrice[i];
            }
            for (size_t i = 0; i < TYPELENGTH; i++) {
                *logFile << "," << env->market.avgTransactionPrice[i];
            }
            for (size_t i = 0; i < TYPELENGTH; i++) {
                *logFile << "," << env->market.requestCount[i];
            }
            for (size_t i = 0; i < TYPELENGTH; i++) {
                *logFile << "," << env->market.supplyCount[i];
            }
            *logFile << std::endl;
        }
        else if (RUNS > 1) {
            if (env->getState(TURN) == 0&&currentRun>1) {
                //First turn of non-first run in multiple run
                //Calculate the average of last run
                tempPopulation /= (float)TURNS_PERRUN;
                tempPovRate /= (float)TURNS_PERRUN;
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    tempStock[i] /= (float)TURNS_PERRUN;
                    tempPrice[i] /= (float)TURNS_PERRUN;
                    tempTPrice[i] /= (float)TURNS_PERRUN;
                    tempDemand[i] /= (float)TURNS_PERRUN;
                    tempSupply[i] /= (float)TURNS_PERRUN;
                }
                //Log the data of last run
                if (isExtincted) {
                    *logFile << currentRun - 1 << ","
                        << -1;
                }
                else {
                    *logFile << currentRun - 1 << ","
                        << tempPopulation;
                }
                *logFile << currentRun - 1 << ","
                    << tempPovRate;

                for (size_t i = 0; i < TYPELENGTH; i++) {
                    *logFile << "," << tempStock[i];
                }
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    *logFile << "," << tempPrice[i];
                }
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    *logFile << "," << tempTPrice[i];
                }
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    *logFile << "," << tempDemand[i];
                }
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    *logFile << "," << tempSupply[i];
                }
                *logFile << std::endl;
                //Clear the temp memory
                tempPopulation = 0.f;
                tempPovRate = 0.f;
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    tempStock[i] = 0.f;
                    tempPrice[i] = 0.f;
                    tempDemand[i] = 0.f;
                    tempSupply[i] = 0.f;
                    tempTPrice[i] = 0.f;
                }
            }
            else if(env->getState(TURN) != 0){
                //Non-first turn or first turn of first run
                tempPopulation += env->getState(POPULATION) * LOG_INTERVAL;
                tempPovRate += env->getState(POVERTYRATE) * LOG_INTERVAL;
                for (size_t i = 0; i < TYPELENGTH; i++) {
                    tempStock[i] += env->market.stock[i] * LOG_INTERVAL;
                    tempPrice[i] += env->market.avgPrice[i] * LOG_INTERVAL;
                    tempTPrice[i] += env->market.avgTransactionPrice[i] * LOG_INTERVAL;
                    tempDemand[i] += env->market.requestCount[i] * LOG_INTERVAL;
                    tempSupply[i] += env->market.supplyCount[i] * LOG_INTERVAL;
                }
            }
        }
        
    }
    else {
        std::cerr << "Error when writing log file." << std::endl;
    }
}
void Simulation::logWealthData() {
    //Sort the entities by wealth
    env->sortEntityByCash();
    if (logFile->is_open()) {
        int totalPopulation = env->vec_Entities.size(), totalWealth = 0;
        for (size_t i = 0; i < env->vec_Entities.size(); i++) {
            totalWealth += env->vec_Entities.at(i)->cash;
        }
        for (size_t i = 0; i < env->vec_Entities.size(); i++) {
            *logFile << "," <<(float)env->vec_Entities.at(i)->cash / (float)totalWealth;
        }
        *logFile << std::endl;
    }
    /*
    if (logFile->is_open()) {
        int totalPopulation = env->vec_Entities.size(), totalWealth = 0;
        for (size_t i = 0; i < env->vec_Entities.size(); i++) {
            totalWealth+=env->vec_Entities.at(i)->cash;
        }
        for (size_t i = 0; i < env->vec_Entities.size(); i++) {
            *logFile << (float)i/(float)totalPopulation << "," << (float)env->vec_Entities.at(i)->cash / (float)totalWealth;
            *logFile << std::endl;
        }
    }
    */
    
}

//Should also call env.update() once
int Simulation::startNewRun() {
    this->currentRun++;
    // Delete the old object
    if (this->env != nullptr) {
        delete this->env;
    }
    this->env = new Environment();
    this->rw = this->env->getWindow()->getRWin();
    if (currentRun > RUNS)
        return -1;

    return 0;
}