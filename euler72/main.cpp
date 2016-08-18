/*
 	Problem 72 - Counting fractions
*/

#include <iostream>
#include <ctime>

using namespace std;

class Fraction
{
  public :
  unsigned long long int n;
  unsigned long long int d;
		
  Fraction( unsigned long long int nu, unsigned long long int de)
  {
    n = nu;
    d = de;
  }
};

// using Stern-Brocot Tree
unsigned long long int countingFractions( Fraction left, Fraction right, unsigned long long int maxd)
{
  if ((left.d + right.d) > maxd) { return 0; }

  Fraction next = Fraction( left.n + right.n, left.d + right.d);
  return 1 + countingFractions( left, next, maxd) + countingFractions( next, right, maxd);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  unsigned long long int maxd = 100000;
  Fraction left(0,1);
  Fraction right(1,1);
  unsigned long long int howmany = countingFractions( left, right, maxd);
  cout << "howmany=" << howmany << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
