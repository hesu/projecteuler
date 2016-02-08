/*
	 Problem 56 - Powerful digit sum 
 */
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

class BigInt
{
	private:
		std::vector<int> dg; // digit
	public:
		BigInt( int n) 
		{
			char buf[100] = {0,};
			sprintf( buf, "%d", n);
			int len = strlen( buf);
			for(int i=len-1; i>=0; i--)
			{
				dg.push_back( buf[i]-'0');
			}
		}

		std::vector<int> getDigits() { return dg; }

		void print()
		{
			for(int i=dg.size()-1; i>=0; i--)
			{
				cout << dg[i];
			}
			cout << endl;
		}

		void multiply(int m)
		{
			for(int i=0; i<dg.size(); i++) { dg[i] *= m; }

			int nextCarry = 0;
			for(int i=0; i<dg.size(); i++)
			{
				dg[i] += nextCarry;
				nextCarry = 0;
				while( dg[i] >= 10) {
					dg[i] -= 10;
					nextCarry++;
				}
			}

			while( nextCarry > 0) {
				if( nextCarry > 10) {
					dg.push_back( nextCarry%10);
					nextCarry /=10;	
				} else {
					dg.push_back( nextCarry);
					nextCarry = 0;
				}
			}
		}
};


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

		BigInt tonumber()
		{
			BigInt r = BigInt(1);
			for(std::map<int, PrimeFactor>::iterator it= pf.begin(); it != pf.end(); it++)
			{
				for(int i=1; i<=it->second.e; i++)
				{
					r.multiply( it->first);
				}
			}
			return r;
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

	BigInt r = src.tonumber();
	int sum = 0;
	std::vector<int> dg = r.getDigits();
	for(int i=0; i<dg.size(); i++)
	{
		sum += dg[i];
	}
	return sum;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	int max = 0;
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
