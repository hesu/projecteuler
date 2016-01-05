
/*
   By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

   What is the 10 001st prime number?
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>

using namespace std;

int primes[10000] = {0,};
int idx=0;
bool isprime( int p)
{
	for(int i=0; i<=10000; i++)
	{
		if (primes[i] == 0) return true; 
		if (p%primes[i] == 0) {
			return false;
		}
	}
	return true;
}

int prime( int nth)
{
	int prime = 1;

	for(int i=1;; i++)
	{
		if( isprime(i) && prime < i) {
			prime = i;
			cout << "found prime! nth=" << idx << " prime=" << prime << endl;
			primes[idx] = prime;
			idx++;
		}
		if( idx > nth) {
			break;
		}
	}

	return prime;
}

int main(int argc, char** argv)
{
	cout << "10001 prime=" << prime(10001) << endl; 
	return 0;
}
