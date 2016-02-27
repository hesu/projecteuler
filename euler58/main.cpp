/*
 	Problem 58 - Spiral primes
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

std::map<int,int> primes;
std::map<int,int> notprimes;
bool isprime( int n)
{
	if( n == 2) return true;
	std::map<int,int>::iterator it;
	it = notprimes.find(n); if( it != notprimes.end()) { return false; }
	it = primes.find(n); if( it != primes.end()) { return true; }

	int s = sqrt( n) + 1;
	for(int i=s; i>1; i--)
	{
		if (n%i ==0) { 
			notprimes.insert( std::map<int,int>::value_type( n, n));
			return false;
		}
	}

	primes.insert( std::map<int,int>::value_type( n, n));
	return true;
}

std::vector<int> getDiagonalNumbers( int size) 
{
	int bR = size * size; // bottomRight
	int bL = bR - size + 1; // bottomLeft
	int tL = bL - size + 1; // topLeft
	int tR = tL - size + 1; // topRight

	std::vector<int> dn;
	dn.push_back( bR);
	dn.push_back( bL);
	dn.push_back( tL);
	dn.push_back( tR);
	return dn;
}

int getnDiagonals( int size) { return ((size-1)/2)*4; }

int howmanyPrimes( std::vector<int> v)
{
	int n = 0;
	for(int i=0; i<v.size(); i++) {
		if( isprime( v[i])) { n++; }
	}
	return n;
}

double getDiagonalPrimeRatio( int size, double thisSizePrimes)
{
	return thisSizePrimes / getnDiagonals( size);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	std::map<int, int> diagonalPrimes; // rectangleSize, nPrimes
	diagonalPrimes.insert( std::map<int,int>::value_type(1, 0));
	std::map<int, int>::iterator it;

	int size = 3;
	while(true)
	{
		std::vector<int> dn = getDiagonalNumbers( size);
		int p = howmanyPrimes( dn);
		
		it = diagonalPrimes.find( size-2);
		if (it != diagonalPrimes.end()) {
			diagonalPrimes.insert( std::map<int,int>::value_type(size, p + it->second)); 
		}
		double ratio = getDiagonalPrimeRatio( size, p+it->second); 
		if( ratio <= 0.1) break;
		size = size+2;
	}
	cout << "size=" << size << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
