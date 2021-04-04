#builds dsp4.exe
all: dsp4.exe

dsp4.exe: main.o DataSet.o MonteCarlo.o
	g++ -o dsp4.exe main.o DataSet.o MonteCarlo.o

main.o: main.cpp
	g++ -c main.cpp

DataSet.o: DataSet.hpp DataSet.cpp
	g++ -c DataSet.cpp

MonteCarlo.o: MonteCarlo.hpp MonteCarlo.cpp
	g++ -c MonteCarlo.cpp

clean:
	rm *.o dsp4.exe