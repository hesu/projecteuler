/*
 	Problem 60 - Prime pair sets 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <string.h>
#include <algorithm>
using namespace std;

std::map<long int,long int> primes;
std::map<long int,long int> notprimes;
bool isprime( long int n)
{
	if( n == 1) return false;
	if( n == 2) return true;
	std::map<long int,long int>::iterator it;
	it = notprimes.find(n); if( it != notprimes.end()) { return false; }
	it = primes.find(n); if( it != primes.end()) { return true; }

	long int s = sqrt( n) + 1;
	for(long int i=s; i>1; i--)
	{
		if (n%i ==0) { 
			notprimes.insert( std::map<long int, long int>::value_type( n, n));
			return false;
		}
	}

	primes.insert( std::map<long int,long int>::value_type( n, n));
	return true;
}

std::map<int, vector<int>> pairmap;

class PrimePair
{
	private :
	int me;
	int a;
	int b;
	std::map<int,int> pairs;

	public:
		PrimePair(int _me, int _a, int _b) {
			me = _me;

			if (_a < _b) {
				a = _a;
				b = _b;
			} else {
				a = _b;
				b = _a;
			}

			std::map<int, vector<int>>::iterator it;
			// insert a map
			it = pairmap.find(a);
			if ( it != pairmap.end()) {
				if( std::find(it->second.begin(), it->second.end(), b) == it->second.end()) {
					it->second.push_back( b);
				}
			} else {
				std::vector<int> v(b);
				pairmap.emplace( a, v);
			}

			// insert b map
			it = pairmap.find(b);
			if ( it != pairmap.end()) {
				if( std::find(it->second.begin(), it->second.end(), a) == it->second.end()) {
					it->second.push_back( a);
				}
			} else {
				std::vector<int> v(a);
				pairmap.emplace( b, v);
			}

		}

		int getme() { return me; }
		int geta() { return a; }
		int getb() { return b; }

		void print() { cout << me << ":" << a << "," << b; }
};

/*
std::vector<std::vector<int>> canProducePrime( PrimePair& a, PrimePair&b)
//std::vector<int> canProducePrime( PrimePair& a, PrimePair&b)
{
	std::vector<std::vector<int>> pair4s;
	// TODO iterate all a.pairs && b.pair
	std::vector<int> pair4;

	std::map<int,int> aPairs = a.getPairs();
	std::map<int,int> bPairs = b.getPairs();
	
	std::map<int,int>::iterator ait = aPairs.begin();
	std::map<int,int>::iterator bit = bPairs.begin();

	for( std::map<int,int>::iterator ait = aPairs.begin(); ait != aPairs.end(); ait++) {
		int w = ait->first;
		int x = ait->second;

		for( std::map<int,int>::iterator bit = bPairs.begin(); bit != bPairs.end(); bit++) {
			int y = bit->first;
			int z = bit->second;

			char buf[1024] = {0,};
			// check wy, wz, yw, zw
			sprintf( buf, "%d%d", w,y);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", w,z);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", y,w);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", z,w);
			if( !isprime(atol(buf))) continue;

			// check xy, xz, yx, zx
			sprintf( buf, "%d%d", x,y);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", x,z);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", y,x);
			if( !isprime(atol(buf))) continue;
			sprintf( buf, "%d%d", z,x);
			if( !isprime(atol(buf))) continue;

			pair4.push_back( w);
			pair4.push_back( x);
			pair4.push_back( y);
			pair4.push_back( z);

			pair4s.push_back( pair4);
		}
	}

	return pair4s;
}

bool canProducePrimes( std::vector<int> p)
{
	for(int i=0; i<p.size()-1; i++)
	{
		for(int j=i+1; j<p.size(); j++)
		{
			if( p[i] == p[j]) return false;
			char buf[1024] = {0,};
			sprintf( buf, "%d%d", p[i],p[j]);
			if( !isprime(atol(buf))) return false;
			sprintf( buf, "%d%d", p[j],p[i]);
			if( !isprime(atol(buf))) return false;
		}
	}
	return true;
}

//int numberOfContains( std::vector<int> src, std::vector<int> compare)
std::vector<int> numberOfContains( std::vector<int> src, std::vector<int> compare)
{
	std::vector<int> r(src);
	for(int i=0; i<compare.size(); i++)
	{
		if( std::find( compare.begin(), compare.end(), src[i]) == compare.end()) {
			r.push_back( compare[i]);
		}
	}
	return r;
}

bool isPrimePairs( std::vector<int> p)
{
	for(int i=0; i<p.size()-1; i++)
	{
		for(int j=i+1; j<p.size(); j++)
		{
			if( p[i] == p[j]) { return false; }
			// make number and check whether is prime
			char buf[1024] = {0,};
			sprintf( buf, "%d%d", p[i], p[j]);
			if( !isprime( atol(buf))) return false;
			sprintf( buf, "%d%d", p[j], p[i]);
			if( !isprime( atol(buf))) return false;
		}
	}
	return true;
}
*/

std::vector<PrimePair> getPrimePairs( int p)
{
	std::vector<PrimePair> r;
	char buf[1024] = {0,};
	sprintf( buf, "%d", p);
	int len = strlen( buf);

	for(int i=0; i<len; i++)
	{
		char b1[1024] = {0,}; char b2[1024] = {0,};
		strncpy( b1, buf, i+1);
		strncpy( b2, buf+i+1, len-i);

		if( b1[0] == '0' || b2[0] == '0' | b2[0] == 0) continue;

		long int n1 = atol(b1); long int n2 = atol(b2);
		if( isprime(n1) && isprime(n2)) {

			char buf2[1024] = {0,};
			sprintf( buf2, "%ld%ld", n2, n1);
			if( isprime( atol( buf2))) {
				PrimePair newp(p, n1, n2);
				r.push_back( newp); 
			}
		}
	}
	return r;
}

#define MAX 1000000
int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	std::vector<PrimePair> pps;
	for(int i=2; i<MAX; i++)
	{
		if( isprime( i)) {
			std::vector<PrimePair> pp = getPrimePairs(i);
			pps.insert( pps.end(), pp.begin(), pp.end());
		}
	}
	cout << "pps.size())=" << pps.size() << endl;

	for(int i=0; i<pps.size(); i++)
	{
		pps[i].print();
		cout << endl;
	}

	cout << "pairmap.size()=" << pairmap.size() << endl;

	// TODO recursive?
	for( auto it = pairmap.begin(); it != pairmap.end(); it++) {
		cout << it->first << " has " << it->second.size() << " members" << endl;
		for(int i=0; i<it->second.size(); i++)
		{
			
		}
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
