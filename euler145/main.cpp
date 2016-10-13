/*
  Problem 145 - How many reversible numbers are there below one-billion?
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

#include "BigInt.h"

using namespace std;

#define MAX 1000000000
//#define MAX 1000

bool consistOnlyOddDigits( vector<int> v)
{
  for(int i=0; i<v.size(); i++)
  {
    if( v[i] % 2 == 0) { return false; }
  }
  return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 0;
  for(unsigned long long int i=1;i<MAX;i++)
  {
    if( i % 100000 == 0) cout << "i=" << i << endl;
    if( i%10 == 0) continue;
    BigInt n(i);
    std::vector<int> ndg = n.getDigits();
    std::vector<int> rev_dg( ndg);
    reverse(rev_dg.begin(), rev_dg.end());
    BigInt rev(rev_dg);

    BigInt added = n + rev;

//    cout << "n=" << n.toString() << " rev=" << rev.toString() << " added=" << added.toString() << endl;
    if( consistOnlyOddDigits( added.getDigits())) { sol++; }
  }

  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
