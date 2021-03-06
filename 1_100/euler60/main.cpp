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

std::map<unsigned long int,unsigned long int> primes;
std::map<unsigned long int,unsigned long int> notprimes;
bool isprime( unsigned long int n)
{
	if( n == 1) return false;
	if( n == 2) return true;
	std::map<unsigned long int,unsigned long int>::iterator it;
	it = notprimes.find(n); if( it != notprimes.end()) { return false; }
	it = primes.find(n); if( it != primes.end()) { return true; }

	unsigned long int s = sqrt( n) + 1;
	for(unsigned long int i=s; i>1; i--)
	{
		if (n%i ==0) { 
			notprimes.insert( std::map<unsigned long int, unsigned long int>::value_type( n, n));
			return false;
		}
	}

	primes.insert( std::map<unsigned long int,unsigned long int>::value_type( n, n));
	return true;
}

std::map<unsigned long int, vector<unsigned long int>> pairmap;

class PrimePair
{
	private :
	unsigned long int me;
	unsigned long int a;
	unsigned long int b;
	bool is;

	public:
		PrimePair(unsigned long int _me, unsigned long int _a, unsigned long int _b) {
			me = _me;
			is = true;

			if (_a < _b) {
				a = _a;
				b = _b;
			} else {
				a = _b;
				b = _a;
			}

			std::map<unsigned long int, vector<unsigned long int>>::iterator it;
			// insert a map
			it = pairmap.find(a);
			if ( it != pairmap.end()) {
				if( std::find(it->second.begin(), it->second.end(), b) == it->second.end()) {
					it->second.push_back( b);
				}
			} else {
				std::vector<unsigned long int> v; v.push_back(b);
				pairmap.emplace( a, v);
			}

			// insert b map
			it = pairmap.find(b);
			if ( it != pairmap.end()) {
				if( std::find(it->second.begin(), it->second.end(), a) == it->second.end()) {
					it->second.push_back( a);
				}
			} else {
				std::vector<unsigned long int> v; v.push_back(a);
				pairmap.emplace( b, v);
			}

		}

		unsigned long int getme() { return me; }
		unsigned long int geta() { return a; }
		unsigned long int getb() { return b; }
		bool getis() { return is; }

		void print() { cout << me << ":" << a << "," << b; }
};

std::vector<PrimePair> getPrimePairs( unsigned long int p)
{
	std::vector<PrimePair> r;
	char buf[1024] = {0,};
	sprintf( buf, "%ld", p);
	int len = strlen( buf);

	for(int i=0; i<len; i++)
	{
		char b1[1024] = {0,}; char b2[1024] = {0,};
		strncpy( b1, buf, i+1);
		strncpy( b2, buf+i+1, len-i);

		if( b1[0] == '0' || b2[0] == '0' | b2[0] == 0) continue;

		unsigned long int n1 = atol(b1); unsigned long int n2 = atol(b2);
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

long int minsum = -1;

void combination( std::vector<unsigned long int> src, int choose, int nowi, std::vector<unsigned long int> result)
{
	if( choose <= 0) {
		// DONE
		unsigned long int sum = 0;
		for(int i=0; i< result.size(); i++)
		{
			sum += result[i];
		}

		if( minsum == -1 || sum < minsum) { 
			minsum = sum;
			for(int i=0; i<result.size(); i++)
			{
				cout << result[i] << " ";
			}
			cout << " minsum : " << minsum << endl;
		}
		return;
	}

	for(int i=nowi; i<src.size(); i++)
	{
		std::vector<unsigned long int> r(result);

		bool keepgo = true;
		for(unsigned long int j=0; j<r.size(); j++)
		{
			std::map<unsigned long int, vector<unsigned long int>>::iterator it;
			it = pairmap.find(r[j]);
			if( it == pairmap.end()) { keepgo = false; break; }

			if( std::find(it->second.begin(), it->second.end(), src[i]) == it->second.end()) {
					char str[1024] = {0,};
					sprintf( str, "%ld%ld", src[i], r[j]); 
					if( isprime( atol(str))) {
						char str2[1024] = {0,};
						sprintf( str2, "%ld%ld", r[j], src[i]);
						if( isprime( atol(str2))) {
							keepgo = true;
						} else {
							keepgo = false; break;
						}
					} else {
						keepgo = false; break;
					}
			}

		}

		if( keepgo) {
			// insert a map
			r.push_back( src[i]);
			if( src[i] == 0) { cout << "i=" << i << " src[i]=" << src[i] << endl; }
			combination( src, choose-1, i+1, r);
		}
	}
	return;
}

#define PICK 5
#define MAX 400000
int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	cout << "MAX=" << MAX << endl;
	std::vector<PrimePair> pps;
	for(unsigned long int i=3; i<MAX; i++)
	{
		if( isprime( i)) {
			std::vector<PrimePair> pp = getPrimePairs(i);
			pps.insert( pps.end(), pp.begin(), pp.end());
		}
	}
	cout << "primes.size())=" << primes.size() << endl;
	cout << "pps.size())=" << pps.size() << endl;
	cout << "pairmap.size()=" << pairmap.size() << endl;

	for( auto it = pairmap.begin(); it != pairmap.end(); it++) {
			std::vector<unsigned long int> r;
			r.push_back( it->first);
			combination( it->second, PICK-1, 0, r);
	}

	cout << "answer minsum = " << minsum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
