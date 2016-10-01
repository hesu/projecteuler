/*
  Problem 80 - Square root digital expansion
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX 100

class AfterDecimal; 
{
  public:
    Small( int _e, int _n)
    {
      e = _e; n = _n;
    }

  private:
  int e; // minus
  int n;
};

std::vector<int> digital_expansion( double n, int max)
{
  std::vector<int> v;

  AfterDecimal n( _e, _n);
  

  return v;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<int> v = digital_expansion( 2, 100);
  

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
