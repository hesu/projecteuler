/*
	 Problem 25 : FIND-digit Fibonacci number
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

#include <ctime>

using namespace std;

void sum( int a[], int b[], int result[], int max)
{
	for(int i=0; i<max; i++)
	{
		int s = a[i] + b[i];

		result[i] += s;

		if( result[i] >= 10) {
			result[i+1] += result[i]/10;
			result[i] = result[i]%10; 
		}
	}
	cout << "sum=";
	for(int i=max-1; i>=0; i--)
	{
		cout << result[i];
	}
	cout << endl;
}

int digit( int arr[], int max)
{
	max++;
	for(int i=max-1; i>=0; i--)
	{
		if (arr[i] != 0){
			return i;
		}
	}
	return 0;
}

#define FIND 999 
#define BUFSIZE 1002 

int main(int argc, char** argv)
{
	int a[BUFSIZE] = {0,};
	int b[BUFSIZE] = {0,};
	int c[BUFSIZE] = {0,};

	a[0] = 1;
	b[0] = 2;

	clock_t begin = clock();

	int nth = 2;
	while( true)
	{
		nth++;
		int mod = nth%3;
		if (mod == 0){
			memset( c, 0, sizeof(c));
			sum(a, b, c, BUFSIZE);

			int d = digit(c, FIND);
			cout << "digit=" << d << endl;
			if (d >= FIND) break;
		} else if (mod == 1) {
			memset( a, 0, sizeof(a));
			sum( b, c, a, BUFSIZE);

			int d = digit(a, FIND);
			cout << "digit=" << d << endl;
			if (d >= FIND) break;
		} else {
			memset( b, 0, sizeof(b));
			sum( c, a, b, BUFSIZE); 

			int d = digit(b, FIND);
			cout << "digit=" << d << endl;
			if (d >= FIND) break;
		}
	}

	clock_t end = clock();
	cout << "nth=" << nth << endl;

	cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << endl;
	return 0;
}

