/*
 	Problem 60 - Prime pair sets 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <string.h>
using namespace std;

std::map<int,int> primes;
std::map<int,int> notprimes;
bool isprime( int n)
{
	if( n == 1) return false;
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

class PrimePair
{
	private :
	int me;
	std::map<int,int> pairs;

	public:
		PrimePair(int n) { 
			me = n; 
			char buf[1000] = {0,};
			sprintf( buf, "%d", me);
			int len = strlen( buf);

			for(int i=0; i<len; i++)
			{
				char b1[1000] = {0,}; char b2[1000] = {0,};
				strncpy( b1, buf, i+1);
				strncpy( b2, buf+i+1, len-i);

				if( b2[0] == 0) continue;

				int n1 = atoi(b1); int n2 = atoi(b2);
				if( isprime(n1) && isprime(n2)) {
					pairs.insert( std::map<int,int>::value_type( n1, n2)); 
				}

			}
		}

		bool isPrimePair() { return (pairs.size() > 0); }
		std::map<int,int> getPairs() { return pairs; }
		int getPairsSize() { return pairs.size(); }
};

int reverseComb(int a, int b)
{
	char buf[1024] = {0,};
	sprintf( buf, "%d%d", b, a);
	return atoi( buf);
}

bool canReversePrimePair( PrimePair& p) 
{
	std::map<int,int> pairs = p.getPairs();
	for(std::map<int,int>::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		if( isprime( reverseComb( it->first, it->second))) { return true; }
	}
	return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	std::vector<PrimePair> splittable;
	for(int i=2; i<100000; i++)
	{
		if( isprime( i)) {
			PrimePair pp(i);
			int pairsSize = pp.getPairsSize();
			if (pp.isPrimePair()) {
//				cout << "i=" << i << " pairs size=" << pairsSize << endl;
				splittable.push_back( pp);
			}
		}
	}

//	cout << "primes.size()=" << primes.size() << endl;
	std::vector<PrimePair> splittable_reversed;
	for(int i=0; i<splittable.size(); i++)
	{
		if( canReversePrimePair( splittable[i])) { 
			splittable_reversed.push_back( splittable[i]);
		}
	}

	cout << "splittable_reversed.size()=" << splittable_reversed.size() << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
