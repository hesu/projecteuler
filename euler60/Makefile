
CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall

all : main t

main : main.o
	$(CXX) -o main main.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

t : t.o
	$(CXX) -o t t.o

t.o : t.cpp
	$(CXX) $(CXXFLAGS) -c t.cpp

clean :
	rm -f *.o main t
