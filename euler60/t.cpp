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

std::map<int, std::map<int,bool>> exclude;

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
						std::map<int, std::map<int,bool>>::iterator it;
						std::map<int,bool>::iterator subit;
						
						it = exclude.find( n1);
						if (it == exclude.end()) {
							std::map<int,bool> data;
							data.emplace( n2, true);
							exclude.emplace( n1, data);
						} else {
							subit = it->second.find( n2);
							if (subit == it->second.end()) {
								it->second.insert( std::map<int, bool>::value_type(n2, true));
							}
						}

						it = exclude.find( n2);
						if (it == exclude.end()) {
							std::map<int,bool> data;
							data.emplace( n1, true);
							exclude.emplace( n2, data);
						} else {
							subit = it->second.find( n1);
							if (subit == it->second.end()) {
								it->second.insert( std::map<int, bool>::value_type(n1, true));
							}
						}

					}
				}
			}
		}

		bool excludes( int n)
		{
			std::map<int,int>::iterator it = pairs.begin();
			if( n < 0) { cout << "WRONG CASE n=" << n << endl; return true; }
			// TODO tweak to nested hash map
			// TODO class.pairs can be plural. so must iterate all

			std::map<int, std::map<int,bool>>::iterator eit;
			eit = exclude.find( me);

			if( eit != exclude.end()) {
				std::map<int,bool>::iterator it;
				it = eit->second.find( n);
				if( it != eit->second.end()) {
					return true;
				}
			}

			// check manually and update exclude map.
			char buf[1024] = {0,};
			sprintf( buf, "%d%d", it->first, n);
			if( !isprime( atoi(buf))) { 
				std::map<int,bool> data;
				data.emplace( n, true);
				exclude.emplace( me, data);
				std::map<int,bool> data2;
				data2.emplace( me, true);
				exclude.emplace( n, data2);
				return true;
			}

			sprintf( buf, "%d%d", it->second, n);
			if( !isprime( atoi(buf))) { 
				std::map<int,bool> data;
				data.emplace( n, true);
				exclude.emplace( me, data);
				std::map<int,bool> data2;
				data2.emplace( me, true);
				exclude.emplace( n, data2);
				return true;
			}

			sprintf( buf, "%d%d", n, it->first);
			if( !isprime( atoi(buf))) { 
				std::map<int,bool> data;
				data.emplace( n, true);
				exclude.emplace( me, data);
				std::map<int,bool> data2;
				data2.emplace( me, true);
				exclude.emplace( n, data2);
				return true;
			}
			sprintf( buf, "%d%d", n, it->second);
			if( !isprime( atoi(buf))) { 
				std::map<int,bool> data;
				data.emplace( n, true);
				exclude.emplace( me, data);
				std::map<int,bool> data2;
				data2.emplace( me, true);
				exclude.emplace( n, data2);
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

bool notExclusive( PrimePair p, std::vector<int> others)
{
	for(int i=0; i<others.size(); i++)
	{
		if( p.excludes(others[i])) return false;
	}
	return true;
}

void combination( int arr[], int arrsize, int choose, int nowi, std::vector<int> result, bool* done)
{
/*	cout << "combination. c=" << choose << "\tnp=" << arr[nowi] << "\tni=" << nowi << "\t";
	for(int i=0; i<result.size(); i++)
	{
		cout << result[i] << "-";
	}
	cout << endl;
	*/

	if( choose <= 0 || nowi >= arrsize-1) {
		/* do something here */
		cout << "done! result.size()=" << result.size() << " result[0]=" << result[0] << "  nowip=" << arr[nowi] << endl;
		if( result.size() == 5 && isPrimePair(result)) {
			cout << "found PrimePair!!!" << endl;
			int sum = 0;
			for(int i=0; i<result.size(); i++)
			{
				cout << result[i] << " ";
				sum += result[i];
			}
			cout << " sum=" << sum << endl;
		}

		/**/
		*done = true;
		return;
	}

	bool d = false;
	for(int i=nowi; i<arrsize;i++)
	{
		std::vector<int> r(result);
		PrimePair pi( arr[nowi]);
		if( notExclusive( pi, r)) {
			r.push_back( arr[nowi]);
			combination( arr, arrsize, choose-1, i+1,r, &d);
		} else {
//			cout << "exclusive pi=" << pi.getMe() << " with r : ";
//			for(int i=0; i<result.size(); i++) { cout << result[i] << "-"; } cout << endl;
			continue;
		}
	}

	*done = true;
	return;
}


int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	int primesArr[60000] = {0,};
	int nprime = 0;
	for(int i=3;; i++)
	{
		if( nprime >= 60000) break;
		if( isprime( i)) {
			primesArr[nprime] = i;
			nprime++;
		}
	}
	cout << "primes.size()=" << primes.size() << endl;

//	for(int i=0; i<nprime; i++) { cout << "primesArr[" << i << "] = " << primesArr[i] << endl;}
	for(int i=0; i<=primes.size()-5; i++)
	{
		cout << "comb at=" << i << endl;
		std::vector<int> c;
		bool done = false;
		while( !done) {
			combination( primesArr, 60000-6, 5, i, c, &done);
		}
	}

/*
	cout << "TEST" << endl;
	PrimePair p1( 37);
	PrimePair p2( 109673);
	cout << "exclude? =" << p1.excludes( 109673) << endl;
	cout << "exclude? =" << p2.excludes( 37) << endl;
//	cout << "37, 109673 canProduce? = " << canProduce4Primes( p1, p2) << endl;
*/
	
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
