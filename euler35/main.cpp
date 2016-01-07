/*
  Problem 35 - Circular primes 
*/

#include <iostream>
#include <ctime>
#include <map>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <queue>

using namespace std;

std::map<int,int> primes;
bool isprime( int n)
{
  std::map<int,int>::iterator it = primes.find(n);
  if( it != primes.end()) { return true; }

  int s = sqrt( n) + 1;
  for(int i=s; i>1; i--)
  {
    if (n%i ==0) { return false; }
  }
  return true;
}

std::map<int,int> circularPrimes;
bool isCircularPrime( int n)
{
  std::map<int,int>::iterator it = circularPrimes.find(n);
  if( it != circularPrimes.end()) { return true; }

  char buf[16] = {0,};
  sprintf( buf, "%d", n);

  int len = strlen( buf);

	std::queue<int> qn;
  for(int i=0; i<len; i++)
  {
		int digit = buf[i] - '0';
		qn.push( digit); 
  }

	bool allPrime = false;
	for(int i=0; i<len; i++)
	{
		 // TODO
	}

	return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  /* starting code */

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
