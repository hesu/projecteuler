all : BigInt.o main

main : main.o BigInt.o
	g++ -o main main.o BigInt.o

main.o : main.cpp
	g++ -c main.cpp

BigInt.o : BigInt.cpp
	g++ -c BigInt.cpp

clean :
	rm -f *.o main
