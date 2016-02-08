/*
	 Problem 56 - Powerful digit sum 
 */
#include <iostream>
#include <ctime>

#include <vector>
#include <map>
#include <cmath>

using namespace std;

#define MAX 1000 
void multiply( int result[], int mul, int maxlen)
{
	for(int i=0; i<maxlen; i++)
	{
		//cout << "i=" << i << " carry=" << carry << endl;
		//int val = result[i] * mul;
		result[i] = result[i] * mul;
	}

	// trim
	int nextcarry = 0;
	for(int i=0; i<maxlen; i++)
	{
		int carry = nextcarry;
		nextcarry = result[i]/10;
		result[i] = result[i]%10 + carry;

		while( result[i]>=10) {
			result[i] = result[i]-10;
			nextcarry++;
		}
	}
}

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
		PrimeFactors() {}

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
			cout << endl;
		}

		int find( int p)
		{
			std::map<int,PrimeFactor>::iterator it = pf.find( p);
			if( it != pf.end()) {
				return (it->second).e;
			}
			return -1;
		}

		std::vector<int> getPrimes()
		{
			std::vector<int> r;
			for( std::map<int, PrimeFactor>::iterator it = pf.begin(); it != pf.end(); it++)
			{
				r.push_back( it->first);
			}
			return r;
		}
		
		PrimeFactor* getPrimeFactor(int p)
		{
			std::map<int, PrimeFactor>::iterator it = pf.find(p);
			if( it == pf.end()) {
				return NULL;	
			}
			return &(it->second);
		}

		int npf() { return pf.size();}
		
		void addPrimeFactor( const PrimeFactor *p)
		{
			std::map<int, PrimeFactor>::iterator it = pf.find( p->p);
			if( it != pf.end()) {
				// add to exist
				it->second.e += p->e;
			} else {
				// add new PrimeFactor
				PrimeFactor n;
				n.p = p->p;
				n.e = p->e;
				pf.insert( std::map<int,PrimeFactor>::value_type(n.p, n)); 
			}
		}
		
		void subtractPrimeFactor( const PrimeFactor *p)
		{
			std::map<int, PrimeFactor>::iterator it = pf.find( p->p);
			if( it != pf.end()) {
				it->second.e -= p->e;
			} else {
				PrimeFactor n;
				n.p = p->p;
				n.e = -(p->e);
				pf.insert( std::map<int,PrimeFactor>::value_type(n.p, n)); 
			}
		}
		
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

		PrimeFactors& operator *= ( PrimeFactors& rhs)
		{
			std::vector<int> primes = rhs.getPrimes();
			for(int i=0; i<primes.size(); i++)
			{
				PrimeFactor *p = rhs.getPrimeFactor( primes[i]);
				if( p) { addPrimeFactor( p); }
			}
			return *this;
		}

		PrimeFactors& operator /= (PrimeFactors & rhs)
		{
			std::vector<int> divPrimes = rhs.getPrimes();
			for(int i=0; i<divPrimes.size(); i++)
			{
				PrimeFactor *p = rhs.getPrimeFactor( divPrimes[i]);
				if(p) { subtractPrimeFactor( p);}
			}
			return *this;
		}

		void tonumber( int r[], int max)
		{
			r[0] = 1;
			for(std::map<int, PrimeFactor>::iterator it= pf.begin(); it != pf.end(); it++)
			{
				for(int i=1; i<=it->second.e; i++)
				{
					multiply( r, it->first, max);
				}
			}
		}
};

int get10PowerRemovedDigitSum( PrimeFactors& src) 
{
	PrimeFactor *pf2 = src.getPrimeFactor( 2); 
	PrimeFactor *pf5 = src.getPrimeFactor( 5); 

	if( pf2 && pf5) {
		int max;
		(pf2->e > pf5->e) ? (max = pf5->e) : (max = pf2->e);
		pf2->e -= max;
		pf5->e -= max;
	}

	int buf[MAX] = {0,};
	src.tonumber( buf, MAX);

	int sum = 0;
	for(int i=0; i<MAX; i++)
	{
		sum += buf[i];
	}
	return sum;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	int max = 0;
	/* starting code */
	for(int a=1; a<100; a++)
	{
		for(int b=1; b<100; b++)
		{
			PrimeFactors pf = PrimeFactors(a,b);
			int sum = get10PowerRemovedDigitSum( pf);
			if( max < sum) { 
				cout << "a=" << a << " b=" << b << " digital sum=" << sum << endl;
				pf.print();
				max = sum; 
			}
		}
	}
	cout << "max val=" << max << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

