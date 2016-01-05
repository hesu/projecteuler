
/*
   2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

   What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include <iostream>
#include <cmath>
#include <cstring>

#include <stdio.h>

using namespace std;

bool smallest_multiple(int n)
{
	for(int i=1; i<21; i++)
	{
		if( n%i != 0) {
			return false;
		}
	}
	return true;
}
int main(int argc, char** argv)
{

	for( int i=20;; i++)
	{
		if (smallest_multiple( i)) {
			cout << "found!! i=" << i << endl;
			return 0;
		}
	}

	return 0;
}
