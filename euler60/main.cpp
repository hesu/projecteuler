/*
 	Problem 60 - Prime pair sets 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <string.h>
#include <sstream>

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

std::map<string, bool> exclude;

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

				if( b2[0] == '0') continue;

				int n1 = atoi(b1); int n2 = atoi(b2);

				if( n1 ==0 || n2 ==0) continue;
				if( isprime(n1) && isprime(n2)) {
					
					char buf2[1024] = {0,};
					sprintf( buf2, "%d%d", n2, n1);
					if( isprime( atoi( buf2))) {
						pairs.insert( std::map<int,int>::value_type( n1, n2)); 
						exclude.insert( std::map<string,bool>::value_type( to_string(n1) + "_" + to_string(n1), true)); 
						exclude.insert( std::map<string,bool>::value_type( to_string(n2) + "_" + to_string(n2), true)); 
					}
				}
			}
		}

		bool excludes( int n)
		{
			std::map<int,int>::iterator it = pairs.begin();
			if( n < 0) { cout << "WRONG CASE n=" << n << endl; return true; }
			std::stringstream s;
			s << to_string( it->first) << "_" << to_string(n);
			
			std::map<string,bool>::iterator eit;
			eit = exclude.find( s.str()); 
			if( eit != exclude.end()) {
				return true;
			}

			// check manually and update exclude map.
			//for(;it != pairs.end(); it++) {
			char buf[1024] = {0,};
			sprintf( buf, "%d%d", it->first, n);
			if( !isprime( atoi(buf))) { 
				std::stringstream ss;
				ss << to_string( it->first) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				ss.str("");
				ss << to_string( it->second) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				return true;
			}

			sprintf( buf, "%d%d", it->second, n);
			if( !isprime( atoi(buf))) { 
				std::stringstream ss;
				ss << to_string( it->first) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				ss.str("");
				ss << to_string( it->second) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				return true;
			}

			sprintf( buf, "%d%d", n, it->first);
			if( !isprime( atoi(buf))) { 
				std::stringstream ss;
				ss << to_string( it->first) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				ss.str("");
				ss << to_string( it->second) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				return true;
			}
			sprintf( buf, "%d%d", n, it->second);
			if( !isprime( atoi(buf))) { 
				std::stringstream ss;
				ss << to_string( it->first) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				ss.str("");
				ss << to_string( it->second) << "_" << to_string(n);
				exclude.insert( std::map<string,bool>::value_type( ss.str(), true));
				return true;
			}
			return false;
		}

		bool isPrimePair() { return (pairs.size() > 0); }
		std::map<int,int> getPairs() { return pairs; }
		int getPairsSize() { return pairs.size(); }
		int getMe() { return me;}

		int getPairSum(){
			std::map<int,int>::iterator it = pairs.begin();
			return (it->first + it->second);
		}

		void print() {
			std::map<int,int>::iterator it = pairs.begin();
			cout << me << "_" << std::to_string(it->first) << ":" << std::to_string(it->second);
		}
};

bool canProduce4Primes( PrimePair& a, PrimePair&b)
{
	std::map<int,int> aPairs = a.getPairs();
	std::map<int,int> bPairs = b.getPairs();
	std::map<int,int>::iterator ait = aPairs.begin();
	std::map<int,int>::iterator bit = bPairs.begin();
	//return !( a.excludes( bit->first) || a.excludes( bit->second) || b.excludes( ait->first) || b.excludes( ait->second));

	for( std::map<int,int>::iterator ait = aPairs.begin(); ait != aPairs.end(); ait++)
	{
		for( std::map<int,int>::iterator bit = bPairs.begin(); bit != bPairs.end(); bit++)
		{
			if( !(a.excludes( bit->first)) && !(a.excludes( bit->second)) && !(b.excludes( ait->first)) && !(b.excludes( ait->second))) {
				return true;
			}
		}
	}
	return false;
}

int find5thPrime( PrimePair &a, PrimePair &b, int sumLimit)
{
//	std::map<int,int>::iterator ait = a.getPairs.begin();
//	std::map<int,int>::iterator bit = b.getPairs.begin();
	for( std::map<int,int>::iterator it = primes.begin(); it != primes.end(); it++)
	{
		//if( ait->first + ait->second + bit->first+ bit->second + it->first < sumLimit) { return -1; } 

//		if( it->first > MAX) { return -1; }

		if( a.getPairSum() + b.getPairSum() + it->first >= sumLimit) { return -1; } 
		if( !(a.excludes(it->first)) && !(b.excludes( it->first))) return (it->first);
	}
	return -1;
}

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
				pps.push_back( pp);
//				pp.print();
//				cout << endl;
			}
		}
	}
	cout << "pps.size()=" << pps.size() << endl;

	// 616667
	cout << "get canProduce4Primes 2pair prime" << endl;
	int sum = MAX * 5;
	cout << "SUM MAX=" << sum << endl;
	for(int i=0; i< pps.size()-1; i++)
	{
		for(int j=i+1; j<pps.size(); j++)
		{
			if( canProduce4Primes( pps[i], pps[j])) {
				cout << "findLastPrime with << " << pps[i].getMe() << " " << pps[j].getMe() << " exclude.size()=" << exclude.size() << endl;
				int last = find5thPrime( pps[i], pps[j], sum);
				if( last > 0) {
					sum = last + pps[i].getPairSum() + pps[j].getPairSum();
					cout << "found 5 Prime!!! " << endl;
					pps[i].print();
					cout << ", ";
					pps[j].print();
					cout << ", last prime=" << last << " sum=" << sum << endl;
					cout << endl;
				}
			}
		}
	}
	cout << "sum=" << sum << endl;
	cout << "exclude.size()=" << exclude.size() << endl;
	
//	for( std::map<string, bool>::iterator it = exclude.begin(); it != exclude.end(); it++) { cout << "exclude it->first=" << it->first << endl; }

	/*
	cout << "TEST" << endl;
	PrimePair p1( 37);
	PrimePair p2( 109673);
	cout << "37, 109673 canProduce? = " << canProduce4Primes( p1, p2) << endl;
	*/

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
