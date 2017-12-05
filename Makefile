program: main.o MCSim.o Vector.o
	g++ --std=c++11 -o program main.o MCSim.o Vector.o
main.o: main.cpp MCSim.h Vector.h
	g++ --std=c++11 -c main.cpp

MCSim.o: MCSim.cpp Vector.h
	g++ --std=c++11 -c MCSim.cpp

Vector.o: Vector.cpp Vector.h
	g++ --std=c++11 -c Vector.cpp
