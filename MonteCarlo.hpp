#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP
#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
class MonteCarlo {
    private:
        struct Category {
            int min,max,occur;          //holds the data from readings.txt
            int dmin,dmax,doccur;       //temp data used for simulation
        };
        int numSimulations;
        int numCategories;
        std::vector<Category> categories;
        std::string unit;
    public:
        MonteCarlo();
        void LoadReadingInput(std::string fileName);
        void PrintReadingInput();
        float GetAnalyticalResult();
        float GetSimulationResult();
        void PrintInterval(float result);       //prints the interval a number is in
        void ResetDistribution();               //resets all simulation data
        void IncrementOccurence(int num);       //increases occurrence of a range during simulation
        void RunSimulation();
};
#endif