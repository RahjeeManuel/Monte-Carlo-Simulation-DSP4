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
        bool CreateBatch(std::string fileName);     //creates batch by filename
        int GenerateBatches();
        bool CheckBatch(std::string fileName);      //checks batch of errors by filename
        int AnalyzeBatches();
        void RunSimulation();
        void DeleteBatches();                       //deletes all batches
};
#endif