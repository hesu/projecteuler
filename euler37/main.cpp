/*
  Problem 37 -Truncatable primes 
*/

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

std::map<int,int> bothSidePrimes;
bool isBothSidePrime( int n)
{
	if( n == 2) return true;
  std::map<int,int>::iterator it = bothSidePrimes.find(n);
  if( it != bothSidePrimes.end()) { return true; }
  int s = sqrt( n) + 1;
  for(int i=s; i>1; i--)
  {
    if (n%i ==0) { return false; }
  }

	if( n < 10) { 
		bothSidePrimes.insert( std::map<int,int>::value_type( n, n));
		return true;
	}

	char buf[1024] = {0,};
	sprintf( buf, "%d", n);
	int r = 0;
	for(int i=0; i<strlen(buf); i++)
	{
		r += pow( 10, i) * ( buf[i] - '0'); 
	}

	s  = sqrt( r) + 1;
	for(int i=s; i>1; i--)
	{
  	if (r%i ==0) { return false; }
	}

	bothSidePrimes.insert( std::map<int,int>::value_type( n, n));
	bothSidePrimes.insert( std::map<int,int>::value_type( r, r));
  return true;
}

std::vector<int> sum;
int main(int argc, char** argv)
{
  clock_t begin = clock();
  /* starting code */

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
