/*
  Problem 40 - Chmpernowne's constant 
*/

#include <iostream>
#include <ctime>
#include <math.h>
#include <stdio.h>

using namespace std;

#define MAXSIZE 10

int getLeftAndStartingDigit( int n, int scopes[], int* digit) 
{
	int i;
	for(i=0; i<MAXSIZE; i++)
	{
		if (n < scopes[i]) {
			*digit = i;
			break;
		}
	}
	return (n - scopes[i-1]); 
}

int getDn( int left, int startingDigit)
{
	int n = pow(10, startingDigit-1); // starting number

	for(;left>startingDigit; left-=startingDigit)
	{
		n++;	
	}

	char buf[32] = {0,};
	sprintf( buf, "%d", n);
	int dn = buf[left-1] - '0';
	return dn;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

	/* starting code */

	int scopes[10];
	scopes[0] = 1;

	int sum = 0;
	for(int i = 1; i< MAXSIZE; i++)
	{
		sum += (pow( 10, i) - pow( 10, i-1)) * i;
		scopes[i] = sum; 
	}

	int products = 1;
	for(int i=1; i<=6; i++)
	{
		int n = pow(10, i);
		int d;
		int left = getLeftAndStartingDigit( n, scopes, &d);

		cout << "n=" << n << " left=" << left << " digit=" << d << endl;
		products *= getDn( left, d);
	}
	cout << endl << "products of dn = " << products << endl;

  /* end of code */

  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
