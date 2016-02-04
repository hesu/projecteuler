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
#include <stdlib.h>

using namespace std;

std::map<int,int> primes;
bool isprime( int n)
{
	if( n == 0 || n == 1) return false;
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

void generateReplacedNumbers( int arr[], int size, int nowi, vector<int> replaceAt, bool* done)
{
	cout << "replaceAt.size()=" <<replaceAt.size()<< endl;
	if (nowi >= size-1) {
		// done; replace it
		vector<int> replacedNumbers;
		bool nopush =false;
		for(int v=0; v<10; v++)
		{
			for(int i=0; i<replaceAt.size(); i++)
			{
				if( v == 0 && replaceAt[i] == size-1) {
					nopush = true;
					break;
				}
				arr[replaceAt[i]] = v;	
			}
			if( !nopush) {
				replacedNumbers.push_back( toint(arr, MAX));
				cout << toint(arr, MAX) << " ";
			}
		}
		int nPrimes = 0;
		for(int i=0; i< replacedNumbers.size(); i++)
		{
			if( isprime( replacedNumbers[i])) {
				nPrimes++;
			}
		}
		cout << " digit=" << size<< " replacedNumbers=" << replacedNumbers.size() << " nPrimes=" << nPrimes << endl;

		if( nPrimes == 8) {
			cout << "found!" << endl;
			for(int i=0; i<replacedNumbers.size(); i++)
			{
				if( isprime( replacedNumbers[i])) { cout << replacedNumbers[i] << " "; }
			}
			cout << endl;

			*done = true;
		}
		return;
	}

	for(int v=0; v<10; v++) 
	{
		arr[nowi] = v;
		return generateReplacedNumbers( arr, size, nowi+1, replaceAt, done);
	}
}


void combination( int arr[], int digits, int choose, int nowi, std::vector<int> result, bool* done)
{
	if( choose <= 0) {
	//	cout << "  digits= " << digits << " choose=" << result.size() << endl;
		int *r = malloc( sizeof(int) * digits);
		generateReplacedNumbers( r, digits, 0, result, done);
		free(r);
		return;
	}

	for(int i=nowi; i<digits; i++)
	{
		std::vector<int> r(result);
		r.push_back(i);

		if (*done == false) {
			combination( arr, digits, choose-1, i+1,r, done);
		}
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

	int t[2]= {0,};
	std::vector<int> r;
	r.push_back(0);
	bool b;
	generateReplacedNumbers( t, 2, 0, r, &b); 

/*
	int digits = 1;
	bool done = false;
	while( !done) 
	{
		cout << "digits:" << digits << endl;
		for(int i=1;i<=digits; i++)
		{
			int digitlist[MAX] = {0,};
			for(int j=0;j<digits-1; j++)
			{
				digitlist[j] = j;
			}
			std::vector<int> c;
			combination( digitlist, digits-1, i, 0, c, &done);
		}
		digits++;
	}
	*/

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
