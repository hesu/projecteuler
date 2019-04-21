
CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall

all : main

main : main.o BigInt.o
	$(CXX) -o main main.o BigInt.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

BigInt.o : BigInt.cpp
	$(CXX) $(CXXFLAGS) -c BigInt.cpp

clean :
	rm -f *.o main
