/*
  Problem 37 -Truncatable primes 
*/

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

std::map<int,int> primes;

bool isLeftSidedPrime( char buf[]) 
{
	int buflen = strlen( buf);
	for(int i=0; i<buflen; i++)
	{
		int sided = 0;
		for(int j=0; j<=i; j++)
		{
			sided += (buf[j] - '0') * pow(10, i-j);
		}
//		cout << "l sided=" << sided << endl;
		if( sided == 0 || sided == 1) { return false; }
		if( sided == 2) { continue; } 

  	std::map<int,int>::iterator it = primes.find(sided);
  	if( it != primes.end()) { continue; } 
		else {
			int s = sqrt( sided)+1;
			for(int j=s; j>1; j--)
			{
				if( sided%j == 0) { return false;}
			}
		}
		primes.insert( std::map<int,int>::value_type( sided, sided));
	}
	return true;
}

bool isRightSidedPrime( char buf[]) 
{
	int buflen = strlen( buf);
	for(int i=0; i<buflen; i++)
	{
		int sided = 0;
		for(int j=i; j<buflen; j++)
		{
			sided += (buf[j] - '0') * pow(10, buflen-j-1);
		}
//		cout << "r sided=" << sided << endl;
		if( sided == 0 || sided == 1) { return false; }
		if( sided == 2) { continue; } 

  	std::map<int,int>::iterator it = primes.find(sided);
  	if( it != primes.end()) { continue; } 
		else {
			int s = sqrt( sided)+1;
			for(int j=s; j>1; j--)
			{
				if( sided%j == 0) { return false;}
			}
		}
		primes.insert( std::map<int,int>::value_type( sided, sided));
	}
	return true;
}

std::map<int,int> bothSidedPrimes;

bool isBothSidedPrime( int n)
{
	char buf[1024] = {0,};
	sprintf( buf, "%d", n);
	
	if (!isLeftSidedPrime( buf)) { return false; }
	if (!isRightSidedPrime( buf)) { return false; }
//	cout << "buf=" << buf << ", reverse=" << reverse << endl;

	bothSidedPrimes.insert( std::map<int,int>::value_type( n, n)); 
	return true;
}

void checkTruncatablePrimes( int n)
{
	for(int i=0; i<9; i++)
	{
		int newn = n*10 + i;
		if( isBothSidedPrime( newn)) {
			checkTruncatablePrimes( newn);
		}
	}
	
	for(int i=0; i<99; i++)
	{
		int newn = n*100 + i;
		if( isBothSidedPrime( newn)) {
			checkTruncatablePrimes( newn);
		}
	}
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
  /* starting code */

	for(int i=0;; i++)
	{
		checkTruncatablePrimes(i);
		if (bothSidedPrimes.size() >= 15) { break; }
	}


	int sum = 0;
	cout << "size = " << bothSidedPrimes.size() << endl;;
	for( std::map<int, int>::iterator it = bothSidedPrimes.begin(); it != bothSidedPrimes.end(); ++it)
	{
		cout << it->first << endl;
		sum += it->first;
	}

	sum -= (2+3+5+7);

	cout << "sum=" << sum << endl;

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
