/*
 	Problem 57 - Square root convergents 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>

#include "BigInt.h"

using namespace std;
int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	int count = 0;
	BigInt n = BigInt(3); // numerator 
	BigInt d = BigInt(2); // denominator
	
	for(int i=1; i<=1000; i++)
	{
		n.print(); cout << "/"; d.print(); cout << endl;
		if( n.getDigitsLen() > d.getDigitsLen()) {
			count++;
		}

		BigInt swp; swp.copy(n);
		n = n+d+d;
		d = swp + d; 
	}
	cout << "count=" << count << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
