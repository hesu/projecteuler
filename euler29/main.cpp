/*
 	Problem 29 - Distinct powers
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

		int npf() { return pf.size();}

		// operator == 정의하고..
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

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

	std::vector<PrimeFactors> pfs;
	int SCOPE = 100;
	
	for(int a=2; a<=SCOPE; a++)
	{
		for(int b=2; b<=SCOPE; b++)
		{
			cout << "a=" << a << " ,b=" << b << endl;
			PrimeFactors pf = PrimeFactors( a, b);
			bool find = false;
			for(int i=0; i<pfs.size(); i++)
			{
				PrimeFactors compare = pfs[i];
				if (compare == pf) {
					find = true;
					break;
				}
			}

			if (!find) {
				pfs.push_back( pf);
				cout << "NEW   : ";
				pf.print();
			}else {
				cout << "EXIST : ";
				pf.print();
				
			};
		}
	}

	cout << "ditinct powers = " << pfs.size() << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

