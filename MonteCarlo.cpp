#include "MonteCarlo.hpp"
MonteCarlo::MonteCarlo() {
    srand(time(NULL));
    numSimulations = 100;
    numCategories = 7;
    categories = {
        {0, 2000, 15},
        {2000, 4000, 25},
        {4000, 8000, 20},
        {8000, 12000, 15},
        {12000, 18000, 10},
        {18000, 24000, 10},
        {24000, 28000, 5}
    };
    unit = "ml";
}
void MonteCarlo::LoadReadings(std::string fileName) {
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string line;
        if (std::getline(inFile, line)) {
            std::stringstream ss(line);
            ss >> numSimulations;
            if (std::getline(inFile, line)) {
                std::stringstream ss(line);
                ss >> numCategories; 
                categories.clear();
                int index = 0;
                int min,max,occurence;
                while (std::getline(inFile, line) && index++ < numCategories) {
                    for (int i = 0; i < line.length(); i++) {
                        if (!isdigit(line[i])) {
                            line[i] = ' ';
                        }
                    }
                    std::stringstream ss(line);
                    ss >> min >> max >> occurence;
                    categories.push_back({min, max, occurence});
                }
                if (std::getline(inFile, line)) {
                    std::stringstream ss(line);
                    ss >> unit;
                }
            }
        }
        inFile.close();
    } else {
        perror("Error loading readings");
        exit(EXIT_FAILURE); 
    }
}
void MonteCarlo::PrintReadings() {
    std::cout << "Simulated days: " << numSimulations << std::endl;
    std::cout << "Number of categories: " << numCategories << std::endl;
    std::cout << "Ranges and occurrences in each range: " << std::endl;
    for (std::vector<int> v : categories) {
        std::cout << v[0] << "-" << v[1] << ": " << v[2] << std::endl; 
    }
    std::cout << "Analytical model: " << "#";
    std::cout << ". Expected value is in the: " << "#" << "-" << "#" << "/" << unit << " range." << std::endl;
    std::cout << "Simulation: " << "#";
    std::cout << ". Expected value is in the: " << "#" << "-" << "#" << "/" << unit << " range." << std::endl;
}
void MonteCarlo::RunSimulation() {

}