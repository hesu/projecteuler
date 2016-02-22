all : main BigInt

main : main.o
	g++ -o main main.o

main.o : main.cpp
	g++ -c main.cpp

BigInt : BigInt.o
	g++ -o BigInt BigInt.o

BigInt.o : BigInt.cpp
	g++ -c BigInt.cpp

clean :
	rm -f *.o main BigInt
