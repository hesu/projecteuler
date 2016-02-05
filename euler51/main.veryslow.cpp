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
std::map<int,int> notprimes;

bool isprime( int n)
{
	if( n == 0 || n == 1) return false;
	if( n == 2) return true;

	std::map<int,int>::iterator it;

	it = notprimes.find(n);
	if( it != notprimes.end()) { return false;}

	it = primes.find(n);
	if( it != primes.end()) { return true; }

	int s = sqrt( n) + 1;
	for(int i=s; i>1; i--)
	{
		if (n%i ==0) { 
			notprimes.insert( std::map<int,int>::value_type(n,n));
			return false; 
		}
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
	/*
	cout << "size=" << size << " replaceAt.size()=" <<replaceAt.size()<< " nowi=" << nowi << endl;
	for(int i=0; i<size; i++)
	{
		cout << " arr[" << i << "]" << " = " << arr[i];
	}
	cout << endl;
	*/

	if (nowi >= size) {

		vector<int> replacedNumbers;
//		bool nopush =false;
		for(int v=0; v<10; v++)
		{
			for(int i=0; i<replaceAt.size(); i++)
			{
				arr[replaceAt[i]] = v;
	//			cout << "replaceAt[i]=" << replaceAt[i] << endl;
			}
			int toi = toint( arr, size);
			if( int(log10(toi)) + 1 == size) {
				replacedNumbers.push_back( toi); 
		//		cout << toi << endl;
			}
		}

		/* isPrime check */////
		int nPrimes = 0;
		for(int i=0; i< replacedNumbers.size(); i++)
		{
			if( isprime( replacedNumbers[i])) {
				nPrimes++;
			}

			//if( i == 0) cout << "replacedNumbers[0]=" << replacedNumbers[0] << endl;
		}

		//cout << "nPrimes=" << nPrimes << endl;
	//	cout << " digit=" << size<< " replacedNumbers=" << replacedNumbers.size() << " nPrimes=" << nPrimes << endl;

		if( nPrimes == 8) {
			cout << "found!" << endl;
			for(int i=0; i<replacedNumbers.size(); i++)
			{
				if( isprime( replacedNumbers[i])) { cout << replacedNumbers[i] << " "; }
			}
			cout << endl;
			clock_t end = clock();
			std::cout << "end time=" << end / CLOCKS_PER_SEC << std::endl;
			exit(1);
	//		*done = true;
		}
		return;
		///////////////////////
	}

	for(int v=0; v<10; v++) 
	{
		arr[nowi] = v;
		//cout << "set value [" << nowi << "] =" << v << endl;
		generateReplacedNumbers( arr, size, nowi+1, replaceAt, done);
	}
}


void combination( int arr[], int digits, int choose, int nowi, std::vector<int> result, bool* done)
{
	if( choose <= 0) {
//		cout << "  digits= " << digits << " choosed=" << result.size() << endl;
		/*
		int *r =(int*) malloc( sizeof(int) * digits);
		for(int i=0; i<digits; i++)
		{
			r[i] = 0;
		}
		*/

		generateReplacedNumbers( arr, digits, 0, result, done);
		//free(r);
		return;
	}

	for(int i=nowi; i<=digits; i++)
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
	/* starting code */
	clock_t begin = clock();
	std::cout << "start time=" << begin / CLOCKS_PER_SEC << std::endl;

	// generateReplaceNumbers test code
	/*
	int t[2];
	std::vector<int> r;
	r.push_back(0); // digit of 0 change & generate!
	bool b;
	generateReplacedNumbers( t, 2, 0, r, &b); 
	*/

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
			combination( digitlist, digits, i, 0, c, &done);
		}
		digits++;
	}

	/* end of code */
	return 0;
}
