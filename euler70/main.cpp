/*
 	Problem 70 - Totient permutation
*/

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cmath>
#include <string.h>

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

unsigned int MAX = 10000000;

unsigned int getTotient( PrimeFactors p)
{
  unsigned int n = 1;
  std::map<int, PrimeFactor> m = p.getpf();
	for( std::map<int, PrimeFactor>::iterator it = m.begin(); it != m.end(); it++)
	{
		PrimeFactor *p = &(it->second);
    n = n * ( pow( p->p, p->e) - pow( p->p, (p->e -1)));
	}
  return n;
}

bool hasSameDigit( unsigned int a, unsigned int b)
{
  int achar[10] = {0,};
  int bchar[10] = {0,};

  char abuf[1000] = {0,};
  sprintf( abuf, "%d", a);
  for(int i=0; i<strlen(abuf); i++) achar[ abuf[i] - '0']++;
  
  char bbuf[1000] = {0,};
  sprintf( bbuf, "%d", b);
  for(int i=0; i<strlen(bbuf); i++) bchar[ bbuf[i] - '0']++;


  // compare
  for(int i=0; i<10; i++)
  {
    if( achar[i] != bchar[i]) return false;
  }
  return true;
}

bool isPandigital( char arr[])
{
	if (strlen(arr) != 10) { return false; }

	bool swit[10] = {false,};
	for(int i=0; i<10; i++)
	{
		int idx = arr[i] - '0';
		if (swit[idx] == true) { return false; }
		else { swit[idx] = true; }
	}

	for(int i=0; i<10; i++)
	{
		if( swit[i] == false) {return false; }
	}
	return true;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

  float min = 2 / (float)getTotient( PrimeFactors(2, 1));
	int minn= 2;
  
  for(unsigned int i=2; i<MAX; i++)
  {
    if( i%10000==0) { cout << "i=" << i << endl; }
		PrimeFactors p = PrimeFactors( i, 1);
    
    unsigned int totient = getTotient( p);

    if( hasSameDigit( totient, i)) {
      float val = i / ((float)totient);
      if (min > val) {
        cout << "totient=" << totient << " i=" << i << " ratio=" << val << endl;
        min= val;
        minn= i;
      }
    }
  }

	cout << "min totient : " << min << " at number : " << minn << endl;
	
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

