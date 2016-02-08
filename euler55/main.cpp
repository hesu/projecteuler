/*
	 Problem 55 - Lychrel numbers 
 */
#include <iostream>
#include <ctime>
#include <cmath>
#include <string.h>

#define MAX 50 

using namespace std;

bool isPalindromic( int n[], int size)
{
	for(int i=0; i<(size/2)+1; i++)
	{ 
		if( n[i] != n[size-1-i]) { return false; } 
	}
	return true;
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

void inc( int n[], int max)
{
	n[0]++;
	for(int i=0; i<max; i++)
	{
		if(n[i] >= 10) {
			if(i+1 < max) {
				n[i+1] += n[i]/10;
			}
			n[i] = n[i]%10;
		} else {
			break;
		}
	}
}

int toint( int n[], int size)
{
	int toi = 0;
	for(int i=0; i<size; i++) { toi += pow(10, i) * n[i]; }
	return toi;
}

void getReverse( int dst[], int src[], int len)
{
	for(int i=len-1; i>=0; i--)
	{
		dst[len-i-1] = src[i];
	}
}

int digitLength( int n[], int maxsize)
{
	for(int i=maxsize-1; i>=0; i--)
	{
		if (n[i] != 0) { return i+1;}
	}
	return 0;
}

bool isLychrel( int n[], int max)
{
	int nbuf[MAX] = {0,};
	memcpy( nbuf, n, sizeof(int) * MAX);
	
	int cnt = 1;
	while( cnt <= 50) {
		int d = digitLength( nbuf, MAX);
		int m[ MAX] = {0,};
		getReverse( m, nbuf, d);
		sum( nbuf, m, MAX);

		d = digitLength( nbuf, MAX);
		if( isPalindromic( nbuf,d)) { 
			return false; 
		}
		cnt++;
	}
	return true;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */ 

	int cnt = 0;
	int n[MAX] = {0,};
	while( true)
	{
		int toi = toint( n, MAX);
		if( toi >= 10000) { break; }
		if( isLychrel( n, MAX)) { cnt++; }
		inc( n, MAX);
	}
	cout << "Lychrel cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

