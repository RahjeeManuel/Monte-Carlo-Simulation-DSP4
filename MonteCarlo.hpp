#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
class MonteCarlo {
    private:
        int numSimulations;
        int numCategories;
        std::vector<std::vector<int>> categories;
        std::string unit;
    public:
        MonteCarlo();
        void LoadReadings(std::string fileName);
        void PrintReadings();
        void RunSimulation();
};
#endif