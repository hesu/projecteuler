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

// using Stern-Brocot Tree
Fraction getLeftNeighbor( Fraction that, int depth)
{
  std::vector<Fraction> start;
  start.push_back( Fraction( 0, 1));
  start.push_back( Fraction( 1, 1));
 
  Fraction left(0, 0);
  for(int i=1; i<depth; i++)
  {
    if( i <= that.d) {
      cout << "i=============== " << i << endl;
      std::vector<Fraction> next;
      for(int j=0; j<start.size(); j++)
      {
        next.push_back( start[j]);
        if( j < start.size()-1) {
          Fraction f( start[j].n + start[j+1].n, start[j].d + start[j+1].d);
          next.push_back( f);
        }
      }
     start = next;
      for(int j=0; j<start.size(); j++){ cout << start[j].n << "/" << start[j].d << endl; }
    } else if( i == that.d+1) {
      cout << "i=============== " << i << endl;
      for(int j=0; j<start.size(); j++){ cout << start[j].n << "/" << start[j].d << endl; }
      for(int j=0; j<start.size(); j++){ 
        //cout << start[j].n << "/" << start[j].d << endl; 
        if( start[j].n == that.n && start[j].d == that.d) {
          left.n = start[j-1].n;
          left.d = start[j-1].d;
          break;
        }
      }
    } else {
      // just find
      left.n = left.n + that.n;
      left.d = left.d + that.d;
    }
  }
  return left;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
  int MAX = 1000000;

  Fraction crit( 3, 7);
  Fraction ret = getLeftNeighbor( crit, 8);

  cout << "left neighbor : " << ret.n << "/" << ret.d << endl;
  cout << "numerator : " << ret.n << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}


