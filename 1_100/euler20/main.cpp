/*
	 Problem 20 - Factorial digit sum
 */

#include <iostream>

using namespace std;

void multiply( int result[], int mul, int maxlen)
{
	for(int i=0; i<maxlen; i++)
	{
		//cout << "i=" << i << " carry=" << carry << endl;
		//int val = result[i] * mul;
		result[i] = result[i] * mul;
	}

	// trim
	int nextcarry = 0;
	for(int i=0; i<maxlen; i++)
	{
		int carry = nextcarry;
		nextcarry = result[i]/10;
		result[i] = result[i]%10 + carry;

		while( result[i]>=10) {
			result[i] = result[i]-10;
			nextcarry++;
		}
	}
}

int main(int argc, char** argv)
{
	int fac[1000] = {0,};
	fac[0] = 1;

	for(int i=1; i<=100; i++)
	{
		multiply( fac, i, 1000);
	}

	int nsum = 0;
	for(int i=0; i<1000; i++)
	{
		cout << fac[i] << " ";
		nsum += fac[i];
	}
	cout << endl;

	cout << "nsum=" << nsum << endl;
	return 0;
}
