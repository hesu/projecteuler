/*
 	Problem 72 - Counting fractions
*/

// 마지막 depth 를 어떻게 구하느냐 인것 같은데..

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Fraction
{
  public :
  unsigned int n;
  unsigned int d;
		
  Fraction( unsigned int nu, unsigned int de)
  {
    n = nu;
    d = de;
  }
};

// using Stern-Brocot Tree
unsigned int countingFractions( std::vector<Fraction> v, unsigned int maxd)
{
  int depth = 0;
  
  std::vector<Fraction> newv;

while( depth < maxd) {

  int vsize = v.size();
  for(int i=0; i<vsize; i++)
  {
    if( i == 0 || i == vsize-1) {
      newv.push_back( v[i]);
    } else {
      Fraction f( v[i].n + v[i+1].n , v[i].d + v[i+1].d);
      newv.push_back(f);
    }
  }
  depth++;
}

}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  unsigned int maxd = 1000000;
 
  Fraction left(0,1);
  Fraction right(1,1);
  
  std::vector<Fraction> f;
  f.push_back( left);
  f.push_back( right);
  
  unsigned int howmany = countingFractions( f, maxd);
  cout << "howmany=" << howmany << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
