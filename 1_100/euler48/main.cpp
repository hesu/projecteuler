/*
 	Problem 48 - Self Powers 
*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <string.h>
#include <stdio.h>

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

int toint( int result[], int size)
{
	int toint = 0;
	for(int i=0; i< size; i++)
	{
		toint += pow(10, i) * result[i];
	}
	return toint;
}

void bigpow( int result[], int exponent, int stopat)
{
	int i = toint(result, stopat);

	while( exponent-1)
	{
		multiply( result, i, stopat);
		exponent--;	
	}	
}

void sum( int dst[], int src[], int max)
{
	for(int i=0; i<max; i++)
	{
		dst[i] += src[i];

		if( dst[i] >= 10) {
			if(i+1 < max) {
				dst[i+1] += dst[i]/10;
			}
			dst[i] = dst[i]%10; 
		}
	}
}

using namespace std;
int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	int result[10]= {0,};
	for(int i=1; i<=1000; i++)
	{
		cout << "i=" << i << endl;
		int buf[10] = {0,};
		char cbuf[10] = {0,};
		sprintf( cbuf, "%d", i);

		int slen = strlen( cbuf);
		for(int c=slen; c>0; c--)
		{
			buf[ slen-c] = cbuf[c-1]-'0';
		}

		bigpow( buf, i, 10);
		sum( result, buf, 10);
	}

	cout << "sum=";
	for(int i=9; i>=0; i--)
	{
		cout << result[i];
	}
	cout << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

