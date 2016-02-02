/*
	 Problem 16 - Power digit sum
 */

#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

using namespace std;

void multiply( int result[], int mul, int maxlen)
{
	int carry = 0;
	for(int i=0; i<maxlen; i++)
	{
		//cout << "i=" << i << " carry=" << carry << endl;
		int prev_carry = carry;
		int val = result[i] * mul;
		carry = val/10;
		result[i] = val%10 + prev_carry;
	}
}

int main(int argc, char** argv)
{
	int sum[1000] = {0,};
	sum[0] = 1;

	for(int i=0; i<1000; i++)
	{
		multiply( sum, 2, 1000);
		//for(int i=0; i<10; i++) { cout << sum[i] << " "; }
		cout << endl;
	}

	int nsum = 0;
	for(int i=0; i<1000; i++)
	{
		nsum += sum[i];
	}

	cout << "nsum=" << nsum << endl;
	return 0;
}
