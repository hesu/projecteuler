/*
	 Problem 51 - Prime digit replacements 
 */
#include <iostream>
#include <ctime>
#include <map>
#include <cmath>
#include <vector>
#include <math.h>

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

#define MAX 5
// TODO
void combination( int arr[], int arrsize, int choose, int pick, std::vector<int> result)
{
	if( pick >= arrsize) return;
 
	if ( choose > 0) {
		result.push_back( arr[pick]);
	}
 
	if( result.size() >= MAX) { 
		for( std::vector<int>::iterator it = result.begin(); it != result.end(); ++it)
		{
			cout << "[" << *it << "]"; 
			if( it != result.end() -1) { cout << "-"; }
		}
		cout << endl;
		return;
	}
 
	for(int i=pick+1; i<=arrsize;i++)
	{
		combination( arr, arrsize, choose-1, i, result); 
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */

	int n[MAX] = {0,};
	n[1] = 1; // starting from 10

	while( true)
	{
		// todo digit combination just once per new digits
		int ntoi = toint( n, MAX);
		int digits = int(log10(ntoi)+1);
		//cout << "\tdigits=" << digits << endl;
		for(int i=1;i<=digits; i++)
		{
			int digitlist[MAX] = {0,};
			for(int j=0;j<digits-1; j++)
			{
				digitlist[j] = j;
			}
			std::vector<int> c;
			combination( digitlist, digits-1, i, 0, c); 
		}
		cout << "n=" << ntoi << endl;
		
		inc( n, MAX);
		if (ntoi >= 101) break;
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

