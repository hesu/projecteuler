/*
 	Problem 73 - Counting fractions in a range
*/

// idea : stern-brocot 트리로 모든 유리수를 셀 수 있으므로 depth 1~12000까지 1/3 과 1/2 사이의 depth 별 tree leaf 들을 모두 세면 되지 않을까..? 
	
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

int sum = 0;

/* using Stern-Brocot Tree
Fraction getLeftNeighbor( Fraction that, Fraction leftbound, int depth)
{
  Fraction answer = Fraction( that.n + leftbound.n, that.d + leftbound.d);

  while(true)
  {
    if (answer.d + that.d > depth) break;
    answer.d += that.d;
    answer.n += that.n;
  }
  return answer;
}
*/

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
  
  /*
  int MAX = 1000000;

  Fraction crit( 3, 7);
  Fraction leftbound( 2, 5);
  Fraction ret = getLeftNeighbor( crit, leftbound, MAX);

  cout << "left neighbor : " << ret.n << "/" << ret.d << endl;
  cout << "numerator : " << ret.n << endl;
  cout << "gcd: " << gcd( ret.n, ret.d) << endl;
  */

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
