/*
  Problem 37 -Truncatable primes 
*/

#include <iostream>
#include <ctime>
#include <map>

using namespace std;

std::map<int,int> primes;
bool isPrimeBothSides( int n)
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


int main(int argc, char** argv)
{
  clock_t begin = clock();

  /* starting code */

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
