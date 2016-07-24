/*
 	Problem 99 - Largest exponential
*/

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <fstream>

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

    /*
    bool operator <=( BigInt const &rhs)
    {
      const int llen = getDigitsLen();
      const int rlen = rhs.getDigitsLen();
      if( llen != rlen) { return (llen < rlen); }
      std::vector<int> rdg = rhs.getDigits();
      for(int i=rlen-1; i>=0; i--)
      {
        if( dg[i] == rdg[i]	) { continue; }
        return (dg[i] < rdg[i]);
      }
      return true;
    }
    */
};

PrimeFactor getBigger(PrimeFactors &a, PrimeFactors &b)
{ 
  PrimeFactor big;

  std::map<int, PrimeFactor> apf = a.getpf();
  std::map<int, PrimeFactor> bpf = b.getpf();

  for( std::map<int, PrimeFactor>::iterator it = apf.begin(); it != apf.end(); it++)
  {
    PrimeFactor *p = &(it->second);
    std::map<int, PrimeFactor>::iterator bit = bpf.find( p->p);
 
   if( bit != bpf.end()) {
     PrimeFactor *bp = &(bit->second);
 //    cout << "find!() a=" << p->p << "^" << p->e << " b=" << bp->p << "^" << bp->e << endl;
     
     int small = (p->e < bp->e)? p->e : bp->e;
  //   cout << "small=" << small << endl;
     p->e -= small;
     bp->e -= small;
   }
  }
 
  // real compare with <apf & bpf>
	for( std::map<int, PrimeFactor>::iterator it = apf.begin(); it != apf.end(); it++)
	{
		PrimeFactor *p = &(it->second);
		cout << "\t" << p->p << "^" << p->e <<"*";
	}
  cout << endl;
	
  for( std::map<int, PrimeFactor>::iterator it = bpf.begin(); it != bpf.end(); it++)
	{
		PrimeFactor *p = &(it->second);
		cout << "\t" << p->p << "^" << p->e <<"*";
	}
  cout << endl;

  cout << "=================================================" << endl;


  return big;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
  ifstream inf( "p099_base_exp.txt");
  string line;

  std::vector<PrimeFactors> v;

  while( std::getline( inf, line)) {
    int p;
    int e;

    string delim = ",";
    size_t lenDelim = delim.length();
    size_t pos = 0;

    while(( pos = line.find( delim)) != std::string::npos) {
      string token = line.substr( 0, pos);
      line.erase( 0, pos + lenDelim);

      p = atoi(token.c_str());
    }
     e = atoi(line.c_str());

     PrimeFactors pf = PrimeFactors( p, e);
     v.push_back( pf);
  }
  inf.close();

  for(int i=0; i<v.size(); i++)
  {
     if( i+1 < v.size()) { 
      getBigger( v[i], v[i+1]);
     }
  }

  cout << "size=" << v.size() << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

