/*
	 Problem 51 - Prime digit replacements 
 */
#include <iostream>
#include <ctime>
#include <map>
#include <cmath>
#include <vector>
#include <math.h>
#include <string.h>

using namespace std;

std::map<int,int> primes;
bool isprime( int n)
{
	if( n == 2) return true;
	std::map<int,int>::iterator it = primes.find(n);
	if( it != primes.end()) { return true; }

	int s = sqrt( n) + 1;
	for(int i=s; i>1; i--)
	{
		if (n%i ==0) { return false; }
	}

	primes.insert( std::map<int,int>::value_type( n, n));
	return true;
}

int toint( int n[], int size)
{
	int toi = 0;
	for(int i=0; i<size; i++)
	{
		toi += pow(10, i) * n[i];
	}
	return toi;
}

void inc( int n[], int size)
{
	n[0]++;
	for(int i=0; i<size; i++)
	{
		if(n[i] >= 10) {
			if(i+1 < size) {
				n[i+1] += n[i]/10;
			}
			n[i] = n[i]%10;
		} else {
			break;
		}
	}
}

#define MAX 8

int n[MAX] = {0,};

void combination( int arr[], int arrsize, int choose, int nowi, std::vector<int> result, bool* done)
{
	if( choose <= 0) {
		vector<int> replacedNumbers;
		for(int i=0;i<10;i++)
		{
			int r[MAX];
			memcpy( r, n,sizeof(int)*MAX);

			bool nopush = false;
			for( std::vector<int>::iterator it= result.begin(); it!=result.end();++it)
			{
				if( i == 0 && *it == arrsize-1) {
					nopush = true;
					break;
				}
				r[*it] = i;
			}
			if (!nopush){
				replacedNumbers.push_back(toint(r, MAX));
			}
		}

		int nPrimes = 0;
		for(int i=0; i<replacedNumbers.size(); i++)
		{
			if (isprime( replacedNumbers[i])) {
				nPrimes++;
			}
		}

		if( nPrimes == 8) {
			cout << "\tfound!" << endl;
			for(int i=0; i<replacedNumbers.size(); i++)
			{
				if( isprime( replacedNumbers[i])) {
					cout << replacedNumbers[i] << " ";
				}
			}
			cout << endl;

			*done = true;
		}
		return;
	}

	for(int i=nowi; i<arrsize;i++)
	{
		std::vector<int> r(result);
		r.push_back(i);
		combination( arr, arrsize, choose-1, i+1,r, done);
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

	n[1] = 1; // starting at 10
	int digits = 1;

	bool done = false;
	while( !done)
	{
		int ntoi = toint( n, MAX);
		int d = int(log10(ntoi)+1);
		if( d> digits) digits = d;

		for(int i=1;i<=digits; i++)
		{
			int digitlist[MAX] = {0,};
			for(int j=0;j<digits-1; j++)
			{
				digitlist[j] = j;
			}
			std::vector<int> c;
			combination( digitlist, digits, i, 0, c, &done); 
		}
		cout << "n=" << ntoi << endl;
		inc( n, MAX);

	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
