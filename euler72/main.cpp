/*
 	Problem 72 - Counting fractions
*/

// 마지막 depth 를 어떻게 구하느냐 인것 같은데..

#include <iostream>
#include <ctime>
#include <vector>

#include <math.h>

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

int findFirstTreeDepth( Fraction left, Fraction right, int maxd)
{
  int depth = 0;
  Fraction ans = Fraction( left.n + right.n, left.d + right.d);

  while( ans.d < maxd) {
    if( depth %2 == 0) {
      left.n = ans.n; left.d = ans.d;
    } else {
      right.n = ans.n; right.d = ans.d;
    }

    ans.n = left.n + right.n; ans.d = left.d + right.d;
    if( ans.d > maxd) { break; }
    depth++;
  }

  cout << "tree depth=" << depth << " (next) ans=" << ans.n << "/" << ans.d << endl;
  return depth;
}

// using Stern-Brocot Tree
unsigned int countingFractions( std::vector<Fraction> v, unsigned int maxd)
{
  unsigned int depth = 0;
  
  std::vector<Fraction> thisturn_new;
  std::vector<Fraction> newv;

  bool findmaxd = false;
  while( !findmaxd) {

    int vsize = v.size();
    for(int i=0; i<vsize; i++)
    {
      newv.push_back( v[i]);
      
      if( i < (vsize-1)) {
        Fraction f( v[i].n + v[i+1].n , v[i].d + v[i+1].d);
        thisturn_new.push_back(f);
        newv.push_back(f);
      }
      
    }

  //  cout << "tree depth=" << depth << " thisturn_new.size()=" << thisturn_new.size() << endl;

    bool all_over = true;
    for(int i=0; i<thisturn_new.size(); i++) {
      if( thisturn_new[i].d >= maxd) { 
        cout << "found!" << endl; all_over = false; 
        break; 
      }
    }
    if( all_over == false) { findmaxd = true; continue;}

    depth++;
//    if( depth % 1000 == 0) { cout << "depth=" << depth << " thisturn_new.size() " << thisturn_new.size() << endl; }

    v = newv;

    newv.clear();
    thisturn_new.clear();
  }

  cout << "depth=" << depth << " vector.size()=" << v.size() << endl;
  
  int sum=0;
  for(int i=0; i<v.size(); i++)
  {
    if( v[i].d <= maxd) {
      cout << v[i].n << "/" << v[i].d <<  " ";
      sum++;
    }
  }
  cout << endl;

  return sum - 2;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  unsigned int maxd = 1000000;
  //unsigned int maxd = 8;
 
  Fraction left(0,1);
  Fraction right(1,1);
  
  std::vector<Fraction> f;
  f.push_back( left);
  f.push_back( right);
  
//  unsigned int howmany = countingFractions( f, maxd);
  //cout << "howmany=" << howmany << endl;

  unsigned int depth = findFirstTreeDepth( left, right, maxd);
  cout << "depth=" << depth << endl;


  int sum=0;
  for(int i=0; i<=depth; i++)
  {
    sum += pow( 2, i);
  }
  cout << "sum=" << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
