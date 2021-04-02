#ifndef DATASET_HPP
#define DATASET_HPP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
class DataSet {
    private:
        int numBatches;
        int numItems;
        float percentBadBatch;
        float percentBadItem;
        int sampleSize;
    public:
        DataSet();
        void LoadTestInput(std::string fileName);
        void PrintTestInput();
        bool CreateBatch(std::string fileName);
        int GenerateBatches();
        bool CheckBatch(std::string fileName);
        int AnalyzeBatches();
        void RunSimulation();
        void DeleteBatches();
};
#endif