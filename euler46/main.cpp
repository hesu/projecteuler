/*
 	Problem 46 - Goldbach's other conjecture
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <map>

using namespace std;

std::map<unsigned long int, unsigned long int> primes;
bool isprime( unsigned long int n)
{
	if( n == 2) return true;

  std::map<unsigned long int,unsigned long int>::iterator it = primes.find(n);
  if( it != primes.end()) { return true; }

  unsigned long int s = sqrt( n) + 1;
  for(unsigned long int i=s; i>1; i--)
  {
    if (n%i ==0) { return false; }
  }

	primes.insert( std::map< unsigned long int, unsigned long int>::value_type( n, n));
  return true;
}

unsigned long int twiceOfSquare( unsigned long int n)
{
	return 2*pow(n,2);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	for(unsigned long int i=1;;i++)
	{
		unsigned long int n = 2*i+1;
		if (!isprime( n)) {
			cout << "n=" << n << endl;
			bool goldbach = false;

			unsigned long int s=1;
			while( true)
			{
				unsigned long int t = twiceOfSquare( s);
				if (t>=n) break;

				if( isprime( n-t)) {
					goldbach = true;
					break;
				}
				s++;
			}
			
			if( !goldbach) {
				cout << "goldbach false number = " << n << endl;
				break;
			}
		}
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
