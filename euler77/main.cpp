/*
  Problem 77 - Prime summations
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

int primeSummations( int n, std::vector<int> primes, int depth)
{
  if( primes.size() == 0) { return 0; }
  if( n == 0) return 1;
  if( n == 1 || n < 0) return 0;

  int ways = 0;
  for(int i=primes.size()-1; i>=0; i--)
  {
    std::vector<int> v;
    for(int j=0; j<=i; j++) {
      v.push_back( primes[j]); 
    }
    
    int next_n = n - v[ v.size()-1];
    ways += primeSummations( next_n, v, depth+1);
  }

  return ways;
}

bool isprime( unsigned long int n)
{
  if( n == 1) return false;
  if( n == 2) return true;

  unsigned long int s = sqrt( n) + 1;
  for(unsigned long int i=s; i>1; i--)
  {
    if (n%i ==0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  /*
  std::vector<int> primes = {2,3,5,7};
  int n = 10;
  int depth = 0;
  int ways = primeSummations( n, primes, depth);
  */

  int n;
  for(n=2;;n++)
  {
    std::vector<int> primes;
    for(int i=2;i<=n;i++)
    {
      if( isprime(i)) primes.push_back(i);
    }

    int ways = primeSummations( n, primes, 0);
    if( ways >= 5000) break;
  }

  cout << "n=" << n << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
