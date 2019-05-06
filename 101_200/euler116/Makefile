
CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall

all : main

main : main.o  BigInt.o
	$(CXX) -o main main.o BigInt.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
 
BigInt.o : ../../misc/BigInt/BigInt.cpp ../../misc/BigInt/BigInt.h
	$(CXX) $(CXXFLAGS) -c ../../misc/BigInt/BigInt.cpp

clean :
	rm -f *.o main
