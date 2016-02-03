/*
 	Problem 49 - Prime permutations 
*/
#include <iostream>
#include <ctime>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>

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

bool foundSequence( std::vector<int> pp, int size, int nowi, int diff, int left)
{
	left--;
	if (left <= 0) { return true;}
	if (nowi >= size) {return false;}

	int next = pp[nowi] + diff;
	for(int i=nowi+1; i<size; i++) {
			if( pp[i]	> next) {
				return false;
			}
			if( pp[i] == next) {
				return foundSequence( pp, size, i, diff, left);
			}
	}
	return false;
}

bool hasPrimePermutations( int n[], int size, int cont)
{
	std::vector<int> pp; // permutation and also prime 
	std::sort( n, n+size);
	do {
		// code logic here
		int toi = toint( n,size);
		if( toi >= 1000 & isprime( toi)) {
			pp.push_back( toi);
		}
	} while( std::next_permutation( n, n+size));

	if( pp.size() < 4) {
		return false;
	}

	std::sort( pp.begin(), pp.begin() + pp.size()); 
	for( int i=0; i<pp.size()-2; i++)
	{
		for( int j = i+1; j< pp.size(); j++)
		{
			int diff = pp[j] - pp[i];
			if (foundSequence( pp, pp.size(), j, diff, cont-1)) {
				cout << "found. pp[i]=" << pp[i] << " pp[j]=" << pp[j] << " pp[j]+diff=" << pp[j]+diff << endl;
				return true;
			}
		}
	}


	return false; 
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

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */ 
	int n[4] = {0,0,0,1}; // start: 1000
	for(int i=0; i<9000; i++) {
		int toi = toint( n, 4);
		if( isprime( toi)) {
			int buf[4] = {0,};
			for(int j=0; j<4; j++) {
				buf[j] = n[j];
			}
			hasPrimePermutations( buf, 4, 3);
		}
		inc( n, 4);
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

