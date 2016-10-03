/*
  Problem 80 - Square root digital expansion
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

#include "BigInt.h"

using namespace std;

#define MAX 100

int digital_expansion( int num, int max)
{
  std::vector<int> input;
  for(int i=0;i<MAX*2;i++) input.push_back(0);

  input.push_back( num%10);
  if( num/10 > 0) {
    input.push_back(num/10);
  }

  BigInt n(input);

  // Get First Integer!
  int fi;
  for(fi=0; fi<num; fi++) if( pow(fi+1, 2) > num) break;

  std::vector<int> comp_vector;
  for(int i=0; i<MAX; i++) comp_vector.push_back(0);
  comp_vector.push_back( fi);

  BigInt comp( comp_vector);

  for( int i=MAX-1; i>=0; i--) {
     for(int j=0; j<9; j++) {
      comp.setIdxVal( i, j+1);
      BigInt comp2( comp);
      BigInt powered = comp * comp2;
      /*
      cout << "try comp : " << comp.toString() << endl;
      cout << "comp2    : " << comp2.toString() << endl;
      cout << "powered  : " << powered.toString() << endl;
      cout << "n        : " << n.toString() << endl;
      */

      if( n < powered) {
        //cout << "set comp idx " << i << " at val " << j << endl;
        comp.setIdxVal( i, j);
        break;
      }
     }
  }

  cout << "done? i=" << num << " comp=" << comp.toString() << " comp.length=" << comp.getDigitsLen() << endl;

  std::vector<int> v = comp.getDigits();
  int sum = 0;
  for(int i=1; i<v.size(); i++) {sum += v[i]; }
  return sum;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<int> rational;
  for(int i=1; i<=10; i++)
  {
    int sq = pow(i,2);
    if( sq <= MAX) { rational.push_back( sq); }
  }

  cout << "rational.size()=" << rational.size() << endl;

  std::vector<int> irrational;
  for(int i=1; i<=MAX; i++)
  {
    if( std::find(rational.begin(), rational.end(), i) == rational.end()) {
      irrational.push_back( i);
    }
  }

  cout << "irrational.size()=" << irrational.size() << endl;

  int sum = 0;
  for(int i=0; i<irrational.size(); i++) {
    sum += digital_expansion( irrational[i], MAX);
  }
  cout << "sum = " << sum << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
