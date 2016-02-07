/*
	 Problem 53 - Combinatoric selections 
 */
#include <iostream>
#include <ctime>

#include <vector>
#include <map>
#include <cmath>

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

		unsigned long int tonumber()
		{
			unsigned long int val = 1;
			for(std::map<int, PrimeFactor>::iterator it= pf.begin(); it != pf.end(); it++)
			{
				unsigned long int powed = pow(it->first, it->second.e);
				val *= powed;
			}
			return val;
		}
};

unsigned long int get_nCr( int n, int r)
{
	std::vector<int> up;
	for(int i=1; i<=n; i++) up.push_back(i);

	std::vector<int> down;
	for(int i=1; i<= n-r; i++) down.push_back(i);
	for(int i=1; i<= r; i++) down.push_back( i);

	PrimeFactors u = PrimeFactors();
	for(int i=0; i<up.size(); i++)
	{
		PrimeFactors p = PrimeFactors( up[i], 1);
		u *= p;
	}

	PrimeFactors d = PrimeFactors();
	for(int i=0; i<down.size(); i++)
	{
		PrimeFactors p = PrimeFactors( down[i], 1);
		d *= p;
	}

	u /= d;
	return u.tonumber();
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */ 

	unsigned long int million = 1000000;
	int cnt = 0;
	for(int n=23; n<=100; n++) 
	{
		for(int r=1; r<=n; r++)
		{
			unsigned long int val = get_nCr( n, r);
			if( val > million) {
				cnt++;
			}
			cout << "getnCr! val=" << val << " n=" << n << " r=" << r << endl;
		}
	}
	cout << "cnt=" << cnt << endl;

/* TEST CODE
		cout << "5c3 val= " << get_nCr( 5, 3) << endl;
		cout << "23c10 val= " << get_nCr( 23, 10) << endl;
		*/

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

