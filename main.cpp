#include "DataSet.hpp"
int main() {
    DataSet ds;

    std::cout << "Simulation 1:" << std::endl;
    ds.LoadTestInput("t5.txt");
    ds.RunSimulation();
    ds.DeleteBatches();

    return 0;
}