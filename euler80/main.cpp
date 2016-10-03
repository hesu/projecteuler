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

std::vector<int> digital_expansion( int num, int max)
{
  std::vector<int> v;
 

  std::vector<int> input;
  input.push_back(num);
  for(int i=0;i<MAX;i++) input.push_back(0);
  
  BigInt n(input);

  // Get First Integer!
  int fi;
  for(fi=0; fi<num; fi++) if( pow(fi+1, 2) > num) break;

  std::vector<int> comp_vector;
  for(int i=0; i<MAX/2; i++) comp_vector.push_back(0);
  comp_vector.push_back( fi);

  BigInt comp( comp_vector);

//  cout << "n length=" << n.getDigitsLen() << " comp len=" << comp.getDigitsLen() << endl;

  return v;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<int> v = digital_expansion( 2, 100);
  

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
