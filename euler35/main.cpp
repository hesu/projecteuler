/*
  Problem 35 - Circular primes 
*/

#include <iostream>
#include <ctime>
#include <map>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

std::map<int,int> primes;
bool isprime( int n)
{
	if( n == 2) return true;

  std::map<int,int>::iterator it = primes.find(n);
  if( it != primes.end()) { return true; }

  int s = sqrt( n) + 1;
  for(int i=s; i>1; i--)
  {
    if (n%i ==0) { return false; }
  }

	primes.insert( std::map<int,int>::value_type( n, n));
  return true;
}

int getCircularNum( std::deque<int> q)
{
	std::deque<int>::iterator it = q.begin();

	int num = 0;
	int expo = 1;
	while( it != q.end())
	{
		num += expo * (*it++);
		expo *=10;
	}
	return num;
}

std::map<int,int> circularPrimes;
bool isCircularPrime( int n)
{
  std::map<int,int>::iterator it = circularPrimes.find(n);
  if( it != circularPrimes.end()) { return true; }

  char buf[16] = {0,};
  sprintf( buf, "%d", n);

  int len = strlen( buf);

	std::deque<int> qn;
  for(int i=0; i<len; i++)
  {
		int digit = buf[i] - '0';
		qn.push_back( digit); 
  }

	std::vector<int> circulars;
	bool allPrime = true;
	for(int i=0; i<len; i++)
	{
		int pop = qn.front();
		qn.pop_front();
		qn.push_back(pop);

		int c = getCircularNum( qn);
		if ( !isprime( c)) {
			allPrime = false;
			break;	
		} else {
			circulars.push_back( c);
		}
	}

	if( allPrime) {
		for(int i=0; i<circulars.size(); i++)
		{
	//		cout << "find! : " << circulars[i] << endl;
			circularPrimes.insert( std::map<int,int>::value_type( circulars[i], circulars[i]));
		}
	}

	return allPrime; 
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  /* starting code */
	for(int i=2; i< 1000000; i++)
	{
		isCircularPrime( i); 
	}

	for( std::map<int, int>::iterator it = circularPrimes.begin(); it != circularPrimes.end(); ++it)
	{
		cout << it->first << endl;
	}
	cout << "size = " << circularPrimes.size() << endl;;

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
