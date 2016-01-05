
/*
   The prime factors of 13195 are 5, 7, 13 and 29.

   What is the largest prime factor of the number 600851475143 ?
*/

#include <iostream>
#include <cmath>
using namespace std;

long l = 600851475143;

bool isprime(int n)
{
	for( int i=2; i<n; i++)
	{
		if (n%i == 0) return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int sqrted = sqrt( l);
	std::cout << "l=" << l<< " sqrted=" << sqrted << std::endl;

	int lpf;
	for( int i=1; i<=sqrted; i++)
	{
		if (l%i==0 && l>i && isprime(i) ) {
			lpf = i;
		}
	}

	std::cout << "lpf=" << lpf << endl;
	return 0;
}
