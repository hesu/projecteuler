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

// 1) fraction map function
std::vector<Fraction> reducedProperFractions(int d)
{
  // get reduced Proper Fractions which denominator is 'd'
  std::vector<Fraction> v;

  for(int i=1; i<d; i++)
  {
    int gcd_this = gcd( d, i);
    if( gcd_this == 1) {
      Fraction f( i, d);
      v.push_back( f);
    }
  }
  return v;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

  int MAX = 1000000;
  std::vector<Fraction> rpf;

  Fraction comp( 3, 7);
  double compval = double(7)/double(3);
  double mindiff = compval;

  int n;
  int d;

  for(int i=2; i<=MAX; i++)
  {
    if( i%10000 == 0) { cout << "i=" << i << endl; }
    for(int j=1; j<i; j++)
    {
//      cout << "done" << endl;
      double val = double(i) / double( j);

//      cout << "val=" << val << " denominator=" << i << " numerator=" << n << endl;
      if( val <= compval) break;

      int gcd_this = gcd( j, i);
      if( gcd_this == 1) {
        double diff = val - compval;
      //  cout << "diff=" << diff << " val=" << val << " compval=" << compval << endl;
        if( diff < mindiff) {
          mindiff = diff;
          n = i;
          d = j;

      //    cout << n << "/" << d << " mindiff=" << mindiff << endl;
        }
      }

    }
  }

  cout << "n=" << n << " d=" << d << endl;

  /*
  for(int i=2; i<=MAX; i++)
  {
    if( i % 100 == 0) { cout << "i=" << i << endl; }
    std::vector<Fraction> v = reducedProperFractions( i);
    rpf.insert( rpf.end(), v.begin(), v.end());
  }
  */


	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}


