/*
 	Problem 73 - Counting fractions in a range
*/

#include <iostream>
#include <ctime>

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
};

// using Stern-Brocot Tree
int countingFractions( Fraction left, Fraction right, int maxd)
{
  if ((left.d + right.d) > maxd) { return 0; }

  Fraction next = Fraction( left.n + right.n, left.d + right.d);
  return 1 + countingFractions( left, next, maxd) + countingFractions( next, right, maxd);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  int maxd = 12000;
  Fraction left(1,3);
  Fraction right(1,2);
  int howmany = countingFractions( left, right, maxd);
  cout << "howmany=" << howmany << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
