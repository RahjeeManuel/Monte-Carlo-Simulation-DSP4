#include "DataSet.hpp"
DataSet::DataSet() {
    srand(time(NULL));
}
void DataSet::LoadTestInput(std::string fileName) {
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string line;
        std::string content = "";
        while (std::getline(inFile, line)) {
            content = content + line + " ";
        }
        std::stringstream ss(content);
        ss >> numBatches >> numItems >> percentBadBatch >> percentBadItem >> sampleSize;
        PrintTestInput();
        inFile.close();
    } else {
        perror("Error loading test input");
        exit(EXIT_FAILURE); 
    }
}
void DataSet::PrintTestInput() {
    std::cout << "Number of batches of items: " << numBatches << std::endl;
    std::cout << "Number of items in each batch: " << numItems << std::endl;
    std::cout << "Percentage of batches containing bad items: " << percentBadBatch << "%" <<  std::endl;
    std::cout << "Percentage of items that are bad in a bad set: " << percentBadItem << "%" <<  std::endl;
    std::cout << "Items sampled from each set: " << sampleSize << std::endl;  
}
bool DataSet::CreateBatch(std::string fileName) {
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        if ((rand() % 100 + 1) <= percentBadBatch) {
            for (int i = 0; i < numItems; i++) {
                if ((rand() % 100 + 1) <= percentBadItem) {
                    outFile << "b" << std::endl;
                } else {
                    outFile << "g" << std::endl;
                }   
            }
            return true;
        } else {
            for (int i = 0; i < numItems; i++) {
                outFile << "g" << std::endl;
            }
        }
        outFile.close();
        return false;
    } else {
        perror("Error creating batch");
        exit(EXIT_FAILURE);
    }
}
int DataSet::GenerateBatches() {
    std::cout << "\nGenerating data sets:" << std::endl;
    int badBatches = 0;
    for (int i = 0; i < numBatches; i++) {
        if(CreateBatch("ds" + std::to_string(i + 1) + ".txt")) {    //iterates through all batches
            std::cout << "Created bad set batch #" << i + 1 << std::endl;
            badBatches++;
        }
    }
    std::cout << "Total bad sets = " << badBatches << std::endl;
    return badBatches;
}
bool DataSet::CheckBatch(std::string fileName) {
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        int tries = 0;
        std::string line;
        while (getline(inFile, line) && tries++ < sampleSize) {
            if (line.compare("b") == 0) {
                return true;
            }
        }
        inFile.close();
        return false;
    } else {
        perror("Error checking batch");
        exit(EXIT_FAILURE);  
    }
}
int DataSet::AnalyzeBatches() {
    std::cout << "\nAnalyzing data sets:" << std::endl;
    int badBatches = 0;
    for (int i = 0; i < numBatches; i++) {
        if(CheckBatch("ds" + std::to_string(i + 1) + ".txt")) { //iterates through all batches
            std::cout << "Batch #" << i + 1 << " is bad" << std::endl;
            badBatches++;
        }
    }
    std::cout << "Bad sets found = " << badBatches << std::endl;
    return badBatches;
}
void DataSet::RunSimulation() {
    int actualBadBatches = GenerateBatches();
    int foundBadBatches = AnalyzeBatches();

    float base = (1.0 - (float)percentBadItem/100.0);
    float percentFailToDetect = pow(base, sampleSize);
    float percentBadDetected = ((float)foundBadBatches/(float)actualBadBatches) * 100.0;

    std::cout << "\nBase: " << base << " ";
    std::cout << "exponent: " << sampleSize << std::endl;
    std::cout << "P(failure to detect bad batch): " << percentFailToDetect << std::endl;
    std::cout << "Percentage of bad batches actually detected: " << percentBadDetected << "%" << std::endl;
}
void DataSet::DeleteBatches() {
    for (int i = 0; i < numBatches; i++) {
        remove(("ds" + std::to_string(i + 1) + ".txt").c_str());
    }
}