#include "DataSet.hpp"
#include "MonteCarlo.hpp"
int main() {
    
    std::cout << "\nPart 1" << std::endl;
    DataSet ds;
    std::cout << "\nSimulation 1:" << std::endl;
    ds.LoadTestInput("t1.txt");
    ds.RunSimulation();

    std::cout << "\nSimulation 2:" << std::endl;
    ds.LoadTestInput("t2.txt");
    ds.RunSimulation();

    std::cout << "\nSimulation 3:" << std::endl;
    ds.LoadTestInput("t3.txt");
    ds.RunSimulation();

    std::cout << "\nSimulation 4:" << std::endl;
    ds.LoadTestInput("t4.txt");
    ds.RunSimulation();

    //ds.DeleteBatches(); //uncomment to remove dsn.txt files

    std::cout << "\nPart 2" << std::endl;
    MonteCarlo mc;
    mc.LoadReadingInput("readings.txt");
    mc.RunSimulation();

    return 0;
}