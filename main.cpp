#include "DataSet.hpp"
#include "MonteCarlo.hpp"
int main() {

    MonteCarlo mc;
    mc.LoadReadings("readings.txt");
    mc.PrintReadings();
    
    /*
    DataSet ds;
    std::cout << "Simulation 1:" << std::endl;
    ds.LoadTestInput("t5.txt");
    ds.RunSimulation();
    ds.DeleteBatches();
    */
    return 0;
}