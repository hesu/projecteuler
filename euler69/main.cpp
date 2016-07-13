/*
 	Problem 69 - Totient maximum
*/
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
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
		
    std::map<int, PrimeFactor> getpf()
		{
      return pf;
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

int MAX = 1000000;
//int MAX = 10;

int getTotient( PrimeFactors p)
{
  int n = 1;
  std::map<int, PrimeFactor> m = p.getpf();
	for( std::map<int, PrimeFactor>::iterator it = m.begin(); it != m.end(); it++)
	{
		PrimeFactor *p = &(it->second);
    n = n * ( pow( p->p, p->e) - pow( p->p, (p->e -1)));
	}

  return n;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	float max = 0;
	int maxn = 0;
  
  for(int i=2; i<=MAX; i++)
  {
    if( i%10000==0) { cout << "i=" << i << endl; }
		PrimeFactors p = PrimeFactors( i, 1);
    
    int totient = getTotient( p);
    float val = i / ((float)totient);
    if (max < val) {
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

