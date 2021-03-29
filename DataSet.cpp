#include "DataSet.hpp"
DataSet::DataSet() {
    srand(time(NULL));
}
void DataSet::LoadInput(int num) {
    std::string fileName = "t" + std::to_string(num) + ".txt";
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string line = "";
        std::string content = "";
        while (std::getline(inFile, line)) {
            content = content + line + " ";
        }
        std::stringstream ss(content);
        ss >> numBatches >> numItems >> badBatchPercentage >> badItemPercentage >> sampleSize;
        inFile.close();
        std::cout << "Number of batches of items: " << numBatches << std::endl;
        std::cout << "Number of items in each batch " << numItems << std::endl;
        std::cout << "Percentage of batches containing bad items " << badBatchPercentage << "%" <<  std::endl;
        std::cout << "Percentage of items that are bad in a bad set " << badItemPercentage << "%" <<  std::endl;
        std::cout << "Items sampled from each set " << sampleSize << std::endl;
    } else {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
}
bool DataSet::CreateDataSet(int num) {
    std::string fileName = "ds" + std::to_string(num) + ".txt";
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        if ((rand() % 100+1) <= badBatchPercentage) {
            for (int i = 0; i < numItems; i++) {
                if ((rand() % 100+1) <= badItemPercentage) {
                    outFile << "b" << std::endl;
                } else {
                    outFile << "g" << std::endl;
                }   
            }
            std::cout << "Created bad batch # " << num << std::endl;
            return false;
        } else {
            for (int i = 0; i < numItems; i++) {
                outFile << "g" << std::endl;
            }
        } 
        outFile.close();
        return true;
    } else {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
}
bool DataSet::ReadDataSet(int num) {
    std::string fileName = "ds" + std::to_string(num) + ".txt";
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        int i = 0;
        std::string line;
        while (getline(inFile, line) && i++ < sampleSize) {
            if (line.compare("b") == 0) {
                return false;
            }
        }
        inFile.close();
        return true;
    } else {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }  
}
void DataSet::RunSimulation() {
    int badBatches = 0;
    std::cout << "Generating data sets:" << std::endl;
    for (int i = 0; i < numBatches; i++) {
        if (CreateDataSet(i + 1) == false) {
            badBatches++;
        }
    }
    std::cout << "Total bad sets = " << badBatches << std::endl;

    std::cout << "Analyzing data sets:" << std::endl;
    int foundBadBatches = 0;
    for (int i = 0; i < numBatches; i++) {
        if (ReadDataSet(i + 1) == false) {
            foundBadBatches++;
            std::cout << "Batch #" + std::to_string(i+1) + " is bad" << std::endl;
        }
    }

    std::cout << "Base = " + std::to_string((1 - ((float)badItemPercentage/10.0))) << " exponent = " << sampleSize << std::endl;
    std::cout << "P(failure to detect bad batch) = " << "?" << std::endl;
    std::cout << "Percentage of bad batches actually detected = " << (((float)foundBadBatches/(float)badBatches) * 100.0) << "%" << std::endl;

    DeleteDataSets(numBatches);
}
void DataSet::DeleteDataSets(int num) {
    for (int i = 0; i < num; i ++) {
        const char* c = ("ds" + std::to_string(i + 1) + ".txt").c_str();
        if (remove(c) != 0) {
            perror("Error deleting file");
        }
    }
}