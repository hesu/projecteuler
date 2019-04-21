/*
  Problem 104 - Pandigital Fibonacci ends
*/

#include <iostream>
#include <ctime>
#include <vector>

#include "BigInt.h"

using namespace std;


bool isPandigitalFiv( BigInt& f)
{
  std::vector<int> dg = f.getDigits();

  if (dg.size() < 18) return false;

  bool head_pandigit[9] = {0,};
  for(int i=0; i<9; i++)
  {
    head_pandigit[ dg[i]-1] = true;
  }

  for(int i=0; i<9; i++) { 
    if (head_pandigit[i] == false) {
      return false;
    }
  }

  bool tail_pandigit[9] = {0,};
  for(int i=dg.size()-9; i<dg.size(); i++)
  {
    tail_pandigit[ dg[i]-1] = true;
  }
  
  for(int i=0; i<9; i++) { 
    if (tail_pandigit[i] == false) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 4;
  BigInt fibn_before(2);
  BigInt fibn(3);

  while( true){
    if( sol % 10000 == 0) { cout << "On Fib " << sol << endl; }
    sol++;
    BigInt fibn_after = fibn_before + fibn;

    if (isPandigitalFiv( fibn_after)) { break; }
    else {
      fibn_before = fibn;
      fibn = fibn_after; 
    }
  }
  

  cout << "sol=" << sol << endl;
  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
