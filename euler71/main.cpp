/*
 	Problem 71 - Ordered fractions
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

int gcd( int a, int b)
{
  while( b != 0)
  {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
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

    std::map<int, PrimeFactor> getpf() { return pf; }

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

    bool areRelativePrimes( PrimeFactors& compare)
    {
      std::vector<int> v = compare.getPrimes();
      for(int i=0; i<v.size(); i++)
      {
        if( find( v[i]) != -1) return false;
      }
      return true;
    }
};


class Fraction
{
  public :
  int n;
  int d;
		
  Fraction( int nu, int de)
  {
    n = nu;
    d = de;
  }

		
  Fraction reduce()
  {
    int gcd_this = gcd( n, d);
    int nu = n / gcd_this;
    int de = d / gcd_this;
    Fraction f = Fraction( nu, de);
    return f;
  }

};

bool areRelativePrimes( int d, int n)
{
  PrimeFactors pfd( d, 1);
  PrimeFactors pfn( n, 1);
  return pfd.areRelativePrimes( pfn);
}

// 1) fraction map function
std::vector<Fraction> reducedProperFractions(int d)
{
  // get reduced Proper Fractions which denominator is 'd'
  std::vector<Fraction> v;

  for(int i=1; i<d; i++)
  {
    /*
    if( areRelativePrimes( d, i)) {
      Fraction f( i, d);
      v.push_back( f);
    }
    */

    int gcd_this = gcd( d, i);
    if( gcd_this == 1) {
      Fraction f( i, d);
      v.push_back( f);
    }
  }
//  cout << "d=" << d << " v.size()=" << v.size() << endl;
  return v;
}

// 2) numerator to 1 -> sorting function
struct ascendSort 
{
  inline bool operator() (const Fraction& a, const Fraction& b)
  {
    double ad = (double)a.d / (double)a.n;
    double bd = (double)b.d / (double)b.n;

    return (ad > bd);
  }
};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

  int MAX = 1000000;
  std::vector<Fraction> rpf;
  for(int i=2; i<=MAX; i++)
  {
    if( i % 100 == 0) { cout << "i=" << i << endl; }
    std::vector<Fraction> v = reducedProperFractions( i);
    rpf.insert( rpf.end(), v.begin(), v.end());
  }

  cout << "rpf.size()=" << rpf.size() << endl;

  cout << "try to sort.." << endl;
  std::sort( rpf.begin(), rpf.end(), ascendSort());

  for(int i=0; i<rpf.size(); i++)
  {
//    cout << rpf[i].n << "/" << rpf[i].d << endl;
    if(rpf[i].n == 3 && rpf[i].d == 7) {
      cout << "find! " << rpf[i-1].n << "/" << rpf[i-1].d << endl;
      break;
    }
  }

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}


