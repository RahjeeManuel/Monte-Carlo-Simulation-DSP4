#include "MonteCarlo.hpp"
MonteCarlo::MonteCarlo() {
    srand(time(NULL));
}
void MonteCarlo::LoadReadingInput(std::string fileName) {
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string line;
        if (std::getline(inFile, line)) {
            std::stringstream ss(line);
            ss >> numSimulations;

                if (std::getline(inFile, line)) {
                    std::stringstream ss(line);
                    ss >> numCategories;

                    int index = 0;
                    while (index++ < numCategories && std::getline(inFile, line)) {
                        std::replace_if(line.begin(), line.end(), ispunct, ' ');    //tokens the categories to have only numbers
                        std::stringstream ss(line);
                        Category c;
                        ss >> c.min >> c.max >> c.occur;
                        categories.push_back(c);
                    }

                    if (std::getline(inFile, line)) {
                        std::stringstream ss(line);
                        ss >> unit;
                    }

                    PrintReadingInput();
                }
        }
        inFile.close();
    } else {
        perror("Error loading reading input");
        exit(EXIT_FAILURE); 
    }
}
void MonteCarlo::PrintReadingInput() {
    std::cout << "Simulated days: " << numSimulations << std::endl;
    std::cout << "Number of categories: " << numCategories << std::endl;
    std::cout << "Ranges and occurrences in each range: " << std::endl;
    for (Category c : categories) {
        std::cout << c.min << "-" << c.max << ": " << c.occur << std::endl;
    }
    std::cout << "Units of measure: " << unit << std::endl;
}
float MonteCarlo::GetAnalyticalResult() {
    float result = 0;
    for (Category c : categories) {
        result = result + (((c.min + c.max) / 2) * c.occur);    //finds mean average from occurence
    }
    return result / numSimulations;
}
float MonteCarlo::GetSimulationResult() {
    float result = 0;
    for (Category c : categories) {
        result = result + (((c.min + c.max) / 2) * c.doccur);       //finds mean average from simulation occurence (doccur)
    }
    return result / numSimulations;
}
void MonteCarlo::PrintInterval(float result) {
    for (Category c : categories) {
        if (result >= c.min && result <= c.max) {   //finds interval a given number is in
            std::cout << "Expected value is in the " << c.min << "-" << c.max << "/" << unit << " range." << std::endl;
            break;
        }
    } 
}
void MonteCarlo::ResetDistribution() {
    int start = 0;
    for (int i = 0; i < numCategories; i++) {   //resets simulation distribution data and changes dmin/dmax to 0-99
        categories[i].doccur = 0;
        categories[i].dmin = start;
        categories[i].dmax = start + (((float)categories[i].occur / numSimulations) * 100) - 1;
        start = categories[i].dmax + 1;
    }
}
void MonteCarlo::IncrementOccurence(int num) {
    for (int i = 0; i < numCategories; i++) {
        if (num >= categories[i].dmin && num <= categories[i].dmax) {   //increments occurence in interval
            categories[i].doccur = categories[i].doccur + 1;
            break;
        }
    }
}
void MonteCarlo::RunSimulation() {
    ResetDistribution();

    float analyticalResult = GetAnalyticalResult();
    std::cout << "Analytical model: " << analyticalResult << ". ";
    PrintInterval(analyticalResult);

    for (int i = 0; i < numSimulations; i++) {
        IncrementOccurence(rand() % 100);
    }
    
    float simulationResult = GetSimulationResult();
    std::cout << "Simulation: " << simulationResult << ". ";
    PrintInterval(simulationResult);

}