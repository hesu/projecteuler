CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall

all : main

main : main.o
	$(CXX) -o main main.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean :
	rm -f *.o main
