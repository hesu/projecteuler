/*
  Problem 78 - Coin partitions
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

#define MAX 1000000

int waysfor( int n, int maxd)
{
  if( maxd <= 0) return 0;
  if( n == 0) return 1;
  if( n < 0) return 0;
  return waysfor(n, maxd-1) + waysfor( n-maxd, maxd);
}

int coin_partition()
{
  // TODO
  return 0;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  cout << "waysfor(4, 2) = " << waysfor( 4, 2) << endl;
  cout << "waysfor(3, 2) = " << waysfor( 3, 2) << endl;
  
  cout << "waysfor(4, 1) = " << waysfor( 4, 1) << endl;
  cout << "waysfor(3, 1) = " << waysfor( 3, 1) << endl;
  cout << "waysfor(2, 1) = " << waysfor( 2, 1) << endl;
  

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
