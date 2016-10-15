/*
  Problem 104 - Pandigital Fibonacci ends
*/

#include <iostream>
#include <ctime>
#include <vector>

#include "BigInt.h"

using namespace std;

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 1;
  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
