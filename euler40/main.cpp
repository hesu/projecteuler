/*
  Problem 40 - Chmpernowne's constant 
*/

// TODO

#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

int getStartingDigit( int n, int scopes[]) 
{
	return scopes[n-1]; 
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

	/* starting code */

	int scopes[10];
	scopes[0] = 1;

	int sum = 0;
	for(int i = 1; i< 10; i++)
	{
		sum += (pow( 10, i) - pow( 10, i-1)) * i;
		scopes[i] = sum; 
	}

	int products = 1;
	for(int i=1; i<=6; i++)
	{
		int digit = getStartingDigit( pow(10, i), scopes);
		cout << "at pow(10," << i << ")" << ", digit=" << digit << endl;
	}

  /* end of code */

  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
