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
					
					char buf2[1024] = {0,};
					sprintf( buf2, "%d%d", n2, n1);
					if( isprime( atoi( buf2))) {
						pairs.insert( std::map<int,int>::value_type( n1, n2)); 
					}
				}

			}
		}

		bool isPrimePair() { return (pairs.size() > 0); }
		std::map<int,int> getPairs() { return pairs; }
		int getPairsSize() { return pairs.size(); }

		void print() {
			std::map<int,int>::iterator it = pairs.begin();
			cout << me << "_" << std::to_string(it->first) << ":" << std::to_string(it->second);
		}
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

bool canProducePrime( PrimePair& a, PrimePair&b)
{
	std::map<int,int> aPairs = a.getPairs();
	std::map<int,int> bPairs = b.getPairs();
	
	std::map<int,int>::iterator ait = aPairs.begin();
	std::map<int,int>::iterator bit = bPairs.begin();

	int w = ait->first;
	int x = ait->second;

	int y = bit->first;
	int z = bit->second;

	char buf[1024] = {0,};
	// check wy, wz, yw, zw
	sprintf( buf, "%d%d", w,y);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", w,z);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", y,w);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", z,w);
	if( !isprime(atoi(buf))) return false;

	// check xy, xz, yx, zx
	sprintf( buf, "%d%d", x,y);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", x,z);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", y,x);
	if( !isprime(atoi(buf))) return false;
	sprintf( buf, "%d%d", z,x);
	if( !isprime(atoi(buf))) return false;

	return true;
}

#define MAX 100000
int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	std::vector<PrimePair> pps;
	for(int i=2; i<MAX; i++)
	{
		if( isprime( i)) {
			PrimePair pp(i);
			int pairsSize = pp.getPairsSize();
			if (pp.isPrimePair()) {
//				cout << "i=" << i << " pairs size=" << pairsSize << endl;
				pps.push_back( pp);
			}
		}
	}

	int cnt = 0;
	for(int i=0; i< pps.size()-1; i++)
	{
		for(int j=i+1; j<pps.size(); j++)
		{
			if( canProducePrime( pps[i], pps[j])) {
				cout << "4 Prime!!!" << endl;
				pps[i].print();
				cout << ", ";
				pps[j].print();
				cout << endl;
				cnt++;
			}
		}
	}

	cout << "cnt=" << cnt << endl;

	cout << "pps.size()=" << pps.size() << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
