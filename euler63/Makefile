
CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall

all : main

main : main.o
	$(CXX) -o main main.o BigInt.o

main.o : main.cpp BigInt.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp BigInt.cpp

clean :
	rm -f *.o main
