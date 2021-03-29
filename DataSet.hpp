#ifndef DATASET_HPP
#define DATASET_HPP
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>
class DataSet {
    private:
        int numBatches;
        int numItems;
        float badBatchPercentage;
        float badItemPercentage;
        int sampleSize;
    public:
        DataSet();
        void LoadInput(int num);
        bool CreateDataSet(int num);
        bool ReadDataSet(int num);
        void RunSimulation();
        void DeleteDataSets(int num);
        //
};
#endif