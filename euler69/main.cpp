/*
 	Problem 47 - Distinct primes factors 
*/
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;
struct _PrimeFactor
{
	int p; // prime number
	int e; // exponent
};
typedef struct _PrimeFactor PrimeFactor;

class PrimeFactors 
{
	private: 
		std::map<int, PrimeFactor> pf;
	public:
		
		PrimeFactors(int n, int e)
		{
			while( true)
			{
				if( n <= 1) break;
				for(int i=2; i<=n; i++)
				{
					if (n%i == 0) {
						n = n/i;
						std::map<int, PrimeFactor>::iterator it = pf.find(i);
						if (it!= pf.end()) {
							(it->second.e)++;
						} else {
							PrimeFactor p;
							p.p = i;
							p.e = 1;
							pf.insert( std::map<int,PrimeFactor>::value_type(i, p));
						}
						break;
					}
				}
			}

			for( std::map<int, PrimeFactor>::iterator it = pf.begin(); it != pf.end(); it++)
			{
				PrimeFactor *p = &(it->second);
				if (e <= 1) break;
				p->e = (p->e)*(e);
			}
		}

		void print()
		{
			for( std::map<int, PrimeFactor>::iterator it = pf.begin(); it != pf.end(); it++)
			{
				PrimeFactor *p = &(it->second);
				cout << p->p << "^" << p->e <<"*";
			}
//			cout << endl;
		}

		std::vector<int> getPrimes()
		{
			std::vector<int> p;
			for( std::map<int, PrimeFactor>::iterator it = pf.begin(); it != pf.end(); it++)
			{
				p.push_back( it->first);
			}
			return p;
		}

		int find( int p)
		{
			std::map<int,PrimeFactor>::iterator it = pf.find( p);
			if( it != pf.end()) {
				return (it->second).e;
			}
			return -1;
		}

		int npf() { return pf.size();}

		bool operator == ( PrimeFactors& rhs)
		{
			if( npf() != rhs.npf()) return false;
			for( std::map<int, PrimeFactor>::iterator it = pf.begin(); it != pf.end(); it++)
			{
				PrimeFactor *p = &(it->second);
				int e = rhs.find( p->p);
				if (e == -1 || e != p->e) { return false;}
			}
			return true; 
		}
};

std::map<int, PrimeFactors> pfsMap;
int MAX = 100000;

bool hasSameDivisor( int src, int compare)
{
//	cout << "hasSameDivisor. src=" << src << " compare=" << compare << endl;
	if( src == compare || compare == 1) return true;

	// (src > compare)
  std::map<int, PrimeFactors>::iterator sit = pfsMap.find( src);
  std::map<int, PrimeFactors>::iterator cit = pfsMap.find( compare);

	std::vector<int> primes = cit->second.getPrimes();
	for(int i=0; i<primes.size(); i++)
	{
		if( sit->second.find( primes[i]) != -1) {
			return true;	
		}
	}
	return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

  for(int i=2; i<=MAX; i++)
  {
//    if( i%1000 == 0) { cout << "\ti=" << i << endl; }
		PrimeFactors p = PrimeFactors( i, 1);
	//	cout << "i=" << i << "\t\t";
	//	p.print();
	//	cout << endl;
		pfsMap.insert( std::map<int, PrimeFactors>::value_type( i, p));
  }

	cout << "get totient.." << endl;

	int max = 0;
	int maxn = 0;
	for(int i=MAX; i>=1; i--)
	{
    double t = 0;
		for(int j=i; j>=1; j--)
		{
			if( !hasSameDivisor(i, j)) {
				t++;
			}
		}
    double val = (double)i / t;
		cout << " for " << i << " totient = " << t << " totient val=" << val << endl;
    if( val > max) {
      max = val;
      maxn = i;
    }
	}

	cout << "max totient : " << max << " at number : " << maxn << endl;
	
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

