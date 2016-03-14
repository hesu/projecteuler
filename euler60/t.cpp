/*
 	Problem 60 - Prime pair sets 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <string.h>

#define MAX 1000000

using namespace std;

std::map<int,int> primes;
std::map<int,int> notprimes;
bool isprime( int n)
{
	if( n <= 1) return false;
	if( n == 2) return true;
	std::map<int,int>::iterator it;
	it = notprimes.find(n); if( it != notprimes.end()) { return false; }
	it = primes.find(n); if( it != primes.end()) { return true; }

	int s = sqrt( n) + 1;
	for(int i=s; i>1; i--)
	{
		if (n%i ==0) { 
			notprimes.insert( std::map<int,int>::value_type( n, n));
			return false;
		}
	}

	primes.insert( std::map<int,int>::value_type( n, n));
	return true;
}

bool isPrimePair( std::vector<int> p)
{
	for(int i=0; i<p.size(); i++)
	{
		for(int j=0; j<p.size(); j++)
		{
			if( i != j) {
				// make number and check whether is prime
				char buf[1024] = {0,};
				sprintf( buf, "%d%d", p[i], p[j]);
				if( !isprime( atoi(buf))) return false;
				sprintf( buf, "%d%d", p[j], p[i]);
				if( !isprime( atoi(buf))) return false;
			}
		}
	}
	return true;
}

void combination( int arr[], int arrsize, int choose, int nowi, std::vector<int> result, bool* done)
{
	if( choose <= 0 ) {
		/* do something here */
		cout << "done! result.size()=" << result.size() << " choose=" << choose << endl;
	
		// printing start
		for(int i=0; i<result.size(); i++) { 
			cout << result[i];
			if( i != result.size()-1) { cout << "-"; }
		}
		cout << endl;
		// printing end

		if( isPrimePair(result)) {
			cout << "found PrimePair!!!" << endl;
			int sum = 0;
			for(int i=0; i<result.size(); i++)
			{
				cout << result[i] << " ";
				sum += result[i];
			}
			cout << " sum=" << sum << endl;
		}

		/* do something here done */
		*done = true;
		return;
	}

	bool d = false;
	if( !(d)) {
		for(int i=nowi; i<arrsize;i++)
		{
			std::vector<int> r(result);
			r.push_back(i);
			combination( arr, arrsize, choose-1, i+1,r, &d);
		}
	}
	*done = true;
	return;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	/*
	std::vector<int> pvec;
	pvec.push_back( 19);
	pvec.push_back( 7);
	pvec.push_back( 4507);
	pvec.push_back( 97);
	pvec.push_back( 612037);
	cout << "isPrimePair?=" << isPrimePair( pvec) << endl;
	*/

#define MAXPRIMES 11
	int primesArr[MAXPRIMES] = {0,};
	int nprime = 0;
	for(int i=2;; i++)
	{
		if( nprime >= MAXPRIMES) break;
		if( isprime( i)) {
			primesArr[nprime] = i;
			nprime++;
		}
	}
	cout << "primes.size()=" << primes.size() << endl;

	for(int i=0; i<=primes.size()-5; i++)
	{
		cout << "comb at=" << i << endl;
		std::vector<int> c;
		bool done = false;
		while( !done) {
			combination( primesArr, MAXPRIMES, 5, i, c, &done);
		}
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
